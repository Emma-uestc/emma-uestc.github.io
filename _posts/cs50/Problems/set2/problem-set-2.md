---
layout: post
title: "CS50 Week 2 Problem Set - Arrays and Strings"
date: 2026-01-12
categories: [CS50, C Programming]
tags: [arrays, strings, cryptography, algorithms]
---

# CS50 Problem Set 2: Arrays and Strings

本文记录 CS50x Week 2 Problem Set 的解题过程。这周的主题是**数组（Arrays）**和**字符串（Strings）**，我们将通过四道题目深入理解这些核心概念。

## 📚 本周知识点回顾

在开始解题之前，让我们回顾 Week 2 的核心概念：

### 数组（Arrays）
- 相同类型数据的连续存储
- 零索引（从 0 开始）
- 固定大小

### 字符串（Strings）
- 字符串本质是 `char` 数组
- 以 `\0`（null terminator）结尾
- `string` 是 CS50 库提供的类型别名（实际是 `char *`）

### 命令行参数
- `int main(int argc, string argv[])`
- `argc`：参数数量
- `argv[]`：参数数组

### 常用函数
- `strlen()`：获取字符串长度
- `isalpha()`、`isdigit()`：字符类型判断
- `isupper()`、`islower()`：大小写判断
- `toupper()`、`tolower()`：大小写转换

---

## 问题概览

| 问题 | 难度 | 核心概念 |
|------|------|---------|
| [Scrabble](#1-scrabble) | ⭐ | 数组映射、字符索引 |
| [Readability](#2-readability) | ⭐⭐ | 字符串分析、算法实现 |
| [Caesar](#3-caesar) | ⭐⭐ | 命令行参数、字符旋转 |
| [Substitution](#4-substitution) | ⭐⭐⭐ | 密钥验证、字符映射 |

---

# 1. Scrabble

## 问题描述

在 [Scrabble](https://en.wikipedia.org/wiki/Scrabble) 游戏中，玩家通过拼单词得分，每个字母有不同的分值：

```
字母: A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
分值: 1  3  3  2  1  4  2  4  1  8  5  1  3  1  1  3  10 1  1  1  1  4  4  8  4  10
```

**任务**：编写程序，让两个玩家输入单词，比较得分，输出获胜者。

## 思路分析

### 核心问题：如何将字母映射到分数？

**关键洞察**：字母表是有序的，可以用数组存储对应分数！

```
A B C D E F ... Z
↓ ↓ ↓ ↓ ↓ ↓     ↓
0 1 2 3 4 5 ... 25  (数组索引)
↓ ↓ ↓ ↓ ↓ ↓     ↓
1 3 3 2 1 4 ... 10  (分数)
```

### 字母到索引的转换

```c
// 大写字母
'A' - 'A' = 0  (索引0)
'B' - 'A' = 1  (索引1)
'Z' - 'A' = 25 (索引25)

// 小写字母
'a' - 'a' = 0  (索引0)
'b' - 'a' = 1  (索引1)
'z' - 'a' = 25 (索引25)
```

### 算法流程

```
1. 定义分数数组
2. 提示两个玩家输入单词
3. 对每个单词计算分数：
   a. 遍历每个字符
   b. 如果是字母，转换为索引
   c. 累加对应分数
4. 比较分数，输出结果
```

## 代码实现

```c
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// 分数数组：索引对应字母表位置
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// 函数原型
int compute_score(string);

int main(void)
{
    // 提示玩家输入单词
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // 计算分数
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // 比较并输出结果
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

/*
 * 计算单词的 Scrabble 分数
 * 忽略非字母字符，大小写不敏感
 */
int compute_score(string word)
{
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i]))
        {
            // 大写字母：'A'-'A'=0, 'B'-'A'=1, ...
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            // 小写字母：'a'-'a'=0, 'b'-'a'=1, ...
            score += POINTS[word[i] - 'a'];
        }
        // 非字母字符不计分
    }
    return score;
}
```

## 代码详解

### 1. 为什么用全局数组？

```c
int POINTS[] = {1, 3, 3, 2, ...};
```

- **优点**：
  - 数据只需定义一次
  - 所有函数都能访问
  - 不需要作为参数传递
- **注意**：全局变量通常用大写命名

### 2. 大小写处理技巧

```c
if (isupper(word[i]))
    score += POINTS[word[i] - 'A'];
else if (islower(word[i]))
    score += POINTS[word[i] - 'a'];
```

**为什么这样写？**
- 'A' 和 'a' 的 ASCII 码不同（65 vs 97）
- 但它们都映射到索引 0
- 通过减去对应的基准字符（'A' 或 'a'），都得到正确的索引

### 3. 示例：计算 "CODE"

```
C: isupper → 'C' - 'A' = 2 → POINTS[2] = 3
O: isupper → 'O' - 'A' = 14 → POINTS[14] = 1
D: isupper → 'D' - 'A' = 3 → POINTS[3] = 2
E: isupper → 'E' - 'A' = 4 → POINTS[4] = 1

总分 = 3 + 1 + 2 + 1 = 7
```

## 运行示例

```bash
$ ./scrabble
Player 1: Question?
Player 2: Question!
Tie!
```

```bash
$ ./scrabble
Player 1: COMPUTER
Player 2: science
Player 1 wins!
```

**计算验证**：
- C(3) + O(1) + M(3) + P(3) + U(1) + T(1) + E(1) + R(1) = 14
- s(1) + c(3) + i(1) + e(1) + n(1) + c(3) + e(1) = 11

## 关键知识点

✅ **数组作为查找表**：用索引快速映射数据  
✅ **ASCII 算术**：字符与整数的转换  
✅ **字符分类函数**：`isupper()`、`islower()`  
✅ **函数抽象**：将计算逻辑封装成函数

---

# 2. Readability

## 问题描述

根据 **Coleman-Liau index**，计算文本的可读性等级（适合几年级学生阅读）。

### Coleman-Liau 公式

```
index = 0.0588 × L - 0.296 × S - 15.8
```

其中：
- **L** = 每 100 个单词的平均字母数
- **S** = 每 100 个单词的平均句子数

### 输出规则

- 等级 < 1：输出 `Before Grade 1`
- 等级 ≥ 16：输出 `Grade 16+`
- 其他：输出 `Grade X`（X 四舍五入到整数）

## 思路分析

### 第一步：理解统计规则

1. **字母（Letters）**：a-z 和 A-Z
2. **单词（Words）**：由空格分隔的字符序列
3. **句子（Sentences）**：以 `.` `!` `?` 结尾

### 第二步：公式转换

```
已知：letters, words, sentences
需要计算：L 和 S

L = (letters / words) × 100
S = (sentences / words) × 100

index = 0.0588 × L - 0.296 × S - 15.8
```

### 第三步：示例计算

**文本**：`"Congratulations! Today is your day."`

**统计**：
- 字母：26 个
- 单词：5 个（Congratulations, Today, is, your, day）
- 句子：2 个（! 和 . 各结尾一个）

**计算**：
```
L = (26 / 5) × 100 = 520
S = (2 / 5) × 100 = 40

index = 0.0588 × 520 - 0.296 × 40 - 15.8
      = 30.576 - 11.84 - 15.8
      = 2.936
      ≈ 3 (四舍五入)

输出：Grade 3
```

## 难点分解

### 难点 1：统计字母数

```c
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))  // 只计算字母
        {
            count++;
        }
    }
    return count;
}
```

**说明**：
- `isalpha()` 判断是否为字母（a-z, A-Z）
- 忽略数字、标点、空格

### 难点 2：统计单词数

这是本题的**核心难点**！

#### 错误方法：数空格

```c
// ❌ 错误方法
int count = 1;  // 从 1 开始
for (int i = 0; i < n; i++)
{
    if (text[i] == ' ')
        count++;
}
```

**问题**：
- 文本开头/结尾有空格会出错
- 连续多个空格会多计数

#### 正确方法：状态机

```c
int count_words(string text)
{
    int count = 0;
    bool in_word = false;  // 状态标记：是否在单词内部
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] != ' ' && !in_word)
        {
            // 进入新单词
            count++;
            in_word = true;
        }
        else if (text[i] == ' ')
        {
            // 离开单词
            in_word = false;
        }
    }
    return count;
}
```

**工作原理**：

以文本 `"Hello  world"` 为例（注意两个空格）：

```
位置  字符  in_word  动作              count
0     'H'   false    进入单词           1
1     'e'   true     在单词内           1
2     'l'   true     在单词内           1
3     'l'   true     在单词内           1
4     'o'   true     在单词内           1
5     ' '   true     离开单词(false)    1
6     ' '   false    仍在单词外         1
7     'w'   false    进入单词           2
...
```

**关键点**：
- `in_word` 标记防止重复计数
- 可以正确处理作业要求中提到的多个连续空格
- 可以处理开头/结尾的空格

### 难点 3：统计句子数

```c
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
```

**说明**：
- 遇到句子结束符就计数
- 三个条件用 `||`（或）连接

### 难点 4：浮点数计算

```c
// ❌ 错误：整数除法
float L = letters / words * 100;  // 会丢失小数部分

// ✅ 正确：强制类型转换
float L = (float) letters / (float) words * 100;
```

**为什么需要类型转换？**

```
假设 letters = 26, words = 5

整数除法：26 / 5 = 5 (丢失小数部分)
浮点除法：26.0 / 5.0 = 5.2 (保留小数)

L = 5 × 100 = 500 ❌
L = 5.2 × 100 = 520 ✅
```

## 代码实现

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// 函数原型
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // 提示用户输入文本
    string text = get_string("Text: ");
    
    // 统计字母、单词、句子数
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // 计算 Coleman-Liau index
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // 四舍五入
    int grade = round(index);

    // 输出结果
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

/*
 * 统计文本中的字母数（a-z, A-Z）
 */
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

/*
 * 统计文本中的单词数（由空格分隔）
 * 使用状态机避免重复计数和处理多余空格
 */
int count_words(string text)
{
    int count = 0;
    bool in_word = false;
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] != ' ' && !in_word)
        {
            count++;       // 进入新单词
            in_word = true;
        }
        else if (text[i] == ' ')
        {
            in_word = false;  // 离开单词
        }
    }
    return count;
}

/*
 * 统计文本中的句子数（以 . ! ? 结尾）
 */
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
```

## 运行示例

### 示例 1：简单文本

```bash
$ ./readability
Text: One fish. Two fish. Red fish. Blue fish.
Before Grade 1
```

**验证**：
- 字母：36
- 单词：8
- 句子：4

```
L = (36/8) × 100 = 450
S = (4/8) × 100 = 50
index = 0.0588 × 450 - 0.296 × 50 - 15.8
      = 26.46 - 14.8 - 15.8
      = -4.14 ≈ -4
```

### 示例 2：《哈利·波特》段落

```bash
$ ./readability
Text: Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard.
Grade 5
```

### 示例 3：高级文本

```bash
$ ./readability
Text: As the average number of letters and words per sentence increases, the Coleman-Liau index gives the text a higher reading level. If you were to take this paragraph, for instance, which has longer words and sentences than either of the prior two examples, the formula would give the text an twelfth-grade reading level.
Grade 12
```

## 关键知识点

✅ **字符串遍历**：逐字符分析文本  
✅ **状态机**：用布尔标记追踪状态  
✅ **字符分类**：`isalpha()` 等函数  
✅ **浮点数运算**：类型转换避免精度丢失  
✅ **数学函数**：`round()` 四舍五入

---

# 3. Caesar

## 问题描述

实现 **凯撒密码（Caesar Cipher）**：一种古老的加密方法，将每个字母按字母表顺序移动固定位数。

### 加密示例

密钥 `k = 1`：

```
明文：  H  E  L  L  O
       ↓  ↓  ↓  ↓  ↓
密文：  I  F  M  M  P
```

- H → I（移动 1 位）
- E → F
- L → M
- O → P

### 加密公式

```
ci = (pi + k) % 26
```

其中：
- `pi`：明文字符在字母表中的位置（A=0, B=1, ..., Z=25）
- `k`：密钥（移动位数）
- `ci`：密文字符的位置
- `% 26`：模运算，确保循环（Z 之后回到 A）

## 需求分析

### 程序要求

1. **命令行参数**：
   - 接受一个非负整数作为密钥
   - 参数必须是纯数字
2. **加密规则**：
   - 只加密字母
   - 保持大小写
   - 非字母字符保持不变
3. **循环处理**：
   - Z + 1 = A
   - 即使 k > 26 也要正确处理

### 程序流程

```
1. 检查命令行参数数量（必须是 1 个）
2. 验证参数是否全为数字
3. 将参数转换为整数
4. 提示用户输入明文
5. 逐字符加密
6. 输出密文
```

## 核心算法：字符旋转

这是本题的**关键难点**！

### 示例 1：基本加密

加密大写字母 `'H'`，密钥 `k = 1`：

```c
步骤 1：转换为位置（0-25）
position = 'H' - 'A'
         = 72 - 65
         = 7

步骤 2：加上密钥并取模
new_position = (7 + 1) % 26
             = 8

步骤 3：转回字符
result = 'A' + 8
       = 65 + 8
       = 73
       = 'I'

结果：'H' → 'I' ✓
```

### 示例 2：循环情况

加密 `'Z'`，密钥 `k = 1`：

```c
步骤 1：
position = 'Z' - 'A' = 25

步骤 2：关键的模运算！
new_position = (25 + 1) % 26
             = 26 % 26
             = 0  ← 循环回到开头

步骤 3：
result = 'A' + 0 = 'A'

结果：'Z' → 'A' ✓
```

### 示例 3：大密钥

加密 `'A'`，密钥 `k = 27`：

```c
position = 0
new_position = (0 + 27) % 26
             = 1

result = 'A' + 1 = 'B'

说明：k=27 等同于 k=1 (27 % 26 = 1)
```

### 为什么要用 % 26？

模运算实现字母表的循环：

```
位置:  0  1  2 ... 24 25 | 26 27 28 ...
字母:  A  B  C ... Y  Z  | A  B  C  ...
                          ↑
                     循环回到开头

(25 + 1) % 26 = 0  → Z + 1 = A
(25 + 2) % 26 = 1  → Z + 2 = B
(25 + 27) % 26 = 0 → Z + 27 = A
```

## 代码实现

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// 函数原型
bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // 检查 1：参数数量必须是 2（程序名 + 密钥）
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // 检查 2：密钥必须是纯数字
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // 将字符串转换为整数
    int key = atoi(argv[1]);
    
    // 提示用户输入明文
    string plaintext = get_string("plaintext: ");
    
    // 加密并输出
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char encrypted = rotate(plaintext[i], key);
        printf("%c", encrypted);
    }
    printf("\n");
    
    return 0;
}

/*
 * 检查字符串是否只包含数字
 */
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

/*
 * 使用凯撒密码旋转字符
 * 保持大小写，非字母字符不变
 */
char rotate(char c, int n)
{
    if (isupper(c))
    {
        // 大写字母
        int position = (c - 'A' + n) % 26;
        return 'A' + position;
    }
    else if (islower(c))
    {
        // 小写字母
        int position = (c - 'a' + n) % 26;
        return 'a' + position;
    }
    else
    {
        // 非字母字符保持不变
        return c;
    }
}
```

## 代码详解

### 1. 命令行参数处理

```c
int main(int argc, string argv[])
```

运行 `./caesar 13` 时：
- `argc = 2`
- `argv[0] = "./caesar"`
- `argv[1] = "13"`

### 2. only_digits 函数

```c
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))  // 检查是否为 0-9
        {
            return false;
        }
    }
    return true;
}
```

**测试**：
- `"123"` → `true`
- `"12a3"` → `false`
- `"-5"` → `false`（负号不是数字）

### 3. rotate 函数的精妙之处

```c
// 为什么分别处理大小写？
if (isupper(c))
    return 'A' + ((c - 'A' + n) % 26);
else if (islower(c))
    return 'a' + ((c - 'a' + n) % 26);
```

**原因**：大小写字母的 ASCII 码不连续

```
ASCII:
'A' = 65, 'B' = 66, ..., 'Z' = 90
'a' = 97, 'b' = 98, ..., 'z' = 122
       ↑
    中间有 6 个其他字符
```

所以必须：
- 大写字母以 `'A'` 为基准
- 小写字母以 `'a'` 为基准

## 运行示例

### 示例 1：基本加密

```bash
$ ./caesar 1
plaintext: HELLO
ciphertext: IFMMP
```

**过程**：
- H (7) + 1 = 8 → I
- E (4) + 1 = 5 → F
- L (11) + 1 = 12 → M
- O (14) + 1 = 15 → P

### 示例 2：保持大小写和标点

```bash
$ ./caesar 13
plaintext: Hello, World!
ciphertext: Uryyb, Jbeyq!
```

**说明**：
- `H` → `U`（大写保持大写）
- `e` → `r`（小写保持小写）
- `,` → `,`（标点不变）
- ` ` → ` `（空格不变）

### 示例 3：循环

```bash
$ ./caesar 1
plaintext: XYZ
ciphertext: YZA
```

**验证**：
- X (23) + 1 = 24 → Y
- Y (24) + 1 = 25 → Z
- Z (25) + 1 = 26 % 26 = 0 → A ✓

### 示例 4：大密钥

```bash
$ ./caesar 27
plaintext: ABC
ciphertext: BCD
```

**说明**：27 % 26 = 1，效果等同于密钥为 1

### 示例 5：错误处理

```bash
$ ./caesar
Usage: ./caesar key
```

```bash
$ ./caesar abc
Usage: ./caesar key
```

```bash
$ ./caesar 1 2
Usage: ./caesar key
```

## 常见错误

### 错误 1：忘记模运算

```c
// ❌ 错误
return 'A' + (c - 'A' + n);  // Z + 1 = '['（ASCII 91）

// ✅ 正确
return 'A' + ((c - 'A' + n) % 26);
```

### 错误 2：大小写处理不当

```c
// ❌ 错误：对所有字符使用同一基准
return 'A' + ((c - 'A' + n) % 26);  // 小写字母会出错

// ✅ 正确：分别处理
if (isupper(c))
    return 'A' + ((c - 'A' + n) % 26);
else if (islower(c))
    return 'a' + ((c - 'a' + n) % 26);
```

### 错误 3：不检查参数

```c
// ❌ 错误：直接使用 argv[1]
int key = atoi(argv[1]);  // 如果没有参数会崩溃

// ✅ 正确：先检查
if (argc != 2)
{
    printf("Usage: ./caesar key\n");
    return 1;
}
```

## 关键知识点

✅ **命令行参数**：`argc` 和 `argv[]`  
✅ **字符串验证**：`isdigit()`、`atoi()`  
✅ **模运算**：实现循环（`% 26`）  
✅ **ASCII 运算**：字符与整数的转换  
✅ **字符判断**：`isupper()`、`islower()`

---

# 4. Substitution

## 问题描述

实现 **替换密码（Substitution Cipher）**：比凯撒密码更复杂，使用 26 个字母的密钥，将字母表中的每个字母映射到密钥中对应位置的字母。

### 加密原理

```
字母表: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
密钥:   N Q X P O M A F T R H L Z G E C Y J I U W S K D V B
```

**映射关系**：
- A → N（字母表第 1 个 → 密钥第 1 个）
- B → Q（字母表第 2 个 → 密钥第 2 个）
- C → X
- ...

### 加密示例

加密 `HELLO`：

```
H (索引 7) → 密钥[7] = F
E (索引 4) → 密钥[4] = O
L (索引 11) → 密钥[11] = L
L (索引 11) → 密钥[11] = L
O (索引 14) → 密钥[14] = E

HELLO → FOLLE
```

## 需求分析

### 密钥验证规则

密钥必须满足：

1. **长度**：恰好 26 个字符
2. **字符类型**：只能包含字母
3. **唯一性**：每个字母只能出现一次
4. **大小写不敏感**：`ABC...` 和 `abc...` 效果相同

### 加密规则

1. 只加密字母
2. 保持大小写
3. 非字母字符保持不变

## 核心算法

### 算法流程

```
对于明文中的每个字符:
    如果是大写字母:
        1. 找到它在字母表中的位置 (0-25)
        2. 用这个位置作为索引，在密钥中查找对应字母
        3. 将结果转换为大写
    如果是小写字母:
        1. 找到它在字母表中的位置 (0-25)
        2. 用这个位置作为索引，在密钥中查找对应字母
        3. 将结果转换为小写
    否则:
        保持原样
```

### 示例演示

密钥：`VCHPRZGJNTLSKFBDQWAXEUYMOI`

**加密 'H'（大写）**：

```c
步骤 1：找位置
index = 'H' - 'A' = 7

步骤 2：查密钥
key[7] = 'J'

步骤 3：确保大写
result = toupper('J') = 'J'

结果：'H' → 'J'
```

**加密 'h'（小写）**：

```c
步骤 1：找位置
index = 'h' - 'a' = 7

步骤 2：查密钥
key[7] = 'J'  (密钥可能是大写)

步骤 3：转换为小写
result = tolower('J') = 'j'

结果：'h' → 'j'
```

## 关键难点：密钥验证

这是本题的**核心挑战**！需要同时检查三个条件。

### 难点 1：如何检查唯一性？

**错误方法**：嵌套循环（低效）

```c
// ❌ O(n²) 时间复杂度
for (int i = 0; i < 26; i++)
{
    for (int j = i + 1; j < 26; j++)
    {
        if (key[i] == key[j])
            return false;
    }
}
```

**正确方法**：布尔数组（高效）

```c
// ✅ O(n) 时间复杂度
bool letter_seen[26] = {false};

for (int i = 0; i < 26; i++)
{
    char c = toupper(key[i]);
    int index = c - 'A';
    
    if (letter_seen[index])  // 已经出现过
        return false;
    
    letter_seen[index] = true;  // 标记为已出现
}
```

### 布尔数组的工作原理

```
数组：letter_seen[26]
索引：  0    1    2   ...  25
字母：  A    B    C   ...  Z
值：   true/false (是否出现过)

示例：处理密钥 "ABC..."

初始状态：
[F F F F F ... F]  (全为 false)

遇到 'A':
index = 0
letter_seen[0] 是 false? ✓ → 设置为 true
[T F F F F ... F]

遇到 'B':
index = 1
letter_seen[1] 是 false? ✓ → 设置为 true
[T T F F F ... F]

如果再遇到 'A':
index = 0
letter_seen[0] 是 false? ✗ (已经是 true)
→ 返回 false (密钥无效)
```

这种技术叫做 **"标记数组"** 或 **"访问数组"**，非常常用！

## 代码实现

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 函数原型
bool is_valid_key(string key);
char substitute(char c, string key);

int main(int argc, string argv[])
{
    // 检查 1：参数数量
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    // 检查 2：密钥有效性
    if (!is_valid_key(argv[1]))
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    string key = argv[1];
    
    // 提示用户输入
    string plaintext = get_string("plaintext: ");
    
    // 加密并输出
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char encrypted = substitute(plaintext[i], key);
        printf("%c", encrypted);
    }
    printf("\n");
    
    return 0;
}

/*
 * 验证密钥是否有效
 * 必须：26个字符，全是字母，无重复
 */
bool is_valid_key(string key)
{
    int len = strlen(key);
    
    // 检查长度
    if (len != 26)
    {
        return false;
    }
    
    // 使用布尔数组追踪字母是否出现过
    bool letter_seen[26] = {false};
    
    for (int i = 0; i < len; i++)
    {
        char c = toupper(key[i]);
        
        // 检查是否为字母
        if (!isalpha(c))
        {
            return false;
        }
        
        // 检查是否重复
        int index = c - 'A';
        if (letter_seen[index])
        {
            return false;  // 这个字母已经出现过
        }
        
        letter_seen[index] = true;  // 标记为已出现
    }
    
    return true;
}

/*
 * 使用替换密码加密字符
 * 保持大小写，非字母字符不变
 */
char substitute(char c, string key)
{
    if (isupper(c))
    {
        // 大写字母
        int index = c - 'A';
        return toupper(key[index]);
    }
    else if (islower(c))
    {
        // 小写字母
        int index = c - 'a';
        return tolower(key[index]);
    }
    else
    {
        // 非字母字符
        return c;
    }
}
```

## 代码详解

### 1. is_valid_key 函数的巧妙设计

```c
bool letter_seen[26] = {false};
```

**一次遍历完成三个检查**：

```c
for (int i = 0; i < 26; i++)
{
    char c = toupper(key[i]);
    
    // 检查 1：是否为字母
    if (!isalpha(c))
        return false;
    
    // 检查 2：是否重复
    int index = c - 'A';
    if (letter_seen[index])
        return false;
    
    // 标记为已出现
    letter_seen[index] = true;
}
```

**效率分析**：
- 时间复杂度：O(26) = O(1)
- 空间复杂度：O(26) = O(1)
- 一次遍历完成所有检查！

### 2. substitute 函数

```c
char substitute(char c, string key)
{
    if (isupper(c))
        return toupper(key[c - 'A']);
    else if (islower(c))
        return tolower(key[c - 'a']);
    else
        return c;
}
```

**为什么要用 toupper/tolower？**

因为密钥本身大小写不敏感：

```bash
./substitution vchpr...  # 小写密钥
./substitution VCHPR...  # 大写密钥
# 两者效果相同
```

但加密后的密文大小写需要与原明文大小写保持一致：
- 大写 → 大写：`'H' → 'J'`
- 小写 → 小写：`'h' → 'j'`

### 3. 完整加密示例

密钥：`VCHPRZGJNTLSKFBDQWAXEUYMOI`  
明文：`Hello, World!`

```
H (索引 7) → key[7] = 'J' → toupper('J') = 'J'
e (索引 4) → key[4] = 'R' → tolower('R') = 'r'
l (索引 11) → key[11] = 'S' → tolower('S') = 's'
l (索引 11) → key[11] = 'S' → tolower('S') = 's'
o (索引 14) → key[14] = 'B' → tolower('B') = 'b'
, → ,
  →  
W (索引 22) → key[22] = 'Y' → toupper('Y') = 'Y'
o (索引 14) → key[14] = 'B' → tolower('B') = 'b'
r (索引 17) → key[17] = 'W' → tolower('W') = 'w'
l (索引 11) → key[11] = 'S' → tolower('S') = 's'
d (索引 3) → key[3] = 'P' → tolower('P') = 'p'
! → !

结果：Jrssb, Ybwsp!
```

## 运行示例

### 示例 1：基本加密

```bash
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext: HELLO
ciphertext: JRSSB
```

### 示例 2：保持大小写

```bash
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext: Hello, World!
ciphertext: Jrssb, Ybwsp!
```

### 示例 3：密钥大小写混合

```bash
$ ./substitution VchprZGJNtlskfbdQWAXeuymoi
plaintext: HELLO
ciphertext: JRSSB
```

（结果相同，密钥大小写不影响）

### 示例 4：错误情况

#### 密钥太短

```bash
$ ./substitution ABC
Key must contain 26 unique alphabetic characters.
```

#### 密钥包含非字母

```bash
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYM01
Key must contain 26 unique alphabetic characters.
```

#### 密钥有重复字母

```bash
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOII
Key must contain 26 unique alphabetic characters.
```

（最后有两个 'I'）

#### 无参数

```bash
$ ./substitution
Usage: ./substitution key
```

## 对比：凯撒密码 vs 替换密码

| 特性 | 凯撒密码 | 替换密码 |
|------|---------|---------|
| 密钥 | 一个数字（0-25） | 26 个字母的排列 |
| 可能性 | 26 种 | 26! ≈ 4×10²⁶ 种 |
| 安全性 | 极低（可暴力破解） | 较高 |
| 加密逻辑 | 固定位移 | 任意映射 |
| 示例 | k=1: A→B, B→C | 密钥定义: A→V, B→C |

**有趣的事实**：凯撒密码是替换密码的特殊情况！

```
凯撒密码 k=1 的密钥：
BCDEFGHIJKLMNOPQRSTUVWXYZA
```

## 关键知识点

✅ **命令行参数验证**：多重条件检查  
✅ **布尔数组技巧**：高效追踪字母出现  
✅ **字符映射**：使用索引实现替换  
✅ **大小写处理**：`toupper()`、`tolower()`  
✅ **字符判断**：`isalpha()`、`isupper()`、`islower()`

---

## 📊 Problem Set 2 总结

### 知识点对比

| 问题 | 核心数据结构 | 核心算法 | 难度亮点 |
|------|------------|----------|---------|
| Scrabble | 数组 | 字符映射 | 数组作为查找表 |
| Readability | 字符串 | 文本分析 | 状态机、浮点运算 |
| Caesar | 字符串 | 字符旋转 | 模运算、大小写处理 |
| Substitution | 字符串、布尔数组 | 字符映射 | 密钥验证、标记数组 |

### 重要技术总结

#### 1. 数组技巧
- **查找表**：用数组索引快速映射数据
- **标记数组**：用布尔数组追踪状态

#### 2. 字符串处理
- **字符分类**：`isalpha()`, `isdigit()`, `isupper()`, `islower()`
- **字符转换**：`toupper()`, `tolower()`, `atoi()`
- **字符串遍历**：`for (int i = 0, n = strlen(s); i < n; i++)`

#### 3. ASCII 运算
```c
// 字母到索引
'A' - 'A' = 0, 'B' - 'A' = 1, ..., 'Z' - 'A' = 25
'a' - 'a' = 0, 'b' - 'a' = 1, ..., 'z' - 'a' = 25

// 索引到字母
'A' + 0 = 'A', 'A' + 1 = 'B', ..., 'A' + 25 = 'Z'
'a' + 0 = 'a', 'a' + 1 = 'b', ..., 'a' + 25 = 'z'
```

#### 4. 模运算
```c
(position + key) % 26  // 实现字母表循环
```

#### 5. 状态机
```c
bool in_word = false;
// 用状态标记追踪复杂逻辑
```

#### 6. 类型转换
```c
(float) a / (float) b  // 避免整数除法丢失精度
```

### 编程技巧

#### ✅ 好的实践

1. **函数抽象**：将复杂逻辑封装成函数
2. **参数验证**：检查输入有效性
3. **清晰命名**：函数名表达意图
4. **注释说明**：解释关键算法
5. **边界测试**：测试极端情况

#### ❌ 常见错误

1. **整数除法**：忘记类型转换
2. **数组越界**：不检查长度
3. **忘记模运算**：字符旋转不循环
4. **大小写混淆**：'A' 和 'a' 的基准不同
5. **参数检查**：直接使用 argv 而不验证

### 学习建议

对于初学者：

1. **理解优先**：先理解算法，再写代码
2. **分步实现**：逐个函数实现和测试
3. **画图辅助**：画出数组、字符映射关系
4. **测试驱动**：先写测试用例，再写代码
5. **调试技巧**：打印中间值验证逻辑

### 下一步

完成 Problem Set 2 后，你已经掌握了：
- ✅ 数组的使用和技巧
- ✅ 字符串的处理方法
- ✅ 命令行参数的处理
- ✅ 基本的密码学概念

Week 3 将学习**算法（Algorithms）**：排序、搜索、递归等，敬请期待！

---

## 参考资源

- [CS50 Week 2 主页](https://cs50.harvard.edu/x/weeks/2/)
- [CS50 Week 2 Notes](https://cs50.harvard.edu/x/notes/2/)
- [CS50 Manual Pages](https://manual.cs50.io/)
- [ASCII Table](https://www.asciitable.com/)

---

**完成时间**：2025-12-11  
**编译命令**：`make <program_name>`  
**测试命令**：`check50 cs50/problems/2025/x/<problem_name>`  
**代码风格**：`style50 <filename>.c`

Happy Coding! 🎉

