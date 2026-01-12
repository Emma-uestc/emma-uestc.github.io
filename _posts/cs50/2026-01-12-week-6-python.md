---
layout: post
title: "CS50 Week 6: Python - 从 C 到高级语言的跨越"
date: 2026-01-12
categories: [CS50, Programming]
tags: [Python, 编程语言, 面向对象, 异常处理, 数据结构]
---

# 欢迎来到 Python！

在前几周的学习中，你已经掌握了编程的基础构建块，并使用底层编程语言 C 进行了实践。今天，我们将使用一门高级编程语言 **Python**。

随着你学习这门新语言，你会发现自己越来越有能力自学新的编程语言——这正是 CS50 的核心目标之一。

课程官方笔记：[https://cs50.harvard.edu/x/notes/6/](https://cs50.harvard.edu/x/notes/6/)

---

## 本周内容概览

| 主题 | C 语言 | Python | 关键区别 |
|------|--------|--------|---------|
| 程序入口 | `int main(void)` | 直接执行 | Python 无需 main 函数 |
| 变量声明 | `int x = 1;` | `x = 1` | Python 自动推断类型 |
| 输出 | `printf("hello\n");` | `print("hello")` | 无需 `\n`，无需分号 |
| 条件 | `if (x > 0) { }` | `if x > 0:` | 用缩进代替大括号 |
| 循环 | `for (int i = 0; i < n; i++)` | `for i in range(n):` | 更简洁的语法 |
| 内存管理 | 手动 malloc/free | 自动垃圾回收 | Python 自动管理内存 |

---

# Hello, Python

与编译型语言 C 不同，Python 是**解释型语言**，无需单独编译程序。相反，你只需在 Python 解释器中运行程序即可。

回顾下我们学习 C 时的第一个程序  
```C
// A program that says hello to the world

#include <stdio.h>

int main(void)
{
    printf("hello, world\n");
}
```  
使用 Python 是可以如下  
```Python
# A program that says hello to the world

print("hello, world")
```  
请注意分号已消失且无需任何库支持。你可在终端中输入 `python hello.py` 运行此程序。
Python 尤其能以相对简单的实现方式完成在 C 语言中相当复杂的任务。  
# Speller：C vs Python 的终极对比

还记得上周我们用 C 实现的拼写检查器吗？那个需要 100+ 行代码、手动管理内存、实现哈希表的程序？

让我们看看 Python 如何用 **不到 20 行代码** 实现相同的功能：  
```Python
# Words in dictionary
words = set()


def check(word):
    """Return true if word is in dictionary else false"""
    return word.lower() in words


def load(dictionary):
    """Load dictionary into memory, returning true if successful else false"""
    with open(dictionary) as file:
        words.update(file.read().splitlines())
    return True


def size():
    """Returns number of words in dictionary if loaded else 0 if not yet loaded"""
    return len(words)


def unload():
    """Unloads dictionary from memory, returning true if successful else false"""
    return True
```   
注意到上面有四个函数：
- `check()`：如果 `word` 在 `words` 集合中，返回 `True`。比 C 语言的实现简单得多！
- `load()`：打开字典文件，将每一行添加到 `words` 集合中
- `size()`：返回 `len(words)`，即单词数量
- `unload()`：直接返回 `True`，因为 **Python 自动管理内存**！

### C vs Python 实现对比

| 方面 | C 实现 | Python 实现 |
|------|--------|-------------|
| 代码行数 | ~120 行 | ~15 行 |
| 数据结构 | 手动实现哈希表 + 链表 | 内置 `set()` |
| 内存管理 | 手动 `malloc`/`free` | 自动垃圾回收 |
| 字符串比较 | `strcasecmp()` | `word.lower() in words` |
| 文件读取 | `fopen`/`fscanf`/`fclose` | `with open() as file` |

> 💡 **关键洞察**：上述代码说明了为什么存在高级语言——**为了简化并让你更容易编写代码**。

### 速度的权衡

然而，速度是一种权衡。由于 C 语言允许程序员对内存管理做出决策，因此它可能比 Python 运行得**更快**。当调用 Python 的内置函数时，Python 会运行所有底层代码，而 C 语言只运行你的代码行。

| 语言 | 优势 | 劣势 |
|------|------|------|
| C | 运行速度快、内存控制精细 | 开发慢、容易出错 |
| Python | 开发速度快、代码简洁 | 运行较慢、内存占用大 |  
更多关于 Python 的内容可以查看[官方文档](https://docs.python.org/3/library/functions.html)。

---

# Filter：图像处理的简化

还记得 Week 4 用 C 实现的图像滤镜吗？在 Python 中，借助第三方库 `PIL`，可以用几行代码实现相同功能：  
```Python
# Blurs an image

from PIL import Image, ImageFilter

# Blur image
before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.BoxBlur(1))
after.save("out.bmp")
```  
注意，此程序从名为 `PIL` 的库中导入模块 `Image` 和 `ImageFilter` 。它接受一个输入文件并创建一个输出文件。  
我们再使用Python 实现一遍 edeges 操作，终端输入 code edges.py  
```Python
# Finds edges in an image

from PIL import Image, ImageFilter

# Find edges
before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.FIND_EDGES)
after.save("out.bmp")
```  
注意，这段代码只是对 blur 代码的一个小调整，但产生了截然不同的结果。  
Python 允许你将编程抽象化，这样在 C 语言和其他低级编程语言中原本会非常复杂的编程任务就会变得简单得多。  

---

# 函数  
C 中输出函数： `printf("hello, world\n");`  
Python 中是这样的 `print("hello, world")`  
# 库，模块，包（Libraries, Modules, and Packages）  
和 C 语言一样，CS50 库也可以在 Python 中使用。   
以下函数将特别有用  
```Python
  get_float
  get_int
  get_string
```  
使用的方法也是导入 cs50 库：`import cs50`  
你也可以选择只从 CS50 库中导入特定函数，如下所示：  
`from cs50 import get_float, get_int, get_string`  

---

# 字符串（Strings）  
还记得在 C 中是这样使用字符串的  
```C
// get_string and printf with %s

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
}
```   
在Python 中可以在这样实现   
```Python
# get_string and print, with concatenation

from cs50 import get_string

answer = get_string("What's your name? ")
print("hello, " + answer)
```  
你可以在终端窗口中执行 code hello.py 来编写这段代码。然后，你可以通过运行 python hello.py 来执行这段代码。注意 + 符号如何将 "hello, " 和 answer 连接起来。  
类似地，这也可以不使用连接操作完成：`print("hello,", answer)`  
注意，`print` 语句会在 `hello` 和 `answer` 之间自动创建一个空格。  
同样，你可以将上述代码实现为：  
```Python
# get_string and print, with format strings

from cs50 import get_string

answer  = get_string("What's your name? ")
print(f"hello, {answer}")
```   
# 位置参数和命名参数(Positional Parameters and Named Parameters)   
C 语言中的函数如 `fread` 、 `fwrite` 和 `printf` 使用位置参数，你提供参数时用逗号作为分隔符。你必须记住哪个参数在哪个位置。这些被称为位置参数.  
在 Python 中，命名参数允许你无需考虑位置来提供参数。  
更多关于 `print` 函数的用法参见[官方文档](https://docs.python.org/3/library/functions.html#print)  
访问该文档，你可能会看到以下内容：  
```Python
print(*objects, sep=' ', end='\n', file=None, flush=False)
```  
注意，`print` 可以提供各种对象进行打印。当向 `print` 提供多个对象时，会显示一个空格作为分隔符。同样，在 print 语句的末尾会提供一个换行符。
# 变量（Variables）  
Python 中变量的声明也简化了。比如，在 C 语言中，使用 `int counter = 0;` 声明变量 `counter` 并初始化 。在 Python 中， 只需要 `counter = 0` 。你不需要声明变量的类型。  
相对于C 语言中使用 `counter++` 递增操作，Python 使用 `counter += 1` 来递增  
# 类型（Types）  
Python 中的数据类型无需显式声明。例如，上面`hello.py` 中的 `answer` 是一个字符串，但我们不必告诉解释器这一点：它自己就知道了。 
在 Python 中，常用的数据类型包括：  
```Python
  bool
  float
  int
  str
```  
请注意没有 `long` 和 `double`。Python 会根据数据大小判断使用哪种数据类型来表示较大和较小的数字。  
Python 中其他数据类型包括：  
```Python
range   sequence of numbers
list    sequence of mutable values
tuple   sequence of immutable values
dict    collection of key-value pairs
set     collection of unique values
```   
这些数据类型在 C 语言中都可以实现，但在 Python 中，它们可以更简单地实现。  

---

# 计算器（Calculator）  
我们用Python 实现之前用C 实现的计算器程序 
```C
// calculator.c
// Addition with int

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for x
    int x = get_int("x: ");

    // Prompt user for y
    int y = get_int("y: ");

    // Perform addition
    printf("%i\n", x + y);
}
```  
```Python
# calculator.py
from cs50 import get_int

# Prompt user for x
x = get_int("x: ")

# Prompt user for y
y = get_int("y: ")

# Perform addition
print(x + y)
```   
注意这里使用的 CS50 库中的 `get_int()` 。然后，从用户那里获取 x 和 y 。最后，打印结果。注意，这里没有 `main` 函数，虽然可以使用 main 函数，但在 Python 中并非必需。 
如果我们不使用 CS50 库中的`get_int()` 函数，实现如下  
```Python
# Addition with int [using input]

# Prompt user for x
x = input("x: ")

# Prompt user for y
y = input("y: ")

# Perform addition
print(x + y)
```   

---

# 条件语句（Conditionals）  
对比下C 和 Python 中的条件语句   
* C  
```C
// Conditionals, Boolean expressions, relational operators

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for integers
    int x = get_int("What's x? ");
    int y = get_int("What's y? ");

    // Compare integers
    if (x < y)
    {
        printf("x is less than y\n");
    }
    else if (x > y)
    {
        printf("x is greater than y\n");
    }
    else
    {
        printf("x is equal to y\n");
    }
}
```  
* Python   
```Python
# Conditionals, Boolean expressions, relational operators

from cs50 import get_int

# Prompt user for integers
x = get_int("What's x? ")
y = get_int("What's y? ")

# Compare integers
if x < y:
    print("x is less than y")
elif x > y:
    print("x is greater than y")
else:
    print("x is equal to y")
```   
注意，Python 不再使用大括号，而是使用缩进来表示。其次，在 `if` 语句中使用了冒号。此外， `elif` 替换了 `else if` 。在 `if` 和 `elif` 语句中，括号也不再需要。  
我们再看一组对比  
* C  
```C
// Logical operators

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user to agree
    char c = get_char("Do you agree? ");

    // Check whether agreed
    if (c == 'Y' || c == 'y')
    {
        printf("Agreed.\n");
    }
    else if (c == 'N' || c == 'n')
    {
        printf("Not agreed.\n");
    }
}
```   
* Python   
```Python
# Logical operators

from cs50 import get_string

# Prompt user to agree
s = get_string("Do you agree? ")

# Check whether agreed
if s == "Y" or s == "y":
    print("Agreed.")
elif s == "N" or s == "n":
    print("Not agreed.")
```   
Python 中的逻辑运算不再是 `||`、`&&`、`!`，而是自然语言 `or`、`and`、`not`。更易读，更易理解。  

使用 `list` 的另一种方法来编写相同的代码可能是如下所示：  
```Python
# Logical operators, using lists

from cs50 import get_string

# Prompt user to agree
s = get_string("Do you agree? ")

# Check whether agreed
if s in ["y", "yes"]:
    print("Agreed.")
elif s in ["n", "no"]:
    print("Not agreed.")
```   
# 面向对象编程（Object-Oriented Programming）  
某些类型的值不仅可以在内部拥有属性或特性，还可以拥有函数。在 Python 中，这些值被称为对象。  
在 C 语言中，我们可以创建一个结构体，在其中关联多个变量。在 Python 中，我们不仅可以这样做，还可以在自定义的数据类型中包含函数。当函数属于特定对象时，它被称为方法。  
例如，Python 中， `strs` 有内置方法。因此，可以按如下方式修改你的代码：  
```Python
# Logical operators, using lists

# Prompt user to agree
s = input("Do you agree? ").lower()

# Check whether agreed
if s in ["y", "yes"]:
    print("Agreed.")
elif s in ["n", "no"]:
    print("Not agreed.")
```  
这段代码中的 `lower()` 就是 `strs` 的内置方法   
同样，回一下C 中的实现   
```C
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Get a string
    char *s = get_string("s: ");
    if (s == NULL)
    {
        return 1;
    }

    // Allocate memory for another string
    char *t = malloc(strlen(s) + 1);
    if (t == NULL)
    {
        return 1;
    }

    // Copy string into memory
    strcpy(t, s);

    // Capitalize copy
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    // Print strings
    printf("s: %s\n", s);
    printf("t: %s\n", t);

    // Free memory
    free(t);
    return 0;
}
```  
而使用 Python，只需要  
```Python
# Capitalizes a copy of a string

# Get a string
s = input("s: ")

# Capitalize copy of string
t = s.capitalize()

# Print strings
print(f"s: {s}")
print(f"t: {t}")
```   

更多关于 string 的用法，查看[官方文档](https://docs.python.org/3/library/stdtypes.html#string-methods)。

---

# 循环（Loops）  
Python 中的循环与 C 中差不多。  
回忆下 C 中的 for 循环   
```C
// Demonstrates for loop

#include <stdio.h>

int main(void)
{
    for (int i = 0; i < 3; i++)
    {
        printf("meow\n");
    }
}
```  
对应的 Python 中的 for 循环  
```Python
# Better design

for i in range(3):
    print("meow")
```  
注意，python 中 `i` 没有声明，但是可以直接使用并可以进行递增操作。  
对应的 while 循环  
```Python
# Demonstrates while loop

i = 0
while i < 3:
    print("meow")
    i += 1
```  
为了更好的理解 Python 中的循环和迭代，通过下面的 `uppercase.py` 代码看下  
```Python
# Uppercases string one character at a time

before = input("Before: ")
print("After:  ", end="")
for c in before:
    print(c.upper(), end="")
print()
```   
请注意如何使用 `end=` 向 `print` 函数传递参数，该函数会在不换行时继续当前行。这段代码每次只传递一个字符串。  
阅读文档，我们发现 Python 有可以作用于整个字符串的方法，如下：  
```Python
# Uppercases string all at once

before = input("Before: ")
after = before.upper()
print(f"After:  {after}")
```   
关注下 `upper` 是如何应用于整个字符串的。  
# 抽象  
与 C 一样，，Python 中也可以通过使用函数并将各种代码抽象为函数来进一步改进代码，使其更具结构化，按照以下方式修改之前创建的 `meow.py` 代码  
```Python
# Abstraction

def main():
    for i in range(3):
        meow()

# Meow once
def meow():
    print("meow")


main()
```  
注意， `meow` 函数对 print 功能进行了抽象。此外， `main` 函数出现在文件顶部。在文件底部，调用了 `main` 函数。按照惯例，在 Python 中，你应当创建一个 main 函数。  
同样，也可以在函数之间传递变量：  
```Python
def main():
    meow(3)


# Meow some number of times
def meow(n):
    for i in range(n):
        print("meow")


main()
```  
注意 `meow` 现在接受一个变量 `n`。在 `main` 函数中，你可以调用 `meow` 并传递一个值 `3` 给它。然后，`meow` 在 `for` 循环中使用了 `n` 的值。

---

# 截断和浮点数精度（Truncation and Floating Point Imprecision）  
回想在 C 语言中，我们遇到过的截断情况，当两个整数做除法是，可能会得到一个不精确的结果。  
我们通过 calculator.py 看下 Python 是如何处理这种情况的。  
```Python
# Division with integers, demonstration lack of truncation

# Prompt user for x
x = int(input("x: "))

# Prompt user for y
y = int(input("y: "))

# Divide x by y
z = x / y
print(z)
```   
执行这段代码会产生一个值，但如果你在 `.333333` 后面看到更多数字，你会发现我们面临的是浮点数精度问题。这里并没有发生截断。  
```Shell
python calculator.py 
x 10
y 3
3.3333333333333335
```   
我们可以通过稍微修改我们的代码来揭示这种不精确性  
```Python
# Floating-point imprecision

# Prompt user for x
x = int(input("x: "))

# Prompt user for y
y = int(input("y: "))

# Divide x by y
z = x / y
print(f"{z:.50f}")
```  
结果   
```shell
python calculator.py 
x 10
y 3
3.33333333333333348136306995002087205648422241210938
```   
这段代码揭示了不精确性。Python 仍然面临这个问题，就像 C 语言一样。  

---

# 异常（Exceptions）  
下面深入探索下Python 中的异常   
继续修改 calculator.py,如下  
```Python
# Doesn't handle exception

# Prompt user for an integer
n = int(input("Input: "))
print("Integer")
```  
当输入一个非整数时会抛出以下异常   
```Shell
 python calculator.py 
Input: 1.2
Traceback (most recent call last):
  File "/workspaces/18479418/week6/calculator.py", line 4, in <module>
    n = int(input("Input: "))
ValueError: invalid literal for int() with base 10: '1.2'
```   
可以使用 try 处理和捕获潜在的异常：  
```Python
# Handles exception

# Prompt user for an integer
try:
    n = int(input("Input: "))
    print("Integer.")
except ValueError:
    print("Not integer.")
```  
处理后的结果  
```Shell
python calculator.py 
Input: 1.2
Not integer.
```  

---

# 马里奥（Mario）  
回想几周前我们实现的像马里奥游戏中那样将三个方块叠放在一起的任务。  

![三个垂直方块](https://cs50.harvard.edu/x/notes/6/cs50Week6Slide073.png)  

在 Python 中实现如下   
```Python
for i in range(3):
    print("#")
```   
接着，C 语言使用 do-while 循环实现的这个任务，在 Python 中，通常使用 while 循环。mario.py 实现如下  
```Python
# Prints a column of n bricks with a loop

from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0:
        break

for i in range(n):
    print("#")
```  
继续，看下面这张图片  

![一行四个问号](https://cs50.harvard.edu/x/notes/6/cs50Week6Slide075.png)  

可以通过继续修改代码实现。同样，`print("?" * 4)` 是一样的效果，而且只使用一行代码就实现了。  

我们来点稍微复杂点的  

![3x3 方块网格](https://cs50.harvard.edu/x/notes/6/cs50Week6Slide078.png)   

可以通过双重循环实现。  
```Python
# Prints a 3-by-3 grid of bricks with loops

for i in range(3):
    for j in range(3):
        print("#", end="")
    print()
```  

---

# 列表（Lists）  
`lists` 是Python中的一种数据结构。
`lists` 内部包含内置的方法或函数。   
我们看下面的代码  
```Python
# Averages three numbers using a list

# Scores
scores = [72, 73, 33]

# Print average
average = sum(scores) / len(scores)
print(f"Average: {average}")
```   
代码中的 `sum` 方法就是内置的方法。  
也可以使用以下语法从用户获取值：  
```Python
# Averages three numbers using a list and a loop

from cs50 import get_int

# Get scores
scores = []
for i in range(3):
    score = get_int("Score: ")
    scores.append(score)

# Print average
average = sum(scores) / len(scores)
print(f"Average: {average}")
```  
这里使用了 lists 的内置方法 append()  
更多使用查看官方文档 [lists](https://docs.python.org/3/library/stdtypes.html#sequence-types-list-tuple-range)。

---

# 搜索和字典（Searching and Dictionaries）  
考虑下面的phonebook.py  
```Python
# Implements linear search for names using loop

# A list of names
names = ["Yuliia", "David", "John"]

# Ask for name
name = input("Name: ")

# Search for name
for n in names:
    if name == n:
        print("Found")
        break
else:
    print("Not found")
```  
使用的是线性搜索查找名字的   
在 Python 中，可以不用遍历列表，而是按以下方式执行线性搜索  
```Python
# Implements linear search for names using `in`

# A list of names
names = ["Yuliia", "David", "John"]

# Ask for name
name = input("Name: ")

# Search for name
if name in names:
    print("Found")
else:
    print("Not found")
```  
`in` 就是用来执行线性搜索的。  
回顾下字典（dict）是由键值对组成的集合。  
Python 中实现 字典的操作如下  
```Python
# Implements a phone book as a list of dictionaries, without a variable

from cs50 import get_string

people = [
    {"name": "Yuliia", "number": "+1-617-495-1000"},
    {"name": "David", "number": "+1-617-495-1000"},
    {"name": "John", "number": "+1-949-468-2750"},
]

# Search for name
name = get_string("Name: ")
for person in people:
    if person["name"] == name:
        print(f"Found {person['number']}")
        break
else:
    print("Not found")
```   
字典的每个元素 都有 `name` and `number` 两个字段。  
继续优化代码如下  
```Python
# Implements a phone book using a dictionary

from cs50 import get_string

people = {
    "Yuliia": "+1-617-495-1000",
    "David": "+1-617-495-1000",
    "John": "+1-949-468-2750",
}

# Search for name
name = get_string("Name: ")
if name in people:
    print(f"Number: {people[name]}")
else:
    print("Not found")
```   
请注意，字典是用花括号实现的。然后，语句 if name in people 用于检查 name 是否在 people 字典中。此外，请注意，在 print 语句中，我们可以使用 name 的值来索引 people 字典。非常实用！  
Python 的内置搜索可以达到常数时间复杂度。  
更多关于 Python 的字典可以查看[官方文档](https://docs.python.org/3/library/stdtypes.html#dict)。

---

# 命令行参数（Command-Line Arguments）   
和 C 语言一样，Python 也可以使用命令行参数   
```Python
# Prints a command-line argument

from sys import argv

if len(argv) == 2:
    print(f"hello, {argv[1]}")
else:
    print("hello, world")
```   
注意， argv[1] 是使用格式化字符串打印的，这一点可以通过 print 语句中的 f 来确认。  
更多关于 Python 的 sys 库的用法请查阅[官方文档](https://docs.python.org/3/library/sys.html)。

---

# 退出状态码（Exit Status）  
sys 库也有内置方法。可以使用 sys.exit(i) 来以特定的退出码退出程序   
```Python
# Exits with explicit value, importing sys

import sys

if len(sys.argv) != 2:
    print("Missing command-line argument")
    sys.exit(1)

print(f"hello, {sys.argv[1]}")
sys.exit(0)
```   

---

# CSV 文件（CSV Files）  
Python 天然支持CSV 文件   
继续按照下面方式修改 phonebook.py  
```Python
import csv

file = open("phonebook.csv", "a")

name = input("Name: ")
number = input("Number: ")

writer = csv.writer(file)
writer.writerow([name,number])

file.close()
```   
writerow 用来添加 CSV 文件中的逗号。  
虽然 file.close 和 file = open 在 Python 中是常见的可用语法，但此代码可以按如下方式改进：  
```Python
import csv

name = input("Name: ")
number = input("Number: ")

with open("phonebook.csv", "a") as file:

    writer = csv.writer(file)
    writer.writerow([name,number])
```   
注意 with 语句的使用。这会在操作完成后自动关闭文件。  
同样，我们可以在 CSV 文件中这样写一个字典：  
```Python
import csv

name = input("Name: ")
number = input("Number: ")

with open("phonebook.csv", "a") as file:

    writer = csv.DictWriter(file, fieldnames=["name", "number"])
    writer.writerow({"name": name, "number": number})
```  
注意这段代码与我们的先前版本非常相似，但使用了 `csv.DictWriter`。  

---

# 第三方库（Third-Party Libraries）  
Python的优势之一在于其庞大的用户群体和同样丰富的第三方库资源。
只要计算机上已安装Python，即可通过输入pip install cs50命令自行安装CS50库。
在演示其他库时，David 展示了 `cowsay` 和 `qrcode` 的使用方法。  

---

# 总结  

在本周课程中，我们学习了如何将之前课程中的编程基础知识用 Python 实现。Python 作为高级语言，让代码更加简洁优雅。

## C vs Python 速查表

| 功能 | C 语言 | Python |
|------|--------|--------|
| Hello World | `printf("hello\n");` | `print("hello")` |
| 变量声明 | `int x = 1;` | `x = 1` |
| 条件判断 | `if (x > 0) { ... }` | `if x > 0:` |
| for 循环 | `for (int i = 0; i < 3; i++)` | `for i in range(3):` |
| 逻辑或 | `\|\|` | `or` |
| 逻辑与 | `&&` | `and` |
| 逻辑非 | `!` | `not` |
| 字符串比较 | `strcmp(s, t) == 0` | `s == t` |
| 内存分配 | `malloc()` / `free()` | 自动管理 |

## 本周知识点清单

- **Python 基础**：解释型语言、无需编译
- **变量与类型**：动态类型、自动推断
- **条件语句**：`if`/`elif`/`else`、用缩进代替大括号
- **循环**：`for i in range(n)`、`while`
- **面向对象编程**：对象、方法（如 `str.lower()`）
- **异常处理**：`try`/`except` 捕获错误
- **数据结构**：`list`、`dict`、`set`
- **文件操作**：`open()`、`with` 语句、CSV 处理
- **命令行参数**：`sys.argv`
- **第三方库**：`pip install`

## 延伸学习

- [Python 官方文档](https://docs.python.org/3/)
- [Python 内置函数](https://docs.python.org/3/library/functions.html)
- [Python 字符串方法](https://docs.python.org/3/library/stdtypes.html#string-methods)

---

**参考资料**：
- [CS50 Week 6 官方笔记](https://cs50.harvard.edu/x/notes/6/)
- [Python 官方教程](https://docs.python.org/3/tutorial/)

下次见！ 🚀