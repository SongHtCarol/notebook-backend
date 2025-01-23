# 存储引擎
> reference:  
> https://dev.mysql.com/doc/refman/8.4/en/innodb-storage-engine.html  
> https://dev.mysql.com/doc/refman/8.4/en/storage-engines.html
- [存储引擎](#存储引擎)
    - [InnoDB](#innodb)
      - [InnoDB ACID](#innodb-acid)
        - [InnoDB autocommit](#innodb-autocommit)
      - [InnoDB doublewrite buffer](#innodb-doublewrite-buffer)
        - [innodb\_flush\_log\_at\_trx\_commit](#innodb_flush_log_at_trx_commit)
        - [sync\_binlog](#sync_binlog)
      - [InnoDB Index](#innodb-index)
        - [Clustered and Secondary Indexes](#clustered-and-secondary-indexes)
        - [B-tree Index](#b-tree-index)
        - [Full-Text Indexes](#full-text-indexes)
    - [MyISAM](#myisam)
    - [MEMORY](#memory)
    - [ARCHIVE](#archive)

---

### InnoDB
<img src='/database/img/innoDB.jpg'>
<img src='/database/img/InnoDB Architecture.jpg'>
<img src='/database/img/InnoDB Cluster.jpg'>

#### InnoDB ACID
> https://dev.mysql.com/doc/refman/8.4/en/mysql-acid.html

- Atomicity
  - The autocommit setting.
  - The COMMIT statement.
  - The ROLLBACK statement.
- Consistency
  - The InnoDB doublewrite buffer
  - InnoDB crash recovery
- Isolation
  - The autocommit setting.
  - Transaction isolation levels and the SET TRANSACTION statement
  - The low-level details of InnoDB locking. Details can be viewed in the INFORMATION_SCHEMA tables and Performance Schema data_locks and data_lock_waits tables.
- Durability
  - The InnoDB doublewrite buffer
  - The innodb_flush_log_at_trx_commit variable.
  - The sync_binlog variable.
  - The innodb_file_per_table variable.
  - The write buffer in a storage device, such as a disk drive, SSD, or RAID array.
  - A battery-backed cache in a storage device.
  - The operating system used to run MySQL, in particular its support for the fsync() system call.
  - An uninterruptible power supply (UPS) protecting the electrical power to all computer servers and storage devices that run MySQL servers and store MySQL data.
  - Your backup strategy, such as frequency and types of backups, and backup retention periods.
  - For distributed or hosted data applications, the particular characteristics of the data centers where the hardware for the MySQL servers is located, and network connections between the data centers.

##### InnoDB autocommit
<img src='/database/img/autocommit.jpg'>

#### InnoDB doublewrite buffer
The doublewrite buffer is a storage area where InnoDB writes pages flushed from the buffer pool before writing the pages to their proper positions in the InnoDB data files. If there is an operating system, storage subsystem, or unexpected mysqld process exit in the middle of a page write, InnoDB can find a good copy of the page from the doublewrite buffer during crash recovery.

Although data is written twice, the doublewrite buffer does not require twice as much I/O overhead or twice as many I/O operations. Data is written to the doublewrite buffer in a large sequential chunk, with a single fsync() call to the operating system (except in the case that innodb_flush_method is set to O_DIRECT_NO_FSYNC).

##### innodb_flush_log_at_trx_commit
<img src='/database/img/innodb_flush_log_at_trx_commit.jpg'>

##### sync_binlog
<img src='/database/img/sync_binlog.jpg'>

#### InnoDB Index
##### Clustered and Secondary Indexes
- When you define a PRIMARY KEY on a table, InnoDB uses it as the clustered index. A primary key should be defined for each table. If there is no logical unique and non-null column or set of columns to use a the primary key, add an auto-increment column. Auto-increment column values are unique and are added automatically as new rows are inserted.
- If you do not define a PRIMARY KEY for a table, InnoDB uses the first UNIQUE index with all key columns defined as NOT NULL as the clustered index.
- If a table has no PRIMARY KEY or suitable UNIQUE index, InnoDB generates a hidden clustered index named GEN_CLUST_INDEX on a synthetic column that contains row ID values. The rows are ordered by the row ID that InnoDB assigns. The row ID is a 6-byte field that increases monotonically as new rows are inserted. Thus, the rows ordered by the row ID are physically in order of insertion.
##### B-tree Index
There are three phases to an index build. 
- In the first phase, the clustered index is scanned, and index entries are generated and added to the sort buffer. When the sort buffer becomes full, entries are sorted and written out to a temporary intermediate file. This process is also known as a “run”. 
- In the second phase, with one or more runs written to the temporary intermediate file, a merge sort is performed on all entries in the file. 
- In the third and final phase, the sorted entries are inserted into the B-tree; this final phase is multithreaded.
##### Full-Text Indexes
- Full-text indexes are created on text-based columns (CHAR, VARCHAR, or TEXT columns) to speed up queries and DML operations on data contained within those columns.
- A full-text index is defined as part of a CREATE TABLE statement or added to an existing table using ALTER TABLE or CREATE INDEX.
- Full-text search is performed using MATCH() ... AGAINST syntax.

### MyISAM
<img src='/database/img/MyISAM.jpg'>

- BLOB and TEXT columns can be indexed.
- NULL values are permitted in indexed columns. This takes 0 to 1 bytes per key.
- All data values are stored with the low byte first. 
- All numeric key values are stored with the high byte first to permit better index compression.
- The maximum number of indexes per MyISAM table is 64.
- The maximum number of columns per index is 16.

### MEMORY
<img src='/database/img/MEMORY.jpg'>

- Space for MEMORY tables is allocated in small blocks. Tables use 100% dynamic hashing for inserts. No overflow area or extra key space is needed. No extra space is needed for free lists. Deleted rows are put in a linked list and are reused when you insert new data into the table. MEMORY tables also have none of the problems commonly associated with deletes plus inserts in hashed tables.
- MEMORY tables use a fixed-length row-storage format. Variable-length types such as VARCHAR are stored using a fixed length.
- MEMORY tables cannot contain BLOB or TEXT columns.
- MEMORY includes support for AUTO_INCREMENT columns.
- Non-TEMPORARY MEMORY tables are shared among all clients, just like any other non-TEMPORARY table.
- The MEMORY storage engine supports both HASH and BTREE indexes. 
- MEMORY tables can have up to 64 indexes per table, 16 columns per index and a maximum key length of 3072 bytes.
- Columns that are indexed can contain NULL values.
- MEMORY tables can have nonunique keys. (This is an uncommon feature for implementations of hash indexes.)

### ARCHIVE
<img src='/database/img/ARCHIVE.jpg'>
- The ARCHIVE engine supports INSERT, REPLACE, and SELECT, but not DELETE or UPDATE. It does support ORDER BY operations, BLOB columns, and spatial data types
- ARCHIVE does not support inserting a value into an AUTO_INCREMENT column less than the current maximum column value. Attempts to do so result in an ER_DUP_KEY error.
- The ARCHIVE engine ignores BLOB columns if they are not requested and scans past them while reading.
- The ARCHIVE storage engine does not support partitioning.