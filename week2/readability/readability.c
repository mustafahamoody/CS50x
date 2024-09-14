/*
References
C isalpha() - C Standard Library. (n.d.). Programiz. Retrieved August 4, 2023, from
    https://www.programiz.com/c-programming/library-function/ctype.h/isalpha
*/

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Gets text from user
    string text = get_string("Text: ");

    // printf("%i letters\n", count_letters(text));
    // printf("%i words\n", count_words(text));
    // printf("%i sentences\n", count_sentences(text));

    // Finds # letters
    float letters = count_letters(text);
    // Finds # words
    float words = count_words(text);
    // Finds # sentences
    float sentences = count_sentences(text);

    // Finds letters / 100 words
    float L = (letters / words) * 100;
    // printf("%f\n", L);

    // Finds sentences / 100 words
    float S = (sentences / words) * 100;
    // printf("%f\n", S);

    // plugs calculated value into Coleman-Liau index to determain grade level of text
    float index = 0.0588 * L - 0.296 * S - 15.8;
    // printf("%f\n", index);

    if (index < 1)
    {
        string grade = "Before Grade 1";
        printf("%s\n", grade);
    }

    else if (index > 16)
    {
        string grade = "Grade 16+";
        printf("%s\n", grade);
    }

    else
    {
        int grade = (round(index));
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int L = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            L++;
        }
    }

    return L;
}

int count_words(string text)
{
    // Starts at 1 to account for missing space character in last word
    int W = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            W++;
        }
    }

    return W;
}

int count_sentences(string text)
{
    int S = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            S++;
        }
    }

    return S;
}