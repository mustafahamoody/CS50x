/*
References
C library function - fseek(). (n.d.). Tutorialspoint. Retrieved July 26, 2023, from https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm
C library function - ftell(). (n.d.). Tutorialspoint. Retrieved July 26, 2023, from https://www.tutorialspoint.com/c_standard_library/c_function_ftell.htm
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");

    // Check file was opened properly
    if (input == NULL)
    {
        printf("Failed to open file");
        return 1;
    }

    // Read header
    // TODO #3
    // Variable head to store header format
    WAVHEADER head;

    fread(&head, 1, 44, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(head) == 0)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");

    // Check file was opened properly
    if (output == NULL)
    {
        printf("Failed to open file");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&head, 1, 44, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(head);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[blockSize];
    long endOfFile = 352844;
    int endOfHeader = 44;

    // Sets pointer to end of file
    fseek(input, endOfFile - blockSize, SEEK_SET);

    // Check that file stops before reading header
    while (ftell(input) >= endOfHeader)
    {
        // Reads the file
        fread(buffer, 1, blockSize, input);

        // Writes to new file
        fwrite(buffer, 1, blockSize, output);

        // Sets pointer 2 blocks back
        fseek(input, -2 * blockSize, SEEK_CUR);
    }

    // Closes the files
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == (BYTE) 'W' && header.format[1] == (BYTE) 'A' && header.format[2] == (BYTE) 'V' &&
        header.format[3] == (BYTE) 'E')
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}