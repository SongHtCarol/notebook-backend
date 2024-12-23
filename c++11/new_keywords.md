# C++11 新增的关键字
> reference: https://en.cppreference.com/w/cpp/11
- [C++11 新增的关键字](#c11-新增的关键字)
    - [decltype](#decltype)
    - [constexpr](#constexpr)
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

