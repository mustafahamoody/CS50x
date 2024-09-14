// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    // sets i to first value in array
    int m = array[0];
    // Checks each value in array to find the greatest
    for (int i = 0; i < n; i++)
    {
        if (array[i] > m)
        {
            // sets m to the greatest value so far
            m = array[i];
        }
    }
    // returns the greatest value
    return m;
}
