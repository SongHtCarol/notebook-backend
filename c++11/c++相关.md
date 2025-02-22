# C++ 相关

- [C++ 相关](#c-相关)
  - [指针](#指针)
    - [指针和引用](#指针和引用)
    - [迭代器和指针](#迭代器和指针)
      - [一、定义](#一定义)
        - [1. 指针](#1-指针)
        - [2. 迭代器](#2-迭代器)
      - [二、核心区别](#二核心区别)
      - [三、详细对比](#三详细对比)
        - [1. 访问方式](#1-访问方式)
        - [2. 遍历操作](#2-遍历操作)
        - [3. 安全性](#3-安全性)
        - [4. 泛型编程](#4-泛型编程)
      - [四、迭代器的分类](#四迭代器的分类)
      - [五、总结](#五总结)
  - [栈指针 和 指针](#栈指针-和-指针)
    - [**一、定义**](#一定义-1)
      - [1. **指针**](#1-指针-1)
      - [2. **栈指针**](#2-栈指针)
    - [**二、核心区别**](#二核心区别-1)
    - [**三、详细对比**](#三详细对比-1)
      - [1. **作用**](#1-作用)
      - [2. **存储位置**](#2-存储位置)
      - [3. **使用场景**](#3-使用场景)
      - [4. **生命周期**](#4-生命周期)
      - [5. **抽象层次**](#5-抽象层次)
    - [**四、示例**](#四示例)
      - [1. **指针示例**](#1-指针示例)
      - [2. **栈指针示例**](#2-栈指针示例)
    - [**五、总结**](#五总结-1)
  - [堆和栈](#堆和栈)
    - [一、堆和栈的定义](#一堆和栈的定义)
      - [1. **栈（Stack）**](#1-栈stack)
      - [2. **堆（Heap）**](#2-堆heap)
    - [二、核心区别](#二核心区别-2)
    - [三、详细对比](#三详细对比-2)
      - [1. **内存管理**](#1-内存管理)
      - [2. **生命周期**](#2-生命周期)
      - [3. **分配速度**](#3-分配速度)
      - [4. **访问方式**](#4-访问方式)
      - [5. **碎片问题**](#5-碎片问题)
      - [6. **适用场景**](#6-适用场景)
    - [四、示例对比](#四示例对比)
      - [1. **栈示例**](#1-栈示例)
      - [2. **堆示例**](#2-堆示例)
    - [五、常见问题](#五常见问题)
      - [1. **栈溢出（Stack Overflow）**](#1-栈溢出stack-overflow)
      - [2. **内存泄漏（Memory Leak）**](#2-内存泄漏memory-leak)
      - [3. **内存碎片（Memory Fragmentation）**](#3-内存碎片memory-fragmentation)
    - [六、总结](#六总结)
  - [为什么栈向下增长](#为什么栈向下增长)
    - [1. **内存布局**](#1-内存布局)
    - [2. **栈向下增长的原因**](#2-栈向下增长的原因)
      - [（1）**历史原因**](#1历史原因)
      - [（2）**与堆的互补**](#2与堆的互补)
      - [（3）**简化内存管理**](#3简化内存管理)
      - [（4）**硬件支持**](#4硬件支持)
    - [3. **栈向下增长的实现**](#3-栈向下增长的实现)
      - [示例：](#示例)
    - [4. **栈向下增长的优点**](#4-栈向下增长的优点)
      - [（1）**高效的内存利用**](#1高效的内存利用)
      - [（2）**简单的指针管理**](#2简单的指针管理)
      - [（3）**硬件优化**](#3硬件优化)
    - [5. **栈向下增长的缺点**](#5-栈向下增长的缺点)
    - [6. **总结**](#6-总结)
  - [mutex vs shared\_mutex](#mutex-vs-shared_mutex)
    - [**一、基本概念**](#一基本概念)
      - [1. **`mutex`（互斥锁）**](#1-mutex互斥锁)
      - [2. **`shared_mutex`（共享互斥锁）**](#2-shared_mutex共享互斥锁)
    - [**二、核心区别**](#二核心区别-3)
    - [**三、详细对比**](#三详细对比-3)
      - [1. **锁模式**](#1-锁模式)
      - [2. **适用场景**](#2-适用场景)
      - [3. **性能**](#3-性能)
      - [4. **C++ 标准**](#4-c-标准)
    - [**四、示例代码**](#四示例代码)
      - [1. **`mutex` 示例**](#1-mutex-示例)
      - [2. **`shared_mutex` 示例**](#2-shared_mutex-示例)
    - [**五、总结**](#五总结-2)
  - [vector](#vector)
    - [1. **头文件与声明**](#1-头文件与声明)
    - [2. **核心操作**](#2-核心操作)
    - [3. **遍历方式**](#3-遍历方式)
    - [4. **性能特点**](#4-性能特点)
    - [5. **适用场景**](#5-适用场景)
    - [6. **示例代码**](#6-示例代码)
    - [7. **最佳实践**](#7-最佳实践)
    - [8. **与其他容器的对比**](#8-与其他容器的对比)
  - [vector vs array](#vector-vs-array)
    - [**一、基本概念**](#一基本概念-1)
      - [1. **`std::vector`**](#1-stdvector)
      - [2. **`std::array`**](#2-stdarray)
    - [**二、核心区别**](#二核心区别-4)
    - [**三、详细对比**](#三详细对比-4)
      - [1. **大小**](#1-大小)
      - [2. **内存管理**](#2-内存管理)
      - [3. **性能**](#3-性能-1)
      - [4. **适用场景**](#4-适用场景)
      - [5. **C++ 标准**](#5-c-标准)
    - [**四、示例代码**](#四示例代码-1)
      - [1. **`std::vector` 示例**](#1-stdvector-示例)
      - [2. **`std::array` 示例**](#2-stdarray-示例)
    - [**五、总结**](#五总结-3)
  - [string](#string)
    - [**一、基本特性**](#一基本特性)
    - [**二、常用操作**](#二常用操作)
      - [1. **构造和初始化**](#1-构造和初始化)
      - [2. **访问元素**](#2-访问元素)
      - [3. **修改字符串**](#3-修改字符串)
      - [4. **查找和替换**](#4-查找和替换)
      - [5. **大小和容量**](#5-大小和容量)
      - [6. **比较字符串**](#6-比较字符串)
      - [7. **转换**](#7-转换)
    - [**三、示例代码**](#三示例代码)
    - [**四、性能优化**](#四性能优化)
    - [**五、总结**](#五总结-4)
  - [sizeof](#sizeof)
    - [1. `sizeof` 的基本用法](#1-sizeof-的基本用法)
      - [示例：](#示例-1)
      - [输出：](#输出)
    - [2. `sizeof` 与 C++11 新特性](#2-sizeof-与-c11-新特性)
      - [（1）`sizeof` 与 `decltype`](#1sizeof-与-decltype)
        - [示例：](#示例-2)
        - [输出：](#输出-1)
      - [（2）`sizeof` 与 `alignof`](#2sizeof-与-alignof)
        - [示例：](#示例-3)
        - [输出：](#输出-2)
    - [3. `sizeof` 的特殊用法](#3-sizeof-的特殊用法)
      - [（1）计算数组的大小](#1计算数组的大小)
        - [示例：](#示例-4)
        - [输出：](#输出-3)
      - [（2）计算结构体的大小](#2计算结构体的大小)
        - [示例：](#示例-5)
        - [输出：](#输出-4)
    - [4. `sizeof` 的注意事项](#4-sizeof-的注意事项)
    - [5. 总结](#5-总结)
  - [sizeof（void）](#sizeofvoid)
    - [1. 为什么 `sizeof(void)` 不合法？](#1-为什么-sizeofvoid-不合法)
    - [2. 示例代码](#2-示例代码)
      - [编译器错误：](#编译器错误)
    - [3. `sizeof(void*)` 是合法的](#3-sizeofvoid-是合法的)
      - [示例：](#示例-6)
      - [输出：](#输出-5)
    - [4. 总结](#4-总结)
  - [前置自增](#前置自增)
    - [1. 语法](#1-语法)
    - [2. 行为](#2-行为)
      - [示例：](#示例-7)
    - [3. 与后置自增的区别](#3-与后置自增的区别)
      - [示例对比：](#示例对比)
    - [4. 性能分析](#4-性能分析)
    - [5. 适用场景](#5-适用场景-1)
      - [示例：循环中使用前置自增](#示例循环中使用前置自增)
    - [6. 自定义类型中的前置自增](#6-自定义类型中的前置自增)
      - [示例：](#示例-8)
    - [7. 总结](#7-总结)
  - [单例模式](#单例模式)
    - [**一、经典实现（非线程安全）**](#一经典实现非线程安全)
      - [1. **实现代码**](#1-实现代码)
      - [2. **使用示例**](#2-使用示例)
      - [3. **特点**](#3-特点)
    - [**二、线程安全实现（C++11）**](#二线程安全实现c11)
      - [1. **实现代码**](#1-实现代码-1)
      - [2. **使用示例**](#2-使用示例-1)
      - [3. **特点**](#3-特点-1)
    - [**三、双重检查锁定（Double-Checked Locking）**](#三双重检查锁定double-checked-locking)
      - [1. **实现代码**](#1-实现代码-2)
      - [2. **使用示例**](#2-使用示例-2)
      - [3. **特点**](#3-特点-2)
    - [**四、Meyer's Singleton（推荐）**](#四meyers-singleton推荐)
      - [1. **实现代码**](#1-实现代码-3)
      - [2. **使用示例**](#2-使用示例-3)
      - [3. **特点**](#3-特点-3)
    - [**五、总结**](#五总结-5)
  - [LRU](#lru)
    - [**设计思路**](#设计思路)
    - [**代码实现**](#代码实现)
    - [**代码说明**](#代码说明)
    - [**测试与优化**](#测试与优化)
    - [**总结**](#总结)
  - [检测内存泄漏的工具](#检测内存泄漏的工具)
    - [一、工具分类](#一工具分类)
      - [1. **静态分析工具**](#1-静态分析工具)
      - [2. **动态分析工具**](#2-动态分析工具)
    - [二、常用工具](#二常用工具)
      - [1. **Valgrind**](#1-valgrind)
      - [2. **AddressSanitizer (ASan)**](#2-addresssanitizer-asan)
      - [3. **Dr. Memory**](#3-dr-memory)
      - [4. **Visual Studio 内存分析工具**](#4-visual-studio-内存分析工具)
      - [5. **LeakSanitizer (LSan)**](#5-leaksanitizer-lsan)
      - [6. **Electric Fence**](#6-electric-fence)
      - [7. **Cppcheck**](#7-cppcheck)
    - [三、选择工具的建议](#三选择工具的建议)
    - [四、预防内存泄漏的最佳实践](#四预防内存泄漏的最佳实践)
    - [五、总结](#五总结-6)

---
## 指针
### 指针和引用

- 指针是一个变量，需要申请内存空间，保存所指向变量的地址；
- 引用是变量的别名，不需要额外申请内存空间，与原变量共享内存地址。
- 引用初始化后，就不能改变，永远和原来的变量绑定。
    <img src='/c++11/img/pointer.jpg'>
- 获取指针指向变量的值需要对指针解引用(回内存地址中对应的对象)。 即*
- 引用没有const，指针有const，const指针不可变。
    <img src='/c++11/img/error.jpg'>
    <img src='/c++11/img/pointer1.jpg'>
- 可以声明只读的引用 `const int& m = i`, 只读的引用不能修改原变量的值
    <img src='/c++11/img/error1.jpg'>
- 只读的指针可以改变指向的变量，但是不能修改指向变量的值。
    <img src='/c++11/img/error2.jpg'>

### 迭代器和指针
**迭代器（Iterator）** 和 **指针（Pointer）** 都是用于访问和遍历数据结构的工具，但它们在设计、功能和使用场景上有显著区别。以下是它们的详细对比：


#### 一、定义
##### 1. 指针
- 指针是 C/C++ 中的一种变量，存储内存地址。
- 可以直接访问内存中的数据，支持算术运算（如 `++`、`--`）。

##### 2. 迭代器
- 迭代器是 C++ 标准库中的一种抽象概念，用于遍历容器（如 `std::vector`、`std::list`）。
- 提供统一的接口访问容器元素，隐藏底层实现细节。


#### 二、核心区别
| **特性**               | **指针**                              | **迭代器**                          |
|------------------------|----------------------------------------|-------------------------------------|
| **语言支持**           | C/C++ 原生支持                         | C++ 标准库支持                      |
| **适用范围**           | 数组、动态内存                         | 标准库容器（如 `vector`、`list`）   |
| **抽象层次**           | 低级别，直接操作内存                   | 高级别，封装底层实现                |
| **安全性**             | 容易出错（如空指针、越界访问）         | 更安全（如边界检查）                |
| **功能扩展**           | 仅支持基本操作（如 `++`、`--`）        | 支持丰富操作（如 `begin()`、`end()`）|
| **泛型编程**           | 不支持                                 | 支持（如 STL 算法）                 |


#### 三、详细对比
##### 1. 访问方式
- **指针**：
  - 直接访问内存地址，适用于数组和动态内存。
  - 示例：
    ```cpp
    int arr[] = {1, 2, 3};
    int* p = arr;
    std::cout << *p << std::endl; // 输出 1
    ```

- **迭代器**：
  - 通过容器提供的接口访问元素，适用于标准库容器。
  - 示例：
    ```cpp
    std::vector<int> vec = {1, 2, 3};
    auto it = vec.begin();
    std::cout << *it << std::endl; // 输出 1
    ```

##### 2. 遍历操作
- **指针**：
  - 使用指针算术运算（如 `++`、`--`）遍历数组。
  - 示例：
    ```cpp
    int arr[] = {1, 2, 3};
    for (int* p = arr; p != arr + 3; ++p) {
        std::cout << *p << std::endl;
    }
    ```

- **迭代器**：
  - 使用迭代器的 `++`、`--` 操作遍历容器。
  - 示例：
    ```cpp
    std::vector<int> vec = {1, 2, 3};
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << std::endl;
    }
    ```

##### 3. 安全性
- **指针**：
  - 容易引发空指针、野指针、越界访问等问题。
  - 示例：
    ```cpp
    int* p = nullptr;
    std::cout << *p << std::endl; // 运行时错误
    ```

- **迭代器**：
  - 提供边界检查，更安全。
  - 示例：
    ```cpp
    std::vector<int> vec = {1, 2, 3};
    auto it = vec.end();
    std::cout << *it << std::endl; // 未定义行为，但部分实现会抛出异常
    ```

##### 4. 泛型编程
- **指针**：
  - 不支持泛型编程，无法直接用于标准库算法。
- **迭代器**：
  - 支持泛型编程，可与 STL 算法（如 `std::sort`、`std::find`）结合使用。
  - 示例：
    ```cpp
    std::vector<int> vec = {3, 1, 2};
    std::sort(vec.begin(), vec.end());
    ```


#### 四、迭代器的分类
C++ 标准库中的迭代器分为以下几类：
1. **输入迭代器（Input Iterator）**：
   - 只读，单向遍历（如 `std::istream_iterator`）。
2. **输出迭代器（Output Iterator）**：
   - 只写，单向遍历（如 `std::ostream_iterator`）。
3. **前向迭代器（Forward Iterator）**：
   - 可读写，单向遍历（如 `std::forward_list` 的迭代器）。
4. **双向迭代器（Bidirectional Iterator）**：
   - 可读写，双向遍历（如 `std::list` 的迭代器）。
5. **随机访问迭代器（Random Access Iterator）**：
   - 可读写，支持随机访问（如 `std::vector` 的迭代器）。


#### 五、总结
- **指针**：
  - 低级别，直接操作内存，适合数组和动态内存。
  - 容易出错，不支持泛型编程。
- **迭代器**：
  - 高级别，封装底层实现，适合标准库容器。
  - 更安全，支持泛型编程和丰富操作。

在实际开发中，优先使用迭代器，除非需要直接操作内存或与 C 代码交互。

--- 

## 栈指针 和 指针
**栈指针（Stack Pointer）** 和 **指针（Pointer）** 是两种不同的概念，尽管它们都涉及内存地址，但在作用和使用场景上有显著区别。以下是它们的详细对比：


### **一、定义**
#### 1. **指针**
- 指针是 C/C++ 中的一种变量，存储内存地址。
- 可以指向任意类型的数据（如 `int`、`char`、结构体等）。
- 示例：
  ```cpp
  int a = 10;
  int* p = &a; // p 是指向 a 的指针
  ```

#### 2. **栈指针**
- 栈指针是 CPU 寄存器（如 `ESP` 或 `RSP`）中的一种特殊指针，用于管理函数调用栈。
- 指向当前栈顶的内存地址。
- 示例：
  - 在汇编语言中，`ESP` 是栈指针寄存器。


### **二、核心区别**
| **特性**               | **指针**                              | **栈指针**                          |
|------------------------|----------------------------------------|-------------------------------------|
| **作用**               | 存储任意内存地址                       | 管理函数调用栈                      |
| **存储位置**           | 内存中的变量                           | CPU 寄存器（如 `ESP`、`RSP`）       |
| **使用场景**           | 访问动态内存、数组、结构体等           | 函数调用、局部变量分配              |
| **生命周期**           | 由程序员控制                           | 由编译器自动管理                    |
| **抽象层次**           | 高级语言特性                           | 低级硬件特性                        |


### **三、详细对比**
#### 1. **作用**
- **指针**：
  - 用于访问和操作内存中的数据。
  - 可以指向堆、栈、全局变量等任意内存区域。
  - 示例：
    ```cpp
    int* p = new int(10); // 指向堆内存
    ```

- **栈指针**：
  - 用于管理函数调用栈。
  - 指向当前栈顶，用于分配和释放局部变量。
  - 示例：
    - 函数调用时，栈指针下移，为局部变量分配空间。
    - 函数返回时，栈指针上移，释放局部变量。

#### 2. **存储位置**
- **指针**：
  - 存储在内存中，是一个普通变量。
  - 示例：
    ```cpp
    int* p; // p 是内存中的一个变量
    ```

- **栈指针**：
  - 存储在 CPU 寄存器中（如 `ESP` 或 `RSP`）。
  - 示例：
    - 在 x86 架构中，`ESP` 是栈指针寄存器。

#### 3. **使用场景**
- **指针**：
  - 动态内存分配（如 `new`、`malloc`）。
  - 数组访问（如 `int arr[10]; int* p = arr;`）。
  - 数据结构（如链表、树）。

- **栈指针**：
  - 函数调用时保存返回地址。
  - 局部变量的分配和释放。
  - 保存函数调用的上下文（如寄存器值）。

#### 4. **生命周期**
- **指针**：
  - 由程序员显式分配和释放（如 `new`/`delete` 或 `malloc`/`free`）。
  - 示例：
    ```cpp
    int* p = new int(10);
    delete p; // 显式释放内存
    ```

- **栈指针**：
  - 由编译器自动管理。
  - 函数调用时自动调整栈指针。
  - 示例：
    - 函数调用时，栈指针下移。
    - 函数返回时，栈指针上移。

#### 5. **抽象层次**
- **指针**：
  - 高级语言特性，程序员可以直接使用。
  - 示例：
    ```cpp
    int a = 10;
    int* p = &a; // 直接使用指针
    ```

- **栈指针**：
  - 低级硬件特性，通常由编译器自动处理。
  - 示例：
    - 在汇编语言中，程序员可以直接操作栈指针。


### **四、示例**
#### 1. **指针示例**
```cpp
#include <iostream>

int main() {
    int a = 10;
    int* p = &a; // p 是指向 a 的指针
    std::cout << *p << std::endl; // 输出 10
    return 0;
}
```

#### 2. **栈指针示例**
```cpp
#include <iostream>

void func() {
    int b = 20; // 局部变量，分配在栈上
    std::cout << b << std::endl;
}

int main() {
    int a = 10; // 局部变量，分配在栈上
    func();
    return 0;
}
```
- **栈指针的作用**：
  - `main()` 函数调用时，栈指针下移，为 `a` 分配空间。
  - `func()` 函数调用时，栈指针再次下移，为 `b` 分配空间。
  - 函数返回时，栈指针上移，释放局部变量。


### **五、总结**
- **指针**：
  - 用于访问和操作内存中的数据。
  - 存储在内存中，由程序员显式管理。
- **栈指针**：
  - 用于管理函数调用栈。
  - 存储在 CPU 寄存器中，由编译器自动管理。

--- 

## 堆和栈
在 C++ 中，**堆（Heap）** 和 **栈（Stack）** 是两种不同的内存区域，用于存储程序运行时的数据。它们在内存管理、生命周期和访问方式上有显著区别。以下是它们的详细对比：


### 一、堆和栈的定义
#### 1. **栈（Stack）**
- 栈是一种后进先出（LIFO）的内存结构，由编译器自动管理。
- 栈用于存储局部变量、函数参数和函数调用的上下文（如返回地址）。

#### 2. **堆（Heap）**
- 堆是一种动态分配的内存区域，由程序员手动管理（或通过智能指针自动管理）。
- 堆用于存储动态分配的对象和数据结构。


### 二、核心区别
| **特性**               | **栈**                                | **堆**                                |
|------------------------|----------------------------------------|---------------------------------------|
| **内存管理**           | 编译器自动管理                         | 程序员手动管理（或智能指针）          |
| **生命周期**           | 随函数调用结束自动释放                 | 显式释放（或程序结束时释放）          |
| **分配速度**           | 快（只需移动栈指针）                   | 慢（需查找合适的内存块）              |
| **内存大小**           | 较小（通常几 MB）                      | 较大（受系统内存限制）                |
| **访问方式**           | 直接访问（通过栈指针）                 | 间接访问（通过指针）                  |
| **碎片问题**           | 无碎片                                 | 可能有内存碎片                        |
| **适用场景**           | 局部变量、函数调用                     | 动态分配的对象、大数据结构            |


### 三、详细对比
#### 1. **内存管理**
- **栈**：
  - 内存由编译器自动分配和释放。
  - 栈的大小有限，通常为几 MB（可通过编译器选项调整）。
- **堆**：
  - 内存由程序员手动分配（如 `new`/`malloc`）和释放（如 `delete`/`free`）。
  - 堆的大小受系统内存限制，通常较大。

#### 2. **生命周期**
- **栈**：
  - 变量的生命周期与函数调用绑定。
  - 函数调用结束时，栈上的变量自动释放。
- **堆**：
  - 变量的生命周期由程序员控制。
  - 必须显式释放内存，否则会导致内存泄漏。

#### 3. **分配速度**
- **栈**：
  - 分配速度快，只需移动栈指针。
- **堆**：
  - 分配速度较慢，需查找合适的内存块。

#### 4. **访问方式**
- **栈**：
  - 直接访问，通过栈指针定位变量。
- **堆**：
  - 间接访问，通过指针定位变量。

#### 5. **碎片问题**
- **栈**：
  - 无内存碎片问题，内存分配和释放是连续的。
- **堆**：
  - 可能有内存碎片问题，频繁分配和释放会导致内存不连续。

#### 6. **适用场景**
- **栈**：
  - 适合存储局部变量、函数参数和函数调用的上下文。
  - 适合生命周期短、大小固定的数据。
- **堆**：
  - 适合存储动态分配的对象和数据结构。
  - 适合生命周期长、大小不固定的数据。


### 四、示例对比
#### 1. **栈示例**
```cpp
void stackExample() {
    int a = 10; // 局部变量，存储在栈上
    int b = 20;
    int c = a + b;
    // 函数结束时，a、b、c 自动释放
}
```

#### 2. **堆示例**
```cpp
void heapExample() {
    int* a = new int(10); // 动态分配内存，存储在堆上
    int* b = new int(20);
    int* c = new int(*a + *b);
    // 必须显式释放内存
    delete a;
    delete b;
    delete c;
}
```


### 五、常见问题
#### 1. **栈溢出（Stack Overflow）**
- 当栈空间不足时（如递归调用过深），会导致栈溢出。
- 解决方法：
  - 减少栈空间的使用（如减少局部变量的大小）。
  - 将递归改为迭代。

#### 2. **内存泄漏（Memory Leak）**
- 当堆上的内存未释放时，会导致内存泄漏。
- 解决方法：
  - 使用智能指针（如 `std::unique_ptr`、`std::shared_ptr`）自动管理内存。
  - 确保每次 `new` 都有对应的 `delete`。

#### 3. **内存碎片（Memory Fragmentation）**
- 频繁分配和释放堆内存会导致内存碎片。
- 解决方法：
  - 使用内存池（Memory Pool）减少碎片。
  - 避免频繁分配和释放小块内存。


### 六、总结
- **栈**：
  - 适合存储局部变量和函数调用的上下文。
  - 内存由编译器自动管理，分配速度快，但大小有限。
- **堆**：
  - 适合存储动态分配的对象和数据结构。
  - 内存由程序员手动管理，分配速度慢，但大小较大。

在实际开发中，应根据数据的生命周期和大小选择合适的存储区域：
- 生命周期短、大小固定的数据适合存储在 **栈** 上。
- 生命周期长、大小不固定的数据适合存储在 **堆** 上。
- 
---
## 为什么栈向下增长
栈（Stack）向下增长是一种常见的设计选择，主要是为了与堆（Heap）的内存分配方式形成互补，从而更高效地利用内存空间。以下是栈向下增长的主要原因和背景：


### 1. **内存布局**
在典型的进程内存布局中，内存被划分为多个区域：
- **栈（Stack）**：用于存储函数调用的上下文（如局部变量、返回地址等）。
- **堆（Heap）**：用于动态内存分配（如 `malloc` 或 `new`）。
- **数据段（Data Segment）**：存储全局变量和静态变量。
- **代码段（Code Segment）**：存储程序的可执行代码。

栈和堆通常位于进程地址空间的两端：
- 栈从高地址向低地址增长。
- 堆从低地址向高地址增长。

这种布局可以最大限度地利用内存空间，避免栈和堆之间的冲突。


### 2. **栈向下增长的原因**
#### （1）**历史原因**
- 早期的计算机系统设计者选择栈向下增长，主要是为了简化内存管理。
- 栈向下增长的设计与硬件架构（如 x86）的调用约定（Calling Convention）密切相关。

#### （2）**与堆的互补**
- 堆通常向上增长（从低地址向高地址），而栈向下增长（从高地址向低地址）。
- 这种设计使得栈和堆可以共享同一块内存空间，动态调整边界，从而更高效地利用内存。

#### （3）**简化内存管理**
- 栈向下增长的设计使得栈指针（Stack Pointer）的调整更加简单。
- 每次函数调用时，栈指针减小（向低地址移动），为新的栈帧分配空间；函数返回时，栈指针增加（向高地址移动），释放栈帧。

#### （4）**硬件支持**
- 许多处理器架构（如 x86）对栈向下增长有硬件支持。
- 例如，x86 的 `PUSH` 和 `POP` 指令会自动调整栈指针（`ESP` 或 `RSP`），并遵循向下增长的规则。


### 3. **栈向下增长的实现**
- **栈指针（Stack Pointer）**：指向栈的当前顶部。
- **栈帧（Stack Frame）**：每次函数调用时，会在栈上分配一个栈帧，用于存储局部变量、返回地址等信息。
- **增长方向**：栈指针向低地址移动表示栈的增长。

#### 示例：
```c
void func() {
    int a = 10; // 局部变量，存储在栈中
    // 栈指针向低地址移动
}
```


### 4. **栈向下增长的优点**
#### （1）**高效的内存利用**
- 栈和堆分别从内存的两端向中间增长，可以最大限度地利用内存空间。
- 当栈和堆的边界相遇时，系统可以检测到内存不足。

#### （2）**简单的指针管理**
- 栈指针的调整（增加或减少）与栈的增长方向一致，逻辑清晰。
- 函数调用和返回时，栈指针的调整非常直观。

#### （3）**硬件优化**
- 许多处理器架构对栈向下增长有专门的优化，例如 x86 的 `PUSH` 和 `POP` 指令。


### 5. **栈向下增长的缺点**
- **容易溢出**：如果栈增长过多，可能会覆盖堆或其他内存区域，导致栈溢出（Stack Overflow）。
- **调试困难**：栈向下增长的方向与人类的直觉相反，可能会增加调试的难度。


### 6. **总结**
栈向下增长的设计主要是为了：
1. 与堆的内存分配方式互补，高效利用内存空间。
2. 简化栈指针的管理和硬件实现。
3. 遵循历史惯例和硬件架构的支持。


## mutex vs shared_mutex
**`mutex`** 和 **`shared_mutex`** 是 C++ 标准库中用于实现线程同步的两种锁机制，它们的主要区别在于锁的粒度和适用场景。以下是它们的详细对比：


### **一、基本概念**
#### 1. **`mutex`（互斥锁）**
- **功能**：提供独占访问，同一时间只有一个线程可以持有锁。
- **适用场景**：保护临界区，防止多个线程同时访问共享资源。

#### 2. **`shared_mutex`（共享互斥锁）**
- **功能**：支持两种模式：
  - **独占模式**：同一时间只有一个线程可以持有锁（类似于 `mutex`）。
  - **共享模式**：多个线程可以同时持有锁（适用于读多写少的场景）。
- **适用场景**：读多写少的场景，允许多个线程同时读取共享资源。


### **二、核心区别**
| **特性**               | **`mutex`**                          | **`shared_mutex`**                  |
|------------------------|----------------------------------------|-------------------------------------|
| **锁模式**             | 独占模式                               | 独占模式 + 共享模式                 |
| **适用场景**           | 通用场景                               | 读多写少的场景                     |
| **性能**               | 简单高效                               | 读操作性能更高                     |
| **C++ 标准**           | C++11                                  | C++17                              |
| **常用操作**           | `lock()`、`unlock()`、`try_lock()`     | `lock()`、`unlock()`、`try_lock()`、`lock_shared()`、`unlock_shared()`、`try_lock_shared()` |


### **三、详细对比**
#### 1. **锁模式**
- **`mutex`**：
  - 只支持独占模式，同一时间只有一个线程可以持有锁。
  - 示例：
    ```cpp
    std::mutex mtx;
    mtx.lock();   // 加锁
    // 临界区
    mtx.unlock(); // 解锁
    ```

- **`shared_mutex`**：
  - 支持两种模式：
    - **独占模式**：同一时间只有一个线程可以持有锁（用于写操作）。
    - **共享模式**：多个线程可以同时持有锁（用于读操作）。
  - 示例：
    ```cpp
    std::shared_mutex smtx;
    smtx.lock_shared(); // 共享模式加锁（读操作）
    // 读操作
    smtx.unlock_shared(); // 共享模式解锁

    smtx.lock(); // 独占模式加锁（写操作）
    // 写操作
    smtx.unlock(); // 独占模式解锁
    ```

#### 2. **适用场景**
- **`mutex`**：
  - 适用于通用场景，保护临界区。
  - 示例：
    ```cpp
    std::mutex mtx;
    int shared_data = 0;

    void increment() {
        mtx.lock();
        ++shared_data;
        mtx.unlock();
    }
    ```

- **`shared_mutex`**：
  - 适用于读多写少的场景，允许多个线程同时读取共享资源。
  - 示例：
    ```cpp
    std::shared_mutex smtx;
    int shared_data = 0;

    void read_data() {
        smtx.lock_shared();
        int value = shared_data;
        smtx.unlock_shared();
    }

    void write_data() {
        smtx.lock();
        ++shared_data;
        smtx.unlock();
    }
    ```

#### 3. **性能**
- **`mutex`**：
  - 简单高效，适合通用场景。
  - 但在读多写少的场景中，性能较差（读操作也需要独占锁）。

- **`shared_mutex`**：
  - 在读多写少的场景中，性能更高（允许多个线程同时读取）。
  - 但在写操作频繁的场景中，性能可能不如 `mutex`。

#### 4. **C++ 标准**
- **`mutex`**：
  - 从 C++11 开始支持。
- **`shared_mutex`**：
  - 从 C++17 开始支持。


### **四、示例代码**
#### 1. **`mutex` 示例**
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock();
        ++shared_data;
        mtx.unlock();
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
```

#### 2. **`shared_mutex` 示例**
```cpp
#include <iostream>
#include <thread>
#include <shared_mutex>

std::shared_mutex smtx;
int shared_data = 0;

void read_data() {
    for (int i = 0; i < 100000; ++i) {
        smtx.lock_shared();
        int value = shared_data;
        smtx.unlock_shared();
    }
}

void write_data() {
    for (int i = 0; i < 100000; ++i) {
        smtx.lock();
        ++shared_data;
        smtx.unlock();
    }
}

int main() {
    std::thread t1(read_data);
    std::thread t2(write_data);

    t1.join();
    t2.join();

    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
```


### **五、总结**
- **`mutex`**：
  - 适用于通用场景，提供独占访问。
  - 简单高效，但在读多写少的场景中性能较差。
- **`shared_mutex`**：
  - 适用于读多写少的场景，支持共享模式。
  - 在读操作频繁的场景中性能更高。
--- 
## vector 
在 C++ 中，`std::vector` 是标准模板库（STL）提供的动态数组容器，支持自动扩容、随机访问和高效的内存管理。以下是详细的中文解析：


### 1. **头文件与声明**
   ```cpp
   #include <vector>  // 必须包含头文件
   using namespace std; // 可选，简化代码

   vector<int> vec;                // 空整数向量
   vector<string> names{"Alice", "Bob"}; // 初始化包含字符串的向量
   vector<double> scores(5);       // 包含5个double元素的向量（默认初始化为0.0）
   ```


### 2. **核心操作**
   - **添加元素**：
     ```cpp
     vec.push_back(10);    // 在末尾添加元素（拷贝构造）
     vec.emplace_back(20); // 在末尾就地构造元素（更高效，C++11起支持）
     ```
   - **访问元素**：
     ```cpp
     int first = vec[0];      // 通过下标访问（无越界检查）
     int second = vec.at(1);  // 通过at()访问（越界时抛出std::out_of_range异常）
     int last = vec.back();   // 获取最后一个元素
     ```
   - **删除元素**：
     ```cpp
     vec.pop_back();          // 删除最后一个元素
     vec.erase(vec.begin());  // 删除第一个元素（需用迭代器）
     vec.clear();             // 清空所有元素
     ```
   - **容量管理**：
     ```cpp
     int size = vec.size();     // 当前元素个数
     bool isEmpty = vec.empty(); // 判断是否为空
     vec.reserve(100);          // 预分配至少容纳100个元素的内存
     vec.shrink_to_fit();       // 释放未使用的内存（C++11+）
     ```


### 3. **遍历方式**
   ```cpp
   // 范围for循环（C++11+）
   for (const auto& num : vec) {
       cout << num << endl;
   }

   // 迭代器遍历
   for (auto it = vec.begin(); it != vec.end(); ++it) {
       cout << *it << endl;
   }
   ```


### 4. **性能特点**
   - **随机访问**：时间复杂度为 O(1)（与数组相同）。
   - **尾部插入/删除**：平均时间复杂度为 O(1)（自动扩容时可能有短暂延迟）。
   - **中间插入/删除**：时间复杂度为 O(n)（需要移动后续元素）。
   - **内存特性**：连续内存布局，缓存友好，但频繁扩容可能导致性能开销。


### 5. **适用场景**
   - 需要动态调整大小的数组。
   - 高频随机访问元素的场景。
   - 需要与C风格接口交互时（通过 `vec.data()` 获取原始指针）。


### 6. **示例代码**
   ```cpp
   #include <iostream>
   #include <vector>
   using namespace std;

   int main() {
       vector<int> nums{1, 2, 3};
       nums.push_back(4);

       cout << "元素列表: ";
       for (int num : nums) {
           cout << num << " "; // 输出: 1 2 3 4
       }

       nums.pop_back(); // 删除末尾元素4
       cout << "\n删除后的大小: " << nums.size(); // 输出: 3
       return 0;
   }
   ```


### 7. **最佳实践**
   - **预分配内存**：已知元素数量时，用 `reserve()` 减少扩容次数。
   - **优先使用 `emplace_back`**：避免不必要的对象拷贝。
   - **避免值传递**：函数参数使用引用传递以提升性能，如：  
     `void process(const vector<int>& data) { ... }`


### 8. **与其他容器的对比**
   - **`std::list`**：适合频繁在中间插入/删除，但无法随机访问。
   - **`std::deque`**：支持高效的头尾插入，但内存不连续。


`std::vector` 是 C++ 中最常用的容器之一，兼具灵活性与性能。建议在需要动态数组时优先选择，但避免在中间频繁插入/删除的场景。

--- 
## vector vs array
**`std::vector`** 和 **`std::array`** 是 C++ 标准库中两种常用的容器，分别用于动态数组和固定大小数组。以下是它们的详细对比：


### **一、基本概念**
#### 1. **`std::vector`**
- **功能**：动态数组，支持自动扩容。
- **适用场景**：需要动态调整大小的数组。

#### 2. **`std::array`**
- **功能**：固定大小数组，大小在编译时确定。
- **适用场景**：需要固定大小的数组。


### **二、核心区别**
| **特性**               | **`std::vector`**                    | **`std::array`**                    |
|------------------------|----------------------------------------|-------------------------------------|
| **大小**               | 动态调整                               | 固定大小                            |
| **内存管理**           | 自动管理                               | 手动管理                            |
| **性能**               | 动态扩容有开销                         | 性能更高                            |
| **适用场景**           | 需要动态调整大小的场景                 | 需要固定大小的场景                  |
| **C++ 标准**           | C++98                                  | C++11                              |
| **常用操作**           | `push_back()`、`pop_back()`、`resize()`| `fill()`、`size()`                  |


### **三、详细对比**
#### 1. **大小**
- **`std::vector`**：
  - 大小可以动态调整。
  - 示例：
    ```cpp
    std::vector<int> vec = {1, 2, 3};
    vec.push_back(4); // 大小变为 4
    ```

- **`std::array`**：
  - 大小在编译时确定，无法动态调整。
  - 示例：
    ```cpp
    std::array<int, 3> arr = {1, 2, 3};
    // arr.size() 始终为 3
    ```

#### 2. **内存管理**
- **`std::vector`**：
  - 自动管理内存，支持动态扩容。
  - 示例：
    ```cpp
    std::vector<int> vec;
    vec.reserve(100); // 预分配内存
    ```

- **`std::array`**：
  - 内存由程序员手动管理。
  - 示例：
    ```cpp
    std::array<int, 100> arr; // 固定大小
    ```

#### 3. **性能**
- **`std::vector`**：
  - 动态扩容时可能涉及内存重新分配和数据拷贝。
  - 示例：
    ```cpp
    std::vector<int> vec;
    for (int i = 0; i < 100000; ++i) {
        vec.push_back(i); // 可能触发多次扩容
    }
    ```

- **`std::array`**：
  - 性能更高，无需动态扩容。
  - 示例：
    ```cpp
    std::array<int, 100000> arr;
    for (int i = 0; i < 100000; ++i) {
        arr[i] = i; // 无需扩容
    }
    ```

#### 4. **适用场景**
- **`std::vector`**：
  - 需要动态调整大小的场景。
  - 示例：存储用户输入、动态生成的数据。

- **`std::array`**：
  - 需要固定大小的场景。
  - 示例：存储固定大小的数据集合（如矩阵、缓冲区）。

#### 5. **C++ 标准**
- **`std::vector`**：
  - 从 C++98 开始支持。
- **`std::array`**：
  - 从 C++11 开始支持。


### **四、示例代码**
#### 1. **`std::vector` 示例**
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3};
    vec.push_back(4); // 动态扩容
    for (int i : vec) {
        std::cout << i << " ";
    }
    return 0;
}
```

#### 2. **`std::array` 示例**
```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 3> arr = {1, 2, 3};
    for (int i : arr) {
        std::cout << i << " ";
    }
    return 0;
}
```


### **五、总结**
- **`std::vector`**：
  - 动态数组，支持自动扩容。
  - 适用于需要动态调整大小的场景。
- **`std::array`**：
  - 固定大小数组，性能更高。
  - 适用于需要固定大小的场景。

--- 
## string
`std::string` 是 C++ 标准库中用于表示和操作字符串的类，它封装了字符数组，提供了丰富的字符串操作功能。以下是关于 `std::string` 的详细介绍：


### **一、基本特性**
1. **动态字符串**：
   - `std::string` 是一个动态数组，可以自动调整大小。
   - 支持高效的字符串操作（如拼接、查找、替换）。

2. **内存管理**：
   - 自动管理内存，无需手动分配和释放。

3. **兼容性**：
   - 可以与 C 风格字符串（`char*`）互相转换。


### **二、常用操作**
#### 1. **构造和初始化**
- 默认构造：
  ```cpp
  std::string str;
  ```
- 使用 C 风格字符串初始化：
  ```cpp
  std::string str = "Hello";
  ```
- 使用字符初始化：
  ```cpp
  std::string str(5, 'A'); // "AAAAA"
  ```

#### 2. **访问元素**
- 使用下标访问：
  ```cpp
  char ch = str[0];
  ```
- 使用 `at()` 访问（带边界检查）：
  ```cpp
  char ch = str.at(0);
  ```

#### 3. **修改字符串**
- 拼接字符串：
  ```cpp
  str += " World";
  str.append("!");
  ```
- 插入字符：
  ```cpp
  str.insert(5, " C++");
  ```
- 删除字符：
  ```cpp
  str.erase(5, 4); // 从位置 5 开始删除 4 个字符
  ```

#### 4. **查找和替换**
- 查找子串：
  ```cpp
  size_t pos = str.find("World");
  ```
- 替换子串：
  ```cpp
  str.replace(6, 5, "Universe"); // 将 "World" 替换为 "Universe"
  ```

#### 5. **大小和容量**
- 获取字符串长度：
  ```cpp
  size_t len = str.size(); // 或 str.length()
  ```
- 检查是否为空：
  ```cpp
  bool isEmpty = str.empty();
  ```
- 调整大小：
  ```cpp
  str.resize(10); // 调整字符串大小为 10
  ```

#### 6. **比较字符串**
- 使用 `==`、`!=`、`<`、`>` 等运算符：
  ```cpp
  if (str1 == str2) {
      std::cout << "Strings are equal" << std::endl;
  }
  ```

#### 7. **转换**
- 转换为 C 风格字符串：
  ```cpp
  const char* cstr = str.c_str();
  ```
- 转换为数值：
  ```cpp
  int num = std::stoi("123");
  double d = std::stod("3.14");
  ```


### **三、示例代码**
```cpp
#include <iostream>
#include <string>

int main() {
    // 构造和初始化
    std::string str = "Hello";
    std::cout << "Initial string: " << str << std::endl;

    // 拼接字符串
    str += " World";
    std::cout << "After concatenation: " << str << std::endl;

    // 插入字符
    str.insert(5, " C++");
    std::cout << "After insertion: " << str << std::endl;

    // 查找子串
    size_t pos = str.find("World");
    if (pos != std::string::npos) {
        std::cout << "'World' found at position: " << pos << std::endl;
    }

    // 替换子串
    str.replace(6, 5, "Universe");
    std::cout << "After replacement: " << str << std::endl;

    // 转换为 C 风格字符串
    const char* cstr = str.c_str();
    std::cout << "C-style string: " << cstr << std::endl;

    return 0;
}
```


### **四、性能优化**
1. **预分配内存**：
   - 使用 `reserve()` 预分配内存，避免频繁扩容。
   ```cpp
   std::string str;
   str.reserve(100); // 预分配 100 字节
   ```

2. **避免不必要的拷贝**：
   - 使用引用或移动语义传递 `std::string`。
   ```cpp
   void processString(const std::string& str); // 使用引用
   ```

3. **使用 `std::string_view`（C++17）**：
   - 避免拷贝，适用于只读字符串操作。
   ```cpp
   std::string_view view = "Hello";
   ```


### **五、总结**
- `std::string` 是 C++ 中用于表示和操作字符串的类，支持动态调整大小和丰富的操作。
- 提供了高效的字符串操作功能，如拼接、查找、替换等。
- 通过预分配内存和使用引用，可以进一步优化性能。

--- 
## sizeof
在 C++11 中，`sizeof` 是一个运算符，用于计算数据类型或对象的大小（以字节为单位）。它是编译时计算的，返回一个 `size_t` 类型的值。`sizeof` 的使用方式在 C++11 中与之前的 C++ 标准基本相同，但 C++11 引入了一些新的特性（如 `decltype` 和 `alignof`），可以与 `sizeof` 结合使用。

### 1. `sizeof` 的基本用法
`sizeof` 可以用于以下两种形式：
1. **计算类型的大小**：
   ```cpp
   sizeof(type)
   ```
2. **计算表达式或对象的大小**：
   ```cpp
   sizeof(expression)
   ```

#### 示例：
```cpp
#include <iostream>

int main() {
    int a = 10;
    std::cout << "Size of int: " << sizeof(int) << std::endl;          // 输出 int 类型的大小
    std::cout << "Size of a: " << sizeof(a) << std::endl;              // 输出变量 a 的大小
    std::cout << "Size of expression: " << sizeof(a + 1.5) << std::endl; // 输出表达式 a + 1.5 的大小
    return 0;
}
```

#### 输出：
```
Size of int: 4
Size of a: 4
Size of expression: 8
```

### 2. `sizeof` 与 C++11 新特性
C++11 引入了一些新特性，可以与 `sizeof` 结合使用。

#### （1）`sizeof` 与 `decltype`
`decltype` 用于推导表达式的类型，可以与 `sizeof` 结合使用来计算类型的大小。

##### 示例：
```cpp
#include <iostream>

int main() {
    int a = 10;
    double b = 3.14;
    std::cout << "Size of decltype(a + b): " << sizeof(decltype(a + b)) << std::endl;
    return 0;
}
```

##### 输出：
```
Size of decltype(a + b): 8
```

#### （2）`sizeof` 与 `alignof`
`alignof` 用于获取类型的对齐要求（alignment），可以与 `sizeof` 结合使用来了解类型的大小和对齐。

##### 示例：
```cpp
#include <iostream>

struct alignas(16) AlignedStruct {
    int a;
    double b;
};

int main() {
    std::cout << "Size of AlignedStruct: " << sizeof(AlignedStruct) << std::endl;
    std::cout << "Alignment of AlignedStruct: " << alignof(AlignedStruct) << std::endl;
    return 0;
}
```

##### 输出：
```
Size of AlignedStruct: 16
Alignment of AlignedStruct: 16
```

### 3. `sizeof` 的特殊用法
#### （1）计算数组的大小
`sizeof` 可以用于计算整个数组的大小。

##### 示例：
```cpp
#include <iostream>

int main() {
    int arr[10];
    std::cout << "Size of array: " << sizeof(arr) << std::endl; // 输出数组的总大小
    std::cout << "Number of elements: " << sizeof(arr) / sizeof(arr[0]) << std::endl; // 输出数组的元素个数
    return 0;
}
```

##### 输出：
```
Size of array: 40
Number of elements: 10
```

#### （2）计算结构体的大小
`sizeof` 可以用于计算结构体的大小，注意结构体可能存在填充（padding）以对齐成员。

##### 示例：
```cpp
#include <iostream>

struct MyStruct {
    char a;
    int b;
    double c;
};

int main() {
    std::cout << "Size of MyStruct: " << sizeof(MyStruct) << std::endl;
    return 0;
}
```

##### 输出：
```
Size of MyStruct: 16
```

### 4. `sizeof` 的注意事项
1. **编译时计算**：`sizeof` 是编译时计算的，不会对表达式进行求值。
   ```cpp
   int a = 10;
   std::cout << sizeof(a++); // a++ 不会被执行
   std::cout << a;           // 输出 10
   ```

2. **指针的大小**：`sizeof` 计算指针时，返回的是指针本身的大小，而不是指向对象的大小。
   ```cpp
   int* ptr;
   std::cout << sizeof(ptr); // 输出指针的大小（通常为 8 字节，64 位系统）
   ```

3. **动态分配的内存**：`sizeof` 不能用于计算动态分配的内存大小。
   ```cpp
   int* arr = new int[10];
   std::cout << sizeof(arr); // 输出指针的大小，而不是数组的大小
   ```

### 5. 总结
- `sizeof` 是 C++ 中用于计算类型或对象大小的运算符。
- 在 C++11 中，`sizeof` 可以与 `decltype` 和 `alignof` 结合使用。
- `sizeof` 是编译时计算的，不会对表达式求值。
- 常用于计算数组大小、结构体大小以及类型的大小。
---
## sizeof（void）
在 C++ 中，`sizeof(void)` 是一个不合法的操作，会导致编译错误。这是因为 `void` 是一个不完整的类型（incomplete type），它没有大小（size），编译器无法计算其大小。

### 1. 为什么 `sizeof(void)` 不合法？
- `void` 是一个特殊的类型，表示“无类型”或“空类型”。
- 它通常用于以下场景：
  - 函数的返回类型（表示函数不返回任何值）。
  - 函数的参数列表（表示函数不接受任何参数）。
  - 通用指针类型（`void*`，可以指向任何类型的数据）。
- 由于 `void` 不表示任何具体的值或对象，因此它没有大小。

### 2. 示例代码
如果尝试编译以下代码，编译器会报错：
```cpp
#include <iostream>

int main() {
    std::cout << sizeof(void) << std::endl; // 错误：非法操作
    return 0;
}
```

#### 编译器错误：
```
error: invalid application of 'sizeof' to a void type
```


### 3. `sizeof(void*)` 是合法的
虽然 `sizeof(void)` 不合法，但 `sizeof(void*)` 是合法的。`void*` 是一个指向 `void` 的指针，指针的大小是固定的，与指向的类型无关。

#### 示例：
```cpp
#include <iostream>

int main() {
    std::cout << "Size of void*: " << sizeof(void*) << std::endl;
    return 0;
}
```

#### 输出：
```
Size of void*: 8  // 在 64 位系统上，指针的大小通常为 8 字节
```


### 4. 总结
- `sizeof(void)` 是不合法的操作，因为 `void` 是一个不完整的类型，没有大小。
- `sizeof(void*)` 是合法的，因为它计算的是指针的大小，而不是 `void` 的大小。
- 如果需要表示“无类型”或“空类型”，应使用 `void` 的指针形式（`void*`）。
---
## 前置自增
前置自增（`++i`）是 C++ 中的一种运算符，用于将变量的值加 1，并返回自增后的值。与后置自增（`i++`）不同，前置自增的效率通常更高，因为它不需要保存自增前的值。


### 1. 语法
```cpp
++i;
```
- `i` 是要自增的变量。
- 表达式的结果是自增后的值。


### 2. 行为
- 先将变量的值加 1。
- 然后返回自增后的值。

#### 示例：
```cpp
int i = 5;
int j = ++i; // i 先自增为 6，然后 j 被赋值为 6
std::cout << i << ", " << j; // 输出: 6, 6
```


### 3. 与后置自增的区别
- **前置自增（`++i`）**：
  - 先自增，后返回值。
  - 效率较高，因为不需要保存自增前的值。
- **后置自增（`i++`）**：
  - 先返回当前值，后自增。
  - 效率较低，因为需要保存自增前的值。

#### 示例对比：
```cpp
int i = 5;
int j = i++; // j 被赋值为 5，然后 i 自增为 6
std::cout << i << ", " << j; // 输出: 6, 5
```


### 4. 性能分析
- **前置自增**：
  - 直接对变量进行自增操作，并返回自增后的值。
  - 不需要额外的临时变量。
- **后置自增**：
  - 需要保存自增前的值，然后自增，最后返回保存的值。
  - 可能会引入额外的开销。

在循环或性能敏感的代码中，优先使用前置自增。

### 5. 适用场景
- **前置自增**：
  - 循环中的迭代器自增。
  - 需要直接使用自增后的值。
- **后置自增**：
  - 需要先使用当前值，再自增。

#### 示例：循环中使用前置自增
```cpp
for (int i = 0; i < 10; ++i) {
    std::cout << i << " "; // 输出: 0 1 2 3 4 5 6 7 8 9
}
```

### 6. 自定义类型中的前置自增
对于自定义类型（如类或结构体），可以通过重载 `operator++` 来实现前置自增。

#### 示例：
```cpp
class Counter {
public:
    int value;

    Counter(int v = 0) : value(v) {}

    // 前置自增
    Counter& operator++() {
        ++value;
        return *this;
    }

    // 后置自增
    Counter operator++(int) {
        Counter temp = *this;
        ++value;
        return temp;
    }
};

int main() {
    Counter c(5);
    ++c; // 前置自增
    std::cout << c.value; // 输出: 6

    Counter d = c++; // 后置自增
    std::cout << c.value << ", " << d.value; // 输出: 7, 6
    return 0;
}
```


### 7. 总结
- 前置自增（`++i`）先自增，后返回值，效率较高。
- 后置自增（`i++`）先返回值，后自增，效率较低。
- 在循环或性能敏感的代码中，优先使用前置自增。
- 对于自定义类型，可以通过重载 `operator++` 实现前置自增和后置自增。
---
## 单例模式
**单例模式（Singleton Pattern）** 是一种设计模式，用于确保一个类只有一个实例，并提供一个全局访问点。以下是 C++ 中实现单例模式的几种常见方式：


### **一、经典实现（非线程安全）**
#### 1. **实现代码**
```cpp
class Singleton {
public:
    // 获取单例实例
    static Singleton& getInstance() {
        static Singleton instance; // 局部静态变量
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    // 私有构造函数
    Singleton() {}
};
```

#### 2. **使用示例**
```cpp
int main() {
    Singleton& instance = Singleton::getInstance();
    return 0;
}
```

#### 3. **特点**
- **优点**：简单易用。
- **缺点**：非线程安全（C++11 之前）。


### **二、线程安全实现（C++11）**
#### 1. **实现代码**
```cpp
#include <mutex>

class Singleton {
public:
    // 获取单例实例
    static Singleton& getInstance() {
        static Singleton instance; // C++11 保证局部静态变量的线程安全
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    // 私有构造函数
    Singleton() {}
};
```

#### 2. **使用示例**
```cpp
int main() {
    Singleton& instance = Singleton::getInstance();
    return 0;
}
```

#### 3. **特点**
- **优点**：线程安全，简单高效。
- **缺点**：依赖 C++11 标准。


### **三、双重检查锁定（Double-Checked Locking）**
#### 1. **实现代码**
```cpp
#include <mutex>

class Singleton {
public:
    // 获取单例实例
    static Singleton* getInstance() {
        if (instance == nullptr) { // 第一次检查
            std::lock_guard<std::mutex> lock(mutex); // 加锁
            if (instance == nullptr) { // 第二次检查
                instance = new Singleton();
            }
        }
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    // 私有构造函数
    Singleton() {}

    // 静态成员变量
    static Singleton* instance;
    static std::mutex mutex;
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;
```

#### 2. **使用示例**
```cpp
int main() {
    Singleton* instance = Singleton::getInstance();
    return 0;
}
```

#### 3. **特点**
- **优点**：线程安全，性能较高（仅在第一次创建实例时加锁）。
- **缺点**：实现复杂，容易出错。


### **四、Meyer's Singleton（推荐）**
#### 1. **实现代码**
```cpp
class Singleton {
public:
    // 获取单例实例
    static Singleton& getInstance() {
        static Singleton instance; // C++11 保证局部静态变量的线程安全
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    // 私有构造函数
    Singleton() {}
};
```

#### 2. **使用示例**
```cpp
int main() {
    Singleton& instance = Singleton::getInstance();
    return 0;
}
```

#### 3. **特点**
- **优点**：线程安全，简单高效。
- **缺点**：依赖 C++11 标准。


### **五、总结**
- **经典实现**：简单但非线程安全。
- **线程安全实现**：C++11 标准下推荐使用。
- **双重检查锁定**：性能较高但实现复杂。
- **Meyer's Singleton**：C++11 标准下最佳选择。

--- 
## LRU
_C++实现一个缓存，用LRU淘汰机制，支持TTL过期，同时要并发安全_
实现一个支持 **LRU 淘汰机制** 和 **TTL 过期** 的并发安全缓存，可以使用以下设计：


### **设计思路**
1. **数据结构**：
   - 使用 `std::unordered_map` 存储键值对，实现 O(1) 的查找。
   - 使用 `std::list` 实现 LRU 链表，记录访问顺序。
   - 使用 `std::mutex` 保证并发安全。

2. **LRU 淘汰机制**：
   - 每次访问（读或写）时，将节点移动到链表头部。
   - 当缓存达到容量上限时，淘汰链表尾部的节点。

3. **TTL 过期机制**：
   - 每个缓存项记录插入时间。
   - 在访问时检查是否过期，过期则删除。

4. **并发安全**：
   - 使用 `std::mutex` 或 `std::shared_mutex` 保护共享资源。


### **代码实现**

```cpp
#include <iostream>
#include <unordered_map>
#include <list>
#include <mutex>
#include <chrono>
#include <thread>
#include <memory>

class LRUCache {
public:
    using KeyType = std::string;
    using ValueType = std::string;
    using TimePoint = std::chrono::steady_clock::time_point;

    struct CacheItem {
        ValueType value;
        TimePoint timestamp;
    };

    LRUCache(size_t capacity, size_t ttlSeconds)
        : capacity_(capacity), ttlSeconds_(ttlSeconds) {}

    // 获取缓存值
    std::optional<ValueType> get(const KeyType& key) {
        std::unique_lock<std::mutex> lock(mutex_);
        auto it = cacheMap_.find(key);
        if (it == cacheMap_.end()) {
            return std::nullopt; // 未找到
        }

        // 检查是否过期
        if (isExpired(it->second.timestamp)) {
            cacheList_.erase(it->second.listIt);
            cacheMap_.erase(it);
            return std::nullopt; // 已过期
        }

        // 更新访问时间并移动到链表头部
        cacheList_.splice(cacheList_.begin(), cacheList_, it->second.listIt);
        return it->second.value;
    }

    // 插入或更新缓存值
    void put(const KeyType& key, const ValueType& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        auto it = cacheMap_.find(key);

        // 如果键已存在，更新值并移动到链表头部
        if (it != cacheMap_.end()) {
            it->second.value = value;
            it->second.timestamp = getCurrentTime();
            cacheList_.splice(cacheList_.begin(), cacheList_, it->second.listIt);
            return;
        }

        // 如果缓存已满，淘汰最久未使用的项
        if (cacheMap_.size() >= capacity_) {
            auto last = cacheList_.back();
            cacheMap_.erase(last);
            cacheList_.pop_back();
        }

        // 插入新项
        cacheList_.push_front(key);
        cacheMap_[key] = {value, getCurrentTime(), cacheList_.begin()};
    }

    // 删除缓存项
    void remove(const KeyType& key) {
        std::unique_lock<std::mutex> lock(mutex_);
        auto it = cacheMap_.find(key);
        if (it != cacheMap_.end()) {
            cacheList_.erase(it->second.listIt);
            cacheMap_.erase(it);
        }
    }

    // 清空缓存
    void clear() {
        std::unique_lock<std::mutex> lock(mutex_);
        cacheMap_.clear();
        cacheList_.clear();
    }

private:
    // 检查是否过期
    bool isExpired(const TimePoint& timestamp) const {
        auto now = getCurrentTime();
        return std::chrono::duration_cast<std::chrono::seconds>(now - timestamp).count() >= ttlSeconds_;
    }

    // 获取当前时间
    TimePoint getCurrentTime() const {
        return std::chrono::steady_clock::now();
    }

    size_t capacity_; // 缓存容量
    size_t ttlSeconds_; // TTL 过期时间（秒）
    std::mutex mutex_; // 互斥锁

    // 缓存数据结构
    std::list<KeyType> cacheList_; // LRU 链表
    std::unordered_map<KeyType, std::pair<CacheItem, typename std::list<KeyType>::iterator>> cacheMap_;
};

int main() {
    LRUCache cache(2, 5); // 容量为 2，TTL 为 5 秒

    cache.put("key1", "value1");
    cache.put("key2", "value2");

    if (auto value = cache.get("key1")) {
        std::cout << "key1: " << *value << std::endl;
    } else {
        std::cout << "key1 not found or expired" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(6)); // 等待 6 秒

    if (auto value = cache.get("key1")) {
        std::cout << "key1: " << *value << std::endl;
    } else {
        std::cout << "key1 not found or expired" << std::endl;
    }

    return 0;
}
```

### **代码说明**
1. **数据结构**：
   - `cacheList_`：双向链表，记录访问顺序。
   - `cacheMap_`：哈希表，存储键值对和链表迭代器。

2. **LRU 淘汰机制**：
   - 每次访问时，将节点移动到链表头部。
   - 当缓存满时，淘汰链表尾部的节点。

3. **TTL 过期机制**：
   - 每个缓存项记录插入时间。
   - 在访问时检查是否过期，过期则删除。

4. **并发安全**：
   - 使用 `std::mutex` 保护共享资源。


### **测试与优化**
1. **测试**：
   - 测试并发访问（多线程读写）。
   - 测试 LRU 淘汰和 TTL 过期逻辑。

2. **优化**：
   - 使用 `std::shared_mutex` 实现读写锁，提高读性能。
   - 使用定时器定期清理过期缓存项。


### **总结**
- 该实现支持 LRU 淘汰和 TTL 过期，同时保证并发安全。
- 适用于高并发场景下的缓存需求，如 Web 服务器、数据库查询缓存等。

--- 
## 检测内存泄漏的工具
在 C++ 中，内存泄漏是一个常见问题，通常是由于动态分配的内存未正确释放导致的。为了检测和修复内存泄漏，可以使用多种工具和技术。以下是一些常用的内存泄漏检测工具：



### 一、工具分类
#### 1. **静态分析工具**
- 在编译时或代码编写阶段分析代码，检测潜在的内存泄漏问题。
- 优点：无需运行程序，适合早期发现问题。
- 缺点：可能产生误报或漏报。

#### 2. **动态分析工具**
- 在程序运行时检测内存泄漏。
- 优点：准确率高，能定位具体泄漏点。
- 缺点：需要运行程序，可能影响性能。


### 二、常用工具
#### 1. **Valgrind**
- **平台**：Linux。
- **功能**：
  - 检测内存泄漏、非法内存访问、未初始化内存使用等问题。
  - 提供详细的调用栈信息，帮助定位问题。
- **使用方法**：
  ```bash
  valgrind --leak-check=full ./your_program
  ```
- **输出示例**：
  ```
  ==12345== HEAP SUMMARY:
  ==12345==     in use at exit: 72 bytes in 3 blocks
  ==12345==   total heap usage: 10 allocs, 7 frees, 1,024 bytes allocated
  ==12345==
  ==12345== LEAK SUMMARY:
  ==12345==    definitely lost: 24 bytes in 1 blocks
  ==12345==    indirectly lost: 48 bytes in 2 blocks
  ==12345==      possibly lost: 0 bytes in 0 blocks
  ==12345==    still reachable: 0 bytes in 0 blocks
  ==12345==         suppressed: 0 bytes in 0 blocks
  ```

#### 2. **AddressSanitizer (ASan)**
- **平台**：Linux、macOS、Windows（部分支持）。
- **功能**：
  - 检测内存泄漏、缓冲区溢出、使用释放后的内存等问题。
  - 性能开销较低，适合生产环境。
- **使用方法**：
  - 编译时添加 `-fsanitize=address` 选项：
    ```bash
    g++ -fsanitize=address -g -o your_program your_program.cpp
    ./your_program
    ```
- **输出示例**：
  ```
  =================================================================
  ==12345==ERROR: LeakSanitizer: detected memory leaks

  Direct leak of 24 byte(s) in 1 object(s) allocated from:
      #0 0x4f5b2d in malloc (/path/to/your_program+0x4f5b2d)
      #1 0x4006b6 in main /path/to/your_program.cpp:10
  ```

#### 3. **Dr. Memory**
- **平台**：Windows、Linux。
- **功能**：
  - 检测内存泄漏、非法内存访问、未初始化内存使用等问题。
  - 支持多线程程序。
- **使用方法**：
  ```bash
  drmemory -- ./your_program
  ```

#### 4. **Visual Studio 内存分析工具**
- **平台**：Windows。
- **功能**：
  - 集成在 Visual Studio 中，提供内存使用情况和泄漏检测。
  - 支持调试模式和性能分析。
- **使用方法**：
  1. 在 Visual Studio 中打开项目。
  2. 选择 **Debug > Windows > Memory Usage**。
  3. 运行程序并查看内存使用情况。

#### 5. **LeakSanitizer (LSan)**
- **平台**：Linux、macOS。
- **功能**：
  - 专注于检测内存泄漏。
  - 与 AddressSanitizer 集成，性能开销低。
- **使用方法**：
  - 编译时添加 `-fsanitize=leak` 选项：
    ```bash
    g++ -fsanitize=leak -g -o your_program your_program.cpp
    ./your_program
    ```

#### 6. **Electric Fence**
- **平台**：Linux。
- **功能**：
  - 检测内存越界访问和释放后的内存使用。
  - 通过库链接方式使用。
- **使用方法**：
  ```bash
  g++ -g -o your_program your_program.cpp -lefence
  ./your_program
  ```

#### 7. **Cppcheck**
- **平台**：跨平台。
- **功能**：
  - 静态代码分析工具，检测内存泄漏、未初始化变量等问题。
  - 无需运行程序。
- **使用方法**：
  ```bash
  cppcheck --enable=all your_program.cpp
  ```


### 三、选择工具的建议
1. **开发阶段**：
   - 使用 **静态分析工具**（如 Cppcheck）在早期发现问题。
   - 使用 **动态分析工具**（如 Valgrind、AddressSanitizer）在运行时检测问题。

2. **生产环境**：
   - 使用 **AddressSanitizer** 或 **LeakSanitizer**，性能开销较低。

3. **平台支持**：
   - **Linux**：Valgrind、AddressSanitizer、LeakSanitizer。
   - **Windows**：Visual Studio 内存分析工具、Dr. Memory。
   - **跨平台**：Cppcheck。


### 四、预防内存泄漏的最佳实践
1. **使用智能指针**：
   - 使用 `std::unique_ptr` 或 `std::shared_ptr` 自动管理内存。
   ```cpp
   std::unique_ptr<int> ptr = std::make_unique<int>(42);
   ```

2. **遵循 RAII 原则**：
   - 资源获取即初始化（RAII），确保资源在对象生命周期结束时自动释放。

3. **避免裸指针**：
   - 尽量避免使用裸指针（`int*`），使用智能指针或容器（如 `std::vector`）。

4. **定期检查**：
   - 在开发过程中定期使用工具检测内存泄漏。


### 五、总结
- **Valgrind** 和 **AddressSanitizer** 是最常用的内存泄漏检测工具。
- **智能指针** 和 **RAII** 是预防内存泄漏的最佳实践。
- 根据开发阶段和平台选择合适的工具，可以有效检测和修复内存泄漏问题。