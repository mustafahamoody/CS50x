#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

string lower(string word);
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Converts input to lowercase
    word1 = lower(word1);
    word2 = lower(word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    if (score1 == score2)
    {
        printf("Tie!\n");
    }

    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
}

// Converts word to lowercase
string lower(string word)
{
    for (int n = 0; word[n] != '\0'; n++)
    {
        word[n] = tolower(word[n]);
    }

    return word;
}


int compute_score(string word)
{
    // TODO: Compute and return score for string
    int p = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // 1 point letters
        if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'l' || word[i] == 'n' || word[i] == 'o' || word[i] == 'r'
            || word[i] == 's' || word[i] == 't' || word[i] == 'u')
        {
            p += 1;
        }

        // 2 point letters
        else if (word[i] == 'd' || word[i] == 'g')
        {
            p += 2;
        }

        // 3 point letters
        else if (word[i] == 'b' || word[i] == 'c' || word[i] == 'm' || word[i] == 'p')
        {
            p += 3;
        }

        // 4 point letters
        else if (word[i] == 'f' || word[i] == 'h' || word[i] == 'v' || word[i] == 'w' || word[i] == 'y')
        {
            p += 4;
        }

        // 5 point letters
        else if (word[i] == 'k')
        {
            p += 5;
        }

        // 8 point letters
        else if (word[i] == 'j' || word[i] == 'x')
        {
            p += 8;
        }

        // 10 point letters
        else if (word[i] == 'q' || word[i] == 'z')
        {
            p += 10;
        }
    }

    return p;
}
