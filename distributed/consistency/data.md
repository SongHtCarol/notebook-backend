# 分布式数据一致

- [分布式数据一致](#分布式数据一致)
    - [分布式数据幂等性设计](#分布式数据幂等性设计)
      - [需要幂等性的场景](#需要幂等性的场景)
      - [数据库操作的幂等分析](#数据库操作的幂等分析)
      - [RESTful规范中的HTTP请求方法](#restful规范中的http请求方法)
      - [如何避免重复提交？](#如何避免重复提交)
    - [分布式数据同步方法](#分布式数据同步方法)
      - [主从复制](#主从复制)
        - [运行机制](#运行机制)
        - [半同步复制](#半同步复制)
        - [多主复制](#多主复制)
          - [多主复制模式的优势](#多主复制模式的优势)
          - [不可忽视的问题：多主复制的写冲突问题](#不可忽视的问题多主复制的写冲突问题)
        - [无主复制](#无主复制)
          - [“什么时候解决数据冲突？”](#什么时候解决数据冲突)
          - [“可以在读的时候解决数据冲突？”](#可以在读的时候解决数据冲突)
    - [分布式数据一致性级别](#分布式数据一致性级别)
      - [几种数据一致性](#几种数据一致性)
        - [线性一致性](#线性一致性)
        - [PRAM一致性](#pram一致性)
        - [顺序一致性](#顺序一致性)
        - [因果一致性](#因果一致性)
        - [CC+一致性（因果+一致性）](#cc一致性因果一致性)
        - [弱一致性](#弱一致性)
        - [最终一致性](#最终一致性)
    - [分布式数据共识算法](#分布式数据共识算法)
      - [共识算法特征](#共识算法特征)
      - [”拜占庭将军问题“](#拜占庭将军问题)
      - [一致性解决方案](#一致性解决方案)

---

### 分布式数据幂等性设计
> 用户对于同一个操作发起一次请求或多次请求，得到的结果都是一样的，不会因为请求多次而出现异常现象

#### 需要幂等性的场景
- 用户重试：用户多次请求，比如重读点击页面上的按钮
- 系统重试：网络异常，由于网络异常导致在一定时间内未返回调用成功的信息，触发了框架层的重试机制
- 页面回退后，再次提交的动作
- 程序上的重试机制

#### 数据库操作的幂等分析
- C：Create => 不具备幂等性
- R：Read => 天然幂等
- U：Update => 带有计算型的更新非幂等，反之天然幂等
- D：Delete => 天然幂等

#### RESTful规范中的HTTP请求方法
- C：POST => 不具备幂等性
- R：Get => 天然幂等
- U：PUT => 替换资源，天然幂等
- D：Delete => 天然幂等

#### 如何避免重复提交？
- 利用全局唯一ID防止重复提交
- 利用 Token + Redis 机制防止重复提交

### 分布式数据同步方法
#### 主从复制
主服务器记录写操作的更新，然后再将该操作传递到其它所有服务器。
##### 运行机制
- 主节点接收客户端的写请求，在本地执行完毕后，向其它节点发送该操作指令。写操作请求只能向主节点发送。
- 从节点收到来自主节点的写操作指令，执行该操作，并且保证按照与主节点相同的顺序执行写操作
- 主从节点都可以接受执行读操作指令

主从复制即可以是同步复制，也可以是异步复制。区别仅仅在于变更传播的时间。
##### 半同步复制
某个从节点是同步复制，其他从节点是异步复制。

##### 多主复制
多个主节点处理写操作，处理写操作的每个主节点都要把写请求指令传送到其它所有的节点。在每个主节点处理写操作请求的视角中，其它所有节点都是自己的从节点，同时自己也是其他主节点的从节点。

###### 多主复制模式的优势
- 负载均衡：比单个节点接受更多的写流量。通常客户端会从多个主节点中选择一个来发送写请求，然后将这些更新异步地传播到其他主节点，使它们与更改保持同步，并使系统最终保持一致。
- 避免单点故障：一个主节点崩溃，另外的主节点可以继续无缝地处理写请求，集群可以继续工作
- 跨地理分布数据服务的低延迟：如果使用主从复制，当数据库的客户端分布在不同地理位置的时候，写延迟会急剧增加，因为所有地理位置上的客户端的所有写操作都必须到达主节点所在的这个区域。多主复制模式，主节点驻留在离客户端更近的区域，当客户端发出写请求时，请求可以由最近的主节点提供良好的数据服务。

###### 不可忽视的问题：多主复制的写冲突问题
解决办法
- 从根源上杜绝冲突。将不同区域的数据存储到不同的数据中心，基本等价于主从复制。但是无法解决数据中心实效的问题。
- 冲突发生后使用策略使数据达成一致。比如：最后写入者获胜，每个写操作请求会被分配一个全局唯一的可先后排序的ID，一般采用时间戳或者随机数。或者data version也可以。

##### 无主复制
###### “什么时候解决数据冲突？”
主从复制和多主复制都是在数据写入的时候就去解决数据冲突。但用户在做写操作的时候，等待系统响应的时间会很久。

###### “可以在读的时候解决数据冲突？”
无主复制处理写请求时会采用 Quorum 协议。
- Quorum 协议有两个配置参数：执行一次读操作所需的最少参与者R，以及执行一次写操作所需的最少参与者W。集群中的节点数为N
- Quorum 协议要求：R + W > N

N 一般不会太大，且通常为一个奇数。
无主复制方案一般要求参与写请求的节点数和参与读请求的节点数 W = R = （N/2）+1；（向上取整）
此时处理写请求的时间

### 分布式数据一致性级别
几种数据同步方法，最直观的区别是数据不一致的窗口和提供数据服务的读写效率差异。造成这些差异的根本原因是在这些数据同步方法中分别应用了不同级别的数据一致性。

#### 几种数据一致性
##### 线性一致性
最高级别的数据一致性。也称为严格一致性，原子一致性，强一致性。
在线形一致中，所有客户端对数据服务系统的访问都会得到统一的结果，不会出现数据复制滞后的问题。
优点是保证了读取数据的正确性。
缺点是数据服务的读写延迟高。

特点：
- 存在一个合法的操作总顺序。合法事指读操作总能看到最近一次的写操作。
- 所有操作都遵循实时的顺序，操作A在操作B开始之前完成，则在总顺序中，A一定在B之前。
- 一次已完成的写操作将被之后发生的所有读操作看到
- 一旦某个读操作看到了一个值，所有在该读操作之后的其他读操作也必须返回相同的值。直到有新的写操作发生。

##### PRAM一致性
等价于同时实现 read your writes, monotonic writes, monotonic reads 三种一致性级别
-  read your writes：表示如果一个进程执行了一个写操作w，然后该进程执行了一个后续的读操作r，那么r必须观察w的效果
- monotonic writes：表示如果一个进程执行写操作w1，然后执行写操作w2，那么所有进程都在w2之前观察到w1
- monotonic reads：表示如果进程执行读操作r1，然后执行读操作r2，那么r2不能观察到r1种反映的写操作之前的状态。读操作是不能倒退的。

##### 顺序一致性
是具有全局顺序的PRAM一致性。
在实现 顺序一致性 的存储系统上，所有操作在所有副本上都以相同的顺序进行序列化，并且保留每个进程确定的操作顺序。顺序一致性可以拆解出以下几个属性：
- SingleOrder：分布式系统中存在一种全局顺序
- PRAM：保留由同一进程调用的操作的实时排序
- RVal：约束返回值的一致性
顺序一致性不保证跨进程的全局顺序，只保证单个进程内的顺序。

##### 因果一致性
因果一致性会捕获操作之间潜在的因果关系，与因果关系相关的操作应该在所有流程中以相同的顺序出现。但是没有因果关系的操作顺序可能并不会统一。
如：社交网络中，更新访问权限操作是更新相册内容的因。更新访问权限操作和更新相册内容操作大概率在执行时不会在一个进程中，如果使用PRAM一致性则不会满足这种因果关系。
因果一致性模型的定义如下：
- Li：进程Pi的本地执行历史
- O1 > O2：进程Pi上的操作O1在对应一致性模型中的偏序关系中先于O2执行
- H：更进程本地执行历史的集合L1，L2，...Ln

对于因果一致性模型，和PRAM一致性模型一样，每个进程内部拥有自己的执行顺序历史，该历史在所有进程之间不会统一。但是所有具有潜在因果关系的操作一定是具有全局顺序的。

对于并发的操作，两个操作之间并不存在因果关系，因此两个操作在不同节点的执行下可能存在乱序的情况。即使遵循了因果关系，但由于并发依然会乱序。

##### CC+一致性（因果+一致性）
在因果一致性的基础上额外增加了收敛策略。可以避免数据出现不一致的情况。有一些简单的冲突解决策略，比如版本号机制。
版本号一般会产生以下两个问题
- 如果使用武力时间作为版本号，那么同一时间很可能会有很多个操作的版本号相同。解决办法是版本号在时间戳上再添加ID之类的唯一数值 <time, ID>来 消除歧义
- 分布式系统中每个数据中心的时间很难实现精准地同步，常见的解决方式是使用lamport clock：
  - 每个服务器保存一个Tmax：这是每个服务器目前从所有地方看到的最高版本号
  - 当它需要使用版本号时，会根据max（Tmax+1，real time）的方式计算版本号

##### 弱一致性
弱一致性系统不能保证读取返回最近写入的值。典型的用例是可以跨Web应用程序的各个层应用的宽松缓存策略，甚至是在Web浏览器中实现的缓存。

##### 最终一致性
如果没有对给定数据项进行新的更新，则最终对该数据项的所有访问都将返回最后更新的值。
最终一致性三个重要的性质：
- Eventual Delivery：在正确副本上的一次更新最终会被传递到所有的副本上
- Convergence：传递了相同更新的正确副本最终达到等效状态
- Termination：所有方法终止执行

### 分布式数据共识算法
共识算法是比一致性更宽泛的概念。共识算法不仅专注数据层面，而且指分布式系统中多个节点对彼此的状态达成一致结果的过程，比如：
- 节点时间上的共识，以保证事件发生顺序。可以采用逻辑时钟或者容忍物理时钟漂移的方式实现。
- 互斥性的共识，以决定节点对数据的使用权。
- 协调者的共识，以决定哪个节点是领导者。

#### 共识算法特征
- Termination：所有正确的进程最终都会决定某个值
- Integrity：如果所有正确的进程都提出了相同的值，那么任何正确的进程都必须决定该值
- Agreement：所有正确的过程都决定相同的值

#### ”拜占庭将军问题“
> - [The Byzantine Generals Problem](https://dl.acm.org/doi/pdf/10.1145/357172.357176)


CFT共识算法：可以处理非拜占庭错误的情况，如 网络/磁盘故障、服务器宕机。如果节点做出篡改数据等违背共识原则的行为，算法将无法保障系统的安全性。Paxos、Raft等都属于CFT共识算法。
BFT共识算法：可以处理非拜占庭错误的情况，也可以处理部分节点出现拜占庭错误的情况，常被用于区块链系统。PBFT算法、PoW算法都属于BFT共识算法。

#### 一致性解决方案
- [Paxos](/distributed/consensus_algorithm/paxos/basic.md)
- [Raft](/distributed/consensus_algorithm/raft/basic.md)
- 2PC: 同步先确保通知到所有节点再写入，性能瓶颈很容易出现在主节点上
- 3PC: 相比于2PC，降低了事务失败回滚的概率，但是增加了数据不一致的风险，以及增加了事务延迟
- Lease机制: 由授权者授予分布式环境一段时间内的承诺。针对网络拥塞或瞬断的情况下，Lease机制可以进一步处理双主脑裂的情况
- Quorum NWR
  - N-同一份数据的拷贝份数；W-更新一个数据对象的时候需要确保成功更新的份数；R-读取一个数据需要读取的拷贝的份数
  - `W>N/2`;`W+R>N`
  - 写操作要确保成功的份数高于一份数据拷贝总份数的一半
  - 写操作加上读操作的总份数要高于同一份数据拷贝的总份数
  - 例子: TFS(TaoBao File System) 采取N=3，W=3的配置策略
    <table>
        <tr>
            <th>N</th>
            <th>W</th>
            <th>R</th>
            <th>说明</th>
        </tr>
        <tr>
            <td>1</td>
            <td></td>
            <td></td>
            <td>N=1，单点问题，无法满足高可用</td>
        </tr>
        <tr>
            <td>2</td>
            <td></td>
            <td></td>
            <td>一个节点宕掉后，仍然是单点</td>
        </tr>
        <tr>
            <td>3</td>
            <td>2，3</td>
            <td>1，2，3</td>
            <td>读越大，读性能越差；写越大，写性能越差</td>
        </tr>
        <tr>
            <td>4</td>
            <td></td>
            <td></td>
            <td>服务器节点成本高</td>
        </tr>
    </table>
- MVCC(多版本并发控制)
  - 不同数据库对MVCC的具体实现有差异
  - MySQL的InnoDB：`create version` `delete version`
    - 插入时记录`create version`
    - 更新时先将旧记录标记删除，记录`delete version`，然后插入一行新记录`create version`加一
    - 删除时记录`delete version`
- Gossip: 一种去中心化、容错而又最终一致性的算法
  - Gossip协议的主要用途就是信息传播和扩散：即把一些发生的事件传播到全世界。它们也被用于数据库复制，信息扩散，集群成员身份确认，故障探测等。
  - 基于Gossip协议的一些有名的系统：Apache Cassandra，Redis（Cluster模式），Consul等。
  - 传播时间收敛在O(Log(N))以内，N是节点数量
