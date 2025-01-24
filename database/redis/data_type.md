# 数据类型
- [数据类型](#数据类型)
    - [String](#string)
    - [Json](#json)
    - [List](#list)
    - [Set](#set)
    - [Hash](#hash)
    - [Sorted set](#sorted-set)
    - [Stream](#stream)
    - [Geospatial](#geospatial)
    - [Bitmap](#bitmap)
    - [Bitfield](#bitfield)
    - [Probabilistic](#probabilistic)
      - [HyperLogLog](#hyperloglog)
      - [Bloom filter](#bloom-filter)
      - [Cuckoo filter](#cuckoo-filter)
      - [t-digest](#t-digest)
      - [Top-K](#top-k)
      - [Count-min sketch](#count-min-sketch)
      - [Configuration Parameters](#configuration-parameters)
    - [Time series](#time-series)
---

### String
- By default, a single Redis string can be a maximum of 512 MB.
- Most string operations are O(1), which means they're highly efficient. However, be careful with the SUBSTR, GETRANGE, and SETRANGE commands, which can be O(n). These random-access string commands may cause performance issues when dealing with large strings.
- If you're storing structured data as a serialized string, you may also want to consider Redis hashes or JSON.


1. 长度小于20且可以转为整数的时候用int
2. EmbeddedString:小于等于44
3. RawString:大于44
    <img src='/database/img/string.jpg'>
    <img src='/database/img/string check.jpg'>

### Json
- A JSON value passed to a command can have a depth of up to 128. If you pass to a command a JSON value that contains an object or an array with a nesting level of more than 128, the command returns an error.

### List
- The max length of a Redis list is 2^32 - 1 (4,294,967,295) elements.
- List operations that access its head or tail are O(1), which means they're highly efficient. However, commands that manipulate elements within a list are usually O(n). Examples of these include LINDEX, LINSERT, and LSET. Exercise caution when running these commands, mainly when operating on large lists.

1. quicklist
   <img src='/database/img/quicklistnode.jpg'>
   <img src='/database/img/quicklist.jpg'>
2. ziplist
    <img src='/database/img/ziplist.jpg'>

### Set
- The max size of a Redis set is 2^32 - 1 (4,294,967,295) members.
- Most set operations, including adding, removing, and checking whether an item is a set member, are O(1). This means that they're highly efficient. However, for large sets with hundreds of thousands of members or more, you should exercise caution when running the SMEMBERS command. This command is O(n) and returns the entire set in a single response. As an alternative, consider the SSCAN, which lets you retrieve all members of a set iteratively.

1. intset
    <img src='/database/img/intset.jpg'>
2. dict
    <img src='/database/img/setmaxintset.jpg'>
    <img src='/database/img/setmax.jpg'>

### Hash
- Every hash can store up to 4,294,967,295 (2^32 - 1) field-value pairs. In practice, your hashes are limited only by the overall memory on the VMs hosting your Redis deployment.
- Most Redis hash commands are O(1). A few commands, such as HKEYS, HVALS, HGETALL, and most of the expiration-related commands, are O(n), where n is the number of field-value pairs.

1. dict
    <img src='/database/img/dict.jpg'>
2. ziplist
   <img src='/database/img/hash max.jpg'>
   <img src='/database/img/createhash.jpg'>
   <img src='/database/img/hashlist.jpg'>

### Sorted set
- Most sorted set operations are O(log(n)), where n is the number of members.
- Exercise some caution when running the ZRANGE command with large returns values (e.g., in the tens of thousands or more). This command's time complexity is O(log(n) + m), where m is the number of results returned.

1. skiplist
    <img src='/database/img/zsettoskip.jpg'>
2. ziplist
    <img src='/database/img/zsetlistpack.jpg'>
    <img src='/database/img/zsetmaxconfig.jpg'>

### Stream
- Streams are an append-only data structure. 
- You can use streams to record and simultaneously syndicate events in real time
- Redis generates a unique ID for each stream entry. You can use these IDs to retrieve their associated entries later or to read and process all subsequent entries in the stream.

### Geospatial
- GEOADD adds a location to a given geospatial index (note that longitude comes before latitude with this command).
- GEOSEARCH returns locations with a given radius or a bounding box.

### Bitmap
- SETBIT and GETBIT are O(1). 
- BITOP is O(n), where n is the length of the longest string in the comparison.

### Bitfield
- Redis bitfields let you set, increment, and get integer values of arbitrary bit length. For example, you can operate on anything from unsigned 1-bit integers to signed 63-bit integers.
- These values are stored using binary-encoded Redis strings. Bitfields support atomic read, write and increment operations, making them a good choice for managing counters and similar numerical values.


### Probabilistic
#### HyperLogLog
HyperLogLog is a probabilistic data structure that estimates the cardinality of a set.
#### Bloom filter
Bloom filters are a probabilistic data structure that checks for presence of an item in a set
#### Cuckoo filter
Cuckoo filters are a probabilistic data structure that checks for presence of an element in a set
#### t-digest
t-digest is a probabilistic data structure that allows you to estimate the percentile of a data stream.
#### Top-K
Top-K is a probabilistic data structure that allows you to find the most frequent items in a data stream.
#### Count-min sketch
Count-min sketch is a probabilistic data structure that estimates the frequency of an element in a data stream.
#### Configuration Parameters
RedisBloom supports multiple module configuration parameters. All of these parameters can only be set at load-time.

### Time series
- A time series is a linked list of memory chunks. Each chunk has a predefined size of samples. Each sample is a 128-bit tuple: 64 bits for the timestamp and 64 bits for the value.

