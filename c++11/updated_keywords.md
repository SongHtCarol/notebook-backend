# C++11 含义变化的关键字

---

### auto
C++ 98标准/C++03标准：auto被解释为一个自动存储变量的关键字，也就是申明一块临时的变量内存。
C++11：auto被解释为自动推倒变量类型

### class
#### default
[详解博客](https://blog.csdn.net/sevenjoin/article/details/88314531)

在C++中约定，如果定义了一个带参数的构造函数，则不生成默认的构造函数。而在继承里面，派生类只能调用基类的默认构造函数不能调用自定义的构造函数。如果想编译通过：1）在基类里显示定义默认构造函数，这个时候可以用 `A() = default` 的格式定义； 2）或者也可以在派生类里显示的调用基类里的自定义构造函数

`default` 关键字可以用在类的四种特殊成员函数的默认定义上。默认构造函数、析构函数、拷贝构造函数和赋值运算符。


#### delete
- 适用范围：`delete` 关键字可用于任何函数，不仅仅局限于类成员函数
- 作用是禁止使用

#### override
在成员函数声明或定义中， `override` 确保该函数为虚函数并覆写来自基类的虚函数。

#### final
- 阻止从类继承
- 阻止对虚函数重载

### extern
范围比较小的`include`，`include`是引入整个文件，`extern`是指定的全局变量或者函数。

```C++
// fileA
int i = 1;
int j;
int func(int x) {}

//fileB
extern int i;
extern int j;
// extern int func(int x);

#include <iostream>

int main()
{
    // extern int i;
    std::cout << "extern i ="<< i << std::endl;
    std::cout << "extern j ="<< j << std::endl;

    int i = 5;
    std::cout << "new i ="<< i << std::endl;
    int j = 10;
    std::cout << "new j ="<< j << std::endl;
    return 0;
}
```


### inline

- 内联命名空间
- 空间外不需要使用using语句就可以直接访问该命名空间内的内容
- 第一次用inline后，后面的同名namespace可以不加inline，隐式内联（但不建议，编译检查会报warning）


```C++
#include <iostream>

namespace level1
{
    inline namespace level2
    {
        class TestInline1
        {
        public:
            TestInline1()
            {
                std::cout << "TestInline1" << std::endl;
            }
        };
    }

    namespace level2
    {
        class TestInline2
        {
        public:
            TestInline2()
            {
                std::cout << "TestInline2" << std::endl;
            }
        };
    }

    void test_inline()
    {
        TestInline1 in1;
        TestInline2 in2;
    }
}

int main()
{
    level1::TestInline1 in1;
    level1::TestInline2 in2;
    return 0;
}
```

### mutable
- 用来修改const函数中的不可修改类成员的缺陷

```C++
#include <iostream>

namespace testmutable
{
    class TestM
    {
    public:
        void func() const
        {
            std::cout << count << std::endl;

            count++;
        }

    private:
        mutable int count = 0;
    };
}

int main()
{
    testmutable::TestM m;
    m.func();
    m.func();
    m.func();
    return 0;
}
```

### sizeof
- C++ 98标准，sizeof只对静态成员或者实例的成员对象才能操作
- C++11 对非静态成员也可以使用

```C++
#include <iostream>


struct A {public: int b; static int c;};


int main()
{
    A a;

    std::cout << sizeof(a) << std::endl;
    std::cout << sizeof(A) << std::endl;
    std::cout << sizeof(A::b) << std::endl;
    std::cout << sizeof(A::c) << std::endl;
    // std::cout << sizeof(void) << std::endl; // 报错
    return 0;
}
```

### struct
- declaration of a compound type
- declaration of a scoped enumeration type (since C++11)

```C++
struct Foo; // forward declaration of a struct
 
struct Bar  // definition of a struct
{
    Bar(int i) : i(i + i) {}
 
    int i;
};
 
enum struct Pub // scoped enum, since C++11
{
    b, d, p, q,
};
 
int main()
{
    Bar Bar(1);
    struct Bar Bar2(2); // elaborated type
}
```

### using
- using-directives for namespaces and using-declarations for namespace members
- using-declarations for class members
- using-enum-declarations for enumerators(since C++20)
- type alias and alias template declaration(since C++11)
