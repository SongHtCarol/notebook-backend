# 微服务架构

- [微服务架构](#微服务架构)
    - [分布式设计目标](#分布式设计目标)
    - [常见的分布式设计实践](#常见的分布式设计实践)
      - [全局ID生成](#全局id生成)
        - [UUID](#uuid)
        - [ID生成表](#id生成表)
        - [Snowflake](#snowflake)
        - [结合缓存方案](#结合缓存方案)
      - [数据分布方式](#数据分布方式)
        - [哈希取模分配](#哈希取模分配)
        - [一致性哈希](#一致性哈希)
        - [路由表](#路由表)
    - [微服务架构的几个重要问题](#微服务架构的几个重要问题)
    - [服务注册](#服务注册)
    - [服务治理](#服务治理)
    - [RPC框架服务通信](#rpc框架服务通信)
      - [网络通信问题](#网络通信问题)
        - [TCP连接：三次握手（syn，seq，sck）](#tcp连接三次握手synseqsck)
        - [I/O模型](#io模型)
      - [传输协议问题](#传输协议问题)
      - [序列化和反序列化问题](#序列化和反序列化问题)
    - [系统监测](#系统监测)
      - [CPU负载](#cpu负载)
      - [快速分析出CPU性能瓶颈](#快速分析出cpu性能瓶颈)
      - [定位和处理内存泄漏问题](#定位和处理内存泄漏问题)

---
### 分布式设计目标
- 一致性: 多副本数据上的一组读写策略
- 可用性: 可用性代表系统不间断地提供服务的能力。
  - 度量可用性
    - 可靠性使用平均无故障时间（MTBF）来度量
    - 可维护性使用平均可修复时间（MTTR）来度量
    - 可用性 = MTBF / （MTBF + MTTR）
    - 可用性通常有6个9的说法，代表年平均故障修复时间为32秒。
  - 实现可用性的途径
    - 冗余设计 => 减少单点故障
    - 限流设计 => 自身实例的负载能力，拒绝服务/服务降级/优先级请求/弹性伸缩
- 分区容错性
  - 正确进行网络分区，同时保证数据一致性。
  - 提高分区容错性的办法：将数据复制到多个节点上。
  - 自动完成故障切换：过半票决
- 可扩展性
  - 可以通过使用更多的机器来获取更高的系统总吞吐量以及更好的性能。

### 常见的分布式设计实践
#### 全局ID生成
##### UUID
- 构成
  - 当前日期和时间
  - 时钟序列
  - 全局唯一的IEEE机器识别号。如果有网卡，从网卡MAC地址获取，否则以其他方式获取
- 优点
  - 简单、易用
- 缺点
  - 占用空间大
  - 字符串本身无法加工，可读性不强

##### ID生成表
- Flicker案例
  - 采用MySQL自增ID机制
  - 使用mysql独特语法`REPLACE INTO`

##### Snowflake
> - [github地址](https://github.com/twitter-archive/snowflake)

- 生成64位ID
- 构成
  - 41位的时间序列（精确到毫秒，41为长度可以用69年）
  - 10位的机器标识（10位支持最多部署1024个节点）
  - 12位的计数顺序号（每个节点每毫秒产生4096个ID序号）
- 优点
  - 高性能，低延迟
  - 独立部署
  - 按时间有序
- 缺点
  - 需要独立开发和部署

##### 结合缓存方案
- 在ID生成器和客户端之间放一层缓存，提高性能
- 优点：高性能，低延迟
- 缺点：ID不连贯，也可能浪费ID

#### 数据分布方式
##### 哈希取模分配
- id分布不均匀，可能出现计算/存储倾斜的问题
##### 一致性哈希
- 按照常用的hash算法将对应的key哈希到一个具有2^32个桶空间中
- 可以任意动态添加、删除节点。每次添加或者删除一个节点仅会影响一致性哈希环上的相邻节点。
- 常见的改进办法：引入虚拟节点，解决平衡性问题
##### 路由表
- 需要全局计算的节点

### 微服务架构的几个重要问题
- 微服务的边界划分：分的过细，服务数量多，运维成本高，调用链路复杂。 分的过粗，随着业务复杂度上升，将变成一个庞大的单体应用
- 保持数据一致性：各服务可能使用不用的数据库，包括关系型，非关系型。需要保持数据一致/最终一致
- 持续集成和持续部署

### 服务注册
环境：开发机、基础环境（docker）、正式环境
一个新服务的部署： 
- 注册服务名称，语言，编译方式，编译脚本，编译文件目录等
- 申请机器资源（指定idc，核数，实例个数）
- 服务扩容

### 服务治理
- 面对大流量冲击时，系统应该如何限流
- 当服务被拖垮时，系统应该如何自治
- 当有多个服务时，该如何进行链路追踪
- 如何监控服务自身和宿主机器

### RPC框架服务通信
Server和Client端 属于两个进程
核心原理：客户端和服务端按照约定的通信协议进行序列化网络通信
#### 网络通信问题
##### TCP连接：三次握手（syn，seq，sck）
##### I/O模型
- 同步阻塞I/O：在客户端发送请求后，该请求会在内核中阻塞住，直到服务端的响应数据到来后才进行后续处理
  - 适用并发量不大，需要及时响应的场景
  - 如：阻塞socket
- 同步非阻塞I/O：在客户端每次发送请求时，在内核空间控，该请求即使没有等到响应数据也不会阻塞住，会继续往下执行。需要频繁地轮训，很耗CPU资源。
  - 适用并发量不大，不需要及时响应的场景
  - 如：非阻塞socket
- I/O多路复用：在客户端每次发送请求时，服务端不需要每次创建对应的线程去处理，而是通过I/O多路复用技术将多个I/O通道复用在一个复用器上。这样可以实现单线程同时处理多个客户端的请求，提升系统整体性能
  - 适用高并发场景
  - 如：select、poll、epoll
- 异步非阻塞I/O：客户端在发起一个I/O操作后，不需要等待直接返回。等I/O操作完成之后，操作系统内核会主动通知客户端数据已经准备好了。
  - 高性能高并发，且请求消耗比较重的场景
  - 涉及到signal

#### 传输协议问题
都是一种数据传输契约，涉及到数据编码，数据解码
  - HTTP协议
  - Thrift协议
  - 基于protobuf实现的RPC框架

#### 序列化和反序列化问题
  - 序列化：将对象转换为字节序列（网络传输使用的是字节序例形式，传输效率高）
  - 反序列化：将字节序列恢复成对象
  - 常用的序列化方式
    - JSON/XML 格式的序列化
    - 二进制序列化
  - 选择序列化方式需要考虑
    - 是否支持更多的数据结构
    - 是否具备跨语言特性，即在Java中和C语言中的序列化方式是一样的。或者C++服务调用python服务
    - 在性能上是否有足够多的考量

### 系统监测
#### CPU负载
CPU上下文切换
- 进程上下文切换：进程是资源拥有的基本单位。
  - 在某个进程执行终止释放了CPU后，会从就绪队列中取出下一个等待的进程去执行
  - CPU时间片用完后，进程会被挂起
  - 进程遇到系统资源不足时，会被挂起
  - 进程在调用sleep()函数后会被挂起，被唤醒后再重新被调度
  - 优先级更高的进程可以插队进来被调度
  - 发生硬件中断时，进程会被挂起，执行内核中的中断程序
- 线程上下文切换：线程是调度的基本单位。同一个进程内的两个线程的切换，需要切换线程的私有数据、寄存器等部共享的资源
- 中断上下文切换

#### 快速分析出CPU性能瓶颈
CPU性能指标
- CPU使用率
  - 用户CPU使用率：值越大，表示应用程序越繁忙
  - 系统CPU使用率：值越大，表示系统内核越繁忙
  - 等待I/O的CPU使用率：值越大，表示系统与硬件设备的交互时间越长
  - 软中断CPU使用率：值越大，表示系统发生的中断越多
  - 硬中断CPU使用率：值越大，硬中断越多
- 平均负载：平均负载等于CPU数量，表示CPU被充分利用。如果平均负载大于CPU数量，代表过载。
- 上下文切换：过多上下文切换会缩短进程真正的运行时间，使CPU成为性能瓶颈
- CPU缓存命中率

#### 定位和处理内存泄漏问题
- 内存分配和回收
  - 只读内存段：包括程序代码和一些常量。不会造成内存泄漏
  - 数据内存段：包括程序代码的全局变量和静态变量。定义时就定好了内存大小，不会造成内存泄漏
  - 栈内存段：有系统管理的。当分配的内存空间超出了栈内存定义的作用域时，系统会将其回收，不会造成内存泄漏
  - 堆内存段：使用malloc()函数动态分配内存，由程序自己管理，系统不会对这些堆内存空间进行自动回收。除非应用程序退出。所以，需要应用程序自己调用标准库中的free()函数来释放内存空间。如果没有正确释放，会造成内存泄漏。
  - 文件映射段：包括动态链接库以及共享内存。共享内存是由应用程序自己管理的，所以如果没有正确回收他们或者忘记回收，则会造成内存泄漏。
- 内存泄漏的定位和处理
  - 内存泄漏的不断积累会将系统内存资源耗尽，触发OOM结束应用程序的进程。
> 无论派生类有没有申请堆上的资源，请将父类的析构函数声明为virtual.谁申请，谁释放

<img src='/distributed/img/tips1.png'>
<img src='/distributed/img/tips2.png'>

- [std::unique_ptr/std::shared_ptr/std::weak_ptr](/c++11/other_features.md)