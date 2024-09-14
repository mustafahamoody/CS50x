#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startNum;
    do
    {
        startNum = get_int("What's the starting population of llamas? ");
    }
    while (startNum < 9);

    // TODO: Prompt for end size
    int endNum;
    do
    {
        endNum = get_int("What's the ending population of llamas? ");
    }
    while (endNum < startNum);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (startNum < endNum)
    {
        startNum += ((startNum / 3) - (startNum / 4));
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}
