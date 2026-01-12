# Cash - Python Version
# 使用贪心算法计算最少硬币数

from cs50 import get_int

# 获取找零金额（非负整数）
while True:
    cents = get_int("Change owed: ")
    if cents >= 0:
        break

# 贪心算法：从大面值到小面值
coins = 0
denominations = [25, 10, 5, 1]

for coin in denominations:
    coins += cents // coin
    cents %= coin

print(coins)

