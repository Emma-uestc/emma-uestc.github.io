#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Function prototypes
int count_letters(string);
int count_words(string);
int count_sentences(string);

// Main function
int main(void)
{
    // Prompt user enter text
    string text = get_string("Text: ");
    // Call functions to compute letters, words, sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute L,S and index
    float L = (float)letters / (float)words * 100;
    float S = (float)sentences / (float)words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    //  round the result to the nearest whole number
    int grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// functions:
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
        count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 0;
    bool in_word = false;
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        if (text[i] != ' ' && !in_word)
        {
            count++;
            in_word = true;
        }
        else if (text[i] == ' ')
        {
            in_word = false;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
    }
    return count;
}

