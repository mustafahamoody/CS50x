#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Checks proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Opens file
    FILE *raw = fopen(argv[1], "r");

    // Create space in memory for file
    FILE *image = NULL;

    // Returns 1 if file could not be opened
    if (raw == NULL)
    {
        printf("could not open file\n");
        return 1;
    }

    // Define block size
    int blockSize = 512;

    // Creates a buffer for fread
    BYTE buffer[blockSize];

    // Creates a space for filename from sprintf
    char filename[8];
    int fnum = 0;

    // Bool to check if first jpg has been found yet
    int foundJpg = 0;

    while (fread(buffer, 1, blockSize, raw) == blockSize)
    {
        // If start of new jpg
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // If first jpg is found
            if (foundJpg == 0)
            {
                // set found jpg to true
                foundJpg = 1;

                // Create a file name called 000.jpg
                sprintf(filename, "%03i.jpg", fnum);
                // create a file called "filename"
                image = fopen(filename, "w");

                // Returns 1 if file could not be opened
                if (image == NULL)
                {
                    printf("could not open file\n");
                    return 1;
                }

                // Writes jpg contents to file
                fwrite(buffer, 1, blockSize, image);
                fnum++;
            }

            // If subsequent jpg has been found
            else
            {
                // Closes last file
                fclose(image);

                // Create a file name called "filenum".jpg
                sprintf(filename, "%03i.jpg", fnum);

                // create a file called "filename"
                image = fopen(filename, "w");

                // Returns 1 if file could not be opened
                if (image == NULL)
                {
                    printf("could not open file\n");
                    return 1;
                }

                // Writes jpg contents to file
                fwrite(buffer, 1, blockSize, image);
                fnum++;
            }
        }

        // Else if didn't yet find subsequent jpg
        else if (foundJpg != 0)
        {
            // Continue writing from current jpg
            fwrite(buffer, 1, blockSize, image);
        }
    }

    // Close files
    fclose(image);
    fclose(raw);
}
