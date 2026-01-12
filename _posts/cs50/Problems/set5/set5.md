---
layout: post
title: "CS50 Problem Set 5: 数据结构实战 - 遗传模拟与拼写检查器"
date: 2025-12-24
categories: [CS50, Programming]
tags: [C, 数据结构, 哈希表, 链表, 递归, 指针]
---

# Problem Set 5 概述

本周作业围绕**数据结构**主题展开，需要运用 Week 5 学习的链表、哈希表等知识解决实际问题。

| 题目 | 难度 | 核心知识点 |
|------|------|-----------|
| Inheritance | ⭐⭐ | 递归、动态内存分配、树结构 |
| Speller | ⭐⭐⭐⭐ | 哈希表、链表、文件操作、性能优化 |

作业页面：
- [Problem Set 5 总览](https://cs50.harvard.edu/x/psets/5/)
- [Inheritance 题目](https://cs50.harvard.edu/x/psets/5/inheritance/)
- [Speller 题目](https://cs50.harvard.edu/x/psets/5/speller/)

---

# 1. Inheritance（遗传模拟）
## 题目背景  
血型遗传问题  
这道题涉及到的核心知识点是**指针（Pointers）、动态内存分配（malloc/free）、递归（Recursion）**。  
想象下我们小时候学习的family tree，没错，这里我们就是要构建树这种结构。  
## 一、核心概念分析  
### 1. 数据结构：倒置的树  
在这题中，一个人(`person`)有一对父母。  
- 通常的树是根(root)在顶端，分叉在下面，通过指针由根节点指向子节点  
- family tree 中，孩子在最下层做为根节点，指向父母，父母再指向自己的父母。。。  
```
         祖父母
       /      \
   父亲        母亲
       \      /
         孩子

三代人的遗传关系：
- 孩子的等位基因来自父母
- 父母的等位基因来自祖父母  
```  
- 每个节点 (`person`)包含：  
1. `person[2]`:指向爸爸和妈妈的指针  
2. `alleles[2]`:两个血型基因字符（比如 'A' 和 'B'）。  
### 2. 递归构建(Recursion)  
- **Create**:要创建一个person,必须先创建其父母，要创建“父母”，必须先创建“祖父母”，这是一个典型的递归过程。（涉及到树结构，基本上就是使用递归）。   
- **Basic Case(终止条件)**：当我们达到` generations`(祖父母) 代，他们没有父母，模拟时指针设置为`NULL`,基因也是随机生成的。  
### 3. 孟德尔遗传定律   
- 每个人的两个基因 (alleles)，一个来自父亲，一个来自母亲。
- 我们要随机决定从父亲的两个基因里选哪一个，再从母亲的两个基因里选哪一个。
## 逐步解决   
我们的任务是完成 `create_family` 和 `free_family` 中的 TODO。  
### 1. `create_family`(构建 family tree)  
**思考**： 
1. 不管这个人是谁，都要为其在内存上开辟空间，使用 `malloc` 动态分配内存。  
2. 判断代数  
  - 如果有上一代(generations > 1)  
    - 调用 `create_family` 把其父母创建出来，并把指针存储到当前 `parents` 数组中  
    - 决定基因：根据刚刚创建出来的父母的基因，随机决定孩子的基因。  
  - 如果是祖宗(即不再有父母)  
    - 父母指针设为 `NULL`  
    - 不再有父母，没有上一代数据， 调用 `random_allele()` 基因随机生成。 
3. 把创建好的这个人返回给上一层。  
实现如下：  
```C
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *p = malloc(sizeof(person));
    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person
        p->parents[0] = parent0;
        p->parents[1] = parent1;

        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        p->alleles[0] = parent0->alleles[random() % 2];
        p->alleles[1] = parent1->alleles[random() % 2];
    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // TODO: Randomly assign alleles
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    return p;
    // return NULL;
}
```   
### 2. `free_family()`（释放内存）   
原则：你必须先释放“引用对象”，才能释放“引用者”  
在递归中，通常是后序遍历 (Post-order Traversal)：先释放每一个人的父母（子树），最后释放这个人自己（根）。如果你先释放了自己，你就找不到父母的指针了，那些内存就泄漏了。  
- Base Case：如果指针是 NULL，说明没东西可释放，直接返回。
- 递归释放父母：先去把 parents[0] 和 parents[1] 这两条线上的所有人清理干净。
- 释放自己：最后 free(p)。   
代码实现：  
```C
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
}
```  
# 2. Speller  
这题文件有点多  
```Shell
speller/ $ tree -L 2
.
├── dictionaries
│   ├── large
│   └── small
├── dictionary.c
├── dictionary.h
├── keys
│   ├── aca.txt
│   ├── austen.txt
│   ├── birdman.txt
│   ├── burnett.txt
│   ├── carroll.txt
│   ├── cat.txt
│   ├── constitution.txt
│   ├── federalist.txt
│   ├── frankenstein.txt
│   ├── grimm.txt
│   ├── her.txt
│   ├── holmes.txt
│   ├── homer.txt
│   ├── lalaland.txt
│   ├── mansfield.txt
│   ├── pneumonoultramicroscopicsilicovolcanoconiosis.txt
│   ├── revenant.txt
│   ├── rinehart.txt
│   ├── shakespeare.txt
│   ├── stein.txt
│   ├── stoker.txt
│   ├── surgery.txt
│   ├── tolstoy.txt
│   ├── wells.txt
│   ├── whittier.txt
│   ├── wordsworth.txt
│   ├── xueqin1.txt
│   └── xueqin2.txt
├── Makefile
├── speller50
├── speller.c
└── texts
    ├── aca.txt
    ├── austen.txt
    ├── birdman.txt
    ├── burnett.txt
    ├── carroll.txt
    ├── cat.txt
    ├── constitution.txt
    ├── federalist.txt
    ├── frankenstein.txt
    ├── grimm.txt
    ├── her.txt
    ├── holmes.txt
    ├── homer.txt
    ├── lalaland.txt
    ├── mansfield.txt
    ├── pneumonoultramicroscopicsilicovolcanoconiosis.txt
    ├── revenant.txt
    ├── rinehart.txt
    ├── shakespeare.txt
    ├── stein.txt
    ├── stoker.txt
    ├── surgery.txt
    ├── tolstoy.txt
    ├── wells.txt
    ├── whittier.txt
    ├── wordsworth.txt
    ├── xueqin1.txt
    └── xueqin2.txt
```  
## 一、问题背景   
**我们要解决什么问题** ：写一个拼写检查器 (Spell Checker)。  
1. 一本字典(dictionary)：包含几万甚至十几万的正确单词。  
2. 一个文件(text):比如电影《 La La Land》的剧本。  
程序需要做的事情是：  
1. 把字典加载到内存上  
2. 遍历文件的每一个单词  
3. 判断这个单词是否存在于字典中（忽略大小写）  
4. 如果不在，这个单词是错误，打印出这个错误单词。  
5. 统计并输出加载、检查、释放的时间（Benchmark）。  
**这题的难点**   
**速度**： 默认字典中有143,091个单词，而文章可能有十几万字，如果我们的查找算法不够快（比如每次都遍历整个字典），程序可能会跑几分钟甚至几小时。目标是在几分之一秒内完成。  
**内存**：不能把所有单词都写死在代码里，必须动态分配内存。而且用完必须释放，不能有内存泄漏。  
## 二、核心数据结构（Data Structure）  
为了实现“极速查找”，题目强制要求使用 **哈希表 (Hash Table)**。  
1. 结构体定义  
在 `dictionary.c` 中，定义了节点（Node）：  
```C  
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;
```  
2. 哈希表   
```C
// Hash table
node *table[N];
```   
这是一个指针数组，  
- `N` 是桶（Buckets）的数量  
- `table[i]` 是第 i 个链表的**头指针(Head Pointer)**   
- 链表存储哈希到同一索引的所有单词
- 初始，所有头指针`table[i]`的值都是`NULL`  
3. 类比  
为了便于理解，做个类比  
想象哈希表是一个巨大的文件柜，有 N 个抽屉。  
回忆下课程notes中的  
![哈希表与链表](https://cs50.harvard.edu/x/notes/5/cs50Week5Slide169.png)  
最终哈希表存储的结果可能如下所示  
```
table[0]  → [apple] → [ant] → [aardvark] → NULL
table[1]  → [banana] → [bear] → NULL
table[2]  → [cat] → [car] → [cat] → NULL
...
table[25] → [zebra] → [zoo] → NULL
```  
## 三、核心概念 ：哈希函数 (Hash Function)  
哈希函数是整个系统的引擎。它的输入是 `const char *word`，输出是 `unsigned int`（也就是数组下标 `index`）。  
输入: "Apple"
处理: 必须不区分大小写。'A' 和 'a' 算出来的结果必须一样。
输出: 0 到 N-1 之间的整数。  
确定性: 每次给它 "Apple"，它必须返回同一个数字。
## 四、逐步分析和实现   
我们不需要写 `main` 函数，只需要填充 `dictionary.c` 里的 5 个函数。建议按以下顺序实现：  
### 1. 准备工作：全局变量与定义  
首先，我们需要确定桶的数量 `N`。  
```C
// 可以先用小一点的数测试，最后改大比如 10000 甚至 150000
const unsigned int N = 26;
```  
需要一个变量来记录字典里到底有多少个词，方便 `size()` 函数使用。  
```C
unsigned int word_count = 0;
```  
### 2. 实现 hash (最简单的版本)  
先别管效率，先让程序能跑起来。最简单的哈希就是取首字母。  
```C  
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}
```  
**问题分析：**  
这个简单版的哈希方法有哪些问题呢？  
- 分布不均匀  
  - 以 'A' 开头的单词很多 → table[0] 很长
  - 以 'X' 开头的单词很少 → table[23] 很短  
示例：
table[0]: [apple, ant, aardvark, able, ...] (几千个)
table[23]: [xylophone, x-ray] (几十个)
结果：
- 查找 'apple'：需要遍历很长的链表
- 性能退化到接近 O(n)  
**改进的哈希函数**
**目标**：将单词均匀分布到更多的桶中   
- 策略1：增加桶的数量  
比如将桶的数量定义为 26*26  
```C
const unsigned int N = 26 * 26;  // 676 个桶（AA-ZZ）
```  
哈希函数必须与桶的数量是匹配的，因此，我们需要修改上述哈希函数如下：  
```C
unsigned int hash(const char *word)
{
    unsigned int index = 0;
    
    // 获取第一个字母的数值 (0-25)
    unsigned int first = toupper(word[0]) - 'A';
    
    // 检查是否有第二个字母
    // word[1] 是字符串的第二个字符。如果是 '\0'，说明单词结束了，长度只有1
    if (word[1] == '\0') 
    {
        // 如果只有一个字母，就直接用它
        // 注意：为了不浪费空间，我们还是得把它放到某个位置
        // 比如 "A" 可以放在 "AA" 的位置，或者单独处理
        // 最简单的策略：假设第二个字母是 'A' (即值0)
        index = first * 26 + 0;
    }
    else
    {
        // 获取第二个字母的数值
        // 注意：这里需要处理撇号 '，或者假设输入都是字母
        // 健壮性写法：如果是撇号，把它当成 0 或者其他处理，这里假设是字母
        unsigned int second = 0;
        if (isalpha(word[1]))
        {
             second = toupper(word[1]) - 'A';
        }
        // 如果是撇号，second 保持为 0，或者你可以自定义
        
        // 套用公式
        index = first * 26 + second;
    }

    // 双重保险：防止计算出的值越界 (虽然理论上不会)
    return index % N;
}
```    
为什么对应的hash 函数是这样的。  
哈希函数的逻辑必须与桶的数量（N）相匹配。如果 N变了，但哈希函数没变，增加的桶就浪费了。  
前面设定 N= 26，简单版 Hash：`return toupper(word[0]) - 'A'`;  

#### 背景回顾

*   **此前设定**：$N = 26$
*   **简单版 Hash**：`return toupper(word[0]) - 'A';`
    *   这个函数返回值的范围是 $0$ 到 $25$。
    *   正好覆盖了 $table[0]$ 到 $table[25]$。

#### 场景分析：$N = 26 \times 26 = 676$

如果把 $N$ 改大了，但哈希函数还是只看**第一个字母**，那么：
*   哈希函数依然只返回 $0-25$。
*   数据只会填充在前 26 个桶里。
*   后面的 $table[26]$ 到 $table[675]$ 全部是空的（NULL），完全浪费了空间，且没有解决冲突拥挤的问题。

#### 解决方案：利用前两个字母

为了充分利用 $676$ 个桶，我们需要让哈希函数的返回值范围扩大到 $0$ 到 $675$。一个很自然的想法是利用单词的**前两个字母**。

#### 数学逻辑（Base-26 进制）

想象这是一个 26 进制的系统：
*   第 1 个字母代表“高位”（就像十进制里的十位）。
*   第 2 个字母代表“低位”（就像十进制里的个位）。

**公式设计：**
$$ Index = (第一个字母的值 \times 26) + 第二个字母的值 $$

**举例：**
*   **"AA"**:
    *   'A' -> 0, 'A' -> 0
    *   Index = $0 \times 26 + 0 = 0$
*   **"BA"**:
    *   'B' -> 1, 'A' -> 0
    *   Index = $1 \times 26 + 0 = 26$
*   **"ZZ"**:
    *   'Z' -> 25, 'Z' -> 25
    *   Index = $25 \times 26 + 25 = 650 + 25 = 675$

这样，从 "AA" 到 "ZZ" 的所有双字母组合都能映射到 $0-675$ 之间唯一的桶。

#### 代码实现细节

这里有几个边界情况（Edge Cases）需要处理：
1.  **单词长度只有 1**（比如 "A", "I"）：它们没有第二个字母。
2.  **非字母字符**：虽然题目说单词主要是字母，但要小心特殊符号（如撇号 `'`）。不过简化起见，通常我们只处理字母。

### 进一步思考：为什么 26*26 还是不够好？

虽然 676 个桶比 26 个好很多，但对于 14 万个单词的字典来说：
$$ 143,000 / 676 \approx 211 $$
平均每个桶里还是有 **211** 个单词。查找时还是要在长链表里跑。

这就是为什么在实际工程和进阶优化中，我们不再试图用“字母的几何意义”（第1个字、第2个字）来设计哈希，而是使用**数学混淆**。

**数学混淆法（多项式哈希）**：
不关心字母的位置含义，只关心把字符串变成一串混乱的数字。
比如：
$$ Hash = (H \times 33) + C $$
这种算法算出来的数可能很大（几十亿），然后我们要模上桶的数量 $N$。
$$ Index = (VeryBigNumber) \% N $$
这时，你可以把 $N$ 设为 $10,000$ 甚至 $100,000$，哈希函数完全不需要改代码，只需要改 $N$ 的值即可（只要哈希算出来的值足够大且分散）。
这种基于“多项式滚动哈希”的算法，最著名的实现被称为 **djb2**（由 Dan Bernstein 提出）。它在 C 语言社区和许多开源项目中被广泛使用，因其在处理英文字符串时分布极其均匀且计算速度快而闻名。 
**总结：**
如果用 $N=676$，必须手动硬编码“前两个字母”的逻辑。但更好的做法是使用通用的数学哈希算法，这样你可以随意调整 $N$ 的大小，代码具有更好的扩展性。 
### djb2 的核心逻辑  
#### 1. 核心逻辑  
这种哈希算法的思想不是把字母看作“位置”（如第1个、第2个）， 而是把整个单词看作一个巨大的数字。  
公式如下： 
$$ Hash_{new} = (Hash_{old} \times 33) + CurrentCharacter $$  
* **初始值**：通常设为一个较大的质数，比如 5381。   
*** 乘数 33**：这是一个神奇的数字。实验表明，乘 33 能很好地将英语单词里的字母特征分散到哈希值的各个二进制位上，避免冲突。   
* **累加字符**：把当前字母的 ASCII 值加进去。
#### 2. 代码实现
```c
#include <ctype.h>   // 需要用到 tolower
#include <strings.h> // 需要用到 strcasecmp

// 1. 调整 N 的大小
// 既然用了高级哈希，桶就要够多才能发挥威力。
// 建议设为大一点的数字，比如 100,000 甚至更大。
// 为了减少冲突，最好是一个质数，比如 143091 (字典大小) 附近的质数。
const unsigned int N = 100000; 

unsigned int hash(const char *word)
{
    // 2. 初始化哈希值为 5381 (djb2 算法的经典初始值)
    // 为什么是 5381？这是 Dan Bernstein 通过实验发现的"魔数"
    // 使用 unsigned long 以防溢出（虽然溢出回绕在这里其实没关系，甚至有帮助）
    unsigned long hash = 5381;  // ⚠️ 注意：必须是 5381，不是其他数字！

    // 3. 遍历单词的每一个字符
    for (int i = 0; word[i] != '\0'; i++)
    {
        // 4. 核心公式：hash * 33 + c
        // 必须使用 tolower()，因为题目要求哈希表不区分大小写
        // "Cat" 和 "cat" 必须算出相同的 hash 值
        hash = ((hash << 5) + hash) + tolower(word[i]);
    }

    // 5. 取模运算
    // 算出来的 hash 可能非常大（几十亿），必须映射到 0 到 N-1 的范围内
    return hash % N;
}
```  
#### 3. 代码细节深度解析
1. 为什么是 `((hash << 5) + hash)`？
这其实就是 `hash * 33` 的位运算优化写法。
*   `hash << 5` 意思是把二进制位向左移 5 位，相当于乘以 $2^5$，即 **乘以 32**。
*   所以：`(hash * 32) + hash` 就等于 `hash * 33`。
*   在旧的编译器上，位运算比乘法快。虽然现代编译器很聪明，会自动帮你优化，但这样写显得你很懂底层（Geek 范儿）。当然，直接写 `hash = (hash * 33) + tolower(word[i]);` 也是完全正确的。

2. 为什么要 `tolower`？
题目明确要求 `check` 函数是 **case-insensitive**（不区分大小写）的。
这意味着如果你在 `load` 字典时，单词 "Apple" 被存进了 5 号桶（因为 'A' 的值），而在 `check` 时，文章里的 "apple" 算出来是 30 号桶（因为 'a' 的值），那你就永远找不到它了。
**原则**：存入和查找时，必须统一转成小写（或大写）来计算哈希值。

3. 为什么要 `% N`？
循环结束后，`hash` 变量里存着一个巨大的整数（例如 `384918423`）。
你的 `table` 数组只有 `N` 个格子。
`% N` 操作能确保结果永远落在 `0` 到 `N-1` 之间，作为数组的合法下标。

#### 4. 性能提升预期

如果把 `N` 改为 **100,000** 并配合这个哈希函数：
*   **原本 (N=26)**：平均每个桶有 5500 个单词。`check` 一个词要对比 5500 次字符串。
*   **现在 (N=100000)**：平均每个桶只有 **1.4** 个单词！
*   **结果**：绝大多数情况下，`check` 函数只需要对比 1 次或 2 次就能得出结果。程序的运行速度将提升成百上千倍。

这就是哈希表的魔力：**通过良好的哈希函数和足够的空间，实现接近 $O(1)$ 的查找速度。**  
### 3. load() - 加载字典 ⭐最复杂  
把字典从磁盘搬到内存。  
#### **功能需求**
```
输入：字典文件路径（如 "dictionaries/large"）
输出：成功返回 true，失败返回 false

步骤：
1. 打开字典文件
2. 逐行读取单词
3. 为每个单词创建节点
4. 计算哈希值
5. 插入到哈希表（链表头部）
6. 关闭文件  
伪代码逻辑:
```
fopen 打开字典文件。检查是否为 NULL。
准备一个临时字符数组 buffer 存读到的词。
Loop: 使用 fscanf(file, "%s", buffer) 循环读取直到文件结束 (EOF)。
malloc 一个新节点 new_node。如果 NULL，报错并 return false。
strcpy 把 buffer 里的词复制到 new_node->word。
调用 hash(buffer) 算出 index。
插入链表 (头插法):
new_node->next 指向 table[index] (原本的头)。
table[index] 指向 new_node (新节点变成头)。
word_count 加 1。
fclose 文件。
返回 true。
```   
完整实现   
```C
// 全局变量：记录字典中的单词数
unsigned int word_count = 0;

bool load(const char *dictionary)
{
    // 1. 打开字典文件
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // 2. 初始化哈希表（所有指针设为 NULL）
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // 3. 读取单词（缓冲区）
    char word[LENGTH + 1];

    // 4. 逐个读取单词
    while (fscanf(file, "%s", word) != EOF)
    {
        // 5. 创建新节点
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            // 内存分配失败，清理并返回
            fclose(file);
            unload();
            return false;
        }

        // 6. 复制单词到节点
        strcpy(new_node->word, word);

        // 7. 计算哈希值
        unsigned int index = hash(word);

        // 8. 插入到链表头部（最快）
        new_node->next = table[index];
        table[index] = new_node;

        // 9. 更新计数器
        word_count++;
    }

    // 10. 关闭文件
    fclose(file);

    return true;
}
```  
注意，在将读到的word 复制到hash table 时使用的是`strcpy(new_node->word, word);`,而不是`new_node->word = word;`  
是因为word 是局部变量，只复制会被覆盖。  
### 4. `size()` 操作  
这个非常简单，前面在将词典从磁盘加载到内存时定义了一个全局变量 `word_count`，每次读取一个单词时，计数器就加一，所以`size()`直接返回该全局变量即可。 
```C
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}
```  
**注意**: 如果 load 没成功，应该根据 word_count 的初始值返回 0，这也符合逻辑。  
### 5. `check()`  
这是在检查文章拼写时需要被疯狂调用的函数。  
#### **功能需求**
输入：待检查的单词
输出：在字典中返回 true，否则 false  
步骤：
1. 计算哈希值
2. 遍历对应的链表
3. 比较每个节点的单词（不区分大小写） 
伪代码  
1. 调用 `hash(word)` 计算这个`word` 在哪个桶 `index`  
2. 创建一个指针 `cursor` 指向 `table[index]`  
3. **Loop**: `while (cursor != NULL)`
  - 使用 `strcmp(word, cursor->word)` 比较  
  - 如果值为 `0`，说明找到了，返回 `true`  
  - 当前节点没找到，继续下一个 `cursor = cursor->next`  
4. 循环完了还没找到，说明不在字典中，拼写错误，返回 `false`.  
代码实现   
```C
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // ⚠️ 关键：必须使用 strcasecmp 进行大小写不敏感比较！
        // 如果使用 strcmp，"Apple" 和 "apple" 会被视为不同单词
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}
```  

> ⚠️ **常见 Bug 警告**：很多同学（包括我最初）使用 `strcmp` 而不是 `strcasecmp`，导致大量"拼写错误"。因为字典中存的是 `apple`，而文章中可能是 `Apple`，`strcmp` 会认为它们不相等！

**性能分析**：
最好情况：O(1) - 单词在链表头部
最坏情况：O(n) - 链表很长，单词在末尾或不存在
平均情况：O(n/N) - n 个单词，N 个桶

优化关键：
- N 越大，链表越短
- 哈希函数越好，分布越均匀  
### 6. unload()  
程序结束前必须释放内存。我们必须遍历所有桶，销毁所有链表。  
**伪代码逻辑:**   
**Loop**: 遍历桶，`i` 从 `0` 到 `N-1`  
  设置 `cursor` 指向 `table[i]`
  **Inner Loop**: `while (cursor != NULL)`
    `node *tmp = cursor;` 
    `cursor = cursor->next;`
    `free(tmp);`
返回`true`  
完整实现   
```C
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;  // 注意：这里返回 true，不是 tmp！
}
```  
完整的 `dictionary.c` 在 speller 目录下。  
### 三、测试和优化  
#### 1. 基础测试   
```shell
# 编译
make speller

# 测试小字典 + 小文本
./speller dictionaries/small texts/cat.txt  
* 方法 1 hash  
```shell
speller/ $ ./speller dictionaries/small texts/cat.txt 

MISSPELLED WORDS

A
is
not
a

WORDS MISSPELLED:     4
WORDS IN DICTIONARY:  2
WORDS IN TEXT:        6
TIME IN load:         0.00
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.00
TIME IN TOTAL:        0.00
```   
这个规模比较小，即便hash() 方法 1也是瞬间完成，后面就不用这个文本测试了。 

# 测试大字典 + 中等文本
./speller texts/holmes.txt   
- hash() 方法  1  
```shell
WORDS MISSPELLED:     122102
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        1150970
TIME IN load:         0.02
TIME IN check:        33.36
TIME IN size:         0.00
TIME IN unload:       0.00
TIME IN TOTAL:        33.39
```  
- hash() 方法  2  
```shell
WORDS MISSPELLED:     122102
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        1150970
TIME IN load:         0.02
TIME IN check:        7.13
TIME IN size:         0.00
TIME IN unload:       0.00
TIME IN TOTAL:        7.16
```   
- hash() 方法  3  
```shell 
WORDS MISSPELLED:     122102
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        1150970
TIME IN load:         0.03
TIME IN check:        1.37
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        1.41
```  
hash() 方法 3明显快了很多，但还是与官方实现的有差距，可以尝试调整 N 的大小再去优化。 
# 与官方实现对比
./speller50 texts/holmes.txt
./speller texts/holmes.txt  
* 官方测评  
```shell
WORDS MISSPELLED:     955
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        17756
TIME IN load:         0.02
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.06
```     
#### 2. 检查正确性   
```shell
# 使用 check50
check50 cs50/problems/2024/x/speller

# 手动比较输出
./speller texts/holmes.txt > student.txt
./speller50 texts/holmes.txt > staff.txt
diff student.txt staff.txt
```    
方法 1 与官方比较  
```shell
122107c17850
< WORDS MISSPELLED:     122102
---
> WORDS MISSPELLED:     17845
122111c17854
< TIME IN check:        23.92
---
> TIME IN check:        0.98
122113,122114c17856,17857
< TIME IN unload:       0.00
< TIME IN TOTAL:        23.94
---
> TIME IN unload:       0.01
> TIME IN TOTAL:        1.02
```   
- hash() 方法 2 与官方比较  
```shell
< WORDS MISSPELLED:     122102
---
> WORDS MISSPELLED:     17845
122111c17854
< TIME IN check:        4.73
---
> TIME IN check:        0.98
122113,122114c17856,17857
< TIME IN unload:       0.00
< TIME IN TOTAL:        4.75
---
> TIME IN unload:       0.01
> TIME IN TOTAL:        1.02
```  
hash() 方法 3 与 官方比较  
```shell
< WORDS MISSPELLED:     122102
---
> WORDS MISSPELLED:     17845
122110,122111c17853,17854
< TIME IN load:         0.03
< TIME IN check:        0.99
---
> TIME IN load:         0.02
> TIME IN check:        0.98
122114c17857
< TIME IN TOTAL:        1.03
---
> TIME IN TOTAL:        1.02
```   

### ⚠️ Bug 分析：为什么拼写错误数差这么多？

注意到上面的测试结果中，我的程序报告 **122,102** 个拼写错误，而官方只有 **17,845** 个！

**原因**：我最初在 `check()` 函数中使用了 `strcmp()` 而不是 `strcasecmp()`！ 
这里的bug 分析是我让AI 帮我 review 我的实现和笔记，AI 给出的，这里是我阅读官方 hints 部分不仔细，"To compare two strings case-insensitively, you may find strcasecmp (declared in strings.h) useful!" 非常明白的给了提示的。  

```c
// 错误写法 ❌
if (strcmp(word, cursor->word) == 0)

// 正确写法 ✅
if (strcasecmp(word, cursor->word) == 0)
```

**后果**：
- 字典中存的是小写 `"apple"`
- 文章中可能出现 `"Apple"` 或 `"APPLE"`
- `strcmp("Apple", "apple")` 返回非零值（不相等）
- 程序错误地认为 `"Apple"` 是拼写错误

**修复后**：拼写错误数与官方一致！

> 💡 **教训**：这个 bug 让我深刻理解了为什么 CS50 强调 "case-insensitive" 比较的重要性。在实际项目中，这类 bug 可能导致严重后果。

#### 3. 内存泄漏检查   
```shell
# 使用 valgrind
valgrind --leak-check=full ./speller texts/cat.txt

# 应该看到：
# All heap blocks were freed -- no leaks are possible
```

#### 4 性能优化
#### **性能目标**
```shell
Staff Solution (speller50) 基准：
- TIME IN load:    0.02-0.05s
- TIME IN check:   0.00-0.01s  (重点优化)
- TIME IN unload:  0.00-0.02s

你的目标：
- 接近或超过官方实现
- check() 时间最关键（调用次数最多）
```   
**优化策略**  
1. 调整哈希表大小 N  
2. 改进哈希函数  
这两点是对应的，前面我们在实现 `hash()` 函数时已经讲到。  

---

# 总结

## 知识点对照表

| 题目 | 核心数据结构 | 关键算法 | 课程对应内容 |
|------|-------------|---------|-------------|
| Inheritance | 树（指针数组） | 递归构建、递归释放 | Week 5: Trees, Recursion |
| Speller | 哈希表（链表数组） | 哈希函数、链表操作 | Week 5: Hash Tables, Linked Lists |

## 常见错误清单

| 错误类型 | 具体错误 | 正确做法 |
|---------|---------|---------|
| 字符串比较 | 使用 `strcmp` | 使用 `strcasecmp`（大小写不敏感）|
| 返回值 | `unload()` 返回 `tmp` | 返回 `true` |
| 头文件 | 忘记包含 `<strings.h>` | 使用 `strcasecmp` 需要此头文件 |
| 哈希初值 | 使用随意数字 | djb2 算法使用 `5381` |
| 内存泄漏 | 忘记 `free()` | 使用 `valgrind` 检查 |

## 性能优化要点

```
哈希表性能公式：平均链表长度 = 单词总数 / 桶数量

N = 26:      143,091 / 26 ≈ 5,500 个节点/桶 → 很慢
N = 676:     143,091 / 676 ≈ 212 个节点/桶 → 一般
N = 100,000: 143,091 / 100,000 ≈ 1.4 个节点/桶 → 很快！
```

## 调试技巧

1. **使用 valgrind 检查内存泄漏**：
   ```bash
   valgrind --leak-check=full ./speller texts/cat.txt
   ```

2. **使用 diff 对比输出**：
   ```bash
   ./speller texts/lalaland.txt > student.txt
   ./speller50 texts/lalaland.txt > staff.txt
   diff -y student.txt staff.txt
   ```

3. **使用 check50 官方测试**：
   ```bash
   check50 cs50/problems/2025/x/speller
   ```

## 延伸学习

- **哈希函数设计**：了解更多哈希算法如 FNV-1a、MurmurHash
- **数据结构优化**：学习开放寻址法、布隆过滤器等
- **算法复杂度**：深入理解 O(1) vs O(n) 的实际影响

---

**参考资料**：
- [CS50 Week 5 官方笔记](https://cs50.harvard.edu/x/notes/5/)
- [CS50 Problem Set 5 官方页面](https://cs50.harvard.edu/x/psets/5/)
- [Speller 题目详情](https://cs50.harvard.edu/x/psets/5/speller/)
- [djb2 哈希算法](http://www.cse.yorku.ca/~oz/hash.html)

下次见！ 🚀

