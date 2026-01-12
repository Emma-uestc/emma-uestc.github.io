/*
 * cash.c
 *
 * CS50 Problem Set 1
 * Cash - Greedy Algorithm
 *
 * This program calculates the minimum number of coins needed
 * to make change using US coins: 25¢, 10¢, 5¢, and 1¢.
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