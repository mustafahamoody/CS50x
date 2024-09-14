#include <cs50.h>
#include <stdio.h>

int getHeight(void);
void pyramid(int height);


int main(void)
{

    pyramid(getHeight());

}

// Function to return height of pyramid
int getHeight(void)
{
    // Checks that user input is a valid number
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    return h;
}

// Function to make pyramid acording to height
void pyramid(int height)
{
    // Prints row of blocks acording to height and increments blocks printed on leaft and right, each itteration
    for (int n = 1; n <= height; n++)
    {
        // Print space on left = to height - 1
        for (int s = height - n; s > 0; s--)
        {
            printf(" ");
        }

        // Print blocks on left (variable)
        for (int i = 0; i < n; i++)
        {
            printf("#");
        }

        // Print space in between blocks (costant)
        printf("  ");

        // Print blocks on right (variable)
        for (int j = 0; j < n; j++)
        {
            printf("#");
        }
        //Goes to newline after row is finished
        printf("\n");

    }
}