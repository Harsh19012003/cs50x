#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    //checking valid command line arguments
    if (argc != 2)
    {
        printf("Usage: Enter one command line argument.");
        return 1;
    }

    //open a memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open a file.");
        return 2;
    }

    //define BYTE
    typedef uint8_t BYTE;
    BYTE block[512];
    int counter = 0;
    bool isjpg = false;
    //mallock for filename array
    char *newfilename = malloc(50);
    int bytesRead;
    //file pointer named jpg
    FILE *jpg;
    bool islastjpg = false;

    //indefinite loop
    while (true)
    {
        //read a chunk of memory from card to buffer named block
        bytesRead = fread(block, 1, 512, card);
        if (bytesRead != 512)
        {
            break;
        }

        //if start of jpg.
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            isjpg = true;
            counter++;
        }
        else
        {
            isjpg = false;
        }

        if (isjpg == true)
        {
            //if start of first jpg.
            if (counter == 1)
            {
                sprintf(newfilename, "%03i.jpg", counter - 1);
                jpg = fopen(newfilename, "w");
                if (jpg == NULL)
                {
                    printf("Could not open a file.");
                    return 2;
                }

                fwrite(block, 1, 512, jpg);
            }
            //not first jpg.
            else
            {
                fclose(jpg);
                sprintf(newfilename, "%03i.jpg", counter - 1);
                jpg = fopen(newfilename, "w");
                if (jpg == NULL)
                {
                    printf("Could not open a file.");
                    return 2;
                }

                fwrite(block, 1, 512, jpg);
            }
        }
        //if is not a jpg block.
        else
        {
            if (counter >= 1)
            {
                fwrite(block, 1, 512, jpg);
            }
        }
    }

    //free up space of used malloc.
    free(newfilename);

    return 0;
}
