# 内存相关问题

- [内存相关问题](#内存相关问题)
  - [内存泄漏](#内存泄漏)
    - [**一、内存泄漏常见原因**](#一内存泄漏常见原因)
    - [**二、检测工具与实战步骤**](#二检测工具与实战步骤)
      - [**1. 使用 `pprof` 分析内存**](#1-使用-pprof-分析内存)
      - [**2. 使用 `runtime` 包监控**](#2-使用-runtime-包监控)
      - [**3. 使用 `trace` 分析 Goroutine 泄漏**](#3-使用-trace-分析-goroutine-泄漏)
    - [**三、常见泄漏场景与修复**](#三常见泄漏场景与修复)
      - [**场景 1：Goroutine 阻塞导致泄漏**](#场景-1goroutine-阻塞导致泄漏)
      - [**场景 2：全局缓存未清理**](#场景-2全局缓存未清理)
      - [**场景 3：Slice 底层数组残留**](#场景-3slice-底层数组残留)
    - [**四、最佳实践**](#四最佳实践)

---

## 内存泄漏
以下是 Go 语言中内存泄漏的常见检测方法和工具，结合场景与代码示例：

### **一、内存泄漏常见原因**
1. **Goroutine 泄漏**  
   - Goroutine 未正常退出（如未关闭的 Channel 导致阻塞）。
2. **全局变量/缓存**  
   - 全局 Map 或缓存未清理，持续增长。
3. **未释放资源**  
   - 文件句柄、网络连接未关闭。
4. **Slice/Map 底层数组引用**  
   - 大 Slice 截取小 Slice 后，底层数组仍被引用。


### **二、检测工具与实战步骤**

#### **1. 使用 `pprof` 分析内存**
   - **步骤**：  
     1. 导入 `net/http/pprof` 包并启动 HTTP 服务：  
        ```go
        import _ "net/http/pprof"
        go func() { http.ListenAndServe(":6060", nil) }()
        ```
     2. 访问 `http://localhost:6060/debug/pprof/heap?debug=1` 查看实时堆内存。  
     3. 生成内存分析文件：  
        ```bash
        go tool pprof -http=:8080 http://localhost:6060/debug/pprof/heap
        ```

   - **关键指标**：  
     - `inuse_objects`：当前存活对象数。  
     - `inuse_space`：当前内存占用。  
     - 查看 `top` 命令输出，定位内存占用高的函数。

#### **2. 使用 `runtime` 包监控**
   ```go
   import "runtime"

   // 打印内存统计
   func printMemStats() {
       var m runtime.MemStats
       runtime.ReadMemStats(&m)
       fmt.Printf("Alloc = %v MiB\n", m.Alloc/1024/1024)
       fmt.Printf("TotalAlloc = %v MiB\n", m.TotalAlloc/1024/1024)
   }
   ```
   - **TotalAlloc**：累计分配内存（持续增长可能表示泄漏）。

#### **3. 使用 `trace` 分析 Goroutine 泄漏**
   ```go
   import (
       "os"
       "runtime/trace"
   )

   func main() {
       f, _ := os.Create("trace.out")
       trace.Start(f)
       defer trace.Stop()
       // ... 业务代码 ...
   }
   ```
   - 分析命令：  
     ```bash
     go tool trace trace.out
     ```
   - 查看 Goroutine 数量是否持续增长。


### **三、常见泄漏场景与修复**

#### **场景 1：Goroutine 阻塞导致泄漏**
   ```go
   func leak() {
       ch := make(chan int)
       go func() {
           val := <-ch  // Goroutine 永久阻塞（无数据写入）
           fmt.Println(val)
       }()
   }
   ```
   **修复**：  
   - 确保 Channel 有发送/关闭逻辑。  
   - 使用 `context` 设置超时：  
     ```go
     ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
     defer cancel()
     select {
     case <-ch:
         // 正常处理
     case <-ctx.Done():
         // 超时退出
     }
     ```

#### **场景 2：全局缓存未清理**
   ```go
   var cache = make(map[string][]byte)

   func addToCache(key string, data []byte) {
       cache[key] = data  // 数据长期驻留内存
   }
   ```
   **修复**：  
   - 使用 LRU 缓存策略或定期清理。  
   - 使用弱引用（如 `sync.Map` 或第三方库）。

#### **场景 3：Slice 底层数组残留**
   ```go
   func processLargeData() {
       data := make([]byte, 100*1024*1024) // 100MB
       small := data[:10]  // 小 Slice 引用底层大数组
       // data 不再使用，但 small 仍持有引用，GC 无法回收
   }
   ```
   **修复**：  
   - 使用 `copy` 创建独立数据副本：  
     ```go
     small := make([]byte, 10)
     copy(small, data[:10])
     ```


### **四、最佳实践**
1. **代码规范**  
   - 使用 `defer` 确保资源释放（如文件、锁、连接）。  
   - 避免在全局变量中存储大量数据。  
2. **工具链集成**  
   - 在 CI/CD 中集成内存分析（如自动化 `pprof` 测试）。  
3. **监控告警**  
   - 通过 Prometheus + Grafana 监控应用内存指标。

