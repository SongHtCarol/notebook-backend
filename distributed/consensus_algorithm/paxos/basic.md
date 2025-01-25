# 基本原理
- [基本原理](#基本原理)
    - [Problem](#problem)
    - [Choosing a Value](#choosing-a-value)
      - [Proposer and Acceptor](#proposer-and-acceptor)
    - [Learning a Chosen Value](#learning-a-chosen-value)
    - [Progress](#progress)
---

> - [The Part-Time Parliament](https://lamport.azurewebsites.net/pubs/lamport-paxos.pdf)
> - [Paxos Made Simple](https://lamport.azurewebsites.net/pubs/paxos-simple.pdf)

### Problem
```
The safety requirements for consensus are:
    - Only a value that has been proposed may be chosen,
    - Only a single value is chosen, and
    - A process never learns that a value has been chosen unless it actually has been.
```

### Choosing a Value
```
- P1. An acceptor must accept the first proposal that it receives.
- P2. If a proposal with value v is chosen, then every higher-numbered proposal that is chosen has value v.
    - P2a. If a proposal with value v is chosen, then every higher-numbered proposal accepted by any acceptor has value v.
    - P2b. If a proposal with value v is chosen, then every higher-numbered proposal issued by any proposer has value v.
    - P2c. For any v and n, if a proposal with value v and number n is issued, then there is a set S consisting of a majority of acceptors such that either 
        - (a) no acceptor in S has accepted any proposal numbered less than n, or 
        - (b) v is the value of the highest-numbered proposal among all proposals numbered less than n accepted by the acceptors in S.
```

#### Proposer and Acceptor
```
Phase 1.
    (a) A proposer selects a proposal number n and sends a prepare request with number n to a majority of acceptors.
    (b) If an acceptor receives a prepare request with number n greater than that of any prepare request to which it has already responded, then it responds to the request with a promise not to accept any more proposals numbered less than n and with the highest-numbered proposal (if any) that it has accepted.
Phase 2. 
    (a) If the proposer receives a response to its prepare requests (numbered n) from a majority of acceptors, then it sends an accept request to each of those acceptors for a proposal numbered n with a value v, where v is the value of the highest-numbered proposal among the responses, or is any value if the responses reported no proposals.
    (b) If an acceptor receives an accept request for a proposal numbered n, it accepts the proposal unless it has already responded to a prepare request having a number greater than n.
```

###  Learning a Chosen Value
```
Method 1.
- To learn that a value has been chosen, a learner must find out that a proposal has been accepted by a majority of acceptors. 
- The obvious algorithm is to have each acceptor, whenever it accepts a proposal, respond to all learners, sending them the proposal.
- This allows learners to find out about a chosen value as soon as possible, but it requires each acceptor to respond to each learner—a number of responses equal to the product of the number of acceptors and the number of learners.

Method 2.
- The assumption of non-Byzantine failures makes it easy for one learner to find out from another learner that a value has been accepted. 
- We can have the acceptors respond with their acceptances to a distinguished learner, which in turn informs the other learners when a value has been chosen. 
- This approach requires an extra round for all the learners to discover the chosen value. 
- It is also less reliable, since the distinguished learner could fail. 
- But it requires a number of responses equal only to the sum of the number of acceptors and the number of learners

Method 3.
- More generally, the acceptors could respond with their acceptances to some set of distinguished learners, each of which can then inform all the learners when a value has been chosen.
- Using a larger set of distinguished learners provides greater reliability at the cost of greater communication complexity.
```

### Progress
```
It’s easy to construct a scenario in which two proposers each keep issuing a sequence of proposals with increasing numbers, none of which are ever chosen. 
1) Proposer p completes phase 1 for a proposal number n1. 
2) Another proposer q then completes phase 1 for a proposal number n2 > n1. 
3) Proposer p’s phase 2 accept requests for a proposal numbered n1 are ignored because the acceptors have all promised not to accept any new proposal numbered less than n2. 
4) So, proposer p then begins and completes phase 1 for a new proposal number n3 > n2, causing the second phase 2 accept requests of proposer q to be ignored. And so on.

To guarantee progress, a distinguished proposer must be selected as the only one to try issuing proposals. 
- If the distinguished proposer can communicate successfully with a majority of acceptors, and if it uses a proposal with number greater than any already used, then it will succeed in issuing a proposal that is accepted. 
- By abandoning a proposal and trying again if it learns about some request with a higher proposal number, the distinguished proposer will eventually choose a high enough proposal number.

If enough of the system (proposer, acceptors, and communication network) is working properly, liveness can therefore be achieved by electing a single distinguished proposer. 
The famous result of Fischer, Lynch, and Patterson [1] implies that a reliable algorithm for electing a proposer must use either randomness or real time—for example, by using timeouts. 
However, safety is ensured regardless of the success or failure of the election.
```