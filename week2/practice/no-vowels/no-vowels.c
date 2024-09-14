// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string word);

int main(int argc, string argv[])
{
    // only accept a single command-line argument
    if (argc != 2)
    {
        printf("please enter one word\n");
        return 1;
    }

    // runs the replace function and prints the moddified word
    printf("%s\n", replace(argv[1]));

}


string replace(string word)
{
    string new = "";
    for (int i = 0; word[i] != '\0'; i++)
    {
        // replaces the following vowels to numbers
        switch (word[i])
        {
            case 'a':
                word[i] = '6';
                break;

            case 'e':
                word[i] = '3';
                break;

            case 'i':
                word[i] = '1';
                break;

            case 'o':
                word[i] = '0';
                break;
        }
    }
    // returns the new word
    return word;
}