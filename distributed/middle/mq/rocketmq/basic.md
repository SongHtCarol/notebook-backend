# RocketMQ

> reference   
> - [RocketMQ 官方文档](https://rocketmq.apache.org/docs/)
> - [Apache RocketMQ开发者指南](https://github.com/apache/rocketmq/blob/develop/docs/cn/README.md)

- [RocketMQ](#rocketmq)
    - [架构](#架构)
      - [部署架构](#部署架构)
      - [消息存储架构](#消息存储架构)
    - [几个概念](#几个概念)
      - [Producer](#producer)
      - [Consumer](#consumer)
      - [Topic](#topic)
      - [Offset](#offset)
        - [Offset](#offset-1)
        - [ConsumerOffset](#consumeroffset)
      - [Broker](#broker)
      - [NameServer](#nameserver)
    - [消息过滤](#消息过滤)
      - [Tag过滤](#tag过滤)
      - [属性过滤](#属性过滤)
    - [消息重试](#消息重试)
      - [重试触发条件](#重试触发条件)
      - [重试流程](#重试流程)
      - [重试间隔](#重试间隔)
      - [注意事项](#注意事项)
    - [消费重试](#消费重试)
      - [消息重试的触发条件](#消息重试的触发条件)
      - [消息重试策略主要行为](#消息重试策略主要行为)
    - [流量控制](#流量控制)
      - [触发条件](#触发条件)
      - [流控行为](#流控行为)
      - [处理建议](#处理建议)
    - [负载均衡](#负载均衡)
      - [广播消费和共享消费](#广播消费和共享消费)
      - [消费者负载均衡](#消费者负载均衡)
        - [消息粒度负载均衡](#消息粒度负载均衡)
        - [队列粒度负载均衡](#队列粒度负载均衡)

---
### 架构
#### 部署架构
<img src='/distributed/img/rocketmq.jpg'>

#### 消息存储架构
<img src='/distributed/img/rocketmq message.jpg'>

### 几个概念
#### Producer
负责生产消息，一般由业务系统负责生产消息。一个消息生产者会把业务应用系统里产生的消息发送到broker服务器。RocketMQ提供多种发送方式，同步发送、异步发送、顺序发送、单向发送。同步和异步方式均需要Broker返回确认信息，单向发送不需要。
- **Client ID**
  - the identity of a producer client. This attribute is used to distinguish between different producers. A client ID is globally unique within a cluster.
- **Communication parameters**
  - Endpoints (Required) : the endpoint used to connect to the server. This endpoint is used to identify the cluster.
  - Credential (Optional) : the credential used by the client for authentication.
  - Request Timeout (Optional) : the timeout period of the network request. 
- **Prebound topic list**
  - the list of topics to which a producer of Apache RocketMQ sends messages. Prebound topics provide the following benefits:
    - Transaction messages (Required): The prebound topic list attribute must be specified for transaction messages. 
    - Non-transaction messages (Optional): The server checks the access permissions and validity of the destination topics based on the list of prebound topics during producer initialization, instead of performing the check after the application is started. 
  - For transaction messages, prebound topics must be specified and used together with a transaction checker.
- **Transaction checker**
  - Apache RocketMQ uses a transaction messaging mechanism that requires a producer to implement a transaction checker to ensure eventual consistency of transactions. 
  - When a producer sends transaction messages, a transaction checker must be configured and used together with prebound topics

#### Consumer
负责消费消息，一般是后台系统负责异步消费。一个消息消费者会从Broker服务器拉取消息、并将其提供给应用程序。从用户应用的角度而言提供了两种消费形式：拉取式消费、推动式消费。
- **Consumer group name**
  - the name of the consumer group associated with the current consumer. Consumers inherit their behavior from the consumer groups. 
- **Client ID**
  - the identity of a consumer client. This attribute is used to distinguish between different consumers. The value must be unique within a cluster.
- **Communication parameters**
  - Endpoints (Required) : the endpoint used to connect to the server. This endpoint is used to identify the cluster.
  - Credential (Optional) : the credential used by the client for authentication.
  - Request Timeout (Optional) : the timeout period of the network request. 
- **Pre-bound subscription list**
  - the subscription list of the specified consumer. The Apache RocketMQ broker can use the pre-bound subscription list to verify the permissions and validity of the subscribed topic during consumer initialization instead of after the application is started.
- **Message listener**
  -  the listener that a consumer uses to invoke the message consumption logic after Apache RocketMQ broker pushes a message to the consumer.
  -  When you consume messages as a push consumer, you must configure the message listener on the consumer client. 

#### Topic
表示一类消息的集合，每个主题包含若干条消息，每条消息只能属于一个主题，是RocketMQ进行消息订阅的基本单位。
- **topic name**
  - the name of a topic. A topic name identifies the topic and is globally unique in a cluster.
  - Characters suggest：a~z A~Z 0~9 （）（-）（%）
  - Suggested length：1~64 characters
- **queues**
  - the actual storage unit that stores messages. A topic contains one or more queues.
  - You can specify the number of queues when you create a topic. 
  -  A topic must contain at least one queue.
- **message type**
  - the message type that is specified for a topic.
  - When you create a topic in Apache RocketMQ, select one of the following message types for the topic:
    - Normal: A normal message does not require special semantics and is not correlated with other normal messages.
    <img src='/distributed/img/rocketmq normal message.jpg'>
    - FIFO:  Apache RocketMQ uses a message group to determine the order of a specified set of messages. The messages are delivered in the order in which they are sent.
    <img src='/distributed/img/rocketmq fifo message1.jpg'>
    <img src='/distributed/img/rocketmq fifo message2.jpg'>
    <img src='/distributed/img/rocketmq fifo message3.jpg'>
    - Delay: You can specify a delay to make messages available to consumers only after the delay has elapsed, instead of delivering messages immediately when they are produced.
    <img src='/distributed/img/rocketmq delay message.jpg'>
    - Transaction: Apache RocketMQ supports distributed transaction messages and ensures transaction consistency of database updates and message calls.
    <img src='/distributed/img/rocketmq transaction message1.jpg'>
    <img src='/distributed/img/rocketmq transaction message2.jpg'>

#### Offset
##### Offset
- 通过主题、队列和位点就可以定位任意一条消息的位置
- MinOffset：队列中最早一条消息的位点为最小消息位点
- MaxOffset：最新一条消息的位点为最大消息位点
- 由于服务端物理节点的存储空间有限， Apache RocketMQ 会滚动删除队列中存储最早的消息。因此，消息的最小消费位点和最大消费位点会一直递增变化
##### ConsumerOffset
- 通过消费位点管理消息的消费进度
- 每条消息被某个消费者消费完成后不会立即在队列中删除，Apache RocketMQ 会基于每个消费者分组维护一份消费记录，该记录指定消费者分组消费某一个队列时，消费过的最新一条消息的位点，即消费位点。
- 当消费者客户端离线，又再次重新上线时，会严格按照服务端保存的消费进度继续处理消息。如果服务端保存的历史位点信息已过期被删除，此时消费位点向前移动至服务端存储的最小位点。
<img src='/distributed/img/rocketmq consumer offset.jpg'>

#### Broker
> Broker主要负责消息的存储、投递和查询以及服务高可用保证，为了实现这些功能，Broker包含了以下几个重要子模块。
> - Remoting Module：整个Broker的实体，负责处理来自Client端的请求。
> - Client Manager：负责管理客户端(Producer/Consumer)和维护Consumer的Topic订阅信息。
> - Store Service：提供方便简单的API接口处理消息存储到物理硬盘和查询功能。
> - HA Service：高可用服务，提供Master Broker 和 Slave Broker之间的数据同步功能。
> - Index Service：根据特定的Message key对投递到Broker的消息进行索引服务，以提供消息的快速查询。
#### NameServer
> NameServer是一个非常简单的Topic路由注册中心，其角色类似Dubbo中的zookeeper，支持Broker的动态注册与发现。主要包括两个功能：
> - Broker管理，NameServer接受Broker集群的注册信息并且保存下来作为路由信息的基本数据。然后提供心跳检测机制，检查Broker是否还存活；
> - 路由信息管理，每个NameServer将保存关于Broker集群的整个路由信息和用于客户端查询的队列信息。
> 然后Producer和Consumer通过NameServer就可以知道整个Broker集群的路由信息，从而进行消息的投递和消费。
> 
> NameServer通常也是集群的方式部署，各实例间相互不进行信息通讯。
> Broker是向每一台NameServer注册自己的路由信息，所以每一个NameServer实例上面都保存一份完整的路由信息。
> 当某个NameServer因某种原因下线了，Broker仍然可以向其它NameServer同步其路由信息，Producer和Consumer仍然可以动态感知Broker的路由的信息。

### 消息过滤
#### Tag过滤
- Tag标签设置
  - Tag由生产者发送消息时设置，每条消息允许设置一个Tag标签。
  - Tag使用可见字符，建议长度不超过128字符。
- Tag标签过滤规则
  - Tag标签过滤为精准字符串匹配，过滤规则设置格式如下：
    - 单Tag匹配：过滤表达式为目标Tag。表示只有消息标签为指定目标Tag的消息符合匹配条件，会被发送给消费者。
    - 多Tag匹配：多个Tag之间为或的关系，不同Tag间使用两个竖线（||）隔开。例如，Tag1||Tag2||Tag3，表示标签为Tag1或Tag2或Tag3的消息都满足匹配条件，都会被发送给消费者进行消费。
    - 全部匹配：使用星号（*）作为全匹配表达式。表示主题下的所有消息都将被发送给消费者进行消费。
<img src='/distributed/img/rocketmq tag.jpg'>

#### 属性过滤
> SQL属性过滤是 Apache RocketMQ 提供的高级消息过滤方式，通过生产者为消息设置的属性（Key）及属性值（Value）进行匹配。生产者在发送消息时可设置多个属性，消费者订阅时可设置SQL语法的过滤表达式过滤多个属性。

- 消息属性设置
  - 生产者发送消息时可以自定义消息属性，每个属性都是一个自定义的键值对（Key-Value）。
  - 每条消息支持设置多个属性。
- SQL属性过滤规则
  - SQL属性过滤使用SQL92语法作为过滤规则表达式
  - 由于SQL属性过滤是生产者定义消息属性，消费者设置SQL过滤条件，因此过滤条件的计算结果具有不确定性，服务端的处理方式如下：
    - 异常情况处理：如果过滤条件的表达式计算抛异常，消息默认被过滤，不会被投递给消费者。例如比较数字和非数字类型的值。
    - 空值情况处理：如果过滤条件的表达式计算值为null或不是布尔类型（true和false），则消息默认被过滤，不会被投递给消费者。例如发送消息时未定义某个属性，在订阅时过滤条件中直接使用该属性，则过滤条件的表达式计算结果为null。
    - 数值类型不符处理：如果消息自定义属性为浮点型，但过滤条件中使用整数进行判断，则消息默认被过滤，不会被投递给消费者。
<img src='/distributed/img/rocketmq attr.jpg'>

### 消息重试
> Apache RocketMQ 客户端连接服务端发起消息发送请求时，可能会因为网络故障、服务异常等原因导致调用失败。为保证消息的可靠性， Apache RocketMQ 在客户端SDK中内置请求重试逻辑，尝试通过重试发送达到最终调用成功的效果。
> 
> 同步发送和异步发送模式均支持消息发送重试。

#### 重试触发条件
- 客户端消息发送请求调用失败或请求超时
- 网络异常造成连接失败或请求超时
- 服务端节点处于重启或下线等状态造成连接失败
- 服务端运行慢造成请求超时
- 服务端返回失败错误码
  - 系统逻辑错误：因运行逻辑不正确造成的错误
  - 系统流控错误：因容量超限造成的流控错误
- 对于事务消息，只会进行透明重试（transparent retries），网络超时或异常等场景不会进行重试
#### 重试流程
- 同步发送：调用线程会一直阻塞，直到某次重试成功或最终重试失败，抛出错误码和异常
- 异步发送：调用线程不会阻塞，但调用结果会通过异常事件或者成功事件返回
#### 重试间隔
- 除服务端返回系统流控错误场景，其他触发条件触发重试后，均会立即进行重试，无等待间隔
- 若由于服务端返回流控错误触发重试，系统会按照指数退避策略进行延迟重试
#### 注意事项
- 链路耗时阻塞评估
  - 需要合理评估每次调用请求的超时时间以及最大重试次数，避免影响全链路的耗时
- 最终异常兜底
  - 客户端内置的发送请求重试机制并不能保证消息发送一定成功。当最终重试仍然失败时，业务方调用需要捕获异常，并做好冗余保护处理，避免消息发送结果不一致。
- 消息重复问题
  - 因请求超时触发消息发送重试流程，客户端进行的消息发送重试可能会产生消息重复问题，业务逻辑需要自行处理消息重复问题。
### 消费重试
```
消费重试主要解决的是业务处理逻辑失败导致的消费完整性问题，是一种为业务兜底的策略
```
#### 消息重试的触发条件
- 消费失败，包括消费者返回消息失败状态标识或抛出非预期异常。
- 消息处理超时，包括在PushConsumer中排队超时。
#### 消息重试策略主要行为
- 重试过程状态机：控制消息在重试流程中的状态和变化逻辑。
- 重试间隔：上一次消费失败或超时后，下次重新尝试消费的间隔时间。
- 最大重试次数：消息可被重试消费的最大次数。

<img src='/distributed/img/rocketmq pushconsumer retry.jpg'>
<img src='/distributed/img/rocketmq pushconsumer time.jpg'>
<img src='/distributed/img/rocketmq SimpleConsumer retry.jpg'>
<img src='/distributed/img/rocketmq SimpleConsumer time.jpg'>

### 流量控制
#### 触发条件
- 存储压力大：参考消费进度管理的原理机制，消费者分组的初始消费位点为当前队列的最大消费位点。若某些场景例如业务上新等需要回溯到指定时刻前开始消费，此时队列的存储压力会瞬间飙升，触发消息流控。
- 服务端请求任务排队溢出：若消费者消费能力不足，导致队列中有大量堆积消息，当堆积消息超过一定数量后会触发消息流控，减少下游消费系统压力。
#### 流控行为
- 当系统触发消息发送流控时，客户端会收到系统限流错误和异常，错误码信息如下：
    - reply-code：530
    - reply-text：TOO_MANY_REQUESTS
- 客户端收到系统流控错误码后，会根据指数退避策略进行消息发送重试。
#### 处理建议
- 如何避免触发消息流控：触发限流的根本原因是系统容量或水位过高，您可以利用可观测性功能监控系统水位容量等，保证底层资源充足，避免触发流控机制。、
- 突发消息流控处理：如果因为突发原因触发消息流控，且客户端内置的重试流程执行失败，则建议业务方将请求调用临时替换到其他系统进行应急处理。

### 负载均衡
#### 广播消费和共享消费
<img src='/distributed/img/rocketmq consume mode.jpg'>

#### 消费者负载均衡
##### 消息粒度负载均衡
```
PushConsumer和SimpleConsumer默认负载策略
```
- 同一消费者分组内的多个消费者将按照消息粒度平均分摊主题中的所有消息
- 保证同一个队列的消息可以被多个消费者共同处理，但是该策略使用的消息分配算法结果是随机的，并不能指定消息被哪一个特定的消费者处理
- 消费者获取某条消息后，服务端会将该消息加锁，保证这条消息对其他消费者不可见，直到该消息消费成功或消费超时。因此，即使多个消费者同时消费同一队列的消息，服务端也可保证消息不会被多个消费者重复消费。
- 顺序消息场景下，消息粒度负载均衡策略还需要保证同一消息组内的消息，按照服务端存储的先后顺序进行消费。
- 不同消费者处理同一个消息组内的消息时，会严格按照先后顺序锁定消息状态，确保同一消息组的消息串行消费。
<img src='/distributed/img/rocketmq Message-based load balancing.jpg'>
<img src='/distributed/img/rocketmq ordered Message-based load balancing.jpg'>

##### 队列粒度负载均衡 
```
PullConsumer默认负载策略
```
- 同一消费者分组内的多个消费者将按照队列粒度消费消息，即每个队列仅被一个消费者消费
- 若队列数小于消费者数量，可能会出现部分消费者无绑定队列的情况
- 每个队列绑定到特定的消费者，然后每个消费者按照取消息>提交消费位点>持久化消费位点的消费语义处理消息，取消息过程不提交消费状态
- 为了避免消息被多个消费者重复消费，每个队列仅支持被一个消费者消费
- 在消费者数量、队列数量发生变化时，可能会出现短暂的队列分配结果不一致，从而导致少量消息被重复处理
- 该策略在流式处理场景下有天然优势，能够保证同一队列的消息被相同的消费者处理，对于批量处理、聚合处理更友好
<img src='/distributed/img/rocketmq queue-based load balancing.jpg'>