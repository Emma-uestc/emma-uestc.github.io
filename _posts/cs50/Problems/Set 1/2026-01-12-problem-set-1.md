---
layout: post
title: "CS50 Problem Set 1: C语言编程实战"
date: 2026-01-12
categories: [CS50, Programming, Practice]
tags: [C, 算法, 问题解决]
---

# CS50 Problem Set 1 解题思路与实现

在完成 Week 1 的 C 语言基础学习后，是时候通过实际编程来巩固所学知识了。Problem Set 1 包含四个编程题，难度逐步递增，涵盖了循环、条件判断、算法设计等核心概念。

**官方链接**：[CS50 Problem Set 1](https://cs50.harvard.edu/x/psets/1/)

---

# 问题1：Mario（简单版）

## 问题描述

还记得超级马里奥游戏中的阶梯吗？我们要用 `#` 字符在终端中画出一个右对齐的金字塔。

**要求**：
- 提示用户输入金字塔的高度（1-8之间）
- 使用 `#` 字符绘制右对齐的金字塔

**示例**（高度为4）：
```
   #
  ##
 ###
####
```

**示例**（高度为8）：
```
       #
      ##
     ###
    ####
   #####
  ######
 #######
########
```

## 解题思路

这个问题的关键在于理解**行数、空格数、井号数**之间的关系：

| 行号(i) | 空格数 | 井号数 |
|---------|--------|--------|
| 0       | 7      | 1      |
| 1       | 6      | 2      |
| 2       | 5      | 3      |
| 3       | 4      | 4      |
| ...     | ...    | ...    |
| i       | height - i - 1 | i + 1 |

**规律**：
- **空格数** = `height - i - 1`（随行数增加而减少）
- **井号数** = `i + 1`（随行数增加而增加）

## 代码实现

```c
/*
 * mario.c (Less Comfortable)
 * 
 * 打印右对齐的金字塔
 */
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    
    // 使用 do-while 确保输入在 1-8 之间
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // 打印金字塔
    for (int i = 0; i < height; i++)
    {
        // 第一步：打印前导空格（右对齐）
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        
        // 第二步：打印井号
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        
        // 第三步：换行
        printf("\n");
    }
    
    return 0;
}
```

## 知识点回顾

1. **`do-while` 循环**：先执行一次，再检查条件，适合输入验证
2. **嵌套循环**：外层控制行数，内层控制每行的字符
3. **找规律**：观察输出，总结数学关系

---

# 问题2：Mario（挑战版）

## 问题描述

这次我们要画一个**双侧金字塔**，就像马里奥游戏中的两座相邻的阶梯，中间有2个空格的间隙。

**示例**（高度为4）：
```
   #  #
  ##  ##
 ###  ###
####  ####
```

**示例**（高度为8）：
```
       #  #
      ##  ##
     ###  ###
    ####  ####
   #####  #####
  ######  ######
 #######  #######
########  ########
```

## 解题思路

这个问题是简单版的扩展：

1. **左侧金字塔**：和简单版完全一样（空格 + 井号）
2. **中间间隙**：固定打印2个空格
3. **右侧金字塔**：打印与左侧相同数量的井号

**每行结构**：`[空格] + [左侧#] + [2个空格] + [右侧#]`

## 代码实现

```c
/*
 * mario.c (More Comfortable)
 * 
 * 打印双侧金字塔
 */
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    
    // 确保输入在 1-8 之间
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // 打印双侧金字塔
    for (int i = 0; i < height; i++)
    {
        // 第一步：打印前导空格（右对齐左侧金字塔）
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        
        // 第二步：打印左侧金字塔
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        
        // 第三步：打印中间间隙（固定2个空格）
        printf("  ");
        
        // 第四步：打印右侧金字塔
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        
        // 第五步：换行
        printf("\n");
    }
    
    return 0;
}
```

## 编程技巧

- **模块化思维**：把复杂问题拆解成小步骤（空格、左侧、间隙、右侧、换行）
- **代码复用**：右侧金字塔的循环和左侧完全一样

---

# 问题3：Cash（零钱找零）

## 问题描述

你在商店工作，需要给顾客找零。为了减少找零的硬币数量，你需要使用**贪心算法**。

**美国硬币面值**：
- 25美分（Quarter）
- 10美分（Dime）
- 5美分（Nickel）
- 1美分（Penny）

**要求**：给定找零金额（单位：美分），计算最少需要多少枚硬币。

**示例**：
```
Change owed: 41
4
```

**解释**：41美分 = 1个25美分 + 1个10美分 + 1个5美分 + 1个1美分 = 4枚硬币

## 解题思路：贪心算法（Greedy Algorithm）

**贪心策略**：每次都选择**面值最大**且不超过剩余金额的硬币。

**算法步骤**：
1. 从最大面值（25美分）开始
2. 尽可能多地使用该面值：`硬币数 += 金额 / 面值`
3. 更新剩余金额：`金额 %= 面值`
4. 重复步骤2-3，直到面值为1美分

**为什么贪心算法在这里有效？**

因为美国硬币的面值设计（1, 5, 10, 25）具有特殊性质：每个面值都能被更大的面值整除或有合理的倍数关系。但注意，贪心算法并不总是适用于所有硬币系统！

## 代码实现

```c
/*
 * cash.c
 * 
 * 使用贪心算法计算最少硬币数
 */
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int cents;
    
    // 确保输入是正整数
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    
    int coins = 0; // 硬币总数
    
    // 25美分硬币（Quarter）
    coins += cents / 25;
    cents %= 25;
    
    // 10美分硬币（Dime）
    coins += cents / 10;
    cents %= 10;
    
    // 5美分硬币（Nickel）
    coins += cents / 5;
    cents %= 5;
    
    // 1美分硬币（Penny） - 剩余全部
    coins += cents;
    
    printf("%i\n", coins);
    
    return 0;
}
```

## 运算符回顾

- **`/`（整数除法）**：`41 / 25 = 1`（取商）
- **`%`（取模运算）**：`41 % 25 = 16`（取余数）
- **`+=`（复合赋值）**：`coins += 1` 等同于 `coins = coins + 1`

## 测试用例

| 输入 | 计算过程 | 输出 |
|------|----------|------|
| 25   | 25÷25=1  | 1    |
| 41   | 1×25 + 1×10 + 1×5 + 1×1 | 4 |
| 70   | 2×25 + 2×10 | 4 |
| 99   | 3×25 + 2×10 + 4×1 | 9 |

---

# 问题4：Credit（信用卡验证）

## 问题描述

验证信用卡号是否有效，并识别卡片类型。这个问题需要用到**Luhn算法**（也叫"模10算法"）。

**卡片规则**：
- **AMEX（美国运通）**：15位，以34或37开头
- **MASTERCARD（万事达）**：16位，以51-55开头
- **VISA（维萨）**：13位或16位，以4开头

**示例**：
```
Number: 4003600000000014
VISA

Number: 378282246310005
AMEX

Number: 1234567890
INVALID
```

## Luhn算法详解

**算法步骤**：

1. **从右往左**，对倒数第2位、第4位、第6位...（偶数位置）的数字**乘以2**
2. 如果乘积是两位数（≥10），将两位数字分别相加（例如：`7×2=14 → 1+4=5`）
3. 将所有未乘2的数字（奇数位置）相加
4. 将步骤2和步骤3的和加起来
5. 如果总和能被10整除，卡号有效

**示例**：验证卡号 `4003600000000014`

```
卡号：  4  0  0  3  6  0  0  0  0  0  0  0  0  0  1  4
位置： 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1
       ↑     ↑     ↑     ↑     ↑     ↑     ↑     ↑
      偶数位（从右往左）

步骤1：偶数位乘2
  1×2=2, 0×2=0, 0×2=0, 0×2=0, 0×2=0, 6×2=12→(1+2)=3, 0×2=0, 4×2=8
  
步骤2：偶数位之和
  2 + 0 + 0 + 0 + 0 + 3 + 0 + 8 = 13
  
步骤3：奇数位之和
  4 + 0 + 0 + 0 + 0 + 0 + 3 + 0 = 7
  
步骤4：总和
  13 + 7 = 20
  
步骤5：检查
  20 % 10 = 0 ✓ 有效！
```

## 代码实现

```c
/*
 * credit.c
 * 
 * 使用Luhn算法验证信用卡并识别类型
 */
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // 获取信用卡号
    long card_number = get_long("Number: ");
    
    // 计算卡号长度和获取前1位、前2位数字
    long temp = card_number;
    int length = 0;
    int first_digit = 0;
    int first_two_digits = 0;
    
    // 从右往左遍历，计算长度并提取前缀
    while (temp > 0)
    {
        first_digit = temp % 10;  // 最高位会保留到最后
        if (temp >= 10 && temp < 100)
        {
            first_two_digits = temp;  // 当剩余两位时保存
        }
        temp /= 10;
        length++;
    }
    
    // === Luhn算法验证 ===
    int sum1 = 0;  // 偶数位置（倒数第2、4、6...位）乘2后的和
    int sum2 = 0;  // 奇数位置（倒数第1、3、5...位）的数字和
    temp = card_number;
    int position = 1;  // 位置计数器（从右往左，从1开始）
    
    while (temp > 0)
    {
        int digit = temp % 10;
        
        if (position % 2 == 0)  // 偶数位置
        {
            int product = digit * 2;
            // 如果乘积≥10，需要将两位数字分别相加
            if (product >= 10)
            {
                sum1 += (product / 10) + (product % 10);
            }
            else
            {
                sum1 += product;
            }
        }
        else  // 奇数位置
        {
            sum2 += digit;
        }
        
        temp /= 10;
        position++;
    }
    
    int total = sum1 + sum2;
    
    // 检查校验和：如果总和不能被10整除，卡号无效
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    
    // === 根据长度和前缀识别卡类型 ===
    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    
    return 0;
}
```

## 关键技巧

### 1. 如何获取数字的位数和前缀？

```c
long num = 4003600000000014;
long temp = num;
int length = 0;

while (temp > 0)
{
    temp /= 10;  // 每次去掉最右边一位
    length++;    // 计数
}
// 最终 length = 16
```

### 2. 如何判断位置（从右往左）？

使用一个计数器 `position`，从1开始：
- `position % 2 == 0`：偶数位置
- `position % 2 == 1`：奇数位置

### 3. 如何分离两位数？

对于数字 `14`：
- 十位：`14 / 10 = 1`
- 个位：`14 % 10 = 4`

## 测试用例

可以使用以下测试卡号（来自CS50官方）：

| 卡号 | 类型 |
|------|------|
| 378282246310005 | AMEX |
| 371449635398431 | AMEX |
| 5555555555554444 | MASTERCARD |
| 5105105105105100 | MASTERCARD |
| 4111111111111111 | VISA |
| 4012888888881881 | VISA |
| 4222222222222 | VISA (13位) |
| 1234567890 | INVALID |

## 关于输入处理的注意事项

CS50的`get_long()`函数会自动处理无效输入（如字母、特殊字符），如果用户输入了非数字字符，它会重新提示用户输入，直到得到一个有效的`long`类型整数。

**示例**：
```
$ ./credit
Number: 4003-6000-0000-0014
Number: foo
Number: 4003600000000014
VISA
```

这是`get_long()`的内部行为，不是bug。它会过滤掉破折号和字母，一直重新提示，直到得到纯数字输入。

---

## 代码改进：使用函数抽象 ⭐

上面的代码虽然能正确工作，但所有逻辑都堆在`main`函数中，代码有点"臃肿"。还记得 Week 1 中我们学到的**函数抽象**（Abstraction）吗？

### 为什么需要函数抽象？

回顾 Week 1 的核心思想：
1. **提高可读性**：`main`函数只展示主要流程，具体实现细节隐藏在各个函数中
2. **便于复用**：如果需要在多处使用相同功能，函数可以被反复调用
3. **易于调试**：每个函数职责单一，出错时容易定位
4. **模块化设计**：就像搭积木，每个函数是一个积木块

### 思考：我们可以抽象哪些功能？

看看`main`函数中做了哪些事情：
1. ✅ **获取卡号长度** → `get_length()`
2. ✅ **获取第一位数字** → `get_first_digit()`
3. ✅ **获取前两位数字** → `get_first_two_digits()`
4. ✅ **Luhn算法验证** → `is_valid_luhn()`
5. ✅ **识别卡类型** → `print_card_type()`

### 重构后的代码

```c
/*
 * credit.c (重构版 - 使用函数抽象)
 * 
 * 应用 Week 1 学到的函数抽象思想
 */
#include <cs50.h>
#include <stdio.h>

// ====== 函数声明 ======
int get_length(long number);
int get_first_digit(long number);
int get_first_two_digits(long number);
bool is_valid_luhn(long number);
void print_card_type(long number);

int main(void)
{
    // 获取信用卡号
    long card_number = get_long("Number: ");
    
    // 使用Luhn算法验证卡号
    if (!is_valid_luhn(card_number))
    {
        printf("INVALID\n");
        return 0;
    }
    
    // 识别并打印卡类型
    print_card_type(card_number);
    
    return 0;
}

// ====== 函数定义 ======

/*
 * 计算数字的位数
 * 例如：get_length(4003600000000014) 返回 16
 */
int get_length(long number)
{
    int length = 0;
    while (number > 0)
    {
        number /= 10;
        length++;
    }
    return length;
}

/*
 * 获取数字的第一位（最高位）
 * 例如：get_first_digit(4003600000000014) 返回 4
 */
int get_first_digit(long number)
{
    while (number >= 10)
    {
        number /= 10;
    }
    return number;
}

/*
 * 获取数字的前两位
 * 例如：get_first_two_digits(378282246310005) 返回 37
 */
int get_first_two_digits(long number)
{
    while (number >= 100)
    {
        number /= 10;
    }
    return number;
}

/*
 * 使用Luhn算法验证卡号是否有效
 * 
 * Luhn算法步骤：
 * 1. 从右往左，对偶数位置的数字乘以2
 * 2. 如果乘积≥10，将两位数字分别相加
 * 3. 将所有数字相加
 * 4. 如果总和能被10整除，则有效
 * 
 * 返回 true 表示有效，false 表示无效
 */
bool is_valid_luhn(long number)
{
    int sum1 = 0;  // 偶数位置乘2后的和
    int sum2 = 0;  // 奇数位置的和
    int position = 1;
    
    while (number > 0)
    {
        int digit = number % 10;
        
        if (position % 2 == 0)  // 偶数位置
        {
            int product = digit * 2;
            if (product >= 10)
            {
                // 将两位数分别相加：14 → 1+4=5
                sum1 += (product / 10) + (product % 10);
            }
            else
            {
                sum1 += product;
            }
        }
        else  // 奇数位置
        {
            sum2 += digit;
        }
        
        number /= 10;
        position++;
    }
    
    int total = sum1 + sum2;
    return (total % 10 == 0);
}

/*
 * 根据卡号长度和前缀识别并打印卡片类型
 * 
 * 规则：
 * - AMEX: 15位，以34或37开头
 * - MASTERCARD: 16位，以51-55开头
 * - VISA: 13或16位，以4开头
 */
void print_card_type(long number)
{
    int length = get_length(number);
    int first_digit = get_first_digit(number);
    int first_two_digits = get_first_two_digits(number);
    
    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
```

### 对比：两种实现的优缺点

| 对比维度 | 原始版本 | 函数抽象版本 |
|---------|---------|-------------|
| **代码行数** | ~60行 | ~130行（含注释） |
| **main函数** | 复杂，包含所有逻辑 | 简洁，只有6行核心逻辑 |
| **可读性** | 需要仔细阅读才能理解 | 一眼看出程序结构 |
| **可维护性** | 修改某个功能需要在main中找 | 直接修改对应函数 |
| **可复用性** | 逻辑无法复用 | 函数可在其他地方调用 |
| **调试难度** | 出错时不知道哪部分有问题 | 可以单独测试每个函数 |
| **适合场景** | 小型程序、快速原型 | 大型项目、团队协作 |

### 重构版的亮点 ✨

1. **`main`函数清晰明了**：
   ```c
   // 一眼就能看出程序做了什么：
   // 1. 获取卡号
   // 2. 验证有效性
   // 3. 打印卡类型
   ```

2. **函数命名语义化**：
   - `is_valid_luhn()` - 一看就知道是验证函数，返回bool
   - `get_length()` - 获取长度，返回int
   - `print_card_type()` - 打印类型，无返回值（void）

3. **文档注释完善**：
   - 每个函数都有说明其功能、参数、返回值
   - 符合专业的代码规范

4. **单一职责原则**：
   - 每个函数只做一件事
   - 如果`is_valid_luhn()`有bug，只需检查这一个函数

### 关于注释风格的说明 📝

你可能注意到函数前面的注释采用了特殊格式。这里我使用的是**简化版的文档注释**，只说明函数的功能和示例。

**专业代码中的文档注释**（你现在不需要掌握）：
在大型项目中，程序员会使用 Doxygen 或 JavaDoc 风格的注释，例如：
```c
/**
 * @brief 计算数字的位数
 * @param number 要计算的数字
 * @return 返回位数
 */
```

但对于初学者，**简单的注释就足够了**：
```c
// 计算数字的位数，例如 123 返回 3
```

选择适合自己和团队的注释风格即可！

### 是否"过度抽象"了？🤔

为了理解巩固函数抽象的知识点，上面我把每个可抽象的功能都抽象出来了，其实有的是不必要的。  

#### 必要的抽象 ✅

**`is_valid_luhn()`** - 非常值得抽象
- 代码有20+行
- 逻辑复杂（两个sum，位置判断，乘2等）
- 有明确的功能：验证卡号
- 返回bool值，语义清晰

**`print_card_type()`** - 值得抽象
- 包含多个if-else判断
- 有明确的功能：识别卡类型
- 避免main函数过长

#### 可选的抽象 ⚖️

**`get_length()`, `get_first_digit()`, `get_first_two_digits()`** - 可以讨论

**支持抽象的理由**：
- ✅ 让main函数更简洁
- ✅ 函数名表达了意图（自文档化）
- ✅ 如果将来需要在其他地方使用，可以直接调用

**反对抽象的理由**：
- ❌ 每个函数只有3-5行，非常简单
- ❌ 只在一个地方使用，没有复用
- ❌ 增加了代码跳转，阅读时需要来回翻看

#### 更简洁的方案

因此可以只保留核心函数：

```c
#include <cs50.h>
#include <stdio.h>

// 只声明两个最重要的函数
bool is_valid_luhn(long number);
void print_card_type(long number);

int main(void)
{
    long card_number = get_long("Number: ");
    
    if (!is_valid_luhn(card_number))
    {
        printf("INVALID\n");
        return 0;
    }
    
    print_card_type(card_number);
    return 0;
}

// Luhn算法验证
bool is_valid_luhn(long number)
{
    // ... (保持不变)
}

// 识别并打印卡类型
void print_card_type(long number)
{
    // 直接在这里计算长度和前缀，不单独抽象
    int length = 0;
    long temp = number;
    while (temp > 0)
    {
        temp /= 10;
        length++;
    }
    
    int first_digit = number;
    while (first_digit >= 10)
        first_digit /= 10;
    
    int first_two = number;
    while (first_two >= 100)
        first_two /= 10;
    
    // 判断卡类型
    if (length == 15 && (first_two == 34 || first_two == 37))
        printf("AMEX\n");
    else if (length == 16 && (first_two >= 51 && first_two <= 55))
        printf("MASTERCARD\n");
    else if ((length == 13 || length == 16) && first_digit == 4)
        printf("VISA\n");
    else
        printf("INVALID\n");
}
```

#### 判断是否需要抽象的标准 📏

问自己这些问题：

1. **代码行数**：超过10-15行？ → 考虑抽象
2. **复用性**：会在多处使用？ → 必须抽象
3. **复杂度**：逻辑复杂，难以一眼看懂？ → 应该抽象
4. **命名价值**：函数名能让代码更易读？ → 值得抽象
5. **测试需求**：需要单独测试这个功能？ → 应该抽象

**结论**：
- 对于 Problem Set 1 这个规模，**两种方式都可以**
- 完全抽象版：更适合学习函数抽象的思想
- 折中版：更实用，平衡了可读性和简洁性
- 原始版：逻辑最直接，但main函数较长

**我的建议**：
- 作业提交：使用原始版或折中版
- 学习目的：尝试完全抽象版，理解函数设计
- 未来项目：根据团队规范和项目大小决定

### 学习建议

对于初学者，推荐的编码流程：

1. **第一步**：先写出能工作的代码（像原始版本）
2. **第二步**：测试确保功能正确
3. **第三步**：识别可以抽象的部分
4. **第四步**：重构代码，将功能封装成函数
5. **第五步**：再次测试，确保重构没有引入新bug

> **核心原则**：抽象是为了**解决问题**（提高可读性、复用性、可维护性），而不是为了炫技。如果一个3行的函数只用一次，抽象的价值就很有限。

---

# 总结

## 本次作业涉及的核心概念

1. **循环控制**
   - 使用`for`循环实现嵌套结构（Mario）
   - 使用`do-while`验证输入
   - 使用`while`遍历数字的每一位（Credit）

2. **算法思维**
   - **找规律**：观察输出，抽象出数学关系（Mario）
   - **贪心算法**：每次选择局部最优解（Cash）
   - **Luhn算法**：理解和实现标准算法（Credit）

3. **数学运算**
   - 整数除法 `/` 和取模 `%` 的应用
   - 位数计算和数字提取

4. **函数抽象** ⭐
   - 将复杂逻辑分解为多个小函数
   - 每个函数专注于单一职责
   - 提高代码可读性和可维护性
   - 函数命名要有意义、一看就懂

5. **调试技巧**
   - 使用`printf`打印中间变量
   - 测试边界情况（如高度为1或8）
   - 使用官方测试用例验证

## 编程建议

1. **先理解再编码**：不要急于写代码，先在纸上画出几个例子，找规律
2. **分步实现**：把复杂问题拆解成小步骤，逐个击破
3. **先实现再优化**：第一遍先让代码工作，第二遍再考虑函数抽象和优化
4. **充分测试**：不仅测试正常情况，也要测试边界和异常情况
5. **代码注释**：养成写注释的习惯，解释你的思路
6. **函数抽象**：当一段代码超过20行或有明确的功能模块时，考虑封装成函数

## 扩展思考

1. **Mario**：如果要打印菱形或其他形状，如何修改？
2. **Cash**：如果硬币面值是 `[1, 6, 10]`，贪心算法还有效吗？（提示：对于41美分，贪心给出 `4×10 + 1×1 = 5`枚，但最优是 `4×10 + 1×1 = 5`枚。试试25美分的情况）
3. **Credit**：为什么要用Luhn算法？它能防止什么样的错误？（提示：防止输入错误，如数字顺序颠倒）
4. **函数抽象**：
   - 你能把 Cash 或 Mario 的代码也用函数抽象改写吗？
   - 什么时候应该使用函数？什么时候不需要？
   - 如果要写一个测试函数 `test_luhn()`，应该如何设计？

---

**参考资料**：
- [CS50 Problem Set 1 官方页面](https://cs50.harvard.edu/x/psets/1/)
- [Luhn算法详解（维基百科）](https://en.wikipedia.org/wiki/Luhn_algorithm)
- [贪心算法介绍](https://en.wikipedia.org/wiki/Greedy_algorithm)

下周我们将学习数组，挑战更复杂的问题！💪

