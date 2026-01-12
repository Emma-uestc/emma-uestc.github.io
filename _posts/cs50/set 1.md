[Set 1](https://cs50.harvard.edu/x/psets/1/)  
# What To Do  
1. Log into submit.cs50.io using your GitHub account and click Authorize cs50, then close the tab.
2. Log into cs50.dev using your GitHub account to access your very own “codespace.”
3. Once your codespace has loaded, close any Welcome tabs that might have opened by default.
4. Run update50 in your codespace’s terminal window to ensure that your codespace is up-to-date and, if prompted, click Rebuild now.
5. Complete Hello, World.
6. Submit Hello, It’s Me.
7. Submit one of:
  - this version of Mario, if feeling less comfortable
  - this version of Mario, if feeling more comfortable
8. Submit one of:
  - Cash, if feeling less comfortable
  - Credit, if feeling more comfortable  
# Problems  
1. mario-less  
In a file called mario.c in a folder called mario-less, implement a program in C that recreates that pyramid, using hashes (#) for bricks, as in the below:
在名为 mario.c 的文件中，位于名为 mario-less 的文件夹中，使用哈希（#）来实现一个 C 语言程序，以重现那个金字塔，就像下面那样：
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
我的实现在 `mario-less/mario.c`
2. mario-more  
In a file called mario.c in a folder called mario-more, implement a program in C that recreates that pyramid, using hashes (#) for bricks, as in the below:
在名为 mario.c 的文件中，使用 C 语言实现一个程序，以哈希（#）作为砖块，重现金字塔的结构，如下所示：  
```
   #  #
  ##  ##
 ###  ###
####  ####
```  
And let’s allow the user to decide just how tall the pyramids should be by first prompting them for a positive int between, say, 1 and 8, inclusive.   
```
$ ./mario
Height: 8
       #  #
      ##  ##
     ###  ###
    ####  ####
   #####  #####
  ######  ######
 #######  #######
########  ########
```   
我的实现在 `mario-more/mario.c`
3. cash changed 
Suppose you work at a store and a customer gives you $1.00 (100 cents) for candy that costs $0.50 (50 cents). You’ll need to pay them their “change,” the amount leftover after paying for the cost of the candy. When making change, odds are you want to minimize the number of coins you’re dispensing for each customer, lest you run out (or annoy the customer!). In a file called cash.c in a folder called cash, implement a program in C that prints the minimum coins needed to make the given amount of change, in cents, as in the below:  
```
Change owed: 25
1
```  
But prompt the user for an int greater than 0, so that the program works for any amount of change:  
```
Change owed: 70
4
``` 
我的实现在 `cash.c`  

4. credit card   
[credit](https://cs50.harvard.edu/x/psets/1/credit/)  
我的实现在`credit/credit.c` 中，但是我的实现版本执行示例的几个测试用例结果如下：  
```   
# credit  
执行后：
```
./credit 
Number: 4003-6000-0000-0014
Number: 4003600000000014
VISA

problems/credit/ $ ./credit 
Number: 6176292929
INVALID
```  
课程文档给出的正确的结果如下：    
```
$ ./credit
Number: 4003-6000-0000-0014
Number: foo
Number: 4003600000000014
VISA

$ ./credit
Number: 6176292929
INVALID
```
