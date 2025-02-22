# C++11 新增的关键字
> reference: https://en.cppreference.com/w/cpp/11
- [C++11 新增的关键字](#c11-新增的关键字)
    - [decltype](#decltype)
    - [constexpr](#constexpr)
      - [const和constexpr的区别](#const和constexpr的区别)
        - [1. `const`](#1-const)
          - [示例：](#示例)
        - [2. `constexpr`](#2-constexpr)
          - [示例：](#示例-1)
        - [3. 主要区别](#3-主要区别)
        - [4. 结合使用](#4-结合使用)
        - [5. 总结](#5-总结)
    - [char\_16t char\_32t](#char_16t-char_32t)
    - [nullptr](#nullptr)
    - [long long](#long-long)
    - [static\_assert](#static_assert)
---

### decltype
- Inspects the declared type of an entity or the type and value category of an expression.
- decltype(entity)
- decltype(expression)

```C++
int main () {
    int i = 0;
    decltype(i) j = 3;
    return 0;
}
```

### constexpr
- constexpr 用于修饰编译期的常量或者函数。保证表达式在编译器计算，提高安全性和性能。
- const 用于修饰运行时的常量或者不可变的值。仅能保证在变量的值初始后不可改变，不能保证在编译期计算。
#### const和constexpr的区别
`const` 和 `constexpr` 是 C++ 中用于定义常量的关键字，但它们的用途和行为有所不同。以下是它们的区别和适用场景：


##### 1. `const`
- **含义**：`const` 用于声明一个不可修改的变量（常量），或者表示一个函数不会修改对象的状态。
- **作用范围**：
  - 变量：`const` 变量的值在运行时确定，且不能被修改。
  - 函数：`const` 成员函数表示该函数不会修改类的成员变量。
- **初始化**：
  - `const` 变量必须在声明时初始化（或在构造函数中初始化，对于类的成员变量）。
  - 初始化值可以是编译时或运行时的值。
- **适用场景**：
  - 定义运行时常量。
  - 定义不可修改的函数参数或返回值。
  - 定义类的 `const` 成员函数。

###### 示例：
```cpp
const int x = 10; // x 是一个常量，值在编译时或运行时确定
const int y = someFunction(); // y 的值在运行时确定

void print(const int& value) { // value 是一个不可修改的参数
    std::cout << value << std::endl;
}

class MyClass {
public:
    int getValue() const { // const 成员函数，不会修改成员变量
        return value;
    }
private:
    int value = 42;
};
```


##### 2. `constexpr`
- **含义**：`constexpr` 用于声明一个编译时常量，或者表示一个函数可以在编译时求值。
- **作用范围**：
  - 变量：`constexpr` 变量的值必须在编译时确定。
  - 函数：`constexpr` 函数可以在编译时求值，前提是传入的参数是编译时常量。
- **初始化**：
  - `constexpr` 变量的值必须在编译时确定，因此只能用常量表达式初始化。
  - `constexpr` 函数的返回值必须是编译时可计算的。
- **适用场景**：
  - 定义编译时常量。
  - 定义编译时可计算的函数。
  - 用于模板元编程或需要编译时计算的场景。

###### 示例：
```cpp
constexpr int x = 10; // x 是一个编译时常量
constexpr int square(int n) { // constexpr 函数
    return n * n;
}
constexpr int y = square(5); // y 的值在编译时计算

int main() {
    int array[y]; // 使用编译时常量定义数组大小
    return 0;
}
```


##### 3. 主要区别

| 特性                | `const`                              | `constexpr`                        |
|---------------------|--------------------------------------|------------------------------------|
| **初始化时机**       | 运行时或编译时                       | 必须是编译时                       |
| **变量值**           | 可以是运行时的值                     | 必须是编译时常量                   |
| **函数**             | 不能保证在编译时求值                 | 可以在编译时求值                   |
| **适用场景**         | 运行时常量、不可修改的函数参数       | 编译时常量、编译时计算的函数       |
| **性能**             | 无编译时优化                         | 编译时计算，可能带来性能优化       |


##### 4. 结合使用
`const` 和 `constexpr` 可以结合使用，例如：
```cpp
constexpr int x = 10; // 编译时常量
const int y = x;      // y 是运行时常量，但其值在编译时已知
```


##### 5. 总结
- 使用 `const` 定义运行时常量或不可修改的变量。
- 使用 `constexpr` 定义编译时常量或编译时可计算的函数。
- 在需要编译时计算的场景（如模板元编程、数组大小定义等），优先使用 `constexpr`。
  
### char_16t char_32t
- 用来支持unicode字符的表示，其中char_32t可以表示所有unicode字符
- wchar_t 没有明确的指出是哪种unicode形式，导致在不同平台可能会出现不同的字节序列

### nullptr
> The keyword nullptr denotes the pointer literal. It is a prvalue of type std::nullptr_t. There exist implicit conversions from nullptr to null pointer value of any pointer type and any pointer to member type. Similar conversions exist for any null pointer constant, which includes values of type std::nullptr_t as well as the macro NULL.
- 它的类型是 std::nullptr_t
-  `using nullptr_t = decltype(nullptr);` (since C++11)
-  `sizeof(std::nullptr_t)` is equal to `sizeof(void *)`

### long long
- target type will have width of at least 64 bits

### static_assert
- performs compile-time assertion checking

```C++
int main () {
    auto f = [i](int av, int bv) -> int { return av * bv + i; };
    auto h = [i](int av, int bv) -> int { return av * bv + i; };
    static_assert(!std::is_same_v<decltype(f), decltype(h)>,
        "The type of a lambda function is unique and unnamed");
    return 0;
}
```

