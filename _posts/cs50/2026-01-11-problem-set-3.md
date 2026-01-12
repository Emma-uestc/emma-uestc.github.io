---
layout: post
title: "CS50 Problem Set 3: Algorithms - 选举算法实战"
date: 2026-01-11 10:00:00 +0800
categories: [learning]
tags: [C, 算法, 排序, 递归, 选举系统]
---

# Problem Set 3 概述

本周的作业围绕**算法**主题展开，包含一道排序算法分析题和三道选举系统实现题。三道选举题难度循序渐进：

| 题目 | 难度 | 核心知识点 |
|------|------|-----------|
| Sort | ⭐ | 算法时间复杂度分析 |
| Plurality | ⭐⭐ | 结构体、线性搜索 |
| Runoff | ⭐⭐⭐ | 二维数组、状态管理 |
| Tideman | ⭐⭐⭐⭐⭐ | 图论、递归、DFS |

作业页面：[https://cs50.harvard.edu/x/psets/3/](https://cs50.harvard.edu/x/psets/3/)

---

# 1. Sort - 排序算法识别

## 题目理解

按照[教程](https://cs50.harvard.edu/x/psets/3/sort/)下载并解压文件后，我们看看有哪些文件：

```bash
cd sort/
sort/ $ ls -l 
total 1108
-rw-r--r-- 1 ubuntu ubuntu    125 Dec 31  2021 answers.txt
-rw-r--r-- 1 ubuntu ubuntu  48894 Dec 31  2021 random10000.txt
-rw-r--r-- 1 ubuntu ubuntu 288894 Dec 31  2021 random50000.txt
-rw-r--r-- 1 ubuntu ubuntu  23893 Dec 31  2021 random5000.txt
-rw-r--r-- 1 ubuntu ubuntu  48894 Dec 31  2021 reversed10000.txt
-rw-r--r-- 1 ubuntu ubuntu 288894 Dec 31  2021 reversed50000.txt
-rw-r--r-- 1 ubuntu ubuntu  23893 Dec 31  2021 reversed5000.txt
-rwxr-xr-x 1 ubuntu ubuntu   8368 Dec 31  2021 sort1*
-rwxr-xr-x 1 ubuntu ubuntu   8448 Dec 31  2021 sort2*
-rwxr-xr-x 1 ubuntu ubuntu   8368 Dec 31  2021 sort3*
-rw-r--r-- 1 ubuntu ubuntu  48894 Dec 31  2021 sorted10000.txt
-rw-r--r-- 1 ubuntu ubuntu 288894 Dec 31  2021 sorted50000.txt
-rw-r--r-- 1 ubuntu ubuntu  23893 Dec 31  2021 sorted5000.txt
```

课程已经提供了三种算法的实现：`sort1`、`sort2`、`sort3`，但我们不知道它们分别对应 **Selection Sort**、**Bubble Sort**、**Merge Sort** 中的哪一个。我们的任务是通过运行这三个程序来识别。

## 解题思路

### 步骤1：理解三种排序算法的特性

回顾本周课程中学习的三种算法特性：

| 算法 | 最坏情况 | 最好情况 | 关键特点 |
|------|---------|---------|---------|
| Selection Sort | 𝑂(n²) | Ω(n²) | **无论数据如何，时间复杂度都一样** |
| Bubble Sort | 𝑂(n²) | Ω(n) | **已排序数据极快**（可提前退出）|
| Merge Sort | 𝑂(n log n) | Ω(n log n) | **始终 n log n**，最快但稳定 |

**识别策略**：
- 如果在 **sorted** 数据上明显更快 → **Bubble Sort**
- 如果在所有数据上都很快且稳定 → **Merge Sort**
- 如果时间始终较慢且稳定 → **Selection Sort**

### 步骤2：运行实验

执行以下命令计时：

```bash
# 进入 sort 目录
cd sort

# 测试 sort1
time ./sort1 reversed5000.txt
time ./sort1 sorted5000.txt
time ./sort1 random5000.txt

# 对 sort2 和 sort3 重复上述实验
```

### 步骤3：分析结果

**sort1 的测试结果**：

```bash
$ time ./sort1 reversed5000.txt
real    0m0.066s
user    0m0.045s

$ time ./sort1 sorted5000.txt
real    0m0.045s    # ← 明显更快！
user    0m0.003s

$ time ./sort1 random5000.txt
real    0m0.056s
```

**分析**：sort1 在 sorted 数据上明显更快（0.003s vs 0.045s），这符合 **Bubble Sort** 的特性——已排序数据可以提前退出！

**sort2 的测试结果**：

```bash
$ time ./sort2 reversed10000.txt
real    0m0.047s

$ time ./sort2 sorted10000.txt
real    0m0.051s

$ time ./sort2 random10000.txt
real    0m0.041s
```

**分析**：sort2 在三种数据上的时间差别不大，且整体很快。这符合 **Merge Sort** 的特性——始终 𝑂(n log n)。

**sort3 的测试结果**：

```bash
$ time ./sort3 reversed10000.txt
real    0m0.132s

$ time ./sort3 sorted10000.txt
real    0m0.131s

$ time ./sort3 random10000.txt
real    0m0.159s
```

**分析**：sort3 在三种数据上时间相近且始终较慢（明显慢于 sort2）。这符合 **Selection Sort** 的特性——无论数据如何都是 𝑂(n²)。

### 最终答案

| 程序 | 算法 | 判断依据 |
|------|-----|---------|
| sort1 | **Bubble Sort** | sorted 数据明显更快 |
| sort2 | **Merge Sort** | 始终快且稳定 |
| sort3 | **Selection Sort** | 始终较慢且稳定 |

---

# 2. Plurality - 简单多数票选举

## 题目理解

题目链接：[https://cs50.harvard.edu/x/psets/3/plurality/](https://cs50.harvard.edu/x/psets/3/plurality/)

这是最简单的选举系统：
- 每个选民投**一票**给一个候选人
- 得票**最多**的候选人获胜
- 可能有多个并列第一（平局）

### 数据结构

```c
typedef struct
{
    string name;   // 候选人姓名
    int votes;     // 得票数
} candidate;

candidate candidates[MAX];  // 候选人数组
int candidate_count;        // 实际候选人数量
```

假设运行 `./plurality Alice Bob Charlie`，初始化后：

```
candidates[0]: {name: "Alice",   votes: 0}
candidates[1]: {name: "Bob",     votes: 0}
candidates[2]: {name: "Charlie", votes: 0}
candidate_count = 3
```

## 需要实现的函数

### 1. vote(string name) 函数

**功能**：给指定候选人增加一票

**思路**：
1. 遍历 `candidates` 数组
2. 使用 `strcmp` 比较字符串（Week 2 学过）
3. 找到则 `votes++`，返回 `true`
4. 未找到返回 `false`

```c
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}
```

### 2. print_winner() 函数

**功能**：打印得票最多的候选人（可能有多个）

**思路**：
1. 遍历找出最高票数
2. 再次遍历，打印所有得票等于最高票数的候选人

```c
void print_winner(void)
{
    // 第一遍：找出最高票数
    int max_vote = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_vote)
        {
            max_vote = candidates[i].votes;
        }
    }
    
    // 第二遍：打印所有获胜者
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_vote)
        {
            // 根据 CS50 规范，只输出候选人名字
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
```

> ⚠️ **注意**：输出格式必须符合 CS50 规范，只输出候选人名字，不要加额外文字！

### 知识点回顾

这道题模拟了真实选举的基本流程：

```
真实选举流程          程序对应部分
─────────────────────────────────────
1. 确定候选人         命令行参数
2. 选民投票          vote() 函数
3. 统计票数          vote() 函数内部
4. 宣布结果          print_winner() 函数
```

涉及知识点：**结构体（Week 3）**、**字符串比较（Week 2）**、**线性搜索（Week 3）**

---

# 3. Runoff - 即时决选制

## 题目理解

题目链接：[https://cs50.harvard.edu/x/psets/3/runoff/](https://cs50.harvard.edu/x/psets/3/runoff/)

### Plurality vs Runoff

**Plurality（简单投票）**：

```
班级选班长，每人投1票
- 小明：2票
- 小红：2票
- 小刚：1票
结果：小明和小红并列第一（平局）
```

**Runoff（即时决选）**：

```
班级选班长，每人给所有候选人排名

选民1：第1选择 小明，第2选择 小红，第3选择 小刚
选民2：第1选择 小明，第2选择 小刚，第3选择 小红
选民3：第1选择 小红，第2选择 小明，第3选择 小刚
选民4：第1选择 小红，第2选择 小刚，第3选择 小明
选民5：第1选择 小刚，第2选择 小明，第3选择 小红
第1轮：看第1选择
- 小明：2票
- 小红：2票
- 小刚：1票
→ 没人过半（需要3票），淘汰最少的小刚

第2轮：小刚被淘汰，原本选他的人看第2选择
选民5原本第1选择是小刚，现在看他的第2选择：小明
- 小明：3票（2+1）
- 小红：2票
→ 小明过半，获胜！
```

### 核心数据结构

#### 1. preferences 二维数组

```c
int preferences[MAX_VOTERS][MAX_CANDIDATES];
```

这是一个二维数组，存储每个选民的候选人排序：
- `preferences[i][j]` = 第 i 个选民的第 j 选择是哪个候选人（**存储候选人索引**）

**示例**：3个选民，3个候选人（Alice=0, Bob=1, Charlie=2）

```
选民投票：
选民0: Rank 1: Alice, Rank 2: Bob, Rank 3: Charlie
选民1: Rank 1: Bob, Rank 2: Charlie, Rank 3: Alice
选民2: Rank 1: Charlie, Rank 2: Alice, Rank 3: Bob

转换为 preferences 数组：
                第1选择  第2选择  第3选择
preferences[0] = [  0  ,   1  ,   2  ]  (选民0的排序)
preferences[1] = [  1  ,   2  ,   0  ]  (选民1的排序)
preferences[2] = [  2  ,   0  ,   1  ]  (选民2的排序)
                  ↑       ↑       ↑
              存的是候选人的索引号
```

#### 2. 候选人结构体

```c
typedef struct
{
    string name;        // 名字
    int votes;          // 当前轮次的票数
    bool eliminated;    // 是否被淘汰
} candidate;
```

## 选举流程详解

**示例设置**：
- **候选人**：Alice(0), Bob(1), Charlie(2)
- **选民数**：5人

### 步骤1：收集选票

```
选民0: Alice > Bob > Charlie  →  preferences[0] = [0, 1, 2]
选民1: Alice > Bob > Charlie  →  preferences[1] = [0, 1, 2]
选民2: Bob > Charlie > Alice  →  preferences[2] = [1, 2, 0]
选民3: Bob > Charlie > Alice  →  preferences[3] = [1, 2, 0]
选民4: Charlie > Alice > Bob  →  preferences[4] = [2, 0, 1]
```

### 步骤2：第1轮统计（tabulate）

看每个选民的第1选择 `preferences[i][0]`：

```
voter 0: preferences[0][0] = 0 → Alice +1票
voter 1: preferences[1][0] = 0 → Alice +1票
voter 2: preferences[2][0] = 1 → Bob +1票
voter 3: preferences[3][0] = 1 → Bob +1票
voter 4: preferences[4][0] = 2 → Charlie +1票

结果：Alice: 2票, Bob: 2票, Charlie: 1票
```

### 步骤3：检查获胜者（print_winner）

需要 5/2 + 1 = 3 票才能获胜，没人达到 → 继续

### 步骤4-6：淘汰最少票数候选人

- `find_min()`: 最少票数 = 1
- `is_tie()`: 不是所有人都是1票 → 不是平局
- `eliminate()`: 淘汰 Charlie

### 步骤7：第2轮统计

重新统计，跳过被淘汰的候选人：

```
voter 4: 第1选择 Charlie(2) → 已淘汰！
         看第2选择 Alice(0) → 没淘汰 → Alice +1票

结果：Alice: 3票, Bob: 2票
```

### 步骤8：Alice 获胜！

Alice 有3票 > 2.5 → **Alice 获胜！**

## 需要实现的6个函数

### 1. vote() - 记录选民的排序

```c
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}
```

### 2. tabulate() - 统计票数（最关键！）

```c
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];
            
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break;  // 重要：一人一轮一票！
            }
        }
    }
}
```

> ⚠️ **关键点**：找到第一个没被淘汰的候选人后必须 `break`！否则一个选民会给多个人投票。

### 3. print_winner() - 检查获胜者

```c
bool print_winner(void)
{
    int majority = voter_count / 2 + 1;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}
```

### 4. find_min() - 找最少票数

```c
int find_min(void)
{
    int min_votes = voter_count;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}
```

### 5. is_tie() - 检查平局

```c
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}
```

### 6. eliminate() - 淘汰最少票候选人

```c
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
```

## 常见疑问解答

### Q1: 为什么平局时所有剩余候选人都获胜？

**回答**：因为算法进入了"死胡同"。

假设剩下 Alice、Bob、Charlie 各3票：
- 没人过半 → 需要淘汰
- 最少票数 = 3，所有人都是3票
- 如果继续淘汰，**所有人都会被踢出**！

为了防止这种情况，平局时宣布所有剩余候选人共同获胜。

### Q2: 为什么新一轮统计时所有候选人票数都置零？

**回答**：这是**数据安全性**和**工程简洁性**的考虑。

虽然被淘汰候选人的票数"理论上"不会被使用，但保留**脏数据**（旧的无意义数据）是危险的。每轮开始时统一清零，确保状态干净，不易出 Bug。

---

# 4. Tideman - 排名对投票法（最难！）

## 题目理解

题目链接：[https://cs50.harvard.edu/x/psets/3/tideman/](https://cs50.harvard.edu/x/psets/3/tideman/)

Tideman（也叫 Ranked Pairs）是三种投票方法中**最复杂**的，但它能保证选出**康多塞赢家**（Condorcet Winner）。

### 什么是康多塞赢家？

**定义**：在所有一对一对决中都能获胜的候选人。

**示例**：

```
候选人：小明、小红、小刚
9个选民的排序：

选民1-4：小刚 > 小红 > 小明
选民5-7：小红 > 小明 > 小刚
选民8-9：小明 > 小红 > 小刚

简单投票（只看第1选择）：
- 小刚：4票（最多）→ 小刚获胜

但是！一对一对决：

小红 vs 小刚：
- 喜欢小红 > 小刚：选民5-9 = 5人
- 喜欢小刚 > 小红：选民1-4 = 4人
→ 小红胜

小红 vs 小明：
- 喜欢小红 > 小明：选民1-7 = 7人
- 喜欢小明 > 小红：选民8-9 = 2人
→ 小红胜

结论：小红在所有一对一对决中都赢了！
小红是康多塞赢家，应该当选。
```

### Tideman 算法三步骤

#### 步骤1：Tally（统计偏好）

统计每一对候选人的对决结果，填入 `preferences` 矩阵。

**注意**：Tideman 的 `preferences` 与 Runoff **完全不同**！

| | Runoff | Tideman |
|-|--------|---------|
| **含义** | `preferences[选民][排名]` = 候选人索引 | `preferences[i][j]` = 有多少人认为 i 比 j 好 |
| **维度** | 选民 × 候选人 | 候选人 × 候选人 |

**Tideman 示例**：

```
3个选民投票：
选民0: Alice > Bob > Charlie
选民1: Alice > Bob > Charlie
选民2: Bob > Charlie > Alice

preferences 矩阵：
           Alice  Bob  Charlie
           (0)    (1)   (2)
Alice(0)  [  0     2     2  ]  ← 2人认为Alice>Bob, 2人认为Alice>Charlie
Bob(1)    [  1     0     3  ]  ← 1人认为Bob>Alice, 3人认为Bob>Charlie
Charlie(2)[  1     0     0  ]  ← 1人认为Charlie>Alice

解读：
preferences[0][1] = 2  → 2人认为 Alice > Bob
preferences[1][0] = 1  → 1人认为 Bob > Alice
→ Alice 在与 Bob 的对决中获胜！
```

#### 步骤2：Sort（排序对决）

按**胜利优势**从大到小排序。

```
如果在 100 个选民中：
- A vs B: A 拿了 99 票，B 拿了 1 票（A 狂胜 B）
- C vs D: C 拿了 51 票，D 拿了 49 票（C 险胜 D）

Tideman 认为，"A 赢 B"这件事比"C 赢 D"更可信、更有分量。
我们要优先确立那些"狂胜"的关系。
```

#### 步骤3：Lock（锁定胜局，避免循环）

按顺序添加箭头，**但不能形成循环**。

```
如果已有：
A → B (A 赢 B)
B → C (B 赢 C)

现在想添加 C → A（C 赢 A）...
但这会形成循环：A → B → C → A（石头剪刀布！）

Tideman 规则：跳过这条边，不添加。
```

### 数据结构详解

#### 1. preferences 数组

```c
int preferences[MAX][MAX];
// preferences[i][j] = 有多少人认为候选人 i 比候选人 j 好
```

#### 2. pairs 数组

```c
typedef struct
{
    int winner;   // 赢家索引
    int loser;    // 输家索引
} pair;

pair pairs[MAX * (MAX - 1) / 2];
```

#### 3. locked 数组（图的邻接矩阵）

```c
bool locked[MAX][MAX];
// locked[i][j] = true 表示锁定 i → j 这条边
```

## 需要实现的6个函数

### 1. vote() - 记录单个排名

```c
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}
```

### 2. record_preferences() - 更新偏好矩阵

**核心逻辑**：对于排序中的每一对候选人，前面的比后面的好

```c
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // ranks[i] 排在 ranks[j] 前面
            // 所以 ranks[i] 比 ranks[j] 好
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}
```

**示例**：

```
ranks = [0, 1, 2]  表示 Alice(0) > Bob(1) > Charlie(2)

i=0, j=1: Alice(0) > Bob(1) → preferences[0][1]++
i=0, j=2: Alice(0) > Charlie(2) → preferences[0][2]++
i=1, j=2: Bob(1) > Charlie(2) → preferences[1][2]++
```

### 3. add_pairs() - 创建候选对

```c
void add_pairs(void)
{
    pair_count = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // 平局不添加
        }
    }
}
```

### 4. sort_pairs() - 按优势排序

```c
void sort_pairs(void)
{
    // 使用选择排序，按优势强度从大到小排序
    for (int i = 0; i < pair_count - 1; i++)
    {
        int max_index = i;
        int max_strength = preferences[pairs[i].winner][pairs[i].loser];
        
        // 注意：这里是 pair_count，不是 candidate_count！
        for (int j = i + 1; j < pair_count; j++)
        {
            int strength = preferences[pairs[j].winner][pairs[j].loser];
            if (strength > max_strength)
            {
                max_index = j;
                max_strength = strength;
            }
        }
        
        if (max_index != i)
        {
            pair tmp = pairs[i];
            pairs[i] = pairs[max_index];
            pairs[max_index] = tmp;
        }
    }
}
```

> ⚠️ **常见 Bug**：循环条件写成 `j < candidate_count` 而不是 `j < pair_count`，这会导致数组越界！

### 5. lock_pairs() - 锁定边（使用 DFS 检测循环）

这是**最难**的一步，需要使用**递归 DFS（深度优先搜索）**。

**思路**：在添加边 `winner → loser` 之前，检查是否已经存在从 `loser` 到 `winner` 的路径。如果存在，添加这条边就会形成循环。

```c
// 检查添加 start → end 是否会形成循环
// 使用 DFS：从 end 出发，能否到达 start？
bool create_cycle(int start, int end)
{
    // 基础情况：如果 end 就是 start，说明形成了循环
    if (start == end)
    {
        return true;
    }

    // 递归步骤：检查从 end 出发的所有边
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            // 关键：必须检查递归调用的返回值！
            if (create_cycle(start, i))
            {
                return true;
            }
        }
    }

    return false;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        
        // 只有不会形成循环时才锁定
        if (!create_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}
```

> ⚠️ **严重 Bug 警告**：很多同学在 `create_cycle` 中忘记检查递归返回值，写成：
> ```c
> if (locked[end][i])
> {
>     create_cycle(start, i);  // 错误！没有检查返回值
>     return true;             // 错误！直接返回 true
> }
> ```
> 这会导致只要有任何边存在就返回 `true`，完全破坏了循环检测逻辑！

### 6. print_winner() - 找图的源头

**源头**：没有任何箭头指向的候选人。

```c
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;
        
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])  // 有人指向 i
            {
                is_source = false;
                break;
            }
        }
        
        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
```

## 完整示例

```
候选人：Alice(0), Bob(1), Charlie(2)
选民投票后：
- Bob > Charlie (优势: 3)
- Alice > Bob (优势: 1)
- Alice > Charlie (优势: 1)

排序后的 pairs：
0. Bob(1) → Charlie(2)  优势最大
1. Alice(0) → Bob(1)
2. Alice(0) → Charlie(2)

锁定过程：
1. 锁定 Bob → Charlie ✓
2. 锁定 Alice → Bob ✓（不会形成循环）
3. 锁定 Alice → Charlie ✓（不会形成循环）

最终图：
[Alice] → [Bob] → [Charlie]
    ↓_______________↗

检查源头：
- Alice(0): 没有箭头指向 → 是源头！
- Bob(1): Alice 指向它 → 不是源头
- Charlie(2): Alice 和 Bob 都指向它 → 不是源头

获胜者：Alice
```

---

# 总结

## 知识点对照表

| 题目 | 核心算法/数据结构 | 课程对应内容 |
|------|------------------|-------------|
| Sort | 时间复杂度分析 | Week 3: Big O, Ω, Θ |
| Plurality | 结构体、线性搜索 | Week 3: Structs, Linear Search |
| Runoff | 二维数组、状态机 | Week 2: Arrays; Week 3: Algorithms |
| Tideman | 图论、递归 DFS | Week 3: Recursion, Graph (optional) |

## 常见错误清单

| 错误类型 | 具体错误 | 正确做法 |
|---------|---------|---------|
| 输出格式 | 多余文字如 "the winner is" | 只输出候选人名字 |
| 循环条件 | `j < candidate_count` | `j < pair_count`（在 sort_pairs 中） |
| 递归返回 | 忘记检查递归返回值 | `if (create_cycle(...)) return true;` |
| 数组含义 | 混淆 Runoff 和 Tideman 的 preferences | 仔细阅读题目定义 |

## 调试技巧

1. **使用 printf 调试**：在关键位置打印变量值
   ```c
   printf("preferences[%i][%i] = %i\n", i, j, preferences[i][j]);
   ```

2. **画图辅助**：对于 Tideman，在纸上画出候选人图

3. **边界测试**：
   - 只有 1 个候选人
   - 所有人平局
   - 最大候选人数（9人）

4. **使用 check50**：
   ```bash
   check50 cs50/problems/2025/x/tideman
   ```

## 延伸学习

- **DFS（深度优先搜索）**：本题中用于检测循环，是《数据结构与算法》课程的重要内容
- **图论**：locked 数组其实是图的**邻接矩阵**表示
- **选举理论**：了解更多投票系统如 Borda Count、Schulze Method

---

**参考资料**：
- [CS50 Problem Set 3 官方页面](https://cs50.harvard.edu/x/psets/3/)
- [Tideman 投票法维基百科](https://en.wikipedia.org/wiki/Ranked_pairs)
- [图论入门教程](https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/)

下次见！ 🚀

