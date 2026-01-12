#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// Global variable
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Function prototypes
int compute_score(string);

// Main function
int main(void)
{
    // Prompt user enter word
    string word1 = get_string("Player1: ");
    string word2 = get_string("Player2: ");

    // Call the compute_score to compute the two score
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Compare the two score
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// compute_score definition
int compute_score(string word)
{
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
    }
    return score;
}
