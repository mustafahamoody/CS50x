#include <cs50.h>
#include <stdio.h>

// Takes user name as command line argument
int main(int argc, string argv[])
{
    for (int i = 1; i < argc; i++)
    {   //Prints initials
        printf("%c.", argv[i][0]);
    }
    printf("\n");
}