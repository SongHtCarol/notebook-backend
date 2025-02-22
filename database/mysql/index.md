# 索引
> reference:  
> https://dev.mysql.com/doc/refman/8.4/en/mysql-indexes.html

- [索引](#索引)
  - [innodb的索引](#innodb的索引)
    - [1. **索引类型**](#1-索引类型)
      - [（1）**聚集索引（Clustered Index）**](#1聚集索引clustered-index)
      - [（2）**二级索引（Secondary Index）**](#2二级索引secondary-index)
      - [（3）**覆盖索引（Covering Index）**](#3覆盖索引covering-index)
    - [2. **B+树结构**](#2-b树结构)
    - [3. **索引优化策略**](#3-索引优化策略)
      - [（1）**选择合适的索引列**](#1选择合适的索引列)
      - [（2）**避免冗余索引**](#2避免冗余索引)
      - [（3）**索引下推（Index Condition Pushdown, ICP）**](#3索引下推index-condition-pushdown-icp)
      - [（4）**前缀索引**](#4前缀索引)
    - [4. **索引的代价**](#4-索引的代价)
    - [5. **索引失效场景**](#5-索引失效场景)
    - [6. **监控与分析工具**](#6-监控与分析工具)
      - [（1）**EXPLAIN**](#1explain)
      - [（2）**慢查询日志**](#2慢查询日志)
    - [7. **示例：索引设计与优化**](#7-示例索引设计与优化)
      - [场景：用户表 `users`](#场景用户表-users)
    - [8. **总结**](#8-总结)
  - [innodb 字符串类类型做索引 索引失效](#innodb-字符串类类型做索引-索引失效)
    - [1. **索引失效的常见场景**](#1-索引失效的常见场景)
      - [（1）**隐式类型转换**](#1隐式类型转换)
      - [（2）**函数操作**](#2函数操作)
      - [（3）**LIKE 查询以通配符开头**](#3like-查询以通配符开头)
      - [（4）**OR 条件未全覆盖**](#4or-条件未全覆盖)
      - [（5）**联合索引的最左前缀原则**](#5联合索引的最左前缀原则)
    - [2. **字符串类型索引的优化建议**](#2-字符串类型索引的优化建议)
      - [（1）**前缀索引**](#1前缀索引)
      - [（2）**覆盖索引**](#2覆盖索引)
      - [（3）**全文索引（FULLTEXT）**](#3全文索引fulltext)
      - [（4）**使用合适的字符集和排序规则**](#4使用合适的字符集和排序规则)
    - [3. **监控与分析工具**](#3-监控与分析工具)
      - [（1）**EXPLAIN**](#1explain-1)
      - [（2）**慢查询日志**](#2慢查询日志-1)
    - [4. **示例：优化字符串索引**](#4-示例优化字符串索引)
      - [场景：用户表 `users`](#场景用户表-users-1)
    - [5. **总结**](#5-总结)
  - [innodb的全文搜索](#innodb的全文搜索)
    - [1. **全文搜索的特点**](#1-全文搜索的特点)
    - [2. **全文索引的创建**](#2-全文索引的创建)
      - [示例：](#示例)
    - [3. **全文搜索的查询模式**](#3-全文搜索的查询模式)
      - [（1）**自然语言模式（Natural Language Mode）**](#1自然语言模式natural-language-mode)
      - [（2）**布尔模式（Boolean Mode）**](#2布尔模式boolean-mode)
    - [4. **全文搜索的运算符**](#4-全文搜索的运算符)
      - [示例：](#示例-1)
    - [5. **全文搜索的相关性排序**](#5-全文搜索的相关性排序)
      - [示例：](#示例-2)
    - [6. **全文搜索的限制**](#6-全文搜索的限制)
    - [7. **配置全文搜索**](#7-配置全文搜索)
      - [（1）**修改最小词长度**](#1修改最小词长度)
      - [（2）**自定义停用词**](#2自定义停用词)
    - [8. **中文全文搜索**](#8-中文全文搜索)
      - [（1）**使用 `ngram` 分词插件**](#1使用-ngram-分词插件)
      - [（2）**示例：`ngram` 分词**](#2示例ngram-分词)
    - [9. **全文搜索的性能优化**](#9-全文搜索的性能优化)
    - [10. **总结**](#10-总结)
  - [几种索引原文介绍](#几种索引原文介绍)
    - [How MySQL Uses Indexes](#how-mysql-uses-indexes)
    - [MySQL Indexes](#mysql-indexes)
      - [primary key](#primary-key)
      - [Spatial Indexes](#spatial-indexes)
        - [spatial data type](#spatial-data-type)
      - [Foreign Key](#foreign-key)
      - [FULLTEXT Indexes](#fulltext-indexes)
      - [Index Prefixes](#index-prefixes)
      - [multiple-column index](#multiple-column-index)
    - [B-Tree and Hash Indexes](#b-tree-and-hash-indexes)
      - [B-Tree Index](#b-tree-index)
      - [Hash Index](#hash-index)

---
## innodb的索引
InnoDB 是 MySQL 的默认存储引擎，其索引机制是其高性能的核心。InnoDB 的索引基于 **B+树** 数据结构，支持高效的查询、插入、更新和删除操作。以下是关于 InnoDB 索引的详细解析：


### 1. **索引类型**
#### （1）**聚集索引（Clustered Index）**
- **定义**：InnoDB 的表数据按主键顺序存储，聚集索引的叶子节点直接存储整行数据。
- **特点**：
  - 每个表有且仅有一个聚集索引。
  - 若未显式定义主键，InnoDB 会自动选择一个唯一的非空索引（Unique NOT NULL）作为聚集索引；若无此类索引，则会隐式创建一个 6 字节的 `ROWID` 作为主键。
- **优点**：
  - 范围查询和排序效率高（数据物理有序）。
  - 直接通过主键访问数据只需一次索引查找。

#### （2）**二级索引（Secondary Index）**
- **定义**：所有非主键索引均为二级索引。其叶子节点存储主键值，而非实际数据。
- **查找过程**：
  - 通过二级索引找到主键值。
  - 再通过主键值到聚集索引中查找完整数据（称为 **回表查询**）。
- **示例**：
  ```sql
  -- 创建二级索引
  CREATE INDEX idx_name ON users(name);
  ```

#### （3）**覆盖索引（Covering Index）**
- **定义**：如果二级索引的叶子节点已包含查询所需的所有字段，则无需回表。
- **优化场景**：
  ```sql
  -- 假设索引 (name, age) 存在
  SELECT name, age FROM users WHERE name = 'Alice'; -- 无需回表
  ```


### 2. **B+树结构**
- **特点**：
  - **平衡树**：所有叶子节点位于同一层，查询时间复杂度稳定为 \(O(\log N)\)。
  - **多路分支**：每个节点可存储大量键值，减少树的高度。
  - **叶子节点链表**：叶子节点通过指针连接，支持高效范围查询。
- **B+树 vs B树**：
  - B+树非叶子节点仅存储键（不存储数据），叶子节点存储数据，更适合磁盘 I/O。
  - B+树范围查询更高效（叶子节点链表）。


### 3. **索引优化策略**
#### （1）**选择合适的索引列**
- **高选择性列**：区分度高的列（如唯一键）更适合建索引。
- **联合索引的最左前缀原则**：
  ```sql
  -- 联合索引 (a, b, c) 生效的查询：
  WHERE a = 1; 
  WHERE a = 1 AND b = 2; 
  WHERE a = 1 AND b = 2 AND c = 3;
  -- 不生效的查询：
  WHERE b = 2; 
  WHERE c = 3;
  ```

#### （2）**避免冗余索引**
- 删除未使用或重复的索引（可通过 `sys.schema_unused_indexes` 表监控）。

#### （3）**索引下推（Index Condition Pushdown, ICP）**
- **MySQL 5.6+ 特性**：在存储引擎层过滤不符合条件的记录，减少回表次数。
  ```sql
  -- 索引 (age, city)
  SELECT * FROM users WHERE age > 20 AND city = 'Beijing';
  -- ICP 会先通过索引过滤 city = 'Beijing'，再回表查询 age > 20。
  ```

#### （4）**前缀索引**
- 对长文本字段（如 `VARCHAR(255)`）使用前缀索引，减少索引大小。
  ```sql
  CREATE INDEX idx_email_prefix ON users(email(10)); -- 前 10 个字符作为索引
  ```


### 4. **索引的代价**
- **写操作开销**：插入、更新、删除需维护索引结构，可能触发页分裂或页合并。
- **空间占用**：索引占用额外磁盘空间。
- **优化建议**：根据读写比例权衡索引数量。


### 5. **索引失效场景**
- **隐式类型转换**：
  ```sql
  SELECT * FROM users WHERE name = 123; -- name 是字符串类型，索引失效
  ```
- **函数或表达式操作**：
  ```sql
  SELECT * FROM users WHERE YEAR(create_time) = 2023; -- 索引失效
  -- 可优化为范围查询：
  SELECT * FROM users WHERE create_time >= '2023-01-01' AND create_time < '2024-01-01';
  ```
- **OR 条件未全覆盖**：
  ```sql
  -- 索引 (a) 存在，但 OR 条件包含无索引列 b：
  SELECT * FROM table WHERE a = 1 OR b = 2; -- 索引失效
  ```


### 6. **监控与分析工具**
#### （1）**EXPLAIN**
分析查询的执行计划：
```sql
EXPLAIN SELECT * FROM users WHERE name = 'Alice';
```
- **关键字段**：
  - `type`：访问类型（`const`、`ref`、`range`、`index`、`ALL`）。
  - `key`：实际使用的索引。
  - `rows`：预估扫描行数。
  - `Extra`：附加信息（如 `Using index` 表示覆盖索引）。

#### （2）**慢查询日志**
启用慢查询日志定位低效 SQL：
```sql
SET GLOBAL slow_query_log = 1;
SET GLOBAL long_query_time = 2; -- 超过 2 秒的查询记录
```


### 7. **示例：索引设计与优化**
#### 场景：用户表 `users`
```sql
CREATE TABLE users (
    id INT PRIMARY KEY,
    name VARCHAR(50),
    email VARCHAR(100),
    age INT,
    city VARCHAR(50),
    INDEX idx_name_age (name, age)
);
```
- **高频查询**：
  ```sql
  SELECT id, name, age FROM users WHERE name = 'Alice' AND age > 20; -- 联合索引覆盖
  SELECT * FROM users WHERE city = 'Beijing' ORDER BY id; -- 聚集索引排序
  ```


### 8. **总结**
- **聚集索引**：数据按主键物理排序，直接存储行数据。
- **二级索引**：叶子节点存储主键值，需回表查询。
- **B+树**：平衡多路搜索树，支持高效点查和范围查询。
- **优化核心**：减少回表、利用覆盖索引、避免索引失效。
- **权衡**：索引提升查询性能，但增加写开销和空间占用。

## innodb 字符串类类型做索引 索引失效
在 InnoDB 中使用字符串类型（如 `VARCHAR`、`CHAR`、`TEXT` 等）作为索引时，如果使用不当，可能会导致索引失效，从而影响查询性能。以下是字符串类型索引失效的常见场景及优化建议：


### 1. **索引失效的常见场景**
#### （1）**隐式类型转换**
- **问题**：当查询条件中的数据类型与索引列的数据类型不一致时，MySQL 会进行隐式类型转换，导致索引失效。
- **示例**：
  ```sql
  -- 假设 name 是 VARCHAR 类型
  SELECT * FROM users WHERE name = 123; -- 索引失效，因为 123 是数字类型
  ```
- **优化**：确保查询条件中的数据类型与索引列一致。
  ```sql
  SELECT * FROM users WHERE name = '123'; -- 使用字符串类型
  ```

#### （2）**函数操作**
- **问题**：在索引列上使用函数（如 `LOWER`、`UPPER`、`SUBSTRING` 等）会导致索引失效。
- **示例**：
  ```sql
  SELECT * FROM users WHERE LOWER(name) = 'alice'; -- 索引失效
  ```
- **优化**：避免在索引列上使用函数，或使用函数索引（MySQL 8.0+ 支持）。
  ```sql
  -- MySQL 8.0+ 支持函数索引
  CREATE INDEX idx_lower_name ON users ((LOWER(name)));
  SELECT * FROM users WHERE LOWER(name) = 'alice'; -- 使用函数索引
  ```

#### （3）**LIKE 查询以通配符开头**
- **问题**：当 `LIKE` 查询以通配符（`%` 或 `_`）开头时，索引失效。
- **示例**：
  ```sql
  SELECT * FROM users WHERE name LIKE '%alice'; -- 索引失效
  ```
- **优化**：尽量避免以通配符开头的 `LIKE` 查询，或使用全文索引（FULLTEXT）。
  ```sql
  SELECT * FROM users WHERE name LIKE 'alice%'; -- 索引有效
  ```

#### （4）**OR 条件未全覆盖**
- **问题**：当 `OR` 条件中有一个条件未使用索引时，整个查询的索引可能失效。
- **示例**：
  ```sql
  -- 假设 name 有索引，age 无索引
  SELECT * FROM users WHERE name = 'Alice' OR age = 20; -- 索引失效
  ```
- **优化**：确保 `OR` 条件中的所有列都有索引，或使用 `UNION` 拆分查询。
  ```sql
  SELECT * FROM users WHERE name = 'Alice'
  UNION
  SELECT * FROM users WHERE age = 20;
  ```

#### （5）**联合索引的最左前缀原则**
- **问题**：如果查询条件不满足联合索引的最左前缀原则，索引可能失效。
- **示例**：
  ```sql
  -- 假设有联合索引 (name, age)
  SELECT * FROM users WHERE age = 20; -- 索引失效
  ```
- **优化**：确保查询条件包含联合索引的最左列。
  ```sql
  SELECT * FROM users WHERE name = 'Alice' AND age = 20; -- 索引有效
  ```


### 2. **字符串类型索引的优化建议**
#### （1）**前缀索引**
- **适用场景**：字符串列较长（如 `VARCHAR(255)`），但查询条件通常只使用前几个字符。
- **示例**：
  ```sql
  CREATE INDEX idx_email_prefix ON users(email(10)); -- 前 10 个字符作为索引
  ```
- **注意**：前缀索引会降低索引的选择性，需根据实际情况选择合适的前缀长度。

#### （2）**覆盖索引**
- **适用场景**：查询只需要索引列的数据，无需回表。
- **示例**：
  ```sql
  -- 假设有索引 (name, age)
  SELECT name, age FROM users WHERE name = 'Alice'; -- 覆盖索引，无需回表
  ```

#### （3）**全文索引（FULLTEXT）**
- **适用场景**：对文本内容进行全文搜索。
- **示例**：
  ```sql
  CREATE FULLTEXT INDEX idx_content ON articles(content);
  SELECT * FROM articles WHERE MATCH(content) AGAINST('database');
  ```

#### （4）**使用合适的字符集和排序规则**
- **建议**：选择占用空间较小的字符集（如 `utf8mb4` 替代 `utf8`），并确保排序规则一致。
  ```sql
  CREATE TABLE users (
      id INT PRIMARY KEY,
      name VARCHAR(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
  ```


### 3. **监控与分析工具**
#### （1）**EXPLAIN**
分析查询的执行计划，检查索引使用情况：
```sql
EXPLAIN SELECT * FROM users WHERE name = 'Alice';
```
- **关键字段**：
  - `type`：访问类型（`const`、`ref`、`range`、`index`、`ALL`）。
  - `key`：实际使用的索引。
  - `rows`：预估扫描行数。
  - `Extra`：附加信息（如 `Using index` 表示覆盖索引）。

#### （2）**慢查询日志**
启用慢查询日志定位低效 SQL：
```sql
SET GLOBAL slow_query_log = 1;
SET GLOBAL long_query_time = 2; -- 超过 2 秒的查询记录
```


### 4. **示例：优化字符串索引**
#### 场景：用户表 `users`
```sql
CREATE TABLE users (
    id INT PRIMARY KEY,
    name VARCHAR(50),
    email VARCHAR(100),
    INDEX idx_name (name)
);
```
- **高频查询**：
  ```sql
  SELECT * FROM users WHERE name = 'Alice'; -- 索引有效
  SELECT * FROM users WHERE name LIKE 'Ali%'; -- 索引有效
  SELECT * FROM users WHERE LOWER(name) = 'alice'; -- 索引失效
  ```

- **优化**：
  ```sql
  -- 使用函数索引（MySQL 8.0+）
  CREATE INDEX idx_lower_name ON users ((LOWER(name)));
  SELECT * FROM users WHERE LOWER(name) = 'alice'; -- 索引有效
  ```

### 5. **总结**
- **字符串索引失效的常见原因**：隐式类型转换、函数操作、`LIKE` 通配符开头、`OR` 条件未全覆盖、联合索引最左前缀不匹配。
- **优化建议**：使用前缀索引、覆盖索引、全文索引，确保查询条件与索引列类型一致。
- **监控工具**：`EXPLAIN` 和慢查询日志是分析和优化索引的有力工具。


## innodb的全文搜索
InnoDB 存储引擎从 **MySQL 5.6** 版本开始支持全文搜索（Full-Text Search），这是一种高效的文本搜索技术，特别适用于对大量文本数据进行关键字搜索的场景。全文搜索通过倒排索引（Inverted Index）实现，能够快速定位包含特定关键词的文档。


### 1. **全文搜索的特点**
- **支持自然语言搜索**：可以搜索包含特定关键词的文本。
- **支持布尔模式搜索**：可以使用逻辑运算符（如 `AND`、`OR`、`NOT`）进行复杂查询。
- **支持短语搜索**：可以搜索完整的短语。
- **支持相关性排序**：搜索结果可以按相关性排序。


### 2. **全文索引的创建**
全文索引只能用于 `CHAR`、`VARCHAR` 或 `TEXT` 类型的列。创建全文索引的语法如下：
```sql
CREATE FULLTEXT INDEX index_name ON table_name(column_name);
```

#### 示例：
```sql
CREATE TABLE articles (
    id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(200),
    content TEXT,
    FULLTEXT INDEX idx_content (content) -- 创建全文索引
);
```


### 3. **全文搜索的查询模式**
全文搜索支持两种查询模式：
#### （1）**自然语言模式（Natural Language Mode）**
- **默认模式**：搜索包含指定关键词的文本，并按相关性排序。
- **语法**：
  ```sql
  SELECT * FROM table_name WHERE MATCH(column_name) AGAINST('keyword');
  ```

#### （2）**布尔模式（Boolean Mode）**
- **支持复杂查询**：可以使用逻辑运算符（如 `+`、`-`、`*`）进行高级搜索。
- **语法**：
  ```sql
  SELECT * FROM table_name WHERE MATCH(column_name) AGAINST('+keyword1 -keyword2' IN BOOLEAN MODE);
  ```


### 4. **全文搜索的运算符**
在布尔模式下，可以使用以下运算符：
- **`+`**：必须包含该关键词。
- **`-`**：必须不包含该关键词。
- **`*`**：通配符，匹配以指定前缀开头的单词。
- **`"`**：短语搜索，匹配完整的短语。
- **`()`**：分组操作符。

#### 示例：
```sql
-- 搜索包含 "database" 但不包含 "MySQL" 的文章
SELECT * FROM articles WHERE MATCH(content) AGAINST('+database -MySQL' IN BOOLEAN MODE);

-- 搜索以 "data" 开头的单词
SELECT * FROM articles WHERE MATCH(content) AGAINST('data*' IN BOOLEAN MODE);

-- 搜索完整的短语 "relational database"
SELECT * FROM articles WHERE MATCH(content) AGAINST('"relational database"' IN BOOLEAN MODE);
```

### 5. **全文搜索的相关性排序**
全文搜索会为每条记录计算一个相关性分数（Relevance Score），分数越高表示匹配度越高。可以通过 `MATCH() AGAINST()` 返回的分数进行排序。

#### 示例：
```sql
SELECT id, title, MATCH(content) AGAINST('database') AS score
FROM articles
WHERE MATCH(content) AGAINST('database')
ORDER BY score DESC;
```


### 6. **全文搜索的限制**
- **最小词长度**：默认情况下，全文索引只会对长度大于等于 4 的单词进行索引。可以通过修改 `innodb_ft_min_token_size` 参数调整最小词长度。
- **停用词**：全文索引会忽略常见的停用词（如 "the"、"and" 等）。可以通过修改 `innodb_ft_enable_stopword` 参数自定义停用词列表。
- **中文支持**：默认的全文索引对中文支持较差，需要使用分词插件（如 `ngram`）。


### 7. **配置全文搜索**
#### （1）**修改最小词长度**
```sql
-- 修改最小词长度为 2
SET GLOBAL innodb_ft_min_token_size = 2;
```
修改后需要重建全文索引：
```sql
ALTER TABLE articles DROP INDEX idx_content;
CREATE FULLTEXT INDEX idx_content ON articles(content);
```

#### （2）**自定义停用词**
- 创建停用词表文件（如 `/etc/mysql/stopwords.txt`）。
- 修改 MySQL 配置文件：
  ```ini
  [mysqld]
  innodb_ft_server_stopword_table = 'stopwords.txt'
  ```
- 重启 MySQL 服务并重建全文索引。


### 8. **中文全文搜索**
默认的全文索引对中文支持较差，因为中文没有明显的单词分隔符。可以通过以下方式支持中文全文搜索：
#### （1）**使用 `ngram` 分词插件**
- `ngram` 是 MySQL 5.7+ 提供的中文分词插件。
- 创建全文索引时指定 `ngram` 分词器：
  ```sql
  CREATE TABLE articles (
      id INT PRIMARY KEY AUTO_INCREMENT,
      title VARCHAR(200),
      content TEXT,
      FULLTEXT INDEX idx_content (content) WITH PARSER ngram
  );
  ```
- 查询时使用自然语言模式或布尔模式：
  ```sql
  SELECT * FROM articles WHERE MATCH(content) AGAINST('数据库');
  ```

#### （2）**示例：`ngram` 分词**
```sql
-- 创建表并指定 ngram 分词器
CREATE TABLE articles (
    id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(200),
    content TEXT,
    FULLTEXT INDEX idx_content (content) WITH PARSER ngram
);

-- 插入数据
INSERT INTO articles (title, content) VALUES
('数据库原理', '数据库是存储和管理数据的系统。'),
('MySQL 教程', 'MySQL 是一种流行的关系型数据库管理系统。');

-- 查询包含 "数据库" 的文章
SELECT * FROM articles WHERE MATCH(content) AGAINST('数据库');
```


### 9. **全文搜索的性能优化**
- **选择合适的列**：只为需要搜索的列创建全文索引。
- **避免过度索引**：全文索引会占用额外的存储空间，并增加写操作的开销。
- **使用布尔模式**：布尔模式的性能通常优于自然语言模式。


### 10. **总结**
- InnoDB 的全文搜索是一种高效的文本搜索技术，支持自然语言模式和布尔模式。
- 全文索引适用于 `CHAR`、`VARCHAR` 和 `TEXT` 类型的列。
- 中文全文搜索可以通过 `ngram` 分词插件实现。
- 全文搜索的性能可以通过合理设计索引和查询来优化。

## 几种索引原文介绍

### How MySQL Uses Indexes
_Most MySQL indexes (PRIMARY KEY, UNIQUE, INDEX, and FULLTEXT) are stored in B-trees. Exceptions: Indexes on spatial data types use R-trees; MEMORY tables also support hash indexes; InnoDB uses inverted lists for FULLTEXT indexes._

- To find the rows matching a WHERE clause quickly.
- To eliminate rows from consideration. If there is a choice between multiple indexes, MySQL normally uses the index that finds the smallest number of rows (the most selective index).
- If the table has a multiple-column index, any leftmost prefix of the index can be used by the optimizer to look up rows. For example, if you have a three-column index on (col1, col2, col3), you have indexed search capabilities on (col1), (col1, col2), and (col1, col2, col3).
- To retrieve rows from other tables when performing joins. MySQL can use indexes on columns more efficiently if they are declared as the same type and size. In this context, VARCHAR and CHAR are considered the same if they are declared as the same size.
- To find the MIN() or MAX() value for a specific indexed column key_col. This is optimized by a preprocessor that checks whether you are using WHERE key_part_N = constant on all key parts that occur before key_col in the index. In this case, MySQL does a single key lookup for each MIN() or MAX() expression and replaces it with a constant. If all expressions are replaced with constants, the query returns at once.
- To sort or group a table if the sorting or grouping is done on a leftmost prefix of a usable index (for example, ORDER BY key_part1, key_part2). If all key parts are followed by DESC, the key is read in reverse order.
- In some cases, a query can be optimized to retrieve values without consulting the data rows. (An index that provides all the necessary results for a query is called a covering index.) If a query uses from a table only columns that are included in some index, the selected values can be retrieved from the index tree for greater speed.

### MySQL Indexes
#### primary key 
-  NOT NULL
-  unique
- With the InnoDB storage engine, the table data is physically organized to do ultra-fast lookups and sorts based on the primary key column or columns.
- These unique IDs can serve as pointers to corresponding rows in other tables when you join tables using foreign keys.

#### Spatial Indexes
- For InnoDB and MyISAM tables, MySQL can create spatial indexes using syntax similar to that for creating regular indexes, but using the SPATIAL keyword. Columns in spatial indexes must be declared NOT NULL
- SPATIAL INDEX creates an R-tree index. For storage engines that support nonspatial indexing of spatial columns, the engine creates a B-tree index. A B-tree index on spatial values is useful for exact-value lookups, but not for range scans.
- For comparisons to work properly, each column in a SPATIAL index must be SRID-restricted. That is, the column definition must include an explicit SRID attribute, and all column values must have the same SRID.

##### spatial data type
- `GEOMETRY`
- `POINT`
- `LINESTRING`
- `POLYGON`
InnoDB tables permit SRID values for Cartesian and geographic SRSs. MyISAM tables permit SRID values for Cartesian SRSs.

#### Foreign Key
- split the less-frequently used data into separate tables with a few columns each
- relate them back to the main table by duplicating the numeric ID column from the main table
- you can query just the set of columns that you need using a join operation
- the queries might perform less I/O and take up less cache memory because the relevant columns are packed together on disk

#### FULLTEXT Indexes
- FULLTEXT queries that only return the document ID, or the document ID and the search rank.
- FULLTEXT queries that sort the matching rows in descending order of score and apply a LIMIT clause to take the top N matching rows. For this optimization to apply, there must be no WHERE clauses and only a single ORDER BY clause in descending order.
- FULLTEXT queries that retrieve only the COUNT(*) value of rows matching a search term, with no additional WHERE clauses. Code the WHERE clause as WHERE MATCH(text) AGAINST ('other_text'), without any > 0 comparison operator.

#### Index Prefixes
- With col_name(N) syntax in an index specification for a string column, you can create an index that uses only the first N characters of the column. 
- Indexing only a prefix of column values in this way can make the index file much smaller. 
- When you index a BLOB or TEXT column, you must specify a prefix length for the index.

#### multiple-column index
- If a multiple-column index exists on col1 and col2, the appropriate rows can be fetched directly. If separate single-column indexes exist on col1 and col2, the optimizer attempts to use the Index Merge optimization, or attempts to find the most restrictive index by deciding which index excludes more rows and using that index to fetch the rows.
- If the table has a multiple-column index, any leftmost prefix of the index can be used by the optimizer to look up rows. For example, if you have a three-column index on (col1, col2, col3), you have indexed search capabilities on (col1), (col1, col2), and (col1, col2, col3).
- If an index exists on (col1, col2, col3), only the first two queries use the index. The third and fourth queries do involve indexed columns, but do not use an index to perform lookups because (col2) and (col2, col3) are not leftmost prefixes of (col1, col2, col3).

### B-Tree and Hash Indexes
#### B-Tree Index
- A B-tree index can be used for column comparisons in expressions that use the =, >, >=, <, <=, or BETWEEN operators. 
- The index also can be used for LIKE comparisons if the argument to LIKE is a constant string that does not start with a wildcard character.
  
<img src='/database/img/like_index.jpg'>
<img src='/database/img/and_index.jpg'>

#### Hash Index
- They are used only for equality comparisons that use the = or <=> operators (but are very fast). They are not used for comparison operators such as < that find a range of values. Systems that rely on this type of single-value lookup are known as “key-value stores”; to use MySQL for such applications, use hash indexes wherever possible.
- The optimizer cannot use a hash index to speed up ORDER BY operations. (This type of index cannot be used to search for the next entry in order.)
- MySQL cannot determine approximately how many rows there are between two values (this is used by the range optimizer to decide which index to use). This may affect some queries if you change a MyISAM or InnoDB table to a hash-indexed MEMORY table.
- Only whole keys can be used to search for a row. (With a B-tree index, any leftmost prefix of the key can be used to find rows.)

