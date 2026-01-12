# Mario (More Comfortable) - Python Version
# 打印双侧金字塔

from cs50 import get_int

# 获取高度（1-8 之间）
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# 打印双侧金字塔
for i in range(1, height + 1):
    blocks = "#" * i
    # 左侧右对齐 + 2个空格间隙 + 右侧
    print(blocks.rjust(height) + "  " + blocks)

