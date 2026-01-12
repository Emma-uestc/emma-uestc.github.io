---
layout: post
title: "CS50 Problem Set 6: Python 实战 - 用 Python 重写经典问题"
date: 2025-12-26
categories: [CS50, Programming, Practice]
tags: [Python, 算法, 问题解决]
---

# Problem Set 6 概述

本周作业的核心目标是**用 Python 重新实现之前用 C 写过的程序**。这是一个绝佳的学习机会：通过对比两种语言的实现，你会深刻理解 Python 的简洁与强大。

| 题目 | C 版本 | Python 版本 | 难度 |
|------|--------|-------------|------|
| Hello | Week 1 | 本周 | ⭐ |
| Mario (Less) | Week 1 | 本周 | ⭐⭐ |
| Mario (More) | Week 1 | 本周 | ⭐⭐ |
| Cash | Week 1 | 本周 | ⭐⭐ |
| Credit | Week 1 | 本周 | ⭐⭐⭐ |
| Readability | Week 2 | 本周 | ⭐⭐⭐ |
| DNA | 新题 | 本周 | ⭐⭐⭐⭐ |

**作业页面**：[https://cs50.harvard.edu/x/psets/6/](https://cs50.harvard.edu/x/psets/6/)

> 💡 **学习提示**：这些题目已经用 C 实现过，现在重点关注 **Python 如何用更少的代码实现相同功能**。

---

# 1. Hello

## C vs Python 对比

**C 版本**（7 行）：
```c
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
}
```

**Python 版本**（2 行）：
```python
from cs50 import get_string

answer = get_string("What's your name? ")
print(f"hello, {answer}")
```

**或者不使用 CS50 库**（1 行）：
```python
print(f"hello, {input('What is your name? ')}")
```

> 🎯 **代码量对比**：C 需要 7 行，Python 只需 1-2 行！

---

# 2. Mario (Less) - 右对齐金字塔

**题目链接**：[https://cs50.harvard.edu/x/psets/6/mario/less/](https://cs50.harvard.edu/x/psets/6/mario/less/)

## 输出示例

高度为 4 时：
```
   #
  ##
 ###
####
```

## C vs Python 对比

回顾 C 版本的核心逻辑：
```c
// C: 嵌套循环，分别处理空格和井号
for (int i = 0; i < height; i++)
{
    for (int j = 0; j < height - i - 1; j++)
        printf(" ");
    for (int j = 0; j < i + 1; j++)
        printf("#");
    printf("\n");
}
```

## Python 实现

### 方法 1：直译 C 版本

```python
from cs50 import get_int

# 获取高度（1-8 之间）
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# 打印金字塔
for i in range(height):
    # 打印空格
    for j in range(height - i - 1):
        print(" ", end="")
    # 打印井号
    for j in range(i + 1):
        print("#", end="")
    # 换行
    print()
```

### 方法 2：利用 Python 字符串乘法（推荐）

```python
from cs50 import get_int

# 获取高度
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# 打印金字塔（每行一句话！）
for i in range(height):
    print(" " * (height - i - 1) + "#" * (i + 1))
```

### 方法 3：使用 str.rjust() 右对齐

```python
from cs50 import get_int

while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

for i in range(1, height + 1):
    print(("#" * i).rjust(height))
```

## 关键 Python 技巧

| 技巧 | 说明 | 示例 |
|------|------|------|
| 字符串乘法 | `"#" * 4` → `"####"` | 替代 C 中的循环 |
| `print(end="")` | 不换行打印 | 替代 `printf` 无 `\n` |
| `str.rjust(n)` | 右对齐到 n 位 | 自动补空格 |
| `while True` + `break` | 模拟 `do-while` | Python 没有 `do-while` |

---

# 3. Mario (More) - 双侧金字塔

**题目链接**：[https://cs50.harvard.edu/x/psets/6/mario/more/](https://cs50.harvard.edu/x/psets/6/mario/more/)

## 输出示例

高度为 4 时：
```
   #  #
  ##  ##
 ###  ###
####  ####
```

## Python 实现

```python
from cs50 import get_int

# 获取高度
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# 打印双侧金字塔
for i in range(height):
    # 左侧金字塔（右对齐）
    left = "#" * (i + 1)
    left = left.rjust(height)
    
    # 右侧金字塔（左对齐）
    right = "#" * (i + 1)
    
    # 中间间隙固定 2 个空格
    print(left + "  " + right)
```

### 更简洁的写法

```python
from cs50 import get_int

while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

for i in range(1, height + 1):
    blocks = "#" * i
    print(blocks.rjust(height) + "  " + blocks)
```

> 🔍 **对比 C 版本**：C 需要 4 个嵌套循环（空格、左侧#、间隙、右侧#），Python 用字符串操作一行搞定！

---

# 4. Cash - 贪心算法找零

**题目链接**：[https://cs50.harvard.edu/x/psets/6/cash/](https://cs50.harvard.edu/x/psets/6/cash/)

## 问题回顾

给定找零金额（美分），使用贪心算法计算最少硬币数。

美国硬币：25¢、10¢、5¢、1¢

## C vs Python 对比

**C 版本**：
```c
coins += cents / 25;
cents %= 25;
coins += cents / 10;
cents %= 10;
// ... 依次类推
```

**Python 版本**：

### 方法 1：直译 C 版本

```python
from cs50 import get_int

# 获取找零金额（正整数）
while True:
    cents = get_int("Change owed: ")
    if cents >= 0:
        break

coins = 0

# 25 美分
coins += cents // 25
cents %= 25

# 10 美分
coins += cents // 10
cents %= 10

# 5 美分
coins += cents // 5
cents %= 5

# 1 美分
coins += cents

print(coins)
```

### 方法 2：使用循环（更优雅）

```python
from cs50 import get_int

while True:
    cents = get_int("Change owed: ")
    if cents >= 0:
        break

coins = 0
denominations = [25, 10, 5, 1]  # 面值从大到小

for coin in denominations:
    coins += cents // coin
    cents %= coin

print(coins)
```

### 方法 3：使用 divmod()

```python
from cs50 import get_int

while True:
    cents = get_int("Change owed: ")
    if cents >= 0:
        break

coins = 0
for coin in [25, 10, 5, 1]:
    count, cents = divmod(cents, coin)  # 同时返回商和余数
    coins += count

print(coins)
```

## Python 特性亮点

| 特性 | C 语言 | Python |
|------|--------|--------|
| 整数除法 | `cents / 25` | `cents // 25`（注意双斜杠！） |
| 取模运算 | `cents % 25` | `cents % 25`（相同） |
| 同时取商和余 | 需要两行 | `divmod(cents, 25)` |
| 遍历面值 | 手动逐个写 | `for coin in [25, 10, 5, 1]` |

> ⚠️ **易错点**：Python 中 `/` 是浮点除法，`//` 才是整数除法！

---

# 5. Credit - Luhn 算法验证信用卡

**题目链接**：[https://cs50.harvard.edu/x/psets/6/credit/](https://cs50.harvard.edu/x/psets/6/credit/)

## 问题回顾

使用 Luhn 算法验证信用卡号，并识别卡片类型（AMEX、MASTERCARD、VISA）。

## Python 实现

### 方法 1：直译 C 逻辑

```python
from cs50 import get_int

card = get_int("Number: ")
card_str = str(card)
length = len(card_str)

# Luhn 算法
sum1 = 0  # 偶数位置（倒数第2、4、6...位）乘2后的和
sum2 = 0  # 奇数位置（倒数第1、3、5...位）的数字和

for i, digit in enumerate(reversed(card_str)):
    d = int(digit)
    if i % 2 == 1:  # 偶数位置（从0开始，所以是奇数索引）
        product = d * 2
        sum1 += product // 10 + product % 10
    else:
        sum2 += d

total = sum1 + sum2

# 验证校验和
if total % 10 != 0:
    print("INVALID")
elif length == 15 and card_str[:2] in ["34", "37"]:
    print("AMEX")
elif length == 16 and card_str[:2] in ["51", "52", "53", "54", "55"]:
    print("MASTERCARD")
elif length in [13, 16] and card_str[0] == "4":
    print("VISA")
else:
    print("INVALID")
```

### 方法 2：更 Pythonic 的写法

```python
from cs50 import get_int

def luhn_check(card_str):
    """Luhn 算法验证"""
    total = 0
    for i, digit in enumerate(reversed(card_str)):
        d = int(digit)
        if i % 2 == 1:
            d *= 2
            if d > 9:
                d -= 9  # 等价于 d // 10 + d % 10
        total += d
    return total % 10 == 0

def get_card_type(card_str):
    """识别卡片类型"""
    length = len(card_str)
    prefix = card_str[:2]
    
    if length == 15 and prefix in ["34", "37"]:
        return "AMEX"
    elif length == 16 and prefix in ["51", "52", "53", "54", "55"]:
        return "MASTERCARD"
    elif length in [13, 16] and card_str[0] == "4":
        return "VISA"
    return "INVALID"

# 主程序
card = get_int("Number: ")
card_str = str(card)

if luhn_check(card_str):
    print(get_card_type(card_str))
else:
    print("INVALID")
```

## Python 优势对比

| 操作 | C 语言 | Python |
|------|--------|--------|
| 获取长度 | 循环计数 | `len(str(card))` |
| 获取前两位 | 循环提取 | `card_str[:2]` |
| 遍历每位数字 | `while (temp > 0)` | `for d in card_str` |
| 反向遍历 | 复杂索引 | `reversed(card_str)` |
| 判断前缀 | `if (prefix == 34 \|\| prefix == 37)` | `if prefix in ["34", "37"]` |

### Luhn 算法小技巧

当一个数字乘以 2 后大于 9 时（如 `7×2=14`），我们需要将两位数分别相加（`1+4=5`）。

有一个数学技巧：`d * 2 > 9` 时，`d * 2 - 9` 等价于 `(d * 2) // 10 + (d * 2) % 10`。

```python
# 例如：7 * 2 = 14
# 方法 1：14 // 10 + 14 % 10 = 1 + 4 = 5
# 方法 2：14 - 9 = 5
# 两者等价！
```

---

# 6. Readability - 文本可读性分析

**题目链接**：[https://cs50.harvard.edu/x/psets/6/readability/](https://cs50.harvard.edu/x/psets/6/readability/)

## 问题回顾

使用 **Coleman-Liau 公式** 计算文本的阅读等级：

```
index = 0.0588 * L - 0.296 * S - 15.8
```

其中：
- **L** = 每 100 个单词的平均字母数
- **S** = 每 100 个单词的平均句子数

## C vs Python 对比

### C 版本核心逻辑

```c
// C: 需要三个独立函数，手动遍历字符串
int count_letters(string text) {
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++) {
        if (isalpha(text[i])) count++;
    }
    return count;
}

int count_words(string text) {
    int count = 0;
    bool in_word = false;
    for (int i = 0, n = strlen(text); i < n; i++) {
        if (text[i] != ' ' && !in_word) {
            count++;
            in_word = true;
        } else if (text[i] == ' ') {
            in_word = false;
        }
    }
    return count;
}

int count_sentences(string text) {
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
            count++;
    }
    return count;
}
```

### Python 版本

#### 方法 1：直译 C 版本

```python
from cs50 import get_string


def count_letters(text):
    """统计字母数量"""
    count = 0
    for c in text:
        if c.isalpha():
            count += 1
    return count


def count_words(text):
    """统计单词数量（以空格分隔）"""
    return len(text.split())


def count_sentences(text):
    """统计句子数量（以 . ! ? 结尾）"""
    count = 0
    for c in text:
        if c in '.!?':
            count += 1
    return count


# 主程序
text = get_string("Text: ")

letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)

# 计算 L 和 S
L = letters / words * 100
S = sentences / words * 100

# Coleman-Liau 公式
index = 0.0588 * L - 0.296 * S - 15.8
grade = round(index)

# 输出结果
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
```

#### 方法 2：更 Pythonic 的写法（推荐）

```python
from cs50 import get_string

text = get_string("Text: ")

# 一行搞定统计！
letters = sum(1 for c in text if c.isalpha())
words = len(text.split())
sentences = sum(1 for c in text if c in '.!?')

# Coleman-Liau 公式
L = letters / words * 100
S = sentences / words * 100
index = 0.0588 * L - 0.296 * S - 15.8
grade = round(index)

# 输出
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
```

#### 方法 3：使用正则表达式（进阶）

```python
import re
from cs50 import get_string

text = get_string("Text: ")

# 使用正则表达式
letters = len(re.findall(r'[a-zA-Z]', text))
words = len(text.split())
sentences = len(re.findall(r'[.!?]', text))

# Coleman-Liau 公式
L = letters / words * 100
S = sentences / words * 100
grade = round(0.0588 * L - 0.296 * S - 15.8)

# 输出
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
```

## Python 优势对比

| 操作 | C 语言 | Python |
|------|--------|--------|
| 统计字母 | 手动循环 + `isalpha()` | `sum(1 for c in text if c.isalpha())` |
| 统计单词 | 状态机 + `in_word` 标记 | `len(text.split())` |
| 统计句子 | 循环 + 多个 `\|\|` 判断 | `sum(1 for c in text if c in '.!?')` |
| 四舍五入 | `round()` (需要 `<math.h>`) | `round()` (内置) |
| 类型转换 | `(float)letters / words` | 自动浮点除法 |

### Python 独有技巧

#### 1. 生成器表达式求和

```python
# 统计满足条件的元素个数
sum(1 for c in text if c.isalpha())

# 等价于
count = 0
for c in text:
    if c.isalpha():
        count += 1
```

#### 2. `str.split()` 自动分割

```python
text = "Hello World"
words = text.split()  # ['Hello', 'World']
word_count = len(words)  # 2

# 自动处理多个空格！
text2 = "Hello    World"
text2.split()  # ['Hello', 'World']，仍然是 2 个单词
```

#### 3. `in` 运算符简化判断

```python
# C 语言写法
if (c == '.' || c == '!' || c == '?')

# Python 写法
if c in '.!?'
# 或
if c in ['.', '!', '?']
```

## 测试用例

| 输入文本 | 预期输出 |
|---------|---------|
| `One fish. Two fish. Red fish. Blue fish.` | `Before Grade 1` |
| `Congratulations! Today is your day.` | `Grade 3` |
| `Harry Potter was a highly unusual boy...` | `Grade 5` |
| `A large class of computational problems...` | `Grade 16+` |

```bash
# 测试命令
check50 cs50/problems/2025/x/sentimental/readability
```

# 7. DNA - 身份识别

**题目链接**：[https://cs50.harvard.edu/x/psets/6/dna/](https://cs50.harvard.edu/x/psets/6/dna/)  
这道题目在之前的课程中没有出现过，我们从头分析。  
##  题目背景与目标 (The Mission)  
### 背景  
DNA 由核苷酸序列组成（A, C, G, T）。每个人体内都有一些被称为 **STRs (Short Tandem Repeats，短串联重复序列)** 的特殊片段。
DNA（脱氧核糖核酸）：
- 由 A、C、G、T 四种核苷酸组成
- 每个人的 DNA 序列独特（除了同卵双胞胎）
- 可用于身份识别（亲子鉴定、犯罪调查）

STR（Short Tandem Repeat，短串联重复）：
- DNA 中的重复序列片段
- 例如："AGATAGATAGATAGAT" 中 "AGAT" 重复了 4 次
- 不同人在相同位置的重复次数不同  
### 任务  
实现一个程序，根据 DNA 序列识别身份  
编写一个 Python 程序 dna.py，它接收两个文件作为参数  
```bash
# 程序运行方式
$ python dna.py databases/small.csv sequences/1.txt
Bob

# 解释：
# - 读取数据库（small.csv）：包含多个人的 STR 重复次数
# - 读取 DNA 序列（1.txt）：待识别的 DNA 序列
# - 输出：匹配的人名或 "No match"
```  
#### 1. 数据库文件 (CSV)：包含一群人的名字，以及他们在不同 STR 上的最大重复次数。  
- 例如 small.csv:  
```text
name,AGATC,AATG,TATC
Alice,2,8,3
Bob,4,1,5
Charlie,3,2,5
```   
#### 2. DNA 序列文件 (TXT)：包含一段未知的 DNA 字符串。  
1.txt: AAGGTAAGATCAGATCAGATCTATCTATC...  
**核心任务：**    
程序需要完成三个主要任务：
1. 读取 CSV 数据库
   - 解析 CSV 文件
   - 提取 STR 列表和每个人的数据

2. 读取 DNA 序列
   - 读取 TXT 文件
   - 可能需要处理多行

3. 计算 STR 重复次数
   - 对每个 STR，找到最长连续重复次数
   - 例如：在 "AGATAGATAGATAGAT" 中，"AGAT" 连续重复 4 次

4. 匹配身份
   - 比较计算的 STR 次数与数据库中每个人的数据
   - 找到完全匹配的人，或输出 "No match" 

## 核心概念与思维模型   
### 1. 数据结构的选择   
Python 提供了极其强大的数据结构，不像 C 语言那样需要手搓链表或哈希表。  
- **CSV 数据**： 最适合使用 `csv.DictReader` 读取。每一行可以变成一个字典(Dictionary)，比如 `{'name': 'Alice', 'AGATC': '2', ...}`。  
- **DNA 序列**：就是一个巨大的 字符串 (String)。  
### 2. 算法核心：找最长连续重复次数？  
**问题**：如何找到 STR 在 DNA 序列中的最长连续重复次数？
假设序列是 `AAGATCAGATCTTTTAGATC`，我们要找 AGATC 的最长连续次数。  
- 这里有一段 AGATCAGATC (2次)。
- 后面有一段 AGATC (1次)。
- 最大连续次数是 2。  
**解法思路：**
```
最长连续重复 = 0
当前连续重复 = 0

遍历 DNA 序列的每个位置 i：
    如果从位置 i 开始匹配 STR：
        连续计数 = 0
        while DNA[i:i+len(STR)] == STR:
            连续计数 += 1
            i += len(STR)  # 跳到下一个可能的重复
        
        if 连续计数 > 最长连续重复:
            最长连续重复 = 连续计数

返回 最长连续重复
```    
代码实现思路  
```Python
import csv
import sys

def main():
    # 1. 检查命令行参数
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    
    # 2. 读取 CSV 数据库
    database = read_database(sys.argv[1])
    
    # 3. 读取 DNA 序列
    dna_sequence = read_sequence(sys.argv[2])
    
    # 4. 计算每个 STR 的最长连续重复
    str_counts = {}
    for str_name in database['str_names']:
        str_counts[str_name] = longest_match(dna_sequence, str_name)
    
    # 5. 匹配身份
    person = find_match(database, str_counts)
    
    # 6. 输出结果
    print(person)

def read_database(filename):
    """读取 CSV 数据库"""
    pass

def read_sequence(filename):
    """读取 DNA 序列"""
    pass

def longest_match(sequence, subsequence):
    """找到子序列的最长连续重复次数"""
    pass

def find_match(database, str_counts):
    """在数据库中找到匹配的人"""
    pass

if __name__ == "__main__":
    main()
```

## 分步实现方案 (Step-by-Step Plan)  
### 1. 处理命令行参数   
检查 `sys.argv`  
确保用户输入了两个参数：`python dna.py data.csv sequence.txt`。如果不对，打印用法并退出。  
### 2. 读取 csv 数据库  
使用 Python 内置的 `csv` 模块。  
```Python
import csv

str_names = []
people = []

with open("databases/small.csv") as file:
    reader = csv.DictReader(file)
    str_names = reader.fieldnames[1:]
    # print("STR names: ")
    # print(str_names)
    # print("row are:")
    for row in reader:
        # print(row)
        person = {'name': row['name']}
        for str_name in str_names:
            person[str_name] = int(row[str_name])
            people.append(person)

print("str_names are:")
print(str_names)
print("people are:")
print(people)
```    
**关键点**：`csv.DictReader` 有一个属性，`reader.fieldnames`,返回表头列表， `['name', 'AGATC', 'AATG', 'TATC']`,因此可以通过 Python list 的切片获取所有需要检测的 STR 名称列表。  
另外，为了让初学者更容易理解，我这里加入了一些调试信息，便于确认是否符合预期以及下一步应该用什么方法提取自己想要的信息。  
真正实现时，文件名是通过命令行参数获取的，将这里具体的文件换成从命令行参数获取。
打印的调试信息  
```bash
str_names are:
['AGATC', 'AATG', 'TATC']
people are:
[{'name': 'Alice', 'AGATC': 2, 'AATG': 8, 'TATC': 3}, {'name': 'Alice', 'AGATC': 2, 'AATG': 8, 'TATC': 3}, {'name': 'Alice', 'AGATC': 2, 'AATG': 8, 'TATC': 3}, {'name': 'Bob', 'AGATC': 4, 'AATG': 1, 'TATC': 5}, {'name': 'Bob', 'AGATC': 4, 'AATG': 1, 'TATC': 5}, {'name': 'Bob', 'AGATC': 4, 'AATG': 1, 'TATC': 5}, {'name': 'Charlie', 'AGATC': 3, 'AATG': 2, 'TATC': 5}, {'name': 'Charlie', 'AGATC': 3, 'AATG': 2, 'TATC': 5}, {'name': 'Charlie', 'AGATC': 3, 'AATG': 2, 'TATC': 5}]
```  

### 3. 读取 DNA 序列  
这个比较简单，是一个纯文本操作。  
```Python
with open("sequences/1.txt", "r") as file:
    sequence = file.read().strip()
    print("sequence example")
    print(sequence)
```    
可能有多行，需要拼接，`strip()` 去除首尾空白字符
同上，这里的文件名实际实现时也是从命令行参数获取。  
### 4. 计算最长连续重复 (最难的一步)  
这个不需要我们自己实现，CS50 官方提供了一个辅助函数 `longest_match`   
```Python
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    """
    返回子序列在序列中的最长连续重复次数
    
    参数：
        sequence: DNA 序列（长字符串）
        subsequence: STR（短字符串，如 "AGAT"）
    
    返回：
        最长连续重复次数（整数）
    """
    .... # 省略
```  
### 5. 在数据库中寻找匹配的人 `find_match(database, str_counts)`  
步骤 4 返回的是每个 STR 的最长连续重复次数，
```Python
str_counts = {}
for str_name in str_names:
    str_counts[str_name] = longest_match(sequence, str_name)
```  
现在需要查询数据库做匹配  
```Python
for person in people:
    match = True
    for str_name in str_names:
        if int(person[str_name]) != str_counts[str_name]:
            match = False
            break
    if match:
        print(person['name'])
print("No Match") # 全部查找后也没有匹配的
```   
## 完整的代码

### 基础版本（dna.py）

```python
import csv
import sys


def main():
    # 检查命令行参数
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # 读取 CSV 数据库
    database = []
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        str_names = reader.fieldnames[1:]  # 获取 STR 列表（跳过 name）
        for row in reader:
            database.append(row)

    # 读取 DNA 序列
    with open(sys.argv[2], 'r') as file:
        sequence = file.read().strip()

    # 计算每个 STR 的最长连续重复次数
    str_counts = {}
    for str_name in str_names:
        str_counts[str_name] = longest_match(sequence, str_name)

    # 在数据库中查找匹配（使用 all() 更 Pythonic）
    for person in database:
        if all(int(person[s]) == str_counts[s] for s in str_names):
            print(person['name'])
            return

    print("No match")
```

### 代码亮点

```python
# 使用 all() 简化多条件判断
# 原始写法：
for person in database:
    match = True
    for str_name in str_names:
        if int(person[str_name]) != str_counts[str_name]:
            match = False
            break
    if match:
        print(person['name'])

# Pythonic 写法：
for person in database:
    if all(int(person[s]) == str_counts[s] for s in str_names):
        print(person['name'])
```

> 💡 `all()` 函数：当所有条件都为 `True` 时返回 `True`，遇到 `False` 立即短路返回    
## 测试验证  
### 1. 基础测试   

```bash
# 测试 small 数据库  
$ python dna.py databases/small.csv sequences/1.txt
Bob

$ python dna.py databases/small.csv sequences/2.txt
No match

$ python dna.py databases/small.csv sequences/3.txt
No match

$ python dna.py databases/small.csv sequences/4.txt
Alice  
```

### 2. 验证逻辑

#### **手动验证 sequences/1.txt 匹配 Bob**
```
small.csv 中 Bob 的数据：
- AGATC: 4
- AATG: 1
- TATC: 5

在 sequences/1.txt 中查找：
1. 找到 "AGAT" 最长连续重复：
   AGATAGATAGATAGATAGAT... → 连续 4 次 ✓

2. 找到 "AATG" 最长连续重复：
   ...AATG... → 连续 1 次 ✓

3. 找到 "TATC" 最长连续重复：
   TATCTATCTATCTATCTATC... → 连续 5 次 ✓

结论：所有 STR 都匹配 → Bob  
```      
### 3. 大数据库测试   
```bash
# 测试 large 数据库（更多 STR，更多人）
$ python dna.py databases/large.csv sequences/5.txt
Lavender

$ python dna.py databases/large.csv sequences/10.txt
Albus

$ python dna.py databases/large.csv sequences/13.txt
No match
```

### 4. 完整测试用例表

| 命令 | 预期输出 |
|------|---------|
| `python dna.py databases/small.csv sequences/1.txt` | Bob |
| `python dna.py databases/small.csv sequences/2.txt` | No match |
| `python dna.py databases/small.csv sequences/3.txt` | No match |
| `python dna.py databases/small.csv sequences/4.txt` | Alice |
| `python dna.py databases/large.csv sequences/5.txt` | Lavender |
| `python dna.py databases/large.csv sequences/6.txt` | Luna |
| `python dna.py databases/large.csv sequences/7.txt` | Ron |
| `python dna.py databases/large.csv sequences/8.txt` | Ginny |
| `python dna.py databases/large.csv sequences/9.txt` | Draco |
| `python dna.py databases/large.csv sequences/10.txt` | Albus |
| `python dna.py databases/large.csv sequences/11.txt` | Hermione |
| `python dna.py databases/large.csv sequences/12.txt` | Lily |
| `python dna.py databases/large.csv sequences/13.txt` | No match |
| `python dna.py databases/large.csv sequences/14.txt` | Severus |
| `python dna.py databases/large.csv sequences/15.txt` | Sirius |
| `python dna.py databases/large.csv sequences/16.txt` | No match |
| `python dna.py databases/large.csv sequences/17.txt` | Harry |
| `python dna.py databases/large.csv sequences/18.txt` | No match |
| `python dna.py databases/large.csv sequences/19.txt` | Fred |
| `python dna.py databases/large.csv sequences/20.txt` | No match |

> 🎭 **彩蛋**：注意到了吗？large 数据库里的名字都是《哈利·波特》的角色！  
## 🎓 深入理解（Deep Understanding）

### 1. 为什么 STR 可以识别身份？
```
统计学原理：
- 每个 STR 在不同人之间的重复次数不同
- 多个 STR 组合在一起，唯一性更高

类比：
- 单个 STR：像身高（很多人可能相同）
- 多个 STR：像身高+体重+鞋码+指纹（唯一性高）

数学：
假设每个 STR 有 10 种可能的重复次数：
- 1 个 STR: 10 种组合
- 3 个 STR: 10³ = 1,000 种组合
- 8 个 STR: 10⁸ = 1 亿种组合

实际应用：
FBI 的 CODIS 系统使用 20 个 STR 位点
```

### 2. 真实 DNA 分析的区别

| 本题简化 | 真实情况 |
|---------|---------|
| DNA 序列只包含 A, C, G, T | DNA 测序可能有错误 |
| 完美匹配（没有突变） | 存在突变和变异 |
| 简单的 STR 重复 | STR 分析更复杂（考虑等位基因） |
| 直接比较 | 需要统计学方法判断匹配概率 |

### 3. 算法复杂度分析

```
longest_match(sequence, subsequence):
    外层循环：O(n)，n = len(sequence)
    内层循环：O(m)，m = 最大重复次数
    总时间：O(n * m)
```

**实际运行情况**：

| 参数 | 典型值 |
|------|-------|
| sequence 长度 | 10,000 - 100,000 字符 |
| 每个 STR 长度 | 4-8 字符 |
| 最大重复次数 | 通常 < 20 |
| small.csv 运行时间 | ~0.1 秒 |
| large.csv 运行时间 | ~0.5 秒 |

> 💡 **进阶优化**：可以使用 KMP 算法优化字符串匹配，将复杂度降为 O(n)。     
## 知识点总结  
### 1. Python 的核心概念  
* 文件的操作  
```Python
with open(filename, 'r') as file:
    content = file.read()  # 自动关闭文件
```  
* CSV 处理   
```Python
import csv
with open('data.csv', 'r') as file:
    reader = csv.DictReader(file)  # 字典形式读取
    for row in reader:
        print(row['name'])  # 按列名访问
```  
* 命令行参数   
```Python
import sys
if len(sys.argv) != 3:
    sys.exit("Usage: ...")
database_file = sys.argv[1]
sequence_file = sys.argv[2]
```   
* 字符串切片   
```Python
s = "AGATAGAT"
s[0:4]  # "AGAT"
s[4:8]  # "AGAT"
s[i:i+length]  # 从 i 开始，长度为 length 的子串
```  
* 字典操作   
```Python
# 创建
d = {'name': 'Alice', 'AGATC': 5}

# 访问
d['name']  # 'Alice'

# 遍历键
for key in d.keys():
    print(key, d[key])
```   
### 算法思想   
* 滑动窗口   
```Python
# 在序列中查找模式
for i in range(len(sequence)):
    window = sequence[i:i+pattern_length]
    if window == pattern:
        # 找到匹配
```  
* 贪心算法   
```Python
# 找最长连续重复：一旦找到匹配，尽可能多地计数
while sequence[pos:pos+len] == pattern:
    count += 1
    pos += len
```   
* 线性搜索   
```Python
# 在数据库中查找匹配
for person in database:
    if matches(person, target):
        return person
return None
```

# 代码对比总结

## C vs Python 代码量

| 问题 | C 行数 | Python 行数 | 减少比例 |
|------|--------|-------------|----------|
| Hello | 7 | 2 | 71% |
| Mario (Less) | 25 | 8 | 68% |
| Mario (More) | 35 | 10 | 71% |
| Cash | 30 | 12 | 60% |
| Credit | 80 | 30 | 63% |
| Readability | 90 | 20 | 78% |
| DNA | N/A | 45 | 纯 Python |

## 关键语法对比速查表

| 功能 | C 语言 | Python |
|------|--------|--------|
| 输入验证 | `do-while` 循环 | `while True` + `break` |
| 整数除法 | `/` | `//` |
| 字符串长度 | 循环计数 | `len(s)` |
| 字符串切片 | 复杂索引 | `s[start:end]` |
| 成员判断 | 多个 `\|\|` | `x in [a, b, c]` |
| 反向遍历 | 复杂索引 | `reversed(s)` |
| 带索引遍历 | 手动计数 | `enumerate(s)` |

---

# 测试与提交

## 测试命令

```bash
# Mario (Less)
check50 cs50/problems/2025/x/sentimental/mario/less

# Mario (More)
check50 cs50/problems/2025/x/sentimental/mario/more

# Cash
check50 cs50/problems/2025/x/sentimental/cash

# Credit
check50 cs50/problems/2025/x/sentimental/credit

# Readability
check50 cs50/problems/2025/x/sentimental/readability

# DNA
check50 cs50/problems/2025/x/dna
```

## 代码风格检查

```bash
style50 mario.py
style50 cash.py
style50 credit.py
style50 readability.py
style50 dna.py
```

---

# 学习心得

通过用 Python 重写之前的 C 程序，我深刻体会到：

1. **Python 更简洁**：字符串操作、列表操作让代码量大幅减少
2. **Python 更易读**：`in`、`enumerate`、`reversed` 等语法更接近自然语言
3. **Python 更安全**：自动内存管理，不用担心内存泄漏
4. **C 更底层**：理解 C 的实现有助于理解 Python 背后的原理

> 💡 **David Malan 的建议**：先用 C 学习底层原理，再用 Python 提高开发效率。这正是 CS50 课程设计的精髓！

---

**参考资料**：
- [CS50 Problem Set 6](https://cs50.harvard.edu/x/psets/6/)
- [DNA 题目详情](https://cs50.harvard.edu/x/psets/6/dna/)
- [Python 官方文档](https://docs.python.org/3/)
- [Python csv 模块](https://docs.python.org/3/library/csv.html)
- [Python 字符串方法](https://docs.python.org/3/library/stdtypes.html#string-methods)

---

# Week 6 完成！🎉

恭喜你完成了 CS50 Problem Set 6！通过这周的学习，你已经：

1. ✅ 掌握了 Python 基础语法
2. ✅ 学会了文件读写和 CSV 处理
3. ✅ 理解了命令行参数的使用
4. ✅ 体会了 Python 相比 C 的简洁优势
5. ✅ 完成了一个真实的 DNA 身份识别程序

下周我们将进入 **SQL 数据库**的世界，敬请期待！🚀

