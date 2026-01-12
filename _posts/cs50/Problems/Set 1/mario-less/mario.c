/*
 * mario.c
 *
 * CS50 Problem Set 1
 * Mario Less
 *
 * This program prompts the user for a height and prints a right-aligned
 * pyramid of hashes based on the height.
 * 
 * Example output for height 4:
 *    #
 *   ##
 *  ###
 * ####
 */
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    
    // 确保输入在1-8之间
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // 打印金字塔
    for (int i = 0; i < height; i++)
    {
        // 打印空格（右对齐）
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        
        // 打印#
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        
        // 换行
        printf("\n");
    }
    
    return 0;
}