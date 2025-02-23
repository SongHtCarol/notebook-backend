# 常见问题

- [常见问题](#常见问题)
    - [**一、基础语法与特性**](#一基础语法与特性)
    - [**二、并发与协程**](#二并发与协程)
    - [**三、内存管理与 GC**](#三内存管理与-gc)
    - [**四、高级特性与设计**](#四高级特性与设计)
    - [**五、高频代码题**](#五高频代码题)
  - [interface](#interface)
    - [**一、接口的基本概念**](#一接口的基本概念)
      - [1. **定义接口**](#1-定义接口)
    - [**二、接口的实现**](#二接口的实现)
      - [1. **隐式实现**](#1-隐式实现)
      - [2. **多接口实现**](#2-多接口实现)
      - [3. **使用接口**](#3-使用接口)
    - [**二、空接口（`interface{}`）**](#二空接口interface)
      - [1. **空接口**](#1-空接口)
      - [2. **空接口的应用**](#2-空接口的应用)
    - [**三、接口的组合**](#三接口的组合)
    - [**四、接口的隐式实现**](#四接口的隐式实现)
    - [**五、接口的 `nil` 值**](#五接口的-nil-值)
    - [**六、接口的实际应用**](#六接口的实际应用)
      - [1. **标准库中的应用**](#1-标准库中的应用)
      - [2. **依赖注入**](#2-依赖注入)
      - [3. **多态**](#3-多态)
      - [4. **类型断言与类型转换**](#4-类型断言与类型转换)
    - [**七、接口的底层表示**](#七接口的底层表示)
    - [**八、接口与 `nil` 的陷阱**](#八接口与-nil-的陷阱)
    - [**九、最佳实践**](#九最佳实践)
    - [**十、常见接口示例**](#十常见接口示例)
      - [1. **`error` 接口**](#1-error-接口)
      - [2. **`fmt.Stringer` 接口**](#2-fmtstringer-接口)
    - [**总结**](#总结)
  - [context](#context)
    - [1. **Context 的作用**](#1-context-的作用)
    - [2. **Context 的核心接口**](#2-context-的核心接口)
    - [3. **创建 Context**](#3-创建-context)
      - [（1）`context.Background()`](#1contextbackground)
      - [（2）`context.TODO()`](#2contexttodo)
      - [（3）`context.WithCancel(parent Context)`](#3contextwithcancelparent-context)
      - [（4）`context.WithTimeout(parent Context, timeout time.Duration)`](#4contextwithtimeoutparent-context-timeout-timeduration)
      - [（5）`context.WithDeadline(parent Context, d time.Time)`](#5contextwithdeadlineparent-context-d-timetime)
      - [（6）`context.WithValue(parent Context, key, val interface{})`](#6contextwithvalueparent-context-key-val-interface)
    - [4. **使用 Context**](#4-使用-context)
      - [（1）取消操作](#1取消操作)
      - [（2）超时控制](#2超时控制)
      - [（3）传递值](#3传递值)
    - [5. **Context 的注意事项**](#5-context-的注意事项)
    - [6. **Context 的应用场景**](#6-context-的应用场景)
    - [总结](#总结-1)

---

### **一、基础语法与特性**
1. **Go 语言的特点是什么？**  
   - 简洁高效，编译速度快  
   - 内置并发支持（Goroutine 和 Channel）  
   - 垃圾回收（GC）  
   - 强类型 + 鸭子类型接口（隐式接口实现）  
   - 不支持继承，通过组合实现复用  

2. **值传递 vs 引用传递**  
   - Go **只有值传递**，但可以通过指针（`*T`）或引用类型（Slice/Map/Channel）实现类似引用传递的效果。  
   - 示例：  
     ```go
     func modifySlice(s []int) { s[0] = 100 } // 修改会反映到原 Slice
     func modifyInt(x int) { x = 200 }        // 原值不变
     ```

3. **Slice 和 Array 的区别**  
   - **Array**：固定长度，值类型（赋值时会拷贝整个数组）。  
   - **Slice**：动态长度，底层引用数组（包含指针、长度、容量）。  
   - 示例：  
     ```go
     arr := [3]int{1, 2, 3} // Array
     sli := arr[:]          // Slice（引用 arr 的底层数组）
     ```

4. **`defer` 的执行顺序**  
   - `defer` 语句按**后进先出（LIFO）**顺序执行，在函数返回前执行。  
   - 注意：`defer` 的参数在声明时求值，但函数体延迟执行。  
     ```go
     func main() {
         defer fmt.Println("1") // 第三个输出
         defer fmt.Println("2") // 第二个输出
         fmt.Println("3")       // 第一个输出
     }
     ```


### **二、并发与协程**
1. **Goroutine 和线程的区别**  
   - **轻量级**：Goroutine 初始栈大小 2KB（线程通常 1MB+）。  
   - **调度方式**：Go 运行时调度（协作式/抢占式），线程由 OS 调度。  
   - **通信机制**：Goroutine 通过 Channel 通信，线程依赖共享内存 + 锁。

2. **Channel 的底层实现与使用场景**  
   - **底层**：基于环形队列的同步通信（带锁）。  
   - **类型**：  
     - 无缓冲 Channel：同步阻塞（发送和接收必须同时就绪）。  
     - 有缓冲 Channel：异步（缓冲区满时发送阻塞）。  
   - 示例：  
     ```go
     ch := make(chan int, 3) // 缓冲区大小为 3
     ch <- 1                // 不阻塞
     ```

3. **如何实现 Goroutine 同步？**  
   - **WaitGroup**：等待一组 Goroutine 完成。  
     ```go
     var wg sync.WaitGroup
     wg.Add(2)
     go func() { defer wg.Done() }()
     go func() { defer wg.Done() }()
     wg.Wait()
     ```
   - **Channel**：通过关闭 Channel 或发送信号。  
   - **Mutex**：保护共享资源（`sync.Mutex` 或 `sync.RWMutex`）。

4. **什么是 GMP 调度模型？**  
   - **G**（Goroutine）：任务单元。  
   - **M**（Machine）：系统线程。  
   - **P**（Processor）：逻辑处理器（管理本地 Goroutine 队列）。  
   - 调度流程：P 从队列获取 G，绑定到 M 上执行。当 G 阻塞时，M 会解绑 P 并创建新 M。


### **三、内存管理与 GC**
1. **Go 的垃圾回收机制**  
   - **三色标记法**：  
     1. 初始标记（STW）：标记根对象。  
     2. 并发标记：遍历对象图。  
     3. 重新标记（STW）：修正并发期间的变动。  
     4. 并发清除。  
   - 优化：写屏障（Write Barrier）减少 STW 时间。

2. **如何避免内存泄漏？**  
   - 及时关闭未使用的 Channel 和 Goroutine。  
   - 避免全局变量持有大量数据。  
   - 使用 `pprof` 工具检测内存使用。


### **四、高级特性与设计**
1. **接口（Interface）的隐式实现**  
   - 接口通过方法集合隐式实现，无需显式声明。  
   - 示例：  
     ```go
     type Writer interface { Write([]byte) (int, error) }
     type MyWriter struct{}
     func (w MyWriter) Write(data []byte) (int, error) { ... } // 隐式实现 Writer
     ```

2. **Context 的作用**  
   - 传递请求上下文（如超时、取消信号）。  
   - 示例：  
     ```go
     ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
     defer cancel()
     ```

3. **如何实现深拷贝？**  
   - 使用 `encoding/json` 或 `encoding/gob` 序列化与反序列化。  
   - 手动递归拷贝结构体字段。


### **五、高频代码题**
1. **用 Channel 实现生产者-消费者模型**  
   ```go
   func main() {
       ch := make(chan int, 10)
       // 生产者
       go func() {
           for i := 0; i < 10; i++ {
               ch <- i
           }
           close(ch)
       }()
       // 消费者
       for num := range ch {
           fmt.Println(num)
       }
   }
   ```

2. **反转字符串**  
   ```go
   func reverse(s string) string {
       runes := []rune(s)
       for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
           runes[i], runes[j] = runes[j], runes[i]
       }
       return string(runes)
   }
   ```

## interface
在 Go 语言中，**接口（interface）** 是一种定义方法集合的类型，用于实现多态和代码解耦。接口的核心思想是 **鸭子类型（Duck Typing）**，即只要某个类型实现了接口定义的所有方法，就被视为实现了该接口，无需显式声明。**interface**是一种抽象类型，用于定义对象的行为规范。它通过方法签名描述对象能做什么，而不关心对象的具体实现。接口是 Go 实现多态和灵活设计的核心机制。以下是接口的详细说明及示例：


### **一、接口的基本概念**
#### 1. **定义接口**
接口通过一组方法签名定义，任何实现了这些方法的类型都隐式满足该接口。
```go
type Animal interface {
    Speak() string
    Move() string
}
```
方法无需具体实现：
```go
type Writer interface {
    Write(data []byte) (int, error)  // 方法签名：名称、参数、返回值
}
```

### **二、接口的实现**
#### 1. **隐式实现**
Go 的接口实现是隐式的：**只要类型实现了接口的所有方法，即视为实现了该接口**。无需显式声明（如 Java 的 `implements` 关键字）。
类型无需显式声明实现接口，只需定义接口中的方法即可。
```go
type Dog struct{}

func (d Dog) Speak() string {
    return "Woof!"
}

func (d Dog) Move() string {
    return "Run"
}
```
```go
type File struct{}

func (f File) Write(data []byte) (int, error) {
    return len(data), nil
}

// File 自动实现 Writer 接口
var _ Writer = File{}  // 编译时验证
```

#### 2. **多接口实现**
一个类型可实现多个接口：
```go
type ReadWriter interface {
    Reader  // 接口组合
    Writer
}

type Socket struct{}

func (s Socket) Read(data []byte) (int, error)  { /* ... */ }
func (s Socket) Write(data []byte) (int, error) { /* ... */ }

// Socket 同时实现 Reader 和 Writer 接口
```

#### 3. **使用接口**
将具体类型赋值给接口变量，通过接口调用方法。
```go
func main() {
    var a Animal = Dog{}
    fmt.Println(a.Speak()) // 输出 "Woof!"
    fmt.Println(a.Move())  // 输出 "Run"
}
```

### **二、空接口（`interface{}`）**
#### 1. **空接口**
空接口可以接受任意类型的值，常用于需要处理未知类型的场景（如泛型容器）。
```go
func printAnything(v interface{}) {
    fmt.Println(v)
}

func main() {
    printAnything(42)        // 输出 42
    printAnything("hello")   // 输出 "hello"
    printAnything(Dog{})     // 输出 {}
}
```
#### 2. **空接口的应用**
- **泛型容器**：存储任意类型数据（如 `[]interface{}`）。
- **反射**：结合 `reflect` 包动态处理类型。



### **三、接口的组合**
通过嵌套接口实现方法组合，增强代码复用性。
```go
type Speaker interface {
    Speak() string
}

type Mover interface {
    Move() string
}

// 组合接口
type Animal interface {
    Speaker
    Mover
}
```


### **四、接口的隐式实现**
- **隐式实现的优点**：
  - 类型无需显式绑定接口，减少代码耦合。
  - 可灵活为已有类型添加接口支持。
- **潜在问题**：
  - 若接口方法签名变更，所有实现类型需同步修改，否则编译报错。


### **五、接口的 `nil` 值**
接口变量的零值为 `nil`，但只有当接口的 **动态类型和动态值均为 `nil`** 时，接口变量才为 `nil`。
```go
func main() {
    var a Animal          // 此时 a 是 nil
    var d *Dog            // d 是 nil（指针）
    a = d                 // a 的动态类型是 *Dog，动态值是 nil，因此 a != nil
    fmt.Println(a == nil) // 输出 false
}
```


### **六、接口的实际应用**
#### 1. **标准库中的应用**
- `io.Reader` 和 `io.Writer`：用于输入输出操作。
  ```go
  func readData(r io.Reader) {
      data, _ := ioutil.ReadAll(r)
      fmt.Println(string(data))
  }
  ```

#### 2. **依赖注入**
通过接口解耦依赖，提高代码可测试性。
```go
type Database interface {
    GetData() string
}

type MySQL struct{}

func (m MySQL) GetData() string {
    return "Data from MySQL"
}

func processData(db Database) {
    fmt.Println(db.GetData())
}
```
#### 3. **多态**
通过接口统一处理不同具体类型：
```go
func Save(w Writer, data []byte) error {
    _, err := w.Write(data)
    return err
}

// 可传入 File、网络连接等实现 Writer 的类型
Save(File{}, []byte("data"))
```

#### 4. **类型断言与类型转换**
- **类型断言**：检查接口值的实际类型：
  ```go
  var val interface{} = "hello"
  s, ok := val.(string)  // ok=true 时，s 为字符串
  ```
  
- **类型选择（Type Switch）**：
  ```go
  switch v := val.(type) {
  case int:
      fmt.Println("int:", v)
  case string:
      fmt.Println("string:", v)
  default:
      fmt.Println("unknown type")
  }
  ```


### **七、接口的底层表示**
接口在底层由两个指针组成：
- **动态类型（Type）**：指向具体类型的元数据。
- **动态值（Value）**：指向实际数据的指针。

```go
var w Writer = File{}
```
---

### **八、接口与 `nil` 的陷阱**
- **接口为 `nil` 的条件**：动态类型和动态值均为 `nil`。
- **常见错误**：
  ```go
  var w Writer  // 接口类型和值均为 nil，w == nil

  var f *File
  w = f         // 动态类型为 *File，动态值为 nil，此时 w != nil
  ```

---

### **九、最佳实践**
1. **定义小接口**：如 `io.Reader` 和 `io.Writer` 只含单一方法，易于复用。
2. **避免过度抽象**：仅在需要多态或解耦时使用接口。
3. **优先组合**：通过接口组合扩展功能，而非继承。

---

### **十、常见接口示例**
#### 1. **`error` 接口**
所有错误类型均需实现 `Error()` 方法：
```go
type error interface {
    Error() string
}

// 自定义错误类型
type MyError struct{ Msg string }
func (e MyError) Error() string { return e.Msg }
```

#### 2. **`fmt.Stringer` 接口**
定义对象的字符串表示：
```go
type Stringer interface {
    String() string
}

type User struct{ Name string }
func (u User) String() string { return "User: " + u.Name }

fmt.Println(User{"Alice"})  // 输出：User: Alice
```

### **总结**
| **特性**       | **说明**                                      |
|----------------|-----------------------------------------------|
| 隐式实现       | 无需显式声明，方法匹配即自动实现接口          |
| 空接口         | 表示任意类型，用于泛型场景                    |
| 接口组合       | 通过嵌入复用接口方法                          |
| 类型断言       | 动态检查接口值的实际类型                      |
| 多态设计       | 统一处理不同实现，提升代码扩展性              |

## context
在 Go 语言中，`context` 是一个非常重要的包，用于管理 goroutine 的生命周期、取消信号、超时和传递请求范围的值。它通常用于控制并发操作，特别是在处理请求时，能够优雅地取消或超时 goroutine。


### 1. **Context 的作用**
`context` 的主要用途包括：
- **取消操作**：通过 `context` 传递取消信号，通知 goroutine 停止工作。
- **超时控制**：设置操作的超时时间，避免 goroutine 无限期运行。
- **传递值**：在请求范围内传递键值对数据（例如请求 ID、用户信息等）。


### 2. **Context 的核心接口**
`context` 包的核心是 `Context` 接口，定义如下：
```go
type Context interface {
    Deadline() (deadline time.Time, ok bool) // 返回上下文截止时间
    Done() <-chan struct{}                  // 返回一个 channel，用于接收取消信号
    Err() error                             // 返回上下文取消的原因
    Value(key interface{}) interface{}      // 获取上下文中的值
}
```


### 3. **创建 Context**
`context` 包提供了几种创建 `Context` 的方式：

#### （1）`context.Background()`
- 返回一个空的 `Context`，通常用作根上下文。
- 适用于主函数、初始化或测试。

```go
ctx := context.Background()
```

#### （2）`context.TODO()`
- 返回一个空的 `Context`，通常用于尚未确定上下文类型的场景。
- 与 `context.Background()` 类似，但语义上表示“待实现”。

```go
ctx := context.TODO()
```

#### （3）`context.WithCancel(parent Context)`
- 基于父上下文创建一个可取消的 `Context`。
- 返回一个新的 `Context` 和一个取消函数 `cancel`，调用 `cancel` 会取消该上下文及其子上下文。

```go
ctx, cancel := context.WithCancel(context.Background())
defer cancel() // 确保在函数退出时取消上下文
```

#### （4）`context.WithTimeout(parent Context, timeout time.Duration)`
- 基于父上下文创建一个带有超时的 `Context`。
- 超时后，上下文会自动取消。

```go
ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
defer cancel()
```

#### （5）`context.WithDeadline(parent Context, d time.Time)`
- 基于父上下文创建一个带有截止时间的 `Context`。
- 到达截止时间后，上下文会自动取消。

```go
deadline := time.Now().Add(2 * time.Second)
ctx, cancel := context.WithDeadline(context.Background(), deadline)
defer cancel()
```

#### （6）`context.WithValue(parent Context, key, val interface{})`
- 基于父上下文创建一个包含键值对的 `Context`。
- 用于在请求范围内传递数据。

```go
ctx := context.WithValue(context.Background(), "userID", 123)
```


### 4. **使用 Context**
#### （1）取消操作
通过 `context.WithCancel` 创建的 `Context` 可以手动取消 goroutine。

```go
func worker(ctx context.Context) {
    for {
        select {
        case <-ctx.Done():
            fmt.Println("Worker canceled:", ctx.Err())
            return
        default:
            fmt.Println("Working...")
            time.Sleep(500 * time.Millisecond)
        }
    }
}

func main() {
    ctx, cancel := context.WithCancel(context.Background())
    go worker(ctx)

    time.Sleep(2 * time.Second)
    cancel() // 取消 goroutine

    time.Sleep(1 * time.Second)
}
```

#### （2）超时控制
通过 `context.WithTimeout` 可以设置操作的超时时间。

```go
func worker(ctx context.Context) {
    select {
    case <-ctx.Done():
        fmt.Println("Worker timed out:", ctx.Err())
    case <-time.After(3 * time.Second):
        fmt.Println("Work done!")
    }
}

func main() {
    ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
    defer cancel()

    worker(ctx)
}
```

#### （3）传递值
通过 `context.WithValue` 可以在请求范围内传递数据。

```go
func worker(ctx context.Context) {
    if userID := ctx.Value("userID"); userID != nil {
        fmt.Println("User ID:", userID)
    } else {
        fmt.Println("User ID not found")
    }
}

func main() {
    ctx := context.WithValue(context.Background(), "userID", 123)
    worker(ctx)
}
```


### 5. **Context 的注意事项**
- **不要滥用 `context.WithValue`**：
  - `context` 的主要目的是传递取消信号和超时控制，而不是作为通用的数据存储。
  - 传递的值应该是请求范围的数据（例如请求 ID、用户信息等），而不是函数参数或全局状态。

- **确保取消函数被调用**：
  - 使用 `defer cancel()` 确保在函数退出时取消上下文，避免资源泄漏。

- **Context 是不可变的**：
  - 每次调用 `WithCancel`、`WithTimeout`、`WithValue` 等函数时，都会返回一个新的 `Context`，而不是修改原有的 `Context`。

- **避免传递 `nil` Context**：
  - 如果不知道使用哪个 `Context`，可以使用 `context.TODO()` 或 `context.Background()`。


### 6. **Context 的应用场景**
- **HTTP 请求处理**：
  - 在 HTTP 服务器中，可以使用 `context` 控制请求的超时和取消。
  - 例如，`http.Request` 的 `Context()` 方法返回请求的上下文。

- **数据库操作**：
  - 在数据库查询时，可以使用 `context` 设置超时或取消操作。

- **微服务调用**：
  - 在微服务架构中，可以使用 `context` 传递请求范围的数据（如跟踪 ID）。

- **并发任务管理**：
  - 在启动多个 goroutine 时，可以使用 `context` 统一管理它们的生命周期。


### 总结
`context` 是 Go 语言中用于管理 goroutine 生命周期、取消信号、超时和传递请求范围值的重要工具。它的核心思想是通过链式传递 `Context`，实现并发操作的控制和数据传递。正确使用 `context` 可以编写出更健壮、高效的并发程序。