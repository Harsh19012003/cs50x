#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Function declaration of computing score
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)    //score1 > score2
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)   //score1 < score2
    {
        printf("Player 2 wins!");
    }
    else    //score1 = score2
    {
        printf("Tie");
    }
}

// Function defination of computing score
int compute_score(string word)
{
    int z, score = 0;
    int l = strlen(word);
    for (int i = 0; i <= l; i++)      // TODO: Compute and return score for string
    {
        int v = isalpha(word[i]);
        if (v == 0)
        {
            score = score + 0;
        }
        else
        {
            int n = isupper(word[i]);
            if (n == 0)
            {
                z = word[i] - 97;
                score = score + POINTS[z];
            }
            else
            {
                z = word[i] - 65;
                score = score + POINTS[z];
            }
        }
    }
    printf("%i  \n", score);
    return score;
}