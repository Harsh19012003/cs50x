#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Mallocing memory for header
    uint8_t *header = malloc(HEADER_SIZE);
    if (header ==  NULL)
    {
        return 1;
    }

    // Ensuring correct usage
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Opening a file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    float factor = atof(argv[3]);

    // Read from input file and write to output file
    fread(header, 44, 1, input);
    fwrite(header, 44, 1, output);

    int16_t sample;
    // Loop to multiply volume with given factor
    while (fread(&sample, 2, 1, input))
    {
        sample = sample * factor;
        fwrite(&sample, 2, 1, output);
    }

    // Free allocated memory
    free(header);
    fclose(input);
    fclose(output);
}