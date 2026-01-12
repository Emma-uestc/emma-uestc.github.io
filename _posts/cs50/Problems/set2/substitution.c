#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
bool is_valid_key(string);
char substitute(char, string);

// Main function
int main(int argc, string argv[])
{
    // Check 1, the number of command-line arguments must be 2
    if (argc != 2)
    {
        printf("Usge: ./substitution key\n");
        return 1;
    }
    // Check 2, the key must just contain 26 unique letters
    if (!is_valid_key(argv[1]))
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    // Get the key
    string key = argv[1];
    // Prompt ueser enter plaintext
    string plaintext = get_string("Plaintext: ");
    // Ciphertext
    printf("Ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char encrypted = substitute(plaintext[i], key);
        printf("%c", encrypted);
    }
    printf("\n");
}

// is_valid_key definition
bool is_valid_key(string s)
{
    int len = strlen(s);
    if (len != 26)
    {
        return false;
    }
    // using a boolen array as the flag to record if the letter has been seen before
    bool letter_seen[26] = {false};
    for (int i =0; i < len; i++)
    {
        char c = toupper(s[i]);
        if (!isalpha(c))
        {
            return false;
        }
        if (letter_seen[c - 'A'])
        {
            return false;
        }
        letter_seen[c - 'A'] = true;
    }
    return true;
}

// substitute
char substitute(char c, string key)
{
    if (isupper(c))
    {
        return toupper(key[c - 'A']);
    }
    else if (islower(c))
    {
        return tolower(key[c - 'a']);
    }
    else
    {
        return c;
    }
}
