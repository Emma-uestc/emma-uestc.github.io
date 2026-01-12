#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function Prototypes
bool only_digits(string);
char rotate(char, int);

// Main function
int main(int argc, string argv[])
{
    // Check 1, the number of command-line arguments must be 2
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Check 2, command-line argument must be digit
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert string to int for the key
    int key = atoi(argv[1]);
    // Prompt user enter Plaintext
    string plaintext = get_string("Plaintext: ");
    // Ciphertext
    printf("Ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char encrypted = rotate(plaintext[i], key);
        printf("%c", encrypted);
    }
    printf("\n");
}

// only_digits definition
bool only_digits(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int key)
{
    if (isupper(c))
    {
        int position = (c - 'A' + key) % 26;
        return position + 'A';
    }
    else if (islower(c))
    {
        int position = (c - 'a' + key) % 26;
        return position + 'a';
    }
    else
    {
        return c;
    }
}
