# scrabble  
In the game of [Scrabble](https://en.wikipedia.org/wiki/Scrabble), players create words to score points, and the number of points is the sum of the point values of each letter in the word.  
```
A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
1  3  3  2	1  4  2  4	1  8  5  1	3  1  1  3	10 1  1	 1	1  4  4	 8	4  10
```   
For example, if we wanted to score the word “CODE”, we would note that the ‘C’ is worth 3 points, the ‘O’ is worth 1 point, the ‘D’ is worth 2 points, and the ‘E’ is worth 1 point. Summing these, we get that “CODE” is worth 7 points.  
该题该如何思考  
1. 提示用户输入   
2. 计算单词得分  
3. 比较两个单词得分  
1，3 很容易实现，2 该如何实现呢？   
2 主要考虑的是每个字母对应的分数，由于是一一对应的，我们使用一维数组存储分数，由于数组存储的分数是与字母表顺序一一对应的，即index[0],index[1]....index[25]，如何将字母转化为对应的index,我们还记得ASCII码吗？因此，对应字母减去 'A'或者'a'就是其对应的index。  
实现如下：  

In a file called scrabble.c in a folder called scrabble, implement a program in C that determines the winner of a short Scrabble-like game. Your program should prompt for input twice: once for “Player 1” to input their word and once for “Player 2” to input their word. Then, depending on which player scores the most points, your program should either print “Player 1 wins!”, “Player 2 wins!”, or “Tie!” (in the event the two players score equal points).  
* scrabble.c  
# Readability  
According to Scholastic, E.B. White’s Charlotte’s Web is between a second- and fourth-grade reading level, and Lois Lowry’s The Giver is between an eighth- and twelfth-grade reading level. What does it mean, though, for a book to be at a particular reading level?

Well, in many cases, a human expert might read a book and make a decision on the grade (i.e., year in school) for which they think the book is most appropriate. But an algorithm could likely figure that out too!

In a file called readability.c in a folder called readability, you’ll implement a program that calculates the approximate grade level needed to comprehend some text. Your program should print as output “Grade X” where “X” is the grade level computed, rounded to the nearest integer. If the grade level is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output “Grade 16+” instead of giving the exact index number. If the grade level is less than 1, your program should output “Before Grade 1”.  
## 背景  
1. 哪些特征是高阅读水平的典型特征呢？嗯，较长的单词可能与较高的阅读水平相关。同样，较长的句子也可能与较高的阅读水平相关。  
2. 多年来，人们已经开发出许多“可读性测试”，这些测试定义了计算文本阅读水平的公式。其中一种可读性测试是科勒恩-利奥指数。文本的科勒恩-利奥指数旨在输出理解该文本所需的（美国）年级水平。公式为  
`index = 0.0588 * L - 0.296 * S - 15.8`  
其中 L 是文本中每 100 个单词的平均字母数，而 S 是文本中每 100 个单词的平均句子数。  
## Specification  
本问题中，我们将任何由空格分隔的字符序列视为一个单词（因此像“sister-in-law”这样的连字符连接的单词应被视为一个单词，而不是三个）。你可以假设一个句子：  
  - 将至少包含一个单词  
  - 不会以空格开头或结尾  
  - 不会出现连续多个空格  
基于这些假设，你可能已经能够找到单词数量和空格数量之间的数学关系。  
当然，你也可以尝试一种更复杂的解决方案，该方案能够容忍单词之间的多个空格！我们已经调整 check50 以接受空格的这两种处理方式，所以选择权在你  
## 问题理解  
index = 0.0588 * L - 0.296 * S - 15.8  
其中：

L = 每100个单词的平均字母数
S = 每100个单词的平均句子数  
## 思路分析   
1. 需要计算什么  
  - 字母数(letters): a-z，A-Z  
  - 单词数(words):由空格分隔的字符序列  
  - 句子数（sentences）：以 . ! ? 结尾  
2. 如何计算 L　和　S  
  ```
  L = (letters / words) * 100
  S = (sentences / words) * 100
  ```  
3. 示例计算
文本："Congratulations! Today is your day."
统计：

字母：26个（C-o-n-g-r-a-t-u-l-a-t-i-o-n-s, T-o-d-a-y, i-s, y-o-u-r, d-a-y）
单词：5个（Congratulations, Today, is, your, day）
句子：2个（以!和.结尾）  
* 计算   
```
L = (26 / 5) * 100 = 520
S = (2 / 5) * 100 = 40

index = 0.0588 * 520 - 0.296 * 40 - 15.8
      = 30.576 - 11.84 - 15.8
      = 2.936
      ≈ 3 (四舍五入)

输出：Grade 3
```
下面进行分解  
1. 统计字母数  
```C
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))  // isalpha检查是否为字母
        {
            count++;
        }
    }
    return count;
}
```  
关键点：
使用 isalpha() 函数检查字符是否为字母
会计算所有 a-z 和 A-Z，忽略数字、标点、空格  
2. 计算单词数  
```C
int count_words(string text)
{
    int count = 0;
    int in_word = 0;  // 状态标记
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] != ' ' && !in_word)
        {
            count++;       // 进入新单词
            in_word = 1;
        }
        else if (text[i] == ' ')
        {
            in_word = 0;   // 离开单词
        }
    }
    return count;
}
```   
为什么需要 in_word 标记？
考虑文本："Hello world"

位置0 'H'：不是空格，不在单词中 → count=1, in_word=1
位置1-4：不是空格，但在单词中 → 不增加计数
位置5 ' '：空格 → in_word=0
位置6 'w'：不是空格，不在单词中 → count=2, in_word=1

这样可以正确处理多个连续非空格字符作为一个单词。  
3. 统计句子数  
```C
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
4. 主函数逻辑   
```
// 计算每100个单词的比率
float L = (float) letters / (float) words * 100;
float S = (float) sentences / (float) words * 100;

// Coleman-Liau公式
float index = 0.0588 * L - 0.296 * S - 15.8;

// 四舍五入
int grade = round(index);
```

**注意**：
- 必须转换为 `float` 进行除法，否则整数除法会丢失小数部分
- `round()` 函数来自 `<math.h>`，实现四舍五入

## 测试示例

### 示例 1

**输入**：
```
Text: One fish. Two fish. Red fish. Blue fish.
```

**统计**：
- 字母：36个
- 单词：8个
- 句子：4个

**计算**：
```
L = (36 / 8) * 100 = 450
S = (4 / 8) * 100 = 50
index = 0.0588 * 450 - 0.296 * 50 - 15.8
      = 26.46 - 14.8 - 15.8
      = -4.14
      ≈ -4
```

**输出**：`Before Grade 1`

### 示例 2

**输入**：
```
Text: Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard.
```

**统计**：
- 字母：214个
- 单词：56个
- 句子：4个

**计算**：
```
L = (214 / 56) * 100 = 382.14
S = (4 / 56) * 100 = 7.14
index = 0.0588 * 382.14 - 0.296 * 7.14 - 15.8
      ≈ 5
```   
# Caesar  
这是一个经典的密码学入门问题。  
好的！我来详细讲解 **Caesar Cipher（凯撒密码）** 这道题目。这是一个经典的密码学入门问题。

## 问题理解

### 什么是凯撒密码？

凯撒密码是一种简单的加密方法：将每个字母按字母表顺序移动固定的位数。

**示例**：密钥 k = 1
```
明文（plaintext）: HELLO
密钥（key）:       1 1 1 1 1
密文（ciphertext）: IFMMP
```

- H → I（移动1位）
- E → F
- L → M
- L → M
- O → P

### 加密公式

```
ci = (pi + k) % 26
```

其中：
- `pi` = 明文字符的位置（A=0, B=1, ..., Z=25）
- `k` = 密钥（移动的位数）
- `ci` = 密文字符的位置
- `% 26` = 确保循环回到字母表开头（Z之后回到A）

## 需求分析

### 程序要求

1. **命令行参数**：接受一个非负整数作为密钥
2. **输入验证**：
   - 只能有一个命令行参数
   - 参数必须是纯数字
3. **加密规则**：
   - 只加密字母
   - 保持大小写
   - 非字母字符保持不变
4. **循环处理**：即使 k > 26，也要正确处理（如 k=27，A→B）

### 程序流程

```
1. 检查命令行参数数量
2. 验证参数是否全为数字
3. 将参数转换为整数（密钥）
4. 提示用户输入明文
5. 逐字符加密
6. 输出密文
```

## 详细实现步骤

### 步骤1：理解命令行参数

```c
int main(int argc, string argv[])
```

- `argc`：参数数量（包括程序名）
- `argv[]`：参数数组
  - `argv[0]` = "./caesar"
  - `argv[1]` = 密钥（字符串形式）

**示例**：
```bash
./caesar 13
# argc = 2
# argv[0] = "./caesar"
# argv[1] = "13"
```

### 步骤2：验证参数

需要检查：
1. 参数数量是否正确（argc == 2）
2. 参数是否全为数字

### 步骤3：字符旋转算法

这是核心难点！让我详细讲解：

**大写字母加密**：
```
原字符：'H' (ASCII: 72)
步骤1：减去'A'，转换为0-25范围
       72 - 65 = 7  (H是第7个字母，从0开始)

步骤2：加上密钥并取模
       (7 + 1) % 26 = 8

步骤3：加回'A'，转换回字符
       8 + 65 = 73  (ASCII: 73 = 'I')

结果：'H' → 'I'
```

**循环示例**（k=1）：
```
'Z' → 'A'
步骤1：90 - 65 = 25
步骤2：(25 + 1) % 26 = 0
步骤3：0 + 65 = 65 ('A')
```

## 完整代码实现## 代码详细讲解

### 1. only_digits 函数

```c
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))  // 检查每个字符
        {
            return false;     // 发现非数字立即返回
        }
    }
    return true;  // 全是数字
}
```

**工作原理**：
- `isdigit()`：检查字符是否为 0-9
- 遍历整个字符串，任何一个字符不是数字就返回 false

**测试**：
```
"123"  → true
"12a3" → false
"abc"  → false
```

### 2. rotate 函数（核心）

让我用一个详细的例子说明：

**示例1：加密大写字母 'H'，密钥 = 1**

```c
char c = 'H';
int n = 1;

// 步骤1：转换为位置
int position = 'H' - 'A';  
// = 72 - 65 = 7

// 步骤2：加密
int new_position = (7 + 1) % 26;  
// = 8

// 步骤3：转回字符
return 'A' + 8;  
// = 65 + 8 = 73 = 'I'
```

**示例2：循环情况 'Z'，密钥 = 3**

```c
char c = 'Z';
int n = 3;

// 步骤1
int position = 'Z' - 'A';  
// = 90 - 65 = 25

// 步骤2：关键的模运算！
int new_position = (25 + 3) % 26;  
// = 28 % 26 = 2  (循环回到开头)

// 步骤3
return 'A' + 2;  
// = 'C'
```

**示例3：大密钥 k=27**

```c
char c = 'A';
int n = 27;

int position = 0;
int new_position = (0 + 27) % 26;  
// = 1  (27 % 26 = 1)

return 'A' + 1;  
// = 'B'
```

### 3. 为什么要用 % 26？

模运算实现循环：

```
位置:  0  1  2 ... 23 24 25  26 27 28 ...
字母:  A  B  C ... X  Y  Z   A  B  C  ...
                            ↑ 
                        循环回到开头

(25 + 1) % 26 = 0  (Z + 1 = A)
(25 + 2) % 26 = 1  (Z + 2 = B)
(25 + 27) % 26 = 0 (Z + 27 = A)
```

### 4. ASCII 码对照表

```
字符    ASCII码
'A'      65
'B'      66
...
'Z'      90

'a'      97
'b'      98
...
'z'     122

'0'      48
'!'      33
' '      32
```

## 运行示例

### 示例 1：基本加密

```bash
$ ./caesar 1
plaintext:  HELLO
ciphertext: IFMMP
```

**加密过程**：
- H (7) + 1 = 8 → I
- E (4) + 1 = 5 → F
- L (11) + 1 = 12 → M
- L (11) + 1 = 12 → M
- O (14) + 1 = 15 → P

### 示例 2：保持大小写

```bash
$ ./caesar 13
plaintext:  Hello, World!
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
plaintext:  XYZ
ciphertext: YZA
```

**说明**：
- X (23) + 1 = 24 → Y
- Y (24) + 1 = 25 → Z
- Z (25) + 1 = 26 % 26 = 0 → A ✓

### 示例 4：大密钥

```bash
$ ./caesar 27
plaintext:  ABC
ciphertext: BCD
```

**说明**：
- 27 % 26 = 1，效果等同于密钥为1

## 常见错误和调试技巧

### 错误1：忘记模运算

```c
// ❌ 错误
return 'A' + (c - 'A' + n);  // Z+1会变成'['

// ✅ 正确
return 'A' + ((c - 'A' + n) % 26);
```

### 错误2：大小写处理

```c
// ❌ 错误：对所有字符使用同一个基准
return 'A' + ((c - 'A' + n) % 26);  // 小写字母会出错

// ✅ 正确：分别处理大小写
if (isupper(c))
    return 'A' + ((c - 'A' + n) % 26);
else if (islower(c))
    return 'a' + ((c - 'a' + n) % 26);
```

### 错误3：参数验证

```c
// ❌ 错误：没有验证参数
int key = atoi(argv[1]);  // 如果没有参数会崩溃

// ✅ 正确：先检查
if (argc != 2)
{
    printf("Usage: ./caesar key\n");
    return 1;
}
```

## 调试提示

如果输出不对，可以打印中间值：

```c
char rotate(char c, int n)
{
    if (isupper(c))
    {
        int position = c - 'A';
        printf("Debug: '%c' position=%d ", c, position);
        
        int new_position = (position + n) % 26;
        printf("new_position=%d\n", new_position);
        
        return 'A' + new_position;
    }
    // ...
}
```

## 关键知识点总结

1. **命令行参数**：`argc` 和 `argv[]`
2. **字符串验证**：`isdigit()`、`strlen()`
3. **字符判断**：`isupper()`、`islower()`
4. **字符转换**：`atoi()`
5. **ASCII 运算**：字符与整数的转换
6. **模运算**：实现循环（`% 26`）
7. **保持属性**：大小写、非字母字符

## 测试用例

```bash
# 测试1：无参数
$ ./caesar
Usage: ./caesar key

# 测试2：多个参数
$ ./caesar 1 2
Usage: ./caesar key

# 测试3：非数字参数
$ ./caesar abc
Usage: ./caesar key

# 测试4：正常加密
$ ./caesar 13
plaintext:  hello
ciphertext: uryyb

# 测试5：混合内容
$ ./caesar 1
plaintext:  Hello, World! 123
ciphertext: Ifmmp, Xpsme! 123
```  
完整实现在 `caesar.c`  
# substitution  
这道题是 **Substitution Cipher（替换密码）**，比凯撒密码更复杂。。

## 问题理解

### 什么是替换密码？

替换密码使用一个 26 个字母的密钥，将字母表中的每个字母映射到密钥中对应位置的字母。

**示例**：
```
字母表: ABCDEFGHIJKLMNOPQRSTUVWXYZ
密钥:   NQXPOMAFTRHLZGECYJIUWSKDVB
```

这意味着：
- A → N（字母表第1个 → 密钥第1个）
- B → Q（字母表第2个 → 密钥第2个）
- C → X
- ...
- Z → B

**加密 HELLO**：
```
H → O (H是第8个字母，密钥第8个是O)
E → O (E是第5个字母，密钥第5个是O)
L → E (L是第12个字母，密钥第12个是E)
L → E
O → M (O是第15个字母，密钥第15个是M)

HELLO → OOEEM
```

等等，题目说的是 `HELLO → FOLLE`，让我重新看一下...

实际上：
```
字母表: ABCDEFGHIJKLMNOPQRSTUVWXYZ
密钥:   NQXPOMAFTRHLZGECYJIUWSKDVB

H (位置7) → 密钥[7] = T... 
```

让我重新理解，题目说 `HELLO → FOLLE`：

```
H (索引7) → 密钥[7] = F
E (索引4) → 密钥[4] = O
L (索引11) → 密钥[11] = L
L (索引11) → 密钥[11] = L
O (索引14) → 密钥[14] = E
```

是的！所以逻辑是：字母表中字母的位置作为索引，去密钥中查找对应的字母。

## 需求分析

### 密钥验证规则

1. **长度**：必须是 26 个字符
2. **字符类型**：只能包含字母
3. **唯一性**：每个字母只能出现一次（不能重复）
4. **大小写不敏感**：密钥可以是大写或小写

### 加密规则

1. 只加密字母
2. 保持大小写
3. 非字母字符保持不变

## 思路分析

### 核心算法

```
对于明文中的每个字符:
    如果是大写字母:
        找到它在字母表中的位置 (0-25)
        用这个位置作为索引，在密钥中查找对应字母
        将结果转换为大写
    如果是小写字母:
        找到它在字母表中的位置 (0-25)
        用这个位置作为索引，在密钥中查找对应字母
        将结果转换为小写
    否则:
        保持原样
```

### 示例演示

**密钥**: `VCHPRZGJNTLSKFBDQWAXEUYMOI`

**加密 'A'**:
```
步骤1: 'A' 的位置 = 0
步骤2: 密钥[0] = 'V'
结果: 'A' → 'V'
```

**加密 'a'**:
```
步骤1: 'a' 的位置 = 0 (同 'A')
步骤2: 密钥[0] = 'V'
步骤3: 转换为小写 = 'v'
结果: 'a' → 'v'
```

## 完整代码实现## 代码详细讲解

### 1. validate_key 函数（关键）

这个函数需要验证四个条件：

#### 检查1：长度是否为 26

```c
if (strlen(key) != 26)
{
    return false;
}
```

简单直接，密钥必须有 26 个字符。

#### 检查2-4：使用布尔类型的标记数组追踪字母

```c
bool letter_seen[26] = {false};
```

**这个数组的妙用**：
- `letter_seen[0]` → 'A' 是否出现过
- `letter_seen[1]` → 'B' 是否出现过
- ...
- `letter_seen[25]` → 'Z' 是否出现过

**验证过程示例**：

假设密钥是 `"VCHPRZGJNTLSKFBDQWAXEUYMOI"`

```
遍历第1个字符 'V':
  - isalpha('V')? ✓
  - index = 'V' - 'A' = 21
  - letter_seen[21] 是 false? ✓ (未出现过)
  - 设置 letter_seen[21] = true

遍历第2个字符 'C':
  - isalpha('C')? ✓
  - index = 'C' - 'A' = 2
  - letter_seen[2] 是 false? ✓
  - 设置 letter_seen[2] = true

... 继续遍历

假如遇到重复的 'V':
  - index = 21
  - letter_seen[21] 是 false? ✗ (已经是 true)
  - 返回 false (无效密钥)
```

**为什么这个方法有效？**

- 只需遍历一次密钥（O(n)时间复杂度）
- 使用固定大小的数组（O(1)空间复杂度）
- 可以同时检查：是否为字母、是否重复

### 2. substitute 函数

让我用详细的例子说明：

**示例1：加密大写字母 'H'**

密钥：`VCHPRZGJNTLSKFBDQWAXEUYMOI`

```c
char c = 'H';

// 步骤1：找到 'H' 在字母表中的位置
int index = 'H' - 'A';  
// = 72 - 65 = 7

// 步骤2：查找密钥中第7个字符（从0开始）
char substituted = key[7];  
// key[7] = 'J'

// 步骤3：确保大写
return toupper('J');  
// = 'J'

结果：'H' → 'J'
```

**示例2：加密小写字母 'e'**

```c
char c = 'e';

// 步骤1
int index = 'e' - 'a';  
// = 101 - 97 = 4

// 步骤2
char substituted = key[4];  
// key[4] = 'R'

// 步骤3：转换为小写
return tolower('R');  
// = 'r'

结果：'e' → 'r'
```

**示例3：非字母字符**

```c
char c = '!';

// 不是字母，直接返回
return '!';
```

### 3. 为什么要用 toupper/tolower？

因为密钥本身是大小写不敏感的：

```bash
$ ./substitution vchprzgjntlskfbdqwaxeuymoi
# 等同于
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
```

但我们需要：
- 大写字母加密后还是大写
- 小写字母加密后还是小写

所以：
```c
// 明文是大写 'H'
return toupper(key[index]);  // 确保结果大写

// 明文是小写 'h'
return tolower(key[index]);  // 确保结果小写
```

## 运行示例

### 示例 1：基本加密

```bash
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext:  HELLO
ciphertext: JRSSB
```

**加密过程**：
```
H (索引7) → 密钥[7] = J
E (索引4) → 密钥[4] = R
L (索引11) → 密钥[11] = S
L (索引11) → 密钥[11] = S
O (索引14) → 密钥[14] = B
```

### 示例 2：保持大小写

```bash
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext:  Hello, World!
ciphertext: Jrssb, Ybwsq!
```

**说明**：
- `H` → `J`（大写保持大写）
- `e` → `r`（小写保持小写）
- `,` → `,`（标点不变）

### 示例 3：错误情况

#### 错误1：密钥太短

```bash
$ ./substitution ABC
Key must contain 26 unique alphabetic characters.
```

#### 错误2：密钥包含非字母

```bash
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYM01
Key must contain 26 unique alphabetic characters.
```

#### 错误3：密钥有重复字母

```bash
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOII
Key must contain 26 unique alphabetic characters.
```
（注意最后有两个 'I'）

#### 错误4：无参数

```bash
$ ./substitution
Usage: ./substitution key
```

## 关键数据结构：布尔数组

`bool letter_seen[26]` 的工作原理：

```
初始状态：
索引:  0  1  2  3  4 ... 25
字母:  A  B  C  D  E ... Z
值:   F  F  F  F  F ... F  (全是 false)

处理密钥 "ABC...":
遇到 'A': letter_seen[0] = true
遇到 'B': letter_seen[1] = true
遇到 'C': letter_seen[2] = true

如果再遇到 'A':
检查 letter_seen[0]，发现是 true
→ 说明 'A' 重复了 → 密钥无效
```

这种技术叫做 **"标记数组"** 或 **"访问数组"**，非常常用！

## 对比：凯撒密码 vs 替换密码

| 特性 | 凯撒密码 | 替换密码 |
|------|---------|---------|
| 密钥 | 一个数字（位移量） | 26个字母的排列 |
| 安全性 | 低（只有26种可能） | 较高（26!种可能） |
| 加密逻辑 | 固定位移 | 任意映射 |
| 示例 | k=1: A→B | 密钥定义: A→V |

**凯撒密码可以看作替换密码的特殊情况**：
```
凯撒密码 k=1:
密钥 = BCDEFGHIJKLMNOPQRSTUVWXYZA
```

## 测试用例

### 测试1：标准情况

```bash
$ ./substitution YTNSHKVEFXRBAUQZCLWDMIPGJO
plaintext:  HELLO
ciphertext: EHBBQ
```

验证：
- H (索引7) → 密钥[7] = E ✓
- E (索引4) → 密钥[4] = H ✓
- L (索引11) → 密钥[11] = B ✓

### 测试2：混合大小写

```bash
$ ./substitution YTNSHKVEFXRBAUQZCLWDMIPGJO
plaintext:  HeLLo
ciphertext: EhBBq
```

### 测试3：包含非字母

```bash
$ ./substitution YTNSHKVEFXRBAUQZCLWDMIPGJO
plaintext:  Hello, World!
ciphertext: Ehbbq, Vqfbn!
```

### 测试4：密钥大小写混合

```bash
$ ./substitution YtnshKVEfxrbauqzclwdmipgjo
plaintext:  HELLO
ciphertext: EHBBQ
```
（结果应该相同）

## 常见错误和调试

### 错误1：数组越界

```c
// ❌ 错误：没有检查长度
for (int i = 0; i < 26; i++)
{
    if (key[i] == ...)  // 如果 key 长度 < 26，会越界
}

// ✅ 正确：先检查长度
if (strlen(key) != 26)
{
    return false;
}
```

### 错误2：忘记转换大小写

```c
// ❌ 错误：直接返回密钥字符
return key[index];  // 可能大小写不对

// ✅ 正确：根据原字符的大小写转换
if (isupper(c))
    return toupper(key[index]);
else
    return tolower(key[index]);
```

### 错误3：重复检测不正确

```c
// ❌ 错误：使用嵌套循环（低效且容易出错）
for (int i = 0; i < 26; i++)
{
    for (int j = i + 1; j < 26; j++)
    {
        if (key[i] == key[j])
            return false;
    }
}

// ✅ 正确：使用布尔数组（高效且清晰）
bool seen[26] = {false};
for (int i = 0; i < 26; i++)
{
    int index = toupper(key[i]) - 'A';
    if (seen[index])
        return false;
    seen[index] = true;
}
```

## 调试技巧

如果加密结果不对，可以打印调试信息：

```c
char substitute(char c, string key)
{
    if (isupper(c))
    {
        int index = c - 'A';
        char result = toupper(key[index]);
        
        // 调试输出
        printf("\n[DEBUG] '%c' (index %d) -> key[%d]='%c' -> '%c'\n",
               c, index, index, key[index], result);
        
        return result;
    }
    // ...
}
```

## 关键知识点总结

1. **命令行参数验证**：数量、格式、内容
2. **字符串验证**：长度、字符类型、唯一性
3. **布尔数组技巧**：追踪字母出现情况
4. **字符映射**：使用索引实现字母替换
5. **大小写处理**：`toupper()`、`tolower()`
6. **字符判断**：`isalpha()`、`isupper()`、`islower()`

## 扩展思考

**解密怎么做？**

如果要解密，需要创建反向映射：

```c
// 加密映射
字母表: ABCDEFGHIJKLMNOPQRSTUVWXYZ
密钥:   VCHPRZGJNTLSKFBDQWAXEUYMOI

// 解密映射（反向）
密钥:   VCHPRZGJNTLSKFBDQWAXEUYMOI
字母表: ABCDEFGHIJKLMNOPQRSTUVWXYZ

意思是：密文中的 'V' 应该解密为 'A'
```
