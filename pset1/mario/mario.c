#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h, i, j;
    do                                  //valid input acception
    {
        h = get_int("Height?");
    }
    while (h < 1 || h > 8);

    for (i = 1; i <= h; i++)                 //rows
    {
        for (j = 1 ; j <= h - i ; j++)           //columns blank spaces
        {
            printf(" ");
        }

        for (j = h - i + 1 ; j <= h ; j++)         //columns first half pyramid
        {
            printf("#");
        }

        printf("  ");                   //columns void spaces

        for (j = h + 3 ; j <= h + 2 + i ; j++)       //columns second half pyramid
        {
            printf("#");
        }

        printf("\n");

    }
    return 0;
}