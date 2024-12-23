# C++11 其他关键特性
> reference: https://en.cppreference.com/w/cpp/11
- [C++11 其他关键特性](#c11-其他关键特性)
    - [rvalue references](#rvalue-references)
    - [smart pointer](#smart-pointer)
      - [std::unique\_ptr](#stdunique_ptr)
      - [std::shared\_ptr](#stdshared_ptr)
      - [std::weak\_ptr](#stdweak_ptr)
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