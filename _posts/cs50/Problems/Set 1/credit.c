/*
 * credit.c
 *
 * CS50 Problem Set 1
 * Credit - Card Validation
 *
 * This program validates credit card numbers using Luhn's Algorithm
 * and identifies the card type (VISA, MASTERCARD, or AMEX).
 *
 * Card specifications:
 * - AMEX:       15 digits, starts with 34 or 37
 * - MASTERCARD: 16 digits, starts with 51-55
 * - VISA:       13 or 16 digits, starts with 4
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
    // 从右往左，偶数位置的数字乘2，所有数字相加
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
            // 例如：7×2=14 → 1+4=5
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
