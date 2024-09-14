#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
    return 0;
}

int convert(string input)
{
    // TODO
    int num = 0;
    // Check for null character
    if (strcmp(input, "\0") == 0)
    {
        return 1;
    }

    else
    {
        // Converts last digit from string to int
        num = (input[strlen(input) - 1] - '0');
        // Remove last char from  string by moving the null character one position left.
        input[strlen(input) - 1] = '\0';
        // Return this value plus 10 times the integer value of the new *shortened string* which is convert(input)
        return num + 10 * convert(input);
    }
}