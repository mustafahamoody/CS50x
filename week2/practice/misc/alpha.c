#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{   // Gets usr input
    string str = get_string("Enter String: ");
    // gets # char in user input
    int len = strlen(str);


    for (int i = 0; i < len - 1; i++)
    {   // Checks if not in alpabetical order
        if (str[i] > str[i + 1])
        {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
    return 0;
}