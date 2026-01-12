# Mario (Less Comfortable) - Python Version
# 打印右对齐的金字塔

from cs50 import get_int

# 获取高度（1-8 之间）
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# 打印金字塔（利用 Python 字符串乘法）
for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i)

