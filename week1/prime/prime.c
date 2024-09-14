#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

// Function to check for prime numbers
bool prime(int number)
{
    // runs loop while n is less then number
    for (int n = 2; n < number; n++)
    {
        // If number divided by n gives a remainder, exits loop and returns false
        if (number % n == 0)
        {
            return false;
        }
    }
    // If number greater then 1 returns true
    if (number > 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
