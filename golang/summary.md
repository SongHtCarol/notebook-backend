# 常见问题

- [常见问题](#常见问题)
    - [**一、基础语法与特性**](#一基础语法与特性)
    - [**二、并发与协程**](#二并发与协程)
    - [**三、内存管理与 GC**](#三内存管理与-gc)
    - [**四、高级特性与设计**](#四高级特性与设计)
    - [**五、高频代码题**](#五高频代码题)

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

