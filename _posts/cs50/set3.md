# 1. Sort  
按照[教程](https://cs50.harvard.edu/x/psets/3/sort/)中下载并解压，我们看下有哪些文件  
```
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
课程已经提供了三种算法的实现, `sort1`,`sort2`,`sort3`,但是我们并不知道分别对应`Selection Sort`，`Bubble Sort`，`Merge Sort`的哪个，我们的任务就是通过运行这三个程序验证识别。  
## 如何识别呢  
步骤1. 理解三种排序算法的特性   
我们在课程上学习了这三种算法的特性  
| 算法 | 时间复杂度(最坏) | 时间复杂度(最好) | 特点 |
| --------|--------|------|------|------|
| Selection Sort | 𝑂(n²) | 𝑂(n²) | 无论什么数据都是𝑂(n²) |
| Bubble Sort | 𝑂(n²) | 𝑂(n) | 如果数据已排序，很快 | 
| Merge Sort | 𝑂(n log n) | 𝑂(n log n) | 始终 𝑂(n log n),最快 | 
步骤2. 运行实验   
执行以下命令  
```
# 进入 sort 目录
cd sort

# 运行程序并计时
time ./sort1 reversed5000.txt
time ./sort1 sorted5000.txt
time ./sort1 random5000.txt

# 对 sort2 和 sort3 重复上述实验
time ./sort2 reversed5000.txt
# ...
```  
观察重点   
1. 已排序的数据(sorted*.txt)  
  - Bubble Sort 会很快,𝑂(n)  
  - Selection Sort 和 Merge Sort 时间不变  
2. 逆序排序(reversed*.txt)  
  - 三种算法都比较慢   
  - 但 Merge Sort 仍然最快  
3. 随机数据(random*.txt)  
  - Merge Sort 明显最快  
  - Selection Sort 和 Bubble Sort 差不多慢  
步骤3： 推理判断  
结果  
* `time ./sort1 reversed5000.txt`  
```
4997
4998
4999
5000

real    0m0.066s
user    0m0.045s
sys     0m0.020s
```  
* `time ./sort1 sorted5000.txt`  
```
4997
4998
4999
5000

real    0m0.045s
user    0m0.003s
sys     0m0.019s
```  
* `time ./sort1 random5000.txt`  
```
4997
4998
4999
5000

real    0m0.056s
user    0m0.038s
sys     0m0.018s
``` 
sort1 最好和最坏的时间复杂度不同，随机顺序花费的时间介于这两者之间，判断sort1 是Bubble Sort,因为 Selection Sort 和 Merge Sort 都是稳定排序算法，最好，最坏情况是一样的  
继续  
* `time ./sort2 reversed5000.txt`  
```
real    0m0.034s
user    0m0.005s
sys     0m0.019s  
```  
* `time ./sort2 sorted5000.txt`  
```
real    0m0.032s
user    0m0.003s
sys     0m0.016s
```  
* `time ./sort2 random5000.txt`  
```
real    0m0.022s
user    0m0.006s
sys     0m0.016s
```  
* `time ./sort3 reversed5000.txt`  
* `time ./sort3 sorted5000.txt`   
* `time ./sort3 random5000.txt`  
5000的数据差别不明显，我们再看下10000的数据和50000的数据  
* `time ./sort1 reversed10000.txt`  
```
real    0m0.276s
user    0m0.184s
sys     0m0.042s
```  
* `time ./sort1 sorted10000.txt`   
```
real    0m0.044s
user    0m0.003s
sys     0m0.037s
```   
* `time ./sort1 random10000.txt`
```
real    0m0.185s
user    0m0.142s
sys     0m0.032s
```  
* `time ./sort2 reversed10000.txt`   
```
real    0m0.047s
user    0m0.009s
sys     0m0.033s
```
* `time ./sort2 sorted10000.txt`    
```
real    0m0.051s
user    0m0.010s
sys     0m0.031s
```  
* `time ./sort2 random10000.txt`
```
real    0m0.041s
user    0m0.006s
sys     0m0.032s
```  
sort2 的三种数据顺序时间复杂度差别不大，认为是稳定的，且逆序数据明显小于sort1，因此推断sort2是 Merge Sort.接着看下sort3 验证我们的推断  
* `time ./sort3 reversed10000.txt`  
```
real    0m0.132s
user    0m0.082s
sys     0m0.037s
```  
* `time ./sort3 sorted10000.txt`   
```
real    0m0.131s
user    0m0.068s
sys     0m0.039s
```  
* `time ./sort3 random10000.txt`
```
real    0m0.159s
user    0m0.092s
sys     0m0.034s
```  
同样sort3对于三种顺序的数据时间差别不大，明显高于sort2，所以sort2 为Selection Sort.   
# 2. plurality   
实现一个[plurality 选举](https://cs50.harvard.edu/x/psets/3/plurality/)  
## 题目理解  
这是一个简单的选举系统：
* 每个选民投一票给一个候选人
* 得票最多的候选人获胜
* 可能有多个并列第一（平局）  
已有的数据结构  
```C
typedef struct
{
    string name;   // 候选人姓名
    int votes;     // 得票数
} candidate;

candidate candidates[MAX];  // 候选人数组
int candidate_count;        // 实际候选人数量
```  
假设运行假设运行 `./plurality Alice Bob Charlie`, 初始化  
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
1. 遍历 candidates 数组， 
2. 查找名字匹配的 candidate(strmcp 比较字符串,notes中有详细讲解)  
3. 找到，该 candidate 的 votes + 1，返回true  
4. 没有找到，告诉选民无效的候选人，返回 false  
### 2. print_winner() 函数

**功能**：打印得票最多的候选人（可能有多个）

**思路**：
1. 找出最高票数
2. 打印所有得票等于最高票数的候选人  
这道题模拟了真实选举的基本流程：
```
真实选举流程          程序对应部分
─────────────────────────────────────
1. 确定候选人         命令行参数
2. 选民投票          vote() 函数
3. 统计票数          vote() 函数内部
4. 宣布结果          print_winner() 函数   
```  
知识点   
自定义数据类型，字符串  
## 代码实现   
```C
bool vote(string name)
{
    // 遍历所有候选人，查找匹配的名字
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

// Print the winner (or winners) of the election
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
# 3. Runoff   
## Runoff 是什么  
* Plurality vs Runoff  
Plurality（简单投票）：  
```
班级选班长，每人投1票
- 小明：2票
- 小红：2票
- 小刚：1票
结果：小明和小红并列第一（平局）
```  
Runoff（即时决选）：  
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
## 核心变量解释  
1. 偏好数组（preferences） 
`int preferences[MAX_VOTERS][MAX_CANDIDATES];`  
这是一个二维数组，每一行代表的是每个选民选择候选人的排序  
假设3个选民，3个候选人（Alice=0, Bob=1, Charlie=2）  
选民投票：
```
选民0: Rank 1: Alice, Rank 2: Bob, Rank 3: Charlie
选民1: Rank 1: Bob, Rank 2: Charlie, Rank 3: Alice
选民2: Rank 1: Charlie, Rank 2: Alice, Rank 3: Bob  
```  
转换为 preferences 数组：
```
                第1选择  第2选择  第3选择
preferences[0] = [  0  ,   1  ,   2  ]  (选民0的排序)
preferences[1] = [  1  ,   2  ,   0  ]  (选民1的排序)
preferences[2] = [  2  ,   0  ,   1  ]  (选民2的排序)
                  ↑       ↑       ↑
              存的是候选人的索引号
```    
**注意，preferences 数组 存储的是候选人的索引(Recall that preferences[i][j] stores the index of the candidate who is the jth ranked preference for the ith voter.)**  
2. 候选人结构体  
```C
typedef struct
{
    string name;        // 名字
    int votes;          // 当前轮次的票数
    bool eliminated;    // 是否被淘汰
} candidate;
```  
## 选举流程  
我们假设：  
**候选人**：Alice, Bob, Charlie
**选民数**：5人
程序给出候选人: Alice, Bob, Charlie，对应索引即为 0, 1, 2  
1. 收集选民选票   
```
选民0的排序：
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

选民1的排序：
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

选民2的排序：
Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

选民3的排序：
Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

选民4的排序：
Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob
```  
**转换为 preferences 数组**：  
```
         [第1] [第2] [第3]
voter 0: [  0,   1,   2  ]  (Alice, Bob, Charlie)
voter 1: [  0,   1,   2  ]  (Alice, Bob, Charlie)
voter 2: [  1,   2,   0  ]  (Bob, Charlie, Alice)
voter 3: [  1,   2,   0  ]  (Bob, Charlie, Alice)
voter 4: [  2,   0,   1  ]  (Charlie, Alice, Bob)
```  
收集选民选票的过程中需要判断选民的选票是否是有效选票，即只有有效选票才会被转换为 `preferences` 数组，无效选票返回false。  
这一步就是 `bool vote(int voter, int rank, string name);` ，也是我们需要补全实现的功能。  
**步骤2：第1轮统计（tabulate）**  
每一轮都有 tabulate,仔细阅读文档中 Hints 中 tabulate function 部分。  
看每个选民的第1选择 `preferences[i][0]`：  
```
voter 0: preferences[0][0] = 0 → Alice +1票
voter 1: preferences[1][0] = 0 → Alice +1票
voter 2: preferences[2][0] = 1 → Bob +1票
voter 3: preferences[3][0] = 1 → Bob +1票
voter 4: preferences[4][0] = 2 → Charlie +1票

结果：
Alice:   2票
Bob:     2票
Charlie: 1票
```    
**步骤3：检查是否有人过半（print_winner）**
如果没有就是没有赢家 
需要 5/2 = 2.5，向上取整 = 3票
没人有3票 → 没有赢家  
**步骤4：找出最少票数（find_min）**
最少票数 = 1（Charlie）  
**步骤4：找出最少票数（find_min）**

最少票数 = 1（Charlie）

**步骤5：检查是否平局（is_tie）**

不是所有人都是1票 → 不是平局

**步骤6：淘汰最少票的候选人（eliminate）**

淘汰 Charlie（设置 eliminated = true）

**步骤7：第2轮统计（tabulate）**

重新统计，但跳过被淘汰的候选人：  
```
voter 0: 第1选择 Alice(0) → 没淘汰 → Alice +1票
voter 1: 第1选择 Alice(0) → 没淘汰 → Alice +1票
voter 2: 第1选择 Bob(1) → 没淘汰 → Bob +1票
voter 3: 第1选择 Bob(1) → 没淘汰 → Bob +1票
voter 4: 第1选择 Charlie(2) → 已淘汰！
         看第2选择 Alice(0) → 没淘汰 → Alice +1票

结果：
Alice: 3票
Bob:   2票
```  
**步骤8：检查获胜者**

Alice 有3票 > 2.5 → **Alice 获胜！**  
## 四、需要实现的6个函数  
### 1. vote() - 记录选民的排序  
**功能**：将选民对某个候选人的排名记录到 preferences 数组

**参数**：
- `voter`：选民编号（第几个选民）
- `rank`：这是第几选择（0=第1选择，1=第2选择...）
- `name`：候选人名字  
**例子**：
```
vote(0, 0, "Alice")
→ 选民0的第1选择是Alice
→ 找到Alice的索引是0
→ preferences[0][0] = 0

vote(0, 1, "Bob")
→ 选民0的第2选择是Bob
→ 找到Bob的索引是1
→ preferences[0][1] = 1
```   
同学，别担心，Runoff（即时决选制）之所以是 Week 3 的“难关”，正是因为它的规则比简单的“谁票多谁赢”要复杂得多，而且涉及到了**二维数组**和**状态管理**。

作为你的“教授”，我先用最通俗的生活案例帮你把**选举规则**搞清楚，然后再带你把这些规则映射到代码上。

---

### 第一部分：Runoff（即时决选）到底是在选什么？

想象一下，你和 4 个朋友（共5人）决定去哪吃饭。候选项有三个：**麦当劳、肯德基、汉堡王**。

**如果是 Plurality（之前的题目）：**
每个人只举一次手。
- 2人选麦当劳
- 2人选肯德基
- 1人选汉堡王
结果：麦当劳和肯德基平局，这很尴尬。而且选汉堡王的那个人觉得自己的票完全浪费了。

**现在是 Runoff（本题规则）：**
为了公平，我们规定：每个人必须给这三家店**排名次**（排位）。

**第一轮：**
我们先看大家心中的 **No.1（第一志愿）** 是谁。
- 如果某家店拿到了**超过半数**（> 50%）的“第一志愿”，它直接获胜，游戏结束。
- 如果没有人超过半数（比如麦当劳 2票，肯德基 2票，汉堡王 1票，没人拿到 3票），那谁也没赢。

**淘汰与晋级（关键逻辑）：**
这时候，我们把得票**最少**的那家店淘汰掉（踢出局）。
- 汉堡王（1票）被淘汰了。标记为 `eliminated = true`。

**第二轮（重新计票）：**
关键来了！之前投给汉堡王的那个人，他的第一志愿没了。**他的票并不会作废，而是转移给他的“第二志愿”！**
- 假设那个人的排位是：1. 汉堡王，2. 麦当劳，3. 肯德基。
- 因为汉堡王没了，他的这一票现在算给**麦当劳**。

现在重新数票：
- 麦当劳：2票（原本的）+ 1票（从汉堡王转移过来的）= 3票。
- 肯德基：2票。
- 汉堡王：已淘汰。

**结果：** 麦当劳拿到了 3/5 的票，超过半数，胜出！
---

### 第二部分：核心数据结构解析

理解了规则，我们来看代码里的两个关键变量。这是解题的钥匙。

#### 1. `int preferences[MAX_VOTERS][MAX_CANDIDATES];`
这是一个**二维数组**。你可以把它看作一张 Excel 表格。
*   `i` (行)：代表第几位选民。
*   `j` (列)：代表第几志愿（Rank）。
*   **表格里的值**：代表候选人在 `candidates` 数组里的**索引（Index）**。

**例子：** `preferences[0][1] = 2;`
这行代码的意思是：**第 0 号选民**的**第 2 志愿**（因为索引是 1），是**索引为 2 的候选人**。

#### 2. `candidate candidates[MAX_CANDIDATES];`
每个候选人都有三个属性：
*   `name`: 名字 (Alice)
*   `votes`: 当前轮次的得票数
*   `eliminated`: 生死状态（`true` 表示被淘汰，`false` 表示还在场上）

---

### 第三部分：手把手教你实现 6 个函数

这里的逻辑必须严丝合缝。我们一个一个来。

#### 1. `vote` 函数
**目标**：把选民输入的“名字”，转换成候选人的“索引”，填入二维数组。

*   **输入**：`voter`（第几个选民），`rank`（第几志愿），`name`（选的名字）。
*   **逻辑**：
    1.  遍历所有候选人 (`candidate_count`)。
    2.  用 `strcmp` 比较名字。
    3.  如果名字匹配：
        *   把这个候选人的索引 `i` 存入 `preferences[voter][rank]`。
        *   返回 `true`。
    4.  如果找完都没匹配，返回 `false`。

#### 2. `tabulate` 函数（最难点）
**目标**：统计当前这一轮的票数。
**规则**：看每个选民的第一志愿。如果第一志愿被淘汰了，就看他的第二志愿……以此类推，直到找到一个**没被淘汰**的候选人，给这个人加一票。

*   **逻辑**：
    1.  写一个外层循环遍历所有选民 `i` (从 0 到 `voter_count`)。
    2.  在内部，写一个循环遍历该选民的志愿 `j` (从 0 到 `candidate_count`)。
    3.  **核心判断**：
        *   获取第 `i` 个选民第 `j` 志愿的候选人索引：`int candidate_index = preferences[i][j];`
        *   检查这个候选人：`if (candidates[candidate_index].eliminated == false)`
        *   如果没被淘汰：
            *   给这个人加票：`candidates[candidate_index].votes++;`
            *   **立刻 `break`**！(非常重要：因为这个选民这一轮的票已经投出去了，不能再看他的下一志愿了)。

#### 3. `print_winner` 函数
**目标**：看看有没有人票数过半。

*   **逻辑**：
    1.  遍历所有候选人。
    2.  如果 `candidates[i].votes > voter_count / 2`：
        *   打印名字。
        *   返回 `true`。
    3.  循环结束没人过半，返回 `false`。

#### 4. `find_min` 函数
**目标**：找出依然在场（没被淘汰）的候选人中，最低得票数是多少。

*   **逻辑**：
    1.  定义一个变量 `min`，初始化为 `voter_count` (或者一个很大的数)。
    2.  遍历所有候选人。
    3.  如果这个候选人 **没有被淘汰** 并且 **票数 < min**：
        *   更新 `min` = 他的票数。
    4.  返回 `min`。

#### 5. `is_tie` 函数
**目标**：判断剩下的候选人是不是全都平局（票数都等于 `min`）。如果是平局，就没法淘汰了，比赛直接结束，所有人都是赢家。

*   **逻辑**：
    1.  遍历所有候选人。
    2.  如果候选人 **没有被淘汰** 并且 **票数不等于 min**：
        *   说明有人票数比 min 高，不是平局。
        *   返回 `false`。
    3.  如果循环跑完了，说明所有幸存者的票数都等于 min。
    4.  返回 `true`。

#### 6. `eliminate` 函数
**目标**：淘汰掉票数最少的人。

*   **逻辑**：
    1.  遍历所有候选人。
    2.  如果候选人 **没有被淘汰** 并且 **票数等于 min**：
        *   `candidates[i].eliminated = true;`

---

### 教授的工程建议（Debugging Tips）

1.  **分步调试**：不要想着一次性写完这6个函数再编译。
    *   先写好 `vote`，通过 `check50` 看看 vote 部分对不对。
    *   再写 `tabulate` 和 `print_winner`，这是核心循环。
2.  **关于 Tabulate 的 Break**：很多同学在 `tabulate` 里面忘记写 `break`，导致一个选民在同一轮里给好几个人投了票（比如第一志愿没淘汰投了，第二志愿没淘汰又投了）。一定要记住：**一人一轮一票**。
3.  **数学陷阱**：在计算过半时，`voter_count / 2` 是整数除法。
    *   如果有 5 个选民，`5 / 2` 结果是 `2`。
    *   如果你得票 3，`3 > 2`，获胜。正确。
    *   如果有 4 个选民，`4 / 2` 结果是 `2`。
    *   如果你得票 2，`2 > 2` 是 false，没获胜（必须超过半数，不能只是达到半数）。正确。
    *   CS50 的测试用例通常能通过这种写法，但严谨的写法可以用浮点数比较或者 `votes * 2 > voter_count`。

## 疑问  
看完该问题的背景和runoff 选举机制后我觉得我理解了选举流程，但是在阅读课程提供的`runpff.c`框架代码是有以下疑问的  
1.   
```C
// If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }
```  
为什么平局就是每个候选人都是赢者。  
2. 
```C  
// Reset vote counts back to zero
for (int i = 0; i < candidate_count; i++)
{
candidates[i].votes = 0;
}  
```  
为什么新一轮tabulate 时选票置零时不排除已被eliminated 的候选人呢  
我把我的疑问发给了AI，AI给我答案是：  
这是一个非常敏锐的问题！同学，你能问出这两个问题，说明你不仅是在写代码，而且是在**思考系统的边界情况（Edge Cases）**和**数据的一致性**。这正是从“写代码的人（Coder）”向“工程师（Engineer）”转变的关键特征。

我们来逐一拆解这两个逻辑背后的设计意图。

---

### 问题 1：为什么平局了（Tie），剩下的每个候选人都是赢者？

**一句话总结：因为算法进入了“死胡同”，如果不再此处终止，所有人都会被淘汰。**

让我们推演一下如果不判赢，程序会发生什么。

#### 场景模拟
假设现在还剩下 3 个候选人：Alice, Bob, Charlie。
此时 `voter_count`（总票数）是 9 票。
由于某些原因，现在的计票结果是：
*   **Alice**: 3 票
*   **Bob**: 3 票
*   **Charlie**: 3 票

程序流程如下：
1.  **`print_winner`**: 有人超过半数（> 4.5）吗？没有。每个人都只有 3 票。继续。
2.  **`find_min`**: 最小得票数是多少？`min = 3`。
3.  **`is_tie`**: 大家都是 3 票吗？是的。

**如果不在这里停止（Break），继续往下走会发生什么？**

4.  **`eliminate(min)`**: 规则是“淘汰掉所有得票为 `min` 的人”。
    *   Alice 得票 3 (等于 min) -> **淘汰**。
    *   Bob 得票 3 (等于 min) -> **淘汰**。
    *   Charlie 得票 3 (等于 min) -> **淘汰**。

**结果**：所有候选人都被踢出局了，选举变成了“无人获胜”的空集。
在算法设计中，这叫做处理 **死锁（Deadlock）** 或 **终止条件（Termination Condition）**。
Runoff 算法的核心动力是“**通过淘汰最弱者来改变票数分布**”。但是，如果剩下的所有人一样强（票数相同），我们就无法定义谁是“最弱者”。
*   既然无法区分强弱，也就无法进行票数转移。
*   既然无法转移，局势就无法改变。
*   因此，此时剩下的所有人，在数学上被视为“并列第一”。

所以代码逻辑必须是：**如果剩下的幸存者完全平局，立即宣布所有人获胜并结束程序，防止把大家都杀掉。**

---

### 问题 2：为什么新一轮选票置零时，不排除已被 eliminated 的候选人？

代码如下：
```c
// Reset vote counts back to zero
for (int i = 0; i < candidate_count; i++)
{
    candidates[i].votes = 0;
}
```
你问的是：为什么不写成 `if (!candidates[i].eliminated) candidates[i].votes = 0;`？

这里有两个层面的原因：**工程简洁性** 和 **数据安全性**。

#### 1. 工程简洁性（KISS原则 - Keep It Simple, Stupid）
在计算机底层，CPU 执行简单的赋值操作（`votes = 0`）是非常极速的。
*   **方案 A（当前代码）**：不管三七二十一，把 9 个人的内存空间全清零。这是一种“无脑”但高效的清理。
*   **方案 B（你的想法）**：先读内存判断 `eliminated` 是真还是假（逻辑判断），如果是假，再写入内存。

对于只有 9 个候选人（`MAX_CANDIDATES`）的数组，**无差别清零**的代码更短、更不易出错，而且在现代 CPU 的流水线优化下，可能比带 `if` 判断的分支代码跑得还要快（或者没有区别）。既然结果一样，我们倾向于写更简单的代码。

#### 2. 防止“脏数据”（Stale Data）带来的隐患
这是更重要的原因。
虽然被淘汰的候选人理论上不会再参与计票，但在工程实践中，保留**脏数据**（旧的、无意义的数据）是非常危险的。

假设 Alice 在第一轮拿了 2 票，然后被淘汰了。
如果我们**不**把她的票数清零：
*   **第 2 轮开始时**：Alice 的 `votes` 依然存着 `2`。
*   **Tabulate 过程**：因为 `tabulate` 函数里有 `if (!candidates[i].eliminated)` 的检查，所以程序确实不会给 Alice 加新票。
*   **潜在风险**：万一你在后续的代码（比如 `print_winner` 或调试用的 `printf`）里，不小心漏写了 `!eliminated` 的检查，你就会惊讶地发现：“咦？Alice 已经被淘汰了，为什么她还有 2 票？” 这会给调试带来巨大的困惑。

**结论**：
通过 `candidates[i].votes = 0` 把所有人（包括死掉的候选人）票数归零，是为了保证 **每一轮计票开始前，所有人的票数状态都是绝对干净的（Clean Slate）**。

被淘汰的人：票数归零，且 `eliminated=true`。
幸存的人：票数归零，且 `eliminated=false`，等待 `tabulate` 重新填入数值。

这样状态最清晰，最不容易出 Bug。

---
# 4. tideman  

```shell
runoff/ $ cd ..
$ wget https://cdn.cs50.net/2024/fall/psets/3/tideman.zip
--2025-12-17 17:25:09--  https://cdn.cs50.net/2024/fall/psets/3/tideman.zip
Resolving cdn.cs50.net (cdn.cs50.net)... 3.167.56.43, 3.167.56.128, 3.167.56.46, ...
Connecting to cdn.cs50.net (cdn.cs50.net)|3.167.56.43|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 1237 (1.2K) [application/zip]
Saving to: ‘tideman.zip’

tideman.zip                                       100%[============================================================================================================>]   1.21K  --.-KB/s    in 0s      

2025-12-17 17:25:09 (775 MB/s) - ‘tideman.zip’ saved [1237/1237]

$ unzip tideman.zip 
Archive:  tideman.zip
   creating: tideman/
  inflating: tideman/tideman.c       
$ rm -rf tideman.zip 
$ cd tideman/
tideman/ $ ls
tideman.c
```  
Tideman（也叫 Ranked Pairs） 是三种投票方法中最复杂的。  
一、核心概念：康多塞赢家（Condorcet Winner）
什么是康多塞赢家？
定义：在所有一对一对决中都能获胜的候选人。
生活例子：班级选班长  
```
候选人：小明、小红、小刚
9个选民的排序：

选民1-4：小刚 > 小红 > 小明
选民5-7：小红 > 小明 > 小刚  
选民8-9：小明 > 小红 > 小刚

简单投票（只看第1选择）：
- 小刚：4票（最多）
- 小红：3票
- 小明：2票
→ 小刚获胜

但是！让我们看一对一对决：

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
二、Tideman 算法三步骤  
步骤1：小组赛计分Tally（统计偏好）
统计每一对候选人的对决结果。
示例：3个候选人（Alice=0, Bob=1, Charlie=2），3个选民  
```
选民0：Alice > Bob > Charlie
选民1：Alice > Bob > Charlie  
选民2：Bob > Charlie > Alice

对决统计：
Alice vs Bob：2人喜欢Alice，1人喜欢Bob → Alice赢，优势=2
Alice vs Charlie：2人喜欢Alice，1人喜欢Charlie → Alice赢，优势=2
Bob vs Charlie：3人喜欢Bob，0人喜欢Charlie → Bob赢，优势=3
```   
步骤2：确定胜负强度Sort（排序对决）
按优势强度从大到小排序。  
```
1. Bob > Charlie (优势: 3)
2. Alice > Bob (优势: 2)
3. Alice > Charlie (优势: 2)  
这个差别不大，为了说明问题，我们举一个特例   
如果在 100 个选民中：
- A vs B: A 拿了 99 票，B 拿了 1 票。（A 狂胜 B）
- C vs D: C 拿了 51 票，D 拿了 49 票。（C 险胜 D）
Tideman 认为，**“A 赢 B”这件事比“C 赢 D”更可信、更有分量**。所以我们要把所有的胜负关系按“赢了多少”进行排序。我们要优先确立那些“狂胜”的关系。
```   
步骤3：锁定胜局与防止死循环 (Lock - The Graph)
按顺序添加箭头，但不能形成循环。  
```
1. 锁定 Bob → Charlie ✓
   [Bob] → [Charlie]

2. 锁定 Alice → Bob ✓
   [Alice] → [Bob] → [Charlie]

3. 尝试锁定 Alice → Charlie
   如果添加，图仍然是：[Alice] → [Bob] → [Charlie]
   [Alice] → [Charlie] 可以添加 ✓

最终图：
   [Alice] → [Bob] → [Charlie]
        ↓____________↗

获胜者：Alice（没有箭头指向她）  
这是最难的一步。我们想象在白板上画图：
如果 A 赢了 B，我们就画一个箭头：A -> B。
如果 B 赢了 C，画箭头：B -> C。
这就形成了一个链条：A 胜过 B，B 胜过 C。逻辑上，A 也是胜过 C 的。
但是，如果出现了石头剪刀布呢？
A 赢 B (A -> B)
B 赢 C (B -> C)
C 赢 A (C -> A)
这就形成了一个环（Cycle）！一旦形成环，就没人是赢家了。
Tideman 的规则是：按照胜负强度顺序画箭头，如果画这根箭头会导致闭环，那就跳过这根箭头（不画），假装这场比赛没发生过。
```  
三、数据结构详解
1. preferences 数组（偏好矩阵）  
```C
int preferences[MAX][MAX];  
```  
`preferences[i][j]` = 有多少人认为候选人i比候选人j好,这个和runoff 是不同的  
- Runoff: pref[选民][第几名] = 候选人ID
**示例**：  
```
3个选民：
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
preferences[0][1] = 2  → 2人认为Alice > Bob
preferences[1][0] = 1  → 1人认为Bob > Alice  
```  
2. pairs 数组（候选对）  
要把所有的单挑结果存下来。  
```C
typedef struct
{
    int winner;   // 赢家索引
    int loser;    // 输家索引
} pair;

pair pairs[MAX * (MAX - 1) / 2];  
```  
**示例**：  
```
如果 Alice(0) 打败 Bob(1)，优势为2：
pairs[0] = {winner: 0, loser: 1}

如果 Bob(1) 打败 Charlie(2)，优势为3：
pairs[1] = {winner: 1, loser: 2}
```  
3. locked 数组（图的邻接矩阵）  
```C
bool locked[MAX][MAX];
```  
**示例**：  
```  
- `locked[i][j] = true` 意味着：我们正式锁定 i 击败 j。在图中画一条从 i 指向 j 的箭头。
- 如果在 lock_pairs 阶段发现会导致死循环，我们就保持 `locked[i][j] = false`。

locked 矩阵（true用✓表示）：
           Alice  Bob  Charlie
Alice(0)  [  -     ✓     ✓  ]  ← Alice → Bob, Alice → Charlie
Bob(1)    [  -     -     ✓  ]  ← Bob → Charlie
Charlie(2)[  -     -     -  ]

图形化：
[Alice] → [Bob]
   ↓         ↓
   └────→ [Charlie]
```  
四、六个函数详解
函数1：vote() - 记录单个排名
功能：把选民输入的名字转换成 ranks 数组。  
输入：rank（目前的排名，比如第0名、第1名），name（名字），ranks[]（输出数组）。  
逻辑：和 Runoff 几乎一样。遍历 candidates，对比名字，找到索引，存入 ranks[rank] = index。  
```C
// 输入：rank=0, name="Alice", ranks数组
// 输出：ranks[0] = 0 (Alice的索引)

bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;  // 记录索引
            return true;
        }
    }
    return false;
}
```  
**示例**：
```
candidates = ["Alice", "Bob", "Charlie"]

vote(0, "Alice", ranks) → ranks[0] = 0
vote(1, "Bob", ranks) → ranks[1] = 1
vote(2, "Charlie", ranks) → ranks[2] = 2

ranks = [0, 1, 2]  表示：Alice > Bob > Charlie
```  
函数2：record_preferences() - 更新偏好矩阵   
功能：一张选票进来了（比如 [Alice, Bob, Charlie]），我们要拆解成所有的一对一胜负，更新 preferences 计分板。
逻辑：
双重循环！
如果选民的排名是 ranks[0]=A, ranks[1]=B, ranks[2]=C。
你需要记录：A优于B，A优于C，B优于C。
即：对于每一个位置 i，和它后面的所有位置 j，都有 preferences[ranks[i]][ranks[j]]++。 
核心逻辑：对于排序中的每一对候选人，前面的比后面的好  
```C
void record_preferences(int ranks[])
{
    // ranks = [0, 1, 2] 表示 Alice > Bob > Charlie
    
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
**详细示例**：
```
ranks = [0, 1, 2]  表示 Alice(0) > Bob(1) > Charlie(2)

i=0, j=1: Alice(0) > Bob(1) → preferences[0][1]++
i=0, j=2: Alice(0) > Charlie(2) → preferences[0][2]++
i=1, j=2: Bob(1) > Charlie(2) → preferences[1][2]++
```  
函数3：add_pairs() - 创建候选对
功能：找出所有有明确胜负的对决，添加到 pairs 数组  
功能：遍历 preferences 计分板，找出谁赢了谁，填入 pairs 数组。
逻辑：
双重循环遍历所有候选人组合 i 和 j。
如果 preferences[i][j] > preferences[j][i]，说明 i 赢了 j。
记录 pairs[pair_count].winner = i
记录 pairs[pair_count].loser = j
pair_count++
如果是平局，谁也不赢，不记录。
```C
void add_pairs(void)
{
    pair_count = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // 比较 i 和 j 谁赢
            if (preferences[i][j] > preferences[j][i])
            {
                // i 赢 j
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                // j 赢 i
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // 如果相等，不添加（平局）
        }
    }
}
```

**示例**：
```
preferences:
           0   1   2
       0 [ 0   2   2 ]
       1 [ 1   0   3 ]
       2 [ 1   0   0 ]

比较：
0 vs 1: preferences[0][1]=2 > preferences[1][0]=1 → Alice赢Bob
0 vs 2: preferences[0][2]=2 > preferences[2][0]=1 → Alice赢Charlie
1 vs 2: preferences[1][2]=3 > preferences[2][1]=0 → Bob赢Charlie

pairs:
pairs[0] = {winner: 0, loser: 1} (Alice > Bob, 优势2-1=1)
pairs[1] = {winner: 0, loser: 2} (Alice > Charlie, 优势2-1=1)
pairs[2] = {winner: 1, loser: 2} (Bob > Charlie, 优势3-0=3)
``` 
函数4：sort_pairs() - 排序
功能：按胜利优势从大到小排序,即把 pairs 数组排序。赢面大（净胜票数多）的排前面。 
逻辑：需要比较两个 pair 的强度。
优势计算：preferences[winner][loser] - preferences[loser][winner]   
使用任何排序算法（冒泡、选择，或者 qsort）。
```C
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

**排序示例**：
```
排序前：
pairs[0]: Alice > Bob (优势: 2-1=1)
pairs[1]: Alice > Charlie (优势: 2-1=1)
pairs[2]: Bob > Charlie (优势: 3-0=3)

排序后：
pairs[0]: Bob > Charlie (优势: 3) ← 最强
pairs[1]: Alice > Bob (优势: 1)
pairs[2]: Alice > Charlie (优势: 1)
```  
函数5：lock_pairs() - (最难的一步 - 递归/DFS)   
功能：按顺序添加箭头，但不能形成循环
循环检测：使用递归DFS（深度优先搜索）  
功能：遍历排好序的 pairs，试图把它们锁入 locked 图中。前提是不能产生环。
逻辑：
遍历每一个 pair (winner, loser)。
核心检查：如果把 winner -> loser 连起来，会不会形成环？
意思就是：在现有的图中，是不是已经存在一条从 loser 回到 winner 的路径？ 如果有，你再连一条 winner -> loser，就变成圈了。
需要写一个辅助函数 check_cycle(from, to)。
如果 check_cycle 返回 false（没环），就 locked[winner][loser] = true。
关于 check_cycle(start, end) 的递归思路：
目标：判断能不能从 start 走到 end。
基准情况 (Base Case)：如果 start == end，说明绕回来了！返回 true (有环)。
递归步骤：
遍历所有候选人 i。
如果 locked[start][i] 是 true（说明 start 指向 i）：
那么，只要能从 i 走到 end，就意味着能从 start 走到 end。
调用 check_cycle(i, end)。
如果它返回 true，我也返回 true。
如果找遍了所有路都走不通，返回 false。
对于 lock_pairs 里的调用：你想加边 A->B，你需要检查 check_cycle(B, A) 是否为真（即是否存在 B 到 A 的路）。
```C  
// 辅助函数：检查添加 start → end 是否会形成循环
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
        if (locked[end][i])  // 如果有 end → i 的边
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
        // 尝试添加 winner → loser 的边
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        
        // 检查是否会形成循环
        if (!creates_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
        // 否则跳过这条边
    }
}
```

**详细示例**：
```
pairs（已排序）：
0. Bob(1) → Charlie(2)
1. Alice(0) → Bob(1)
2. Alice(0) → Charlie(2)

步骤1：尝试锁定 Bob → Charlie
检查：Charlie 能到达 Bob 吗？
- 没有任何箭头
- 不会形成循环 ✓
- locked[1][2] = true

步骤2：尝试锁定 Alice → Bob
检查：Bob 能到达 Alice 吗？
- Bob → Charlie，Charlie 没有出边
- Bob 不能到达 Alice
- 不会形成循环 ✓
- locked[0][1] = true

步骤3：尝试锁定 Alice → Charlie
检查：Charlie 能到达 Alice 吗？
- Charlie 没有出边
- 不会形成循环 ✓
- locked[0][2] = true

最终图：
[Alice] → [Bob] → [Charlie]
    ↓_____________↗
```

**循环示例**：
```
假设已有：
Alice → Bob
Bob → Charlie

现在尝试添加：Charlie → Alice

检查：Alice 能到达 Charlie 吗？
- Alice → Bob → Charlie
- 能到达！
- 会形成循环 ✗
- 不添加这条边
```  
这里提到的DFS也是一种算法，可以先了解下什么是DFS。在《数据结构与算法》课中会讲到，在讲树这种数据结构时会讲到BFS和DFS。DFS 用到了我们上节课学习到的递归思想。

> ⚠️ **常见 Bug 警告**：
> 
> **Bug 1 - sort_pairs 循环条件错误**：
> ```c
> // 错误！应该是 pair_count，不是 candidate_count
> for (int j = i + 1; j < candidate_count; j++)
> ```
> 
> **Bug 2 - create_cycle 递归返回值未检查**：
> ```c
> // 错误写法：
> if (locked[end][i])
> {
>     create_cycle(start, i);  // 没有检查返回值！
>     return true;             // 直接返回 true 是错误的！
> }
> 
> // 正确写法：
> if (locked[end][i])
> {
>     if (create_cycle(start, i))  // 必须检查返回值
>     {
>         return true;
>     }
> }
> ```
> 错误写法会导致只要存在任何边就返回 true，完全破坏循环检测逻辑！  
函数6：print_winner() - 找源头
功能：找到没有箭头指向的候选人（图的源头）  
逻辑：
源头就是：没有任何箭头指向我。
遍历所有候选人 i。
检查 locked 数组的列。有没有任何一个 j 使得 locked[j][i] 为 true？
如果没有任何人锁定（赢过）i，那么 i 就是赢家，打印出来。  
```C
void print_winner(void)
{
    // 对每个候选人
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;
        
        // 检查是否有箭头指向他
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])  // 如果有 j → i
            {
                is_source = false;
                break;
            }
        }
        
        // 如果没有箭头指向他，他就是源头/赢家
        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
```

**示例**：
```
locked 矩阵：
           0   1   2
       0 [ F   T   T ]  ← Alice → Bob, Alice → Charlie
       1 [ F   F   T ]  ← Bob → Charlie
       2 [ F   F   F ]

检查每个候选人：
- Alice(0): locked[?][0] 都是 F → 没有箭头指向 → 源头！
- Bob(1): locked[0][1] = T → 有箭头指向 → 不是源头
- Charlie(2): locked[0][2]=T, locked[1][2]=T → 有箭头 → 不是源头

输出：Alice
```  

