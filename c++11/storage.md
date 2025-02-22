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
  - [内存泄漏](#内存泄漏)
    - [**一、内存泄漏的常见原因**](#一内存泄漏的常见原因)
    - [**二、检测内存泄漏的工具**](#二检测内存泄漏的工具)
      - [1. **Valgrind（Linux/Mac）**](#1-valgrindlinuxmac)
      - [2. **AddressSanitizer（ASan，Clang/GCC）**](#2-addresssanitizerasanclanggcc)
      - [3. **Visual Studio 内存诊断工具（Windows）**](#3-visual-studio-内存诊断工具windows)
    - [**三、预防内存泄漏的最佳实践**](#三预防内存泄漏的最佳实践)
      - [1. **优先使用智能指针（C++11+）**](#1-优先使用智能指针c11)
      - [2. **遵循 RAII 原则**](#2-遵循-raii-原则)
      - [3. **避免裸指针（Raw Pointer）**](#3-避免裸指针raw-pointer)
      - [4. **异常安全设计**](#4-异常安全设计)
    - [**四、典型场景与修复示例**](#四典型场景与修复示例)
      - [场景 1：容器存储指针未释放](#场景-1容器存储指针未释放)
      - [场景 2：异常导致内存泄漏](#场景-2异常导致内存泄漏)
    - [**五、总结**](#五总结)
---

## C++ 内存分布
<img src='/c++11/img/c++storage.jpg'>

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

## 内存泄漏
在 C++ 中，**内存泄漏（Memory Leak）** 是指程序在动态分配内存后，未能正确释放该内存，导致这部分内存无法被后续程序使用。长期运行的程序（如服务器）若存在内存泄漏，可能引发内存耗尽、程序崩溃等问题。以下是内存泄漏的详细解析与解决方案：


### **一、内存泄漏的常见原因**
1. **忘记释放内存**  
   - 使用 `new` 或 `malloc` 分配内存后，未调用 `delete` 或 `free`。  
     ```cpp
     void leak() {
         int* ptr = new int[100]; // 分配后未释放
     }
     ```

2. **异常导致释放逻辑未执行**  
   - 在 `new` 和 `delete` 之间发生异常，导致释放代码被跳过。  
     ```cpp
     void risky() {
         int* ptr = new int[100];
         throw std::runtime_error("Oops");
         delete[] ptr; // 异常抛出后，此代码不会执行
     }
     ```

3. **指针覆盖**  
   - 指针被重新赋值，导致原内存地址丢失。  
     ```cpp
     void overwrite() {
         int* ptr = new int(10);
         ptr = new int(20); // 原内存无法释放
         delete ptr;         // 仅释放第二个内存块
     }
     ```

4. **容器中的指针未清理**  
   - 容器存储指针，但析构时未释放其指向的内存。  
     ```cpp
     std::vector<int*> vec;
     vec.push_back(new int(5));
     // vec 析构时，其元素（指针）不会被自动删除
     ```


### **二、检测内存泄漏的工具**
#### 1. **Valgrind（Linux/Mac）**  
   - 功能强大的内存检测工具，可检测泄漏、越界访问等问题。  
   - 使用步骤：  
     ```bash
     valgrind --leak-check=full ./your_program
     ```
   - 输出示例：  
     ```
     ==12345== 100 bytes in 1 blocks are definitely lost in loss record 1 of 1
     ==12345==    at 0x4C2E0BE: operator new[](unsigned long) (vg_replace_malloc.c:433)
     ==12345==    by 0x400567: leak() (main.cpp:5)
     ```

#### 2. **AddressSanitizer（ASan，Clang/GCC）**  
   - 编译时插入检测代码，适用于 Linux、macOS 和 Windows（部分支持）。  
   - 使用方式：  
     ```bash
     g++ -fsanitize=address -g main.cpp -o main
     ./main
     ```
   - 输出示例：  
     ```
     ==12345==ERROR: LeakSanitizer: detected memory leaks
     Direct leak of 100 byte(s) in 1 object(s) allocated from:
         #0 0x55a1d2b3c7d9 in operator new[](unsigned long)
         #1 0x55a1d2b3c8b6 in leak() main.cpp:5
     ```

#### 3. **Visual Studio 内存诊断工具（Windows）**  
   - 内置内存泄漏检测功能，适用于调试模式。  
   - 步骤：  
     1. 在代码开头添加 `#define _CRTDBG_MAP_ALLOC` 和 `#include <crtdbg.h>`。  
     2. 在程序退出前调用 `_CrtDumpMemoryLeaks()`。  
     ```cpp
     #define _CRTDBG_MAP_ALLOC
     #include <crtdbg.h>

     int main() {
         int* ptr = new int(10);
         _CrtDumpMemoryLeaks(); // 输出泄漏信息
         return 0;
     }
     ```


### **三、预防内存泄漏的最佳实践**
#### 1. **优先使用智能指针（C++11+）**  
   - **`std::unique_ptr`**：独占所有权，自动释放内存。  
     ```cpp
     void safe_unique() {
         auto ptr = std::make_unique<int>(10);
         // 无需手动 delete，退出作用域时自动释放
     }
     ```
   - **`std::shared_ptr`**：共享所有权（引用计数）。  
     ```cpp
     void safe_shared() {
         auto ptr = std::make_shared<int>(10);
         auto ptr2 = ptr; // 引用计数 +1
     } // 引用计数归零时自动释放
     ```

#### 2. **遵循 RAII 原则**  
   - 资源获取即初始化（Resource Acquisition Is Initialization），将资源绑定到对象生命周期。  
   - 示例：封装文件句柄的类。  
     ```cpp
     class FileHandler {
     public:
         FileHandler(const std::string& path) : file(fopen(path.c_str(), "r")) {}
         ~FileHandler() { if (file) fclose(file); }
     private:
         FILE* file;
     };
     ```

#### 3. **避免裸指针（Raw Pointer）**  
   - 尽量使用容器（如 `std::vector`、`std::string`）代替动态数组。  
     ```cpp
     void no_raw_pointer() {
         std::vector<int> vec(100); // 无需手动管理内存
     }
     ```

#### 4. **异常安全设计**  
   - 使用智能指针或 `try-catch` 确保异常发生时资源被释放。  
     ```cpp
     void exception_safe() {
         auto ptr = std::make_unique<int[]>(100);
         throw std::runtime_error("Safe with smart pointers");
         // 即使抛出异常，ptr 也会自动释放内存
     }
     ```


### **四、典型场景与修复示例**
#### 场景 1：容器存储指针未释放  
**问题代码**：  
```cpp
std::vector<int*> vec;
vec.push_back(new int(5));
// vec 析构时，内部指针不会被删除
```

**修复方法**：  
- 使用 `std::unique_ptr` 或手动遍历释放。  
  ```cpp
  std::vector<std::unique_ptr<int>> vec;
  vec.push_back(std::make_unique<int>(5));
  // 自动释放

  // 或手动释放：
  for (auto ptr : vec) delete ptr;
  vec.clear();
  ```

#### 场景 2：异常导致内存泄漏  
**问题代码**：  
```cpp
void risky() {
    int* ptr = new int(10);
    some_operation(); // 可能抛出异常
    delete ptr;
}
```

**修复方法**：  
- 使用智能指针：  
  ```cpp
  void safe() {
      auto ptr = std::make_unique<int>(10);
      some_operation(); // 即使抛出异常，ptr 也会自动释放
  }
  ```


### **五、总结**
| 方法                | 优点                          | 缺点                  |
|---------------------|-------------------------------|-----------------------|
| 智能指针            | 自动管理生命周期，代码简洁    | 需要 C++11+ 支持      |
| RAII 封装           | 灵活，适用于自定义资源        | 需要额外编码          |
| 工具检测（Valgrind）| 全面检测内存问题              | 运行时性能开销较大    |

**核心原则**：  
- **谁分配，谁释放**：确保每个 `new` 对应一个 `delete`。  
- **优先使用现代 C++ 特性**：智能指针和容器。  
- **结合工具检测**：在开发和测试阶段使用 Valgrind 或 ASan 提前发现问题。