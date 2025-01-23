# C++ 存储相关
> reference:  
> https://en.cppreference.com/w/cpp/language/storage_duration#Storage_duration  
> https://en.cppreference.com/w/cpp/memory  
> https://en.cppreference.com/w/cpp/language/memory_model  
> https://www.cnblogs.com/sparkdev/p/8410350.html


- [C++ 存储相关](#c-存储相关)
  - [C++ 内存分布](#c-内存分布)
  - [storage duration](#storage-duration)
    - [static storage duration](#static-storage-duration)
    - [thread storage duration(since C++11)](#thread-storage-durationsince-c11)
    - [automatic storage duration](#automatic-storage-duration)
    - [dynamic storage duration](#dynamic-storage-duration)
  - [storage class specifiers](#storage-class-specifiers)
    - [auto (until c++11)](#auto-until-c11)
    - [register (until c++17)](#register-until-c17)
    - [static](#static)
    - [thread\_local (since c++11)](#thread_local-since-c11)
    - [extern](#extern)
    - [mutable](#mutable)
---

## C++ 内存分布
<img src='/c++/img/c++storage.jpg'>

## storage duration
- static storage duration
- thread storage duration(since C++11)
- automatic storage duration
- dynamic storage duration

### static storage duration
A variable satisfying all following conditions has static storage duration:

- It belongs to a namespace scope or are first declared with static or extern.
- It does not have thread storage duration.(since C++11)


### thread storage duration(since C++11)
All variables declared with thread_local have thread storage duration.

The storage for these entities lasts for the duration of the thread in which they are created. There is a distinct object or reference per thread, and use of the declared name refers to the entity associated with the current thread.

### automatic storage duration
The following variables have automatic storage duration:

- Variables that belong to a block scope and are not explicitly declared static, thread_local,(since C++11) or extern. The storage for such variables lasts until the block in which they are created exits.
- Variables that belong to a parameter scope (i.e. function parameters). The storage for a function parameter lasts until immediately after its destruction.

### dynamic storage duration
Objects created by the following methods during program execution have dynamic storage duration:

- new expressions. The storage for such objects is allocated by allocation functions and deallocated by deallocation functions.
- Implicitly creation by other means. The storage for such objects overlaps with some existing storage.
- Exception objects. The storage for such objects is allocated and deallocated in an unspecified way.

## storage class specifiers
- auto (until c++11)
- register (until c++17)
- static
- thread_local (since c++11)
- extern
- mutable

### auto (until c++11)
- C++11之后，auto用作自动推倒类型。而不再是表示自动存储变量的关键字
- [auto详细](/c++11/updated_keywords.md#auto)


### register (until c++17)
- 一旦被声明为寄存器变量，则可能存储在寄存器中（加速访问）。编译器不能对其去地址。
- 如果对寄存器变量取地址，会强制存储在内存中。
- C++17以后不再用此关键字

### static
- declarations of namespace members with static storage duration and internal linkage
  - 静态全局变量
  - 静态全局函数
  - 以上都是作用在本文件内
- definitions of block scope variables with static storage duration and initialized once
  - 在函数内定义的静态局部变量，只会初始化一次，保存在数据段。第二次以及以后的函数调用，不会再做初始化
- declarations of class members not bound to specific instances
  - 静态数据成员
    - 只会被初始化一次（一个类有一份，与实例无关）。所有实例共享访问，存储在数据段。
    - 不能在声明类的时候初始化。 `non-const static data member must be initialized out of line` 因为静态数据成员定义的时候需要分配空间。
  - 静态成员函数
    - 静态成员函数可以访问静态数据成员和静态成员函数
    - 非静态成员函数可以访问静态数据成员和静态成员函数
    - 静态成员函数不能访问非静态成员
    - 调用静态成员函数可以用成员访问操作符(.)和(->)为一个类的对象或者指向类对象的指针调用静态成员函数。也可以用类名::静态成员函数名来调用

### thread_local (since c++11)
- thread_local修饰的变量具有线程周期，在线程开始的时候生成，在线程结束的时候销毁

### extern
- [extern详细](/c++11/updated_keywords.md#extern)

### mutable
- [mutable详细](/c++11/updated_keywords.md#mutable)