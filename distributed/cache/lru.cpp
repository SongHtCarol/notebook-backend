/*
1. 缓存结构： unordered_map 存储数据，实现O(1)的查找效率
2. LRU淘汰：链表记录节点访问顺序，访问（get/put）的时候，将节点放在表头；数据总数超出限制，删除末尾的节点
3. TTL过期：数据节点记录缓存插入的时间
4. 并发安全：mutex 或者 share_mutex 保护共享资源
*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <mutex>
#include <chrono>
#include <thread>
#include <memory>

class LRUCache
{
public:
    using KeyType = std::string;
    using ValueType = std::string;
    using TimePoint = std::chrono::steady_clock::time_point;

    struct CacheItem
    {
        ValueType value;
        TimePoint timestamp;
    };

    LRUCache(size_t capacity, size_t ttlSeconds)
        : capacity_(capacity), ttlSeconds_(ttlSeconds) {}

    // 获取缓存值
    std::optional<ValueType> get(const KeyType &key)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        auto it = cacheMap_.find(key);
        if (it == cacheMap_.end())
        {
            return std::nullopt; // 未找到
        }

        // 检查是否过期
        if (isExpired(it->second.timestamp))
        {
            cacheList_.erase(it->second.listIt);
            cacheMap_.erase(it);
            return std::nullopt; // 已过期
        }

        // 更新访问时间并移动到链表头部
        cacheList_.splice(cacheList_.begin(), cacheList_, it->second.listIt);
        return it->second.value;
    }

    // 插入或更新缓存值
    void put(const KeyType &key, const ValueType &value)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        auto it = cacheMap_.find(key);

        // 如果键已存在，更新值并移动到链表头部
        if (it != cacheMap_.end())
        {
            it->second.value = value;
            it->second.timestamp = getCurrentTime();
            cacheList_.splice(cacheList_.begin(), cacheList_, it->second.listIt);
            return;
        }

        // 如果缓存已满，淘汰最久未使用的项
        if (cacheMap_.size() >= capacity_)
        {
            auto last = cacheList_.back();
            cacheMap_.erase(last);
            cacheList_.pop_back();
        }

        // 插入新项
        cacheList_.push_front(key);
        cacheMap_[key] = {value, getCurrentTime(), cacheList_.begin()};
    }

    // 删除缓存项
    void remove(const KeyType &key)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        auto it = cacheMap_.find(key);
        if (it != cacheMap_.end())
        {
            cacheList_.erase(it->second.listIt);
            cacheMap_.erase(it);
        }
    }

    // 清空缓存
    void clear()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cacheMap_.clear();
        cacheList_.clear();
    }

private:
    // 检查是否过期
    bool isExpired(const TimePoint &timestamp) const
    {
        auto now = getCurrentTime();
        return std::chrono::duration_cast<std::chrono::seconds>(now - timestamp).count() >= ttlSeconds_;
    }

    // 获取当前时间
    TimePoint getCurrentTime() const
    {
        return std::chrono::steady_clock::now();
    }

    size_t capacity_;   // 缓存容量
    size_t ttlSeconds_; // TTL 过期时间（秒）
    std::mutex mutex_;  // 互斥锁

    // 缓存数据结构
    std::list<KeyType> cacheList_; // LRU 链表
    std::unordered_map<KeyType, std::pair<CacheItem, typename std::list<KeyType>::iterator>> cacheMap_;
};

int main()
{
    LRUCache cache(2, 5); // 容量为 2，TTL 为 5 秒

    cache.put("key1", "value1");
    cache.put("key2", "value2");

    if (auto value = cache.get("key1"))
    {
        std::cout << "key1: " << *value << std::endl;
    }
    else
    {
        std::cout << "key1 not found or expired" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(6)); // 等待 6 秒

    if (auto value = cache.get("key1"))
    {
        std::cout << "key1: " << *value << std::endl;
    }
    else
    {
        std::cout << "key1 not found or expired" << std::endl;
    }

    return 0;
}