# Kafka

> reference   
> - [Kafka](https://kafka.apache.org/documentation/#theproducer)   
> - [Kafka: a Distributed Messaging System for Log Processing](https://www.microsoft.com/en-us/research/wp-content/uploads/2017/09/Kafka.pdf)   
> - [KSQL: Streaming SQL Engine for Apache Kafka](https://openproceedings.org/2019/conf/edbt/EDBT19_paper_329.pdf)   
> - [Kafka, Samza and the Unix Philosophy of Distributed Data](http://sites.computer.org/debull/A15dec/p4.pdf)   
> - [Data Infrastructure at LinkedIn](https://sites.pitt.edu/~viz/classes/infsci3350/resources/linkedin_icde12.pdf)   
> - [Building LinkedIn’s Real-time Activity Data Pipeline](http://sites.computer.org/debull/A12june/pipeline.pdf)   

- [Kafka](#kafka)
    - [架构](#架构)
    - [几个概念](#几个概念)
      - [Producer](#producer)
      - [Consumer](#consumer)
      - [Topic](#topic)
      - [Broker](#broker)
      - [Offset](#offset)
    - [ZooKeeper](#zookeeper)

---

### 架构
<img src='/distributed/img/Kafka Architecture.jpg'>

### 几个概念
#### Producer
```
Producers are those client applications that publish (write) events to Kafka
```
- The producer sends data directly to the broker that is the leader for the partition without any intervening routing tier. 
- To help the producer do this all Kafka nodes can answer a request for metadata about which servers are alive and where the leaders for the partitions of a topic are at any given time to allow the producer to appropriately direct its requests.
- The client controls which partition it publishes messages to. This can be done at random, implementing a kind of random load balancing, or it can be done by some semantic partitioning function. 
#### Consumer
```
Consumers are those that subscribe to (read and process) these events
```
- The Kafka consumer works by issuing "fetch" requests to the brokers leading the partitions it wants to consume. 
- The consumer specifies its offset in the log with each request and receives back a chunk of log beginning from that position. 
- The consumer thus has significant control over this position and can rewind it to re-consume data if need be.
#### Topic
```
Events are organized and durably stored in topics.
Topics are partitioned, meaning a topic is spread over a number of "buckets" located on different Kafka brokers. 
```
<img src='/distributed/img/ Anatomy of a Kafka topic.jpg'>


```bash
$ bin/kafka-topics.sh --bootstrap-server localhost:9092 --create --topic my_topic_name \
    --partitions 20 --replication-factor 3 --config x=y
```


- **topic name**
  - Each sharded partition log is placed into its own folder under the Kafka log directory. The name of such folders consists of the topic name, appended by a dash (-) and the partition id. 
  - typical folder name can not be over 255 characters long, there will be a limitation on the length of topic names. 
  - We assume the number of partitions will not ever be above 100,000. Therefore, topic names cannot be longer than 249 characters. This leaves just enough room in the folder name for a dash and a potentially 5 digit long partition id.
- **partitions** 
  - The partition count controls how many logs the topic will be sharded into.
  - each partition must fit entirely on a single server. So if you have 20 partitions the full data set will be handled by no more than 20 servers (not counting replicas). 
  - the partition count impacts the maximum parallelism of your consumers.
- **replication-factor**
  - The replication factor controls how many servers will replicate each message that is written.

<img src='/distributed/img/ Two consumer groups reading from a topic with four partitions..jpg'>


#### Broker
```
Kafka is run as a cluster of one or more servers that can span multiple datacenters or cloud regions.
Some of these servers form the storage layer, called the brokers.
```
In Kafka, a special node known as the "controller" is responsible for managing the registration of brokers in the cluster. Broker liveness has two conditions:
1. Brokers must maintain an active session with the controller in order to receive regular metadata updates.
2. Brokers acting as followers must replicate the writes from the leader and not fall "too far" behind.
#### Offset
- The Kafka broker assigns an offset to the message, which is a per-partition monotonically increasing sequence number.
- A Kafka consumer client reads all messages in a topic-partition sequentially. For each partition, the client tracks the offset up to which it has seen messages, and it polls the brokers to await the arrival of messages with a greater offset
- The offset is periodically checkpointed to stable storage; if a consumer client crashes and restarts, it resumes reading from its most recently checkpointed offset.
- Different consumer groups maintain their offsets independently, so they can each read the messages at their own pace.

<img src='/distributed/img/kafka1.jpg'>

### ZooKeeper
Kafka uses Zookeeper for the following tasks: 
1. detecting the addition and the removal of brokers and consumer
2. triggering a rebalance process in each consumer when the above events happen
3. maintaining the consumption relationship and keeping track of the consumed offset of each partition
4. when each broker or consumer starts up, it stores its information in a broker or consumer registry in Zookeeper. 
   1. The broker registry contains the broker’s host name and port, and the set of topics and partitions stored on it. 
   2. The consumer registry includes the consumer group to which a consumer belongs and the set of topics that it subscribes to. 
   3. Each consumer group is associated with an ownership registry and an offset registry in Zookeeper. 
   4. The ownership registry has one path for every subscribed partition and the path value is the id of the consumer currently consuming from this partition. 
   5. The offset registry stores for each subscribed partition, the offset of the last consumed message in the partition. 
5. Each consumer registers a Zookeeper watcher on both the broker registry and the consumer registry, and will be notified whenever a change in the broker set or the consumer group occurs
   1. During the initial startup of a consumer or when the consumer is notified about a broker/consumer change through the watcher, the consumer initiates a rebalance process to determine the new subset of partitions that it should consume from. 

<img src='/distributed/img/balance.jpg'>