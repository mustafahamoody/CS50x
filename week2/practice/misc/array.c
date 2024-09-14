#include <cs50.h>
#include <stdio.h>

int main(void)
{   //Gets length of array from user
    int len;
    do
    {
        len = get_int("Length: ");
    }
    while (len <= 0);

    int array[len];
    array[0] = 1;
    for (int i = 1; i < len; i++)
    {
        //Multiplies previous number in array by 2
        array[i] = 2 * (array[i-1]);
        printf("%i\n", array[i]);
    }
}