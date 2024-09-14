#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Alocate memory space for each plate
        plates[idx] = malloc(strlen(buffer) + 1);

        // Save plate number in alocated space array
        for (int i = 0; i <= strlen(buffer); i++)
        {
            strcpy(plates[idx], buffer);
        }
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    idx = 0;

    for (int i = 0; i < 8; i++)
    {

        free(plates[idx]);
        idx++;
    }

    fclose(infile);
}
