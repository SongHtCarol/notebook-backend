# 基本原理
- [基本原理](#基本原理)
    - [介绍](#介绍)
    - [summary](#summary)
    - [Leader election](#leader-election)
---

### 介绍
> - [Raft paper](https://raft.github.io/raft.pdf)
> - [动态演示](https://thesecretlivesofdata.com/raft/)

### summary
<img src='/distributed/img/raft summary.jpg'>

###  Leader election
```
Raft uses a heartbeat mechanism to trigger leader election.
1) When servers start up, they begin as followers. 
2) A server remains in follower state as long as it receives valid RPCs from a leader or candidate. 
3) Leaders send periodic heartbeats (AppendEntries RPCs that carry no log entries) to all followers in order to maintain their authority. 
4) If a follower receives no communication over a period of time called the election timeout, then it assumes there is no viable leader and begins an election to choose a new leader
```