# 索引
> reference:  
> https://dev.mysql.com/doc/refman/8.4/en/mysql-indexes.html

- [索引](#索引)
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

