# Credit - Python Version
# 使用 Luhn 算法验证信用卡并识别类型

from cs50 import get_int


def luhn_check(card_str):
    """Luhn 算法验证信用卡校验和"""
    total = 0
    for i, digit in enumerate(reversed(card_str)):
        d = int(digit)
        if i % 2 == 1:  # 偶数位置（从右往左第2、4、6...位）
            d *= 2
            if d > 9:
                d -= 9  # 等价于 d // 10 + d % 10
        total += d
    return total % 10 == 0


def get_card_type(card_str):
    """根据长度和前缀识别卡片类型"""
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

