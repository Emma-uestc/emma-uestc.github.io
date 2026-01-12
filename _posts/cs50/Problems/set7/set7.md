---
layout: post
title: "CS50 Problem Set 7: SQL 数据库查询实战"
date: 2025-12-30
categories: [CS50, Programming, Problems]
tags: [SQL, SQLite, 数据库, 侦探游戏]
---

# Problem Set 7: SQL

**作业页面**：[https://cs50.harvard.edu/x/psets/7/](https://cs50.harvard.edu/x/psets/7/)

> 💡 **本周任务**：使用 SQL 查询语句解决三个递进难度的问题，从基础查询到复杂的侦探推理游戏。

## 题目概览

| 题目 | 难度 | 核心技能 | 数据库 |
|------|------|---------|--------|
| Songs | ⭐⭐ | 基础查询、聚合函数、子查询 | `songs.db` |
| Movies | ⭐⭐⭐ | 多表连接、JOIN、嵌套查询 | `movies.db` |
| Fiftyville | ⭐⭐⭐⭐⭐ | 综合推理、多表交叉分析 | `fiftyville.db` |

---

# 1. Songs 🎵

**题目链接**：[https://cs50.harvard.edu/x/psets/7/songs/](https://cs50.harvard.edu/x/psets/7/songs/)

```bash
songs/ $ tree
.
├── 1.sql
├── 2.sql
├── 3.sql
├── 4.sql
├── 5.sql
├── 6.sql
├── 7.sql
├── 8.sql
├── answers.txt
└── songs.db
```  
1. sqlite3 songs.db 进入数据库  
2. 执行 .schema  
```sql
sqlite> .schema
CREATE TABLE songs (
    id INTEGER,
    name TEXT,
    artist_id INTEGER,
    danceability REAL,
    energy REAL,
    key INTEGER,
    loudness REAL,
    speechiness REAL,
    valence REAL,
    tempo REAL,
    duration_ms INTEGER
);
CREATE TABLE artists (
    id INTEGER,
    name TEXT
);
```   

对于初次学习 SQL 查询语句的同学来说，这里总结一个模板，几乎所有的 SQL 查询（SELECT）都遵循这个套路：  
```sql
SELECT [我想看的列名]
FROM [数据来源的表名]
WHERE [筛选条件]
ORDER BY [排序依据]
LIMIT [只看前几条];
```  
我们现在就用这个套路去填写这8个问题。  
由前面的查询结果知，`songs.db` 有两张表，`songs` 和 `artists`  
- `songs` 表：存歌曲信息。注意它有一个 artist_id，这是连接到歌手表的钥匙（外键）。
- `artists` 表：存歌手信息（id 和 name）。  
## 题 1：列出所有歌曲的名称 (List the names of all songs)  
- **我想看什么？** 名字 (`name`)
- **从哪看？** 歌曲表 (`songs`)
- **条件？** 无（所有歌曲）  
套用模板就是如下：  
```sql
-- 1.sql
SELECT name 
FROM songs;
```    
执行`sqlite3 songs.db < 1.sql` 查看下执行结果  
```sql
week7/songs/ $ sqlite3 songs.db < 1.sql
+---------------------------------------------------------+
|                          name                           |
+---------------------------------------------------------+
| God's Plan                                              |
| SAD!                                                    |
| rockstar (feat. 21 Savage)                              |
| Psycho (feat. Ty Dolla $ign)                            |
| In My Feelings                                          |
....
| Dusk Till Dawn - Radio Edit                             |
| Be Alright                                              |
+---------------------------------------------------------+
```  
## 题 2：按节奏 (Tempo) 升序列出所有歌曲名称  
- **我想看什么？** 名字 (`name`)
- **从哪看？** 歌曲表 (`songs`)
- **排序？** ORDER BY tempo (默认就是升序 ASC，不用写)  
```sql
-- 2.sql
SELECT name 
FROM songs 
ORDER BY tempo;
```   
## 题 3：列出前 5 首最长的歌曲名称 (按时长降序)  
- **我想看什么？** 名字 (`name`)
- **从哪看？** 歌曲表 (`songs`)
- **条件？** `ORDER BY duration_ms` 降序 (DESC)
- **限制？**  `LIMIT 5`
```sql
-- 3.sql
SELECT name
FROM songs
ORDER BY duration_ms desc
LIMIT 5;
```  
## 题 4：列出所有“舞曲性” (Danceability) 大于 0.75，且“能量” (Energy) 大于 0.75 的歌曲名称  
- **我想看什么？** 名字 (`name`)
- **从哪看？** 歌曲表 (`songs`)
- **条件？** `danceability > 0.75 AND energy > 0.75`  
```sql
-- 4.sql
SELECT name
FROM songs
WHERE danceability > 0.75 AND energy > 0.75
```  
## 题 5：列出所有歌曲的平均“能量” (Average Energy)  
这里引入了 **聚合函数 (Aggregate Functions)**。
SQL 提供了一些数学工具：`AVG()` (平均), `COUNT()` (计数), `MAX()` (最大), `MIN()` (最小), `SUM()` (求和)。  
- **我想看什么？** 能量的平均值 AVG(energy)
- **从哪看？** 歌曲表 (`songs`)  
```sql
-- 5.sql
SELECT AVG(energy) 
FROM songs;
```  
## 题 6：列出 Post Malone 的所有歌曲名称  
这里涉及两个表,比前面的题目要复杂些。  
1. 我们只知道歌手名字叫 'Post Malone'，但不知道他的 id。
2. `songs` 表里只有 `artist_id`。  
- 方法一：子查询 (Subquery) —— 推荐新手使用
逻辑：先在 `artists` 表里查出 Post Malone 的 `id` 是多少，然后拿着这个 `id` 去 `songs` 表里找歌。  
- 第一步（心里想）：`SELECT id FROM artists WHERE name = 'Post Malone'`
- 第二步：把第一步塞进 `WHERE` 子句里。  
```sql
-- 6.sql
SELECT name
FROM songs
WHERE artist_id = (
    SELECT id
    FROM artists
    WHERE name = 'Post Malone'
);
```  
## 题 7：列出 Drake 的所有歌曲的平均“能量”  
这跟第 6 题逻辑一样，只是最后不是要 `name`，而是要 `AVG(energy)`。  
```sql
-- 7.sql
SELECT AVG(energy)
FROM songs
WHERE artist_id = (
    SELECT id
    FROM artists
    WHERE name = 'Drake'
);
```    
## 题 8：列出所有名字里带有 "feat." 的歌曲名称  
这里引入了 **模糊查询 (LIKE)**。
`%` 代表任意个字符。
`%feat.%` 表示：不管前面有什么，不管后面有什么，只要中间包含 "feat." 就行。
```sql
-- 8.sql
SELECT name
FROM songs
WHERE name LIKE '%feat.%';
```  
观察查询结果  
```sql
sqlite3 songs.db < 8.sql
+---------------------------------------------------------+
|                          name                           |
+---------------------------------------------------------+
| rockstar (feat. 21 Savage)                              |
| Psycho (feat. Ty Dolla $ign)                            |
| Girls Like You (feat. Cardi B)                          |
| Look Alive (feat. Drake)                                |
| These Days (feat. Jess Glynne, Macklemore & Dan Caplen) |
| Meant to Be (feat. Florida Georgia Line)                |
| Taste (feat. Offset)                                    |
| Solo (feat. Demi Lovato)                                |
| River (feat. Ed Sheeran)                                |
| Finesse (Remix) [feat. Cardi B]                         |
| Freaky Friday (feat. Chris Brown)                       |
| FEFE (feat. Nicki Minaj & Murda Beatz)                  |
| Body (feat. brando)                                     |
| Fuck Love (feat. Trippie Redd)                          |
| Dejala que vuelva (feat. Manuel Turizo)                 |
| 1, 2, 3 (feat. Jason Derulo & De La Ghetto)             |
| Corazon (feat. Nego do Borel)                           |
| I Miss You (feat. Julia Michaels)                       |
+---------------------------------------------------------+
```  
## Songs 经验总结

### 🧅 "洋葱剥皮法"

对于新手，不要试图一口气写出复杂的 SQL：

| 步骤 | 操作 | 说明 |
|------|------|------|
| 1️⃣ | `SELECT * FROM table` | 先保证能把数据取出来 |
| 2️⃣ | 加 `WHERE` | 过滤不需要的数据 |
| 3️⃣ | 加 `ORDER BY` 和 `LIMIT` | 整理顺序和数量 |
| 4️⃣ | 修改 `SELECT` | 换成需要的列名或聚合函数 |

### 本节知识点速查

| 关键字 | 用途 | 示例 |
|--------|------|------|
| `SELECT` | 选择列 | `SELECT name` |
| `FROM` | 指定表 | `FROM songs` |
| `WHERE` | 筛选条件 | `WHERE energy > 0.75` |
| `ORDER BY` | 排序 | `ORDER BY tempo DESC` |
| `LIMIT` | 限制数量 | `LIMIT 5` |
| `AVG()` | 平均值 | `SELECT AVG(energy)` |
| `LIKE` | 模糊匹配 | `WHERE name LIKE '%feat.%'` |

---  
# 2. Movies 🎬

**题目链接**：[https://cs50.harvard.edu/x/psets/7/movies/](https://cs50.harvard.edu/x/psets/7/movies/)

与第一题一样，数据源 `movies.db` 是一个 SQLite 数据库，其中存储了来自 IMDb 的电影数据，包括导演、主演及其评分。请编写 SQL 查询来回答有关这个电影数据库的问题。  
与上题一样，先查看 `movies.db` 结构   
```sql
sqlite3 movies.db
sqlite> .schema
CREATE TABLE directors (
    movie_id INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id),
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE movies (
    id INTEGER,
    title TEXT NOT NULL,
    year NUMERIC,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT NOT NULL,
    birth NUMERIC,
    PRIMARY KEY(id)
);
CREATE TABLE ratings (
    movie_id INTEGER NOT NULL UNIQUE,
    rating REAL NOT NULL,
    votes INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id)
);
CREATE TABLE stars (
    movie_id INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id),
    FOREIGN KEY(person_id) REFERENCES people(id)
);
```    
总体来看，这题相对第一题要复杂，涉及**多对多关系 (Many-to-Many Relationships)**。    
## 1. 结构分析（Mental Model）  
在开始写代码前，我们先看清楚这 5 张表是怎么连在一起的。把它们想象成一个网络： 
核心实体表：
movies：电影本身（ID, 标题, 年份）。
people：人（ID, 名字, 生日）。注意：这里的“人”既包含演员，也包含导演。
属性表：
ratings：评分表。它通过 movie_id 挂在 movies 表上。每部电影只有一个评分。
关联表（连接器） —— 最关键的部分：
stars：记录“谁演了哪部戏”。这是一个连接表，连接了 movies 和 people。
一行数据 {movie_id: 1, person_id: 101} 表示：人 101 演了电影 1。
directors：记录“谁导了哪部戏”。也是连接表，结构同上。  
- **核心实体表：**
  - `movies` : 电影本身（ID，标题，年份）  
  - `people`: 人（ID，名字，生日）。这里的人是演职人员，本库的演职人员是演员和导演。  
- **属性表：**  
  - ratings：评分表。它通过 movie_id 与 movies 表产生联系，每部电影只有一个评分。  
- **关联表（连接器）** - 最关键的部分：  
  - stars：记录“谁演了哪部戏”。这是一个连接表，连接了 `movies` 和 `people`。  
    - 一行数据 `{movie_id: 1, person_id: 101}` 表示：人 101 演了电影 1。
  - `directors`：记录“谁导了哪部戏”。也是连接表，结构同上。  
## 2. 逐步击破（精选难题解析）  
题目共有 13 道，前几道是简单的单表查询（类似 `songs`）  
### 题 1. 列出所有在 2008 年发布的电影名称。  
```sql
SELECT [我想看的列名]
FROM [数据来源的表名]
WHERE [筛选条件]
ORDER BY [排序依据]
LIMIT [只看前几条];
```    
- **我想看什么？** 名字 (`title`)
- **从哪看？** 歌曲表 (`movies`)
- **条件？** `WHERE year = 2008`
```sql
-- 1.sql
SELECT title
FROM movies
WHERE year = 2008;
```   
### 题 2. 查询  Emma Stone 的出生年份  
```sql
SELECT birth 
FROM people 
WHERE name = 'Emma Stone';
```   
### 题 3： 查询 2018年之后发行的电影，按字母序排序  
```sql
SELECT title
FROM movies
WHERE year >= 2018
ORDER BY title;
```  
### 题 4： 统计 IMDb 评分 10.0 的电影数  
```sql
SELECT COUNT(*) 
FROM ratings 
WHERE rating = 10.0;
```  
### 题 5：列出所有Harry Potter电影的海报标题和发布年份，按时间顺序排列。  
```sql
SELECT title,year
FROM movies
WHERE title like  'Harry Potter%'
ORDER BY year;
```  
### 题 6：计算2012年发行的电影的平均评分。  
- 这涉及两张表：`movies` (知道年份) 和 `ratings` (知道分数)。
- 子查询思路：先在 `movies` 找 `2012` 的 `ID`，再去 `ratings` 算分。
```sql
SELECT AVG(rating) 
FROM ratings 
WHERE movie_id IN (
    SELECT id 
    FROM movies 
    WHERE year = 2012
);
```   
### 题 7：查询2010年发行的电影以及对应的评分，按评分降序排序，如果评分相等，按 `title` 字母序。  
**思路：**  
- 显示：`movies.title`, `ratings.rating`。
- 连接：需要把两张表拼起来。这里 `JOIN` 比子查询更方便，因为要同时显示两张表的数据。
- 条件：`year = 2010`，`rating` 不为空。
- 排序：`ORDER BY rating DESC, title ASC`。
```sql
SELECT movies.title, ratings.rating 
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010
ORDER BY rating DESC, title;
```    
### 题 8：列出所有出演过《Toy Story》的演员  
**思路：**  
- 显示 `people.name`  
- 连接：使用 `JOIN` 把三张张表拼起来，people + stars + movies。`stars.person_id = people.id, stars.movie_id = movies.id` 
- 条件：title = Toy Story  
```sql
-- 8.sql
SELECT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = 'Toy Story';
```   
这题还可以使用嵌套查询  
- 分析：这是典型的 `people -> stars -> movies` 链条。
- 先找 Toy Story 的 ID。
- 再找 star 关系。
- 最后找人名  
```sql
-- 8.sql
SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT id
        FROM movies
        WHERE title = 'Toy Story'
    )
);
```   
对比总结：子查询 vs JOIN
- **子查询 (Subquery)：**
  - 思维方式是垂直钻取（先找 ID，再找 ID，再找名字）。
  - 逻辑像剥洋葱，一层包一层。
  - 通常在只需要一个最终结果列（如只查 name）时，性能很好，逻辑也很清晰。
- **连接查询 (JOIN)：**
  - 思维方式是水平拼接（把相关信息全摊平放在一张大表里）。
  - 逻辑像拼图。
  - 如果你同时需要 `people.name` 和 `movies.year`（跨表取多列数据），那么 `JOIN` 是必须的。  
## 题 9：列出所有出演2004年上映电影的演员姓名，并按出生年份排序。  
**思路：**
- 显示： perple.name
- 条件： 出演过 `year = 2004` 的电影  
- 排序： `ORDER BY birth`  
- **去重**：一个人可能在 2004 年演了好几部电影，名字不能重复出现，必须用 DISTINCT。 
```sql
-- 9.sql
SELECT DISTINCT(name)
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT id 
        FROM movies
        WHERE year = 2004
    )
)
ORDER BY birth;
``` 
**是否去重对比**    
```bash
# 去重
week7/movies/ $ sqlite3 movies.db <9.sql  | wc -l
36060
# 未去重
week7/movies/ $ sqlite3 movies.db <9.sql  | wc -l
36223
```  
可以看出还要有重复的。  
## 题 10：列出所有曾执导过评分至少为9.0的电影的人员姓名。  
**思路：**  
- 显示 people.name
- 条件： ratings.rating >= 9.0

```sql
-- 10.sql
SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM directors
    WHERE movie_id IN (
        SELECT movie_id FROM ratings
        WHERE rating >= 9.0
    )
);
```
## 题 11：按评分从高到低列出Chadwick Boseman主演的五部最高评分电影的片名   
**思路：**  
- 显示：movies.title
- 条件：Chadwick Boseman 主演
- 排序：ORDER BY rating 
- 限制： LIMIT 5  
这道题不仅要筛选，还要排序。如果用子查询会写出四五层，非常容易晕。
这时候，JOIN 就显示出威力了。**JOIN** 可以把多张表“横向拼接”成一张超级大表。  
JOIN 逻辑：
我们需要的信息分散在：`people` (名字), `stars` (参演关系), `movies` (电影名), `ratings` (分数)。  
我们可以把这 4 张表连起来：
`people -> stars -> movies -> ratings`  

```sql 
-- 11.sql
SELECT title 
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;
```  
题 12：列出所有由Bradley Cooper和Jennifer Lawrence共同主演的电影标题。  
这是经典的 **"Intersection"（交集）** 问题。
**思路**：
思路：
先找出 Bradley Cooper 演过的所有电影 ID。
再找出 Jennifer Lawrence 演过的所有电影 ID。
最后找出两个列表中**重叠**的部分。   
```sql
-- 12.sql
SELECT title FROM movies 
WHERE id IN (
    SELECT movie_id FROM stars 
    WHERE person_id IN (
        SELECT id FROM people
        WHERE name = 'Bradley Cooper'
    )
)
AND id IN (
    SELECT movie_id FROM stars
    WHERE person_id IN (
        SELECT id FROM people
        WHERE name = 'Jennifer Lawrence'
    )
);
```
还可以使用 JOIN  
```sql
-- 12.sql
SELECT title FROM movies
WHERE id IN (
    SELECT movie_id FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE name = 'Bradley Cooper'
)
AND id IN (
    SELECT movie_id FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE name = 'Jennifer Lawrence'
);
```
## 题 13：列出所有与Kevin Bacon共同出演过电影的演员姓名。
查询结果应输出单列表格，每行显示一名演员的姓名。
数据库中可能存在多名名为Kevin Bacon的演员，请确保仅选择1958年出生的Kevin Bacon。
查询结果中不应包含Kevin Bacon本人。   
拆解下就是：找出所有与 1958年出生的 Kevin Bacon 共同出演电影的演员。  
**思路：**  
1. 找出 1958年出生的 Kevin Bacon 的 ID
2. 找出他出演的所有电影的 ID  
3. 找到这些电影所有出演的演员的 ID  
4. 打印出他们的名字，记得剔除 Kevin Bacon  
```sql
-- 13.sql
SELECT DISTINCT(name) FROM people  -- 5. 找名字 (去重 DISTINCT)
WHERE id IN (
    -- 4. 找这些电影里的演员 ID
    SELECT person_id FROM stars 
    WHERE movie_id IN (
        -- 3. 找 Kevin 演过的电影 ID
        SELECT movie_id FROM stars 
        WHERE person_id = (
            -- 2. 找 Kevin 的 ID
            SELECT id FROM people 
            WHERE name = 'Kevin Bacon' AND birth = 1958
        )
    )
)
AND name != 'Kevin Bacon'; -- 排除自己
```  
### Movies 总结

#### 关键技巧

| 技巧 | 说明 | 示例 |
|------|------|------|
| `DISTINCT` | 去重，避免重复出现 | `SELECT DISTINCT(name)` |
| `IN` vs `=` | `IN` 用于多值，`=` 用于单值 | `WHERE id IN (...)` |
| 同名处理 | 用额外条件区分同名人 | `WHERE name = 'Kevin Bacon' AND birth = 1958` |

#### 子查询 vs JOIN 对比

| 特性 | 子查询 (Subquery) | JOIN |
|------|------------------|------|
| 思维方式 | 垂直钻取（一层层剥洋葱） | 水平拼接（拼图） |
| 适用场景 | 只需要一个最终结果列 | 需要跨表取多列数据 |
| 可读性 | 逻辑清晰但可能嵌套深 | 表多时更直观 |

> 💡 **新手建议**：统统用 `IN`，不容易出错。

--- 
# 3. Fiftyville 🔍 侦探游戏

**题目链接**：[https://cs50.harvard.edu/x/psets/7/fiftyville/](https://cs50.harvard.edu/x/psets/7/fiftyville/)

这是一个开放式的侦探游戏。你的身份是侦探，你的工具是 SQL，你的目标是找出：

| 问题 | 目标 |
|------|------|
| 🦹 **谁是小偷？** | 找出窃取 CS50 鸭子的人 |
| ✈️ **小偷逃到了哪个城市？** | 确定逃跑目的地 |
| 🤝 **谁是同伙（接应者）？** | 找出帮助购买机票的人 |

> 🎯 这道题的难点不在于 SQL 语法（你已经会了），而在于**逻辑推理和信息拼接**。
同样，先查看 `fiftyville.db` 结构   
```sql
$ sqlite3 fiftyville.db 
sqlite> .tables
airports              crime_scene_reports   people              
atm_transactions      flights               phone_calls         
bakery_security_logs  interviews          
bank_accounts         passengers          
sqlite> .schema
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
```  
## 第一阶段：案发现场 (The Starting Point)  
题目描述中唯一确定的信息是：
- 案件发生在 **2025年7月28日**。
- 地点是 **Humphrey Street**。  
### 行动 1：查阅犯罪报告
我们需要看看警方的记录，找到案件的具体描述，这会给我们提供后续的线索。 
```sql
-- query crime report
SELECT description 
FROM crime_scene_reports 
WHERE year = 2025 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
```  
从数据库中可以查询到如下案件的描述  
```sql
--------------------+
|                                                                                                       description                                                                                                        |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
```  
由报告可知：“案件发生在上午 10:15 的 Bakery（面包店）。有三名目击者（Witnesses）接受了询问。”   
## 第二阶段：询问证人 (The Interviews)  
既然报告说有目击者，那我们就要去查 `interviews` 表。  
### 行动 2：查阅当天的询问记录  
```sql
-- query transcript of interviews
SELECT name, transcript FROM interviews
WHERE year = 2025 AND month = 7 AND day = 28;
```  
查询出三名证人的名字和证词  
```sql
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|  name   |                                                                                                                                                     transcript                                                                                                                                                      |
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
| Eugene  | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
| Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
| Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
```    
由证词可知  
| 证人   | 证词  | 推断 | 
| --- | ----------- | ---------------- |
| Ruth | 在盗窃发生后的十分钟内，窃贼在面包店停车场上车驶离。| 查看大约 10:15 到 10:25 之间）面包店停车场录像。 | 
| Eugene | 小偷在 Leggett Street ATM 取钱 | 可以查看 ATM  |
| Raymond | 窃贼离开面包店给同伙打了电话，通话时间不足一分钟。计划搭乘明天从五十镇出发的首班航班。让同伙购买机票。| 29日从五十镇出发的首班航班 |  
## 第三阶段：三条线索并行追踪 (Parallel Investigation)  
现在我们要分别处理这三条线索，最后求**交集**。  
### 线索 1：车牌号追踪 (The Car)
**目标**：找到案发时间段在面包店停车场**离开（exit）**的所有车牌。
**涉及表**：`bakery_security_logs`   
```sql
-- query license_plate
SELECT license_plate FROM bakery_security_logs
WHERE year = 2025 AND month = 7 AND day = 28
AND hour = 10 AND minute >= 15 AND minute <= 25
AND activity = 'exit';
```   
查询到这个时间段离开面包店停车场的车辆有：  
```sql
+---------------+
| license_plate |
+---------------+
| 5P2BI95       |
| 94KL13X       |
| 6P58WS2       |
| 4328GD8       |
| G412CB7       |
| L93JTIZ       |
| 322W7JE       |
| 0NTHK55       |
+---------------+
```   
记下这些车牌号，把这个查询结果作为后续查询的子查询。  
### 线索 2：资金流向追踪 (The Money)  
**目标**：找到当天在 Leggett Street 取款（withdraw）的所有银行账号，进而找到对应的人。
**涉及表**：`atm_transactions -> bank_accounts -> people`
**逻辑**：ATM 表有账号，Bank 表把账号和人连起来。    
```sql
-- query person base back account
SELECT person_id FROM bank_accounts
WHERE account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2025 AND month = 7 AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
);
```  
查询到取钱的人的有 
```sql
+-----------+
| person_id |
+-----------+
| 686048    |
| 514354    |
| 458378    |
| 395717    |
| 396669    |
| 467400    |
| 449774    |
| 438727    |
+-----------+
```  
### 线索 3：电话追踪 (The Phone Call)  
目标：找到当天通话时间少于 60 秒的打电话的人（C`aller`）。
涉及表：`phone_calls -> people`   
注意：这里能顺便找到接收者（Receiver），也就是同伙！
```sql
-- query the caller 
SELECT caller
FROM phone_calls
WHERE year = 2025 AND month = 7 AND day = 28
AND duration < 60;
```  
查询到以下数据  
```sql
+----------------+
|     caller     |
+----------------+
| (130) 555-0289 |
| (499) 555-9472 |
| (367) 555-5533 |
| (499) 555-9472 |
| (286) 555-6063 |
| (770) 555-1861 |
| (031) 555-6622 |
| (826) 555-1652 |
| (338) 555-6650 |
+----------------+
```  
### 线索 4：航班追踪 (The Flight)  
**目标**：找到案发第二天（7月29日）从 Fiftyville 出发的、最早的一班飞机，以及上面的乘客。
**涉及表**：`airports -> flights -> passengers`  
#### 1. 找 Fiftyville 的机场 ID：
```sql
SELECT id FROM airports WHERE city = 'Fiftyville';
```  
查询结果  
```sql
+----+
| id |
+----+
| 8  |
+----+
```  
#### 2. 找最早航班：
```sql
-- earliest flight
SELECT id, destination_airport_id, hour, minute 
FROM flights 
WHERE origin_airport_id = 8 
AND year = 2025 AND month = 7 AND day = 29 
ORDER BY hour, minute 
LIMIT 1;
```   
最早的航班信息   
```sql
+----+------------------------+------+--------+
| id | destination_airport_id | hour | minute |
+----+------------------------+------+--------+
| 36 | 4                      | 8    | 20     |
+----+------------------------+------+--------+
```  
#### 3. 找乘客护照号：  
```sql
-- query passengers
SELECT passport_number FROM passengers
WHERE flight_id = 36;
```   
查询如下乘客  
```sql
+-----------------+
| passport_number |
+-----------------+
| 7214083635      |
| 1695452385      |
| 5773159633      |
| 1540955065      |
| 8294398571      |
| 1988161715      |
| 9878712108      |
| 8496433585      |
+-----------------+
```  
## 第四阶段：收网 (The Intersection)  
1. 车牌在面包店出现过的人。
2. 取过钱的人。
3. 打过电话的人。
4. 买了机票的人。   
写一个超级 SQL，把它们全部 `INTERSECT` 或者用 `AND` 连接起来查找 `people` 表：  
超级 sql 的格式如下：
```sql
-- lock the theif
SELECT name
FROM people
WHERE
    -- 1. 必须是那天早上开车离开的人 (车牌匹配)
    license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2025 AND month = 7 AND day = 28
        AND hour = 10 AND minute >= 15 AND minute <= 25
        AND activity = 'exit'
    )
AND
    -- 2. 必须是那天取过钱的人 (ID 匹配)
    id IN (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number FROM atm_transactions
            WHERE year = 2025 AND month = 7 AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
        )
    )
AND
    -- 3. 必须是那天打过短电话的人 (电话号码匹配)
    phone_number IN (
        SELECT caller FROM phone_calls
        WHERE year = 2025 AND month = 7 AND day = 28
        AND duration < 60
    )
AND
    -- 4. 必须是那个最早航班的乘客 (护照号匹配)
    passport_number IN (
        SELECT passport_number FROM passengers
        WHERE flight_id = 36
    );
```  
最终锁定结果  
```sql
sqlite3 fiftyville.db  < log.sql
+-------+
| name  |
+-------+
| Bruce |
+-------+
```  

## 第五阶段：找出逃逸城市 (The Destination)

我们已经知道航班 ID 是 36，目的地机场 ID 是 4。现在查询目的地城市：

```sql
-- query destination city
SELECT city FROM airports WHERE id = 4;
```

查询结果：
```sql
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
```

**小偷逃往了 New York City！** 🗽

## 第六阶段：找出同伙 (The Accomplice)

根据 Raymond 的证词，小偷在离开面包店时打了一个电话，让对方帮忙买机票。我们需要：
1. 找到 Bruce 的电话号码
2. 找到他当天打的那个短电话的接收者
3. 通过接收者的电话号码找到同伙的名字

### 步骤 1：找 Bruce 的电话号码
```sql
SELECT phone_number FROM people WHERE name = 'Bruce';
```
```sql
+----------------+
|  phone_number  |
+----------------+
| (367) 555-5533 |
+----------------+
```

### 步骤 2：找到接收者的电话号码
```sql
SELECT receiver FROM phone_calls
WHERE year = 2025 AND month = 7 AND day = 28
AND duration < 60
AND caller = '(367) 555-5533';
```
```sql
+----------------+
|    receiver    |
+----------------+
| (375) 555-8161 |
+----------------+
```

### 步骤 3：找到同伙的名字
```sql
SELECT name FROM people WHERE phone_number = '(375) 555-8161';
```
```sql
+-------+
| name  |
+-------+
| Robin |
+-------+
```  

**同伙是 Robin！** 🤝

---

## 🎉 案件告破！最终答案

| 问题 | 答案 |
|------|------|
| 🦹 **小偷是谁？** | **Bruce** |
| ✈️ **逃往哪个城市？** | **New York City** |
| 🤝 **同伙是谁？** | **Robin** |

### 一步到位的超级查询（找同伙）

```sql
-- Find the accomplice in one query
SELECT name FROM people
WHERE phone_number = (
    SELECT receiver FROM phone_calls
    WHERE year = 2025 AND month = 7 AND day = 28
    AND duration < 60
    AND caller = (
        SELECT phone_number FROM people WHERE name = 'Bruce'
    )
);
```

---

# 总结

## SQL 技能进阶路线

| 阶段 | 技能点 | 对应题目 |
|------|--------|---------|
| 🌱 入门 | SELECT, WHERE, ORDER BY, LIMIT | Songs 1-5 |
| 🌿 进阶 | 聚合函数 (AVG, COUNT), LIKE 模糊查询 | Songs 5-8 |
| 🌳 中级 | 子查询 (Subquery), 嵌套查询 | Songs 6-7, Movies 6 |
| 🌲 高级 | JOIN 多表连接, DISTINCT 去重 | Movies 7-11 |
| 🏔️ 专家 | 复杂交集查询, 多条件组合 | Movies 12-13, Fiftyville |

## 核心方法论

### 🧅 "洋葱剥皮法"（适合新手）
1. 先写 `SELECT * FROM table` —— 确保能取出数据
2. 加 `WHERE` —— 过滤不需要的数据
3. 加 `ORDER BY` 和 `LIMIT` —— 整理顺序和数量
4. 最后修改 `SELECT` —— 换成需要的列名或聚合函数

### 🔗 子查询 vs JOIN 选择

| 场景 | 推荐方法 |
|------|---------|
| 只需要一列结果 | 子查询 |
| 需要多列跨表数据 | JOIN |
| 需要排序 + 筛选 | JOIN |
| 交集查询 | 多个 `AND id IN (...)` |

## 提交命令

```bash
# Songs
check50 cs50/problems/2026/x/songs
submit50 cs50/problems/2026/x/songs

# Movies
check50 cs50/problems/2026/x/movies
submit50 cs50/problems/2026/x/movies

# Fiftyville
check50 cs50/problems/2026/x/fiftyville
submit50 cs50/problems/2026/x/fiftyville
```

---

**参考资料**：
- [CS50 Problem Set 7](https://cs50.harvard.edu/x/psets/7/)
- [W3Schools SQL Tutorial](https://www.w3schools.com/sql/)
- [SQLite 官方文档](https://www.sqlite.org/docs.html)
