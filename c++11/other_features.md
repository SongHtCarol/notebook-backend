# C++11 其他关键特性
> reference: https://en.cppreference.com/w/cpp/11
- [C++11 其他关键特性](#c11-其他关键特性)
    - [rvalue references](#rvalue-references)
    - [smart pointer](#smart-pointer)
      - [std::unique\_ptr](#stdunique_ptr)
      - [std::shared\_ptr](#stdshared_ptr)
      - [std::weak\_ptr](#stdweak_ptr)
    - [shared\_ptr的unique函数和count计数](#shared_ptr的unique函数和count计数)
      - [1. `unique()` 函数](#1-unique-函数)
        - [示例代码：](#示例代码)
        - [输出：](#输出)
      - [2. `use_count()` 函数](#2-use_count-函数)
        - [示例代码：](#示例代码-1)
        - [输出：](#输出-1)
      - [注意事项](#注意事项)
      - [总结](#总结)
---

### rvalue references
右值引用
<img src='/c++11/img/左值引用&右值引用.png'>

### smart pointer
RAII 思想
https://learn.microsoft.com/zh-cn/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170

#### std::unique_ptr
https://learn.microsoft.com/zh-cn/cpp/cpp/how-to-create-and-use-unique-ptr-instances?view=msvc-170
> std::unique_ptr is a smart pointer that owns (is responsible for) and manages another object via a pointer and subsequently disposes of that object when the unique_ptr goes out of scope.

```C++
// Defined in header <memory>
template<
    class T,
    class Deleter = std::default_delete<T> > class unique_ptr;

template <
    class T,
    class Deleter> class unique_ptr<T[], Deleter>;
```

- `unique_ptr`只有一个所有者，不共享指针。只能通过`std::move`转移指针所有权，同时原始指针不再拥有对应资源

#### std::shared_ptr
> std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer. Several shared_ptr objects may own the same object. The object is destroyed and its memory deallocated when either of the following happens:

> the last remaining shared_ptr owning the object is destroyed;
> the last remaining shared_ptr owning the object is assigned another pointer via operator= or reset().


```C++
// Defined in header <memory>
template< class T > class shared_ptr;
```

- `shared_ptr`可以有多个所有者，可以通过复制共享指针。所有实例均指向同一个对象，并共享对一个“控制块”的访问权限。 当引用计数达到零时，控制块将删除内存资源和自身。

#### std::weak_ptr
> std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to an object that is managed by std::shared_ptr. It must be converted to std::shared_ptr in order to access the referenced object.

> std::weak_ptr models temporary ownership: when an object needs to be accessed only if it exists, and it may be deleted at any time by someone else, std::weak_ptr is used to track the object, and it is converted to std::shared_ptr to acquire temporary ownership. If the original std::shared_ptr is destroyed at this time, the object's lifetime is extended until the temporary std::shared_ptr is destroyed as well.

> Another use for std::weak_ptr is to break reference cycles formed by objects managed by std::shared_ptr. If such cycle is orphaned (i.e., there are no outside shared pointers into the cycle), the shared_ptr reference counts cannot reach zero and the memory is leaked. To prevent this, one of the pointers in the cycle can be made weak.

```C++
// Defined in header <memory>
template< class T > class weak_ptr;
```

- `weak_ptr`可以为一个或多个所有者提供对另一个`shared_ptr`所有者的弱引用。拥有对`shared_ptr`指向资源的访问权，但不参与计数。

### shared_ptr的unique函数和count计数
`std::shared_ptr` 是 C++ 标准库中的智能指针，用于管理动态分配的对象。它通过引用计数机制来自动管理对象的生命周期。`std::shared_ptr` 提供了两个与引用计数相关的函数：`unique()` 和 `use_count()`。

#### 1. `unique()` 函数
`unique()` 函数用于检查当前 `std::shared_ptr` 是否是唯一拥有该对象的所有者。如果引用计数为 1，则返回 `true`，否则返回 `false`。

##### 示例代码：
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::shared_ptr<int> ptr2 = ptr1;

    std::cout << "ptr1 is unique: " << std::boolalpha << ptr1.unique() << std::endl; // 输出 false
    std::cout << "ptr2 is unique: " << std::boolalpha << ptr2.unique() << std::endl; // 输出 false

    ptr2.reset(); // 释放 ptr2 的所有权

    std::cout << "ptr1 is unique: " << std::boolalpha << ptr1.unique() << std::endl; // 输出 true

    return 0;
}
```

##### 输出：
```
ptr1 is unique: false
ptr2 is unique: false
ptr1 is unique: true
```

#### 2. `use_count()` 函数
`use_count()` 函数返回当前 `std::shared_ptr` 所管理对象的引用计数。引用计数表示有多少个 `std::shared_ptr` 共享同一个对象。

##### 示例代码：
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::shared_ptr<int> ptr2 = ptr1;

    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl; // 输出 2
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl; // 输出 2

    ptr2.reset(); // 释放 ptr2 的所有权

    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl; // 输出 1

    return 0;
}
```

##### 输出：
```
ptr1 use_count: 2
ptr2 use_count: 2
ptr1 use_count: 1
```

#### 注意事项
1. **`unique()` 的替代**：在 C++17 中，`unique()` 函数被标记为弃用（deprecated），因为它的行为可以通过 `use_count() == 1` 来判断。建议使用 `use_count()` 来替代 `unique()`。
2. **性能考虑**：`use_count()` 的调用可能会有一定的性能开销，因为它需要访问引用计数。因此，在性能敏感的代码中应谨慎使用。

#### 总结
- `unique()` 用于检查当前 `std::shared_ptr` 是否是唯一的所有者（引用计数为 1）。
- `use_count()` 返回当前 `std::shared_ptr` 所管理对象的引用计数。
- 在 C++17 及更高版本中，建议使用 `use_count() == 1` 来替代 `unique()`。