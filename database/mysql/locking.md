# 锁

- [锁](#锁)
---

### Row-Level Locking
**for InnoDB tables**
`SELECT ... FOR UPDATE`
#### advantages
- Fewer lock conflicts when different sessions access different rows.
- Fewer changes for rollbacks.
- Possible to lock a single row for a long time.

#### deadlock
-  innodb_lock_wait_timeout 
-  innodb_deadlock_detect 
> InnoDB automatically detects deadlock conditions by default and rolls back one of the affected transactions.

### Table-Level Locking
**for MyISAM, MEMORY, and MERGE tables**
#### advantages
- Relatively little memory required (row locking requires memory per row or group of rows locked)
- Fast when used on a large part of the table because only a single lock is involved.
- Fast if you often do GROUP BY operations on a large part of the data or must scan the entire table frequently.
#### deadlock
These storage engines avoid deadlocks by always requesting all needed locks at once at the beginning of a query and always locking the tables in the same order. The tradeoff is that this strategy reduces concurrency; other sessions that want to modify the table must wait until the current data change statement finishes.
#### grants lock
MySQL grants table write locks as follows:
1. If there are no locks on the table, put a write lock on it.
2. Otherwise, put the lock request in the write lock queue.

MySQL grants table read locks as follows:
1. If there are no write locks on the table, put a read lock on it.
2. Otherwise, put the lock request in the read lock queue.