#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n1, n2;
    int x = 0;

    do
    {
        n1 = get_float("Enter starting population: ");            // TODO: Prompt for start size
    }
    while (n1 < 9);

    do
    {
        n2 = get_float("Enter ending poopulatin: ");             // TODO: Prompt for end size
    }
    while (n2 < n1);

    while (n1 < n2)
    {
        n1 = n1 + n1 / 3 - n1 / 4;      // TODO: Calculate number of years until we reach threshold
        x++;
    }

    printf("Years: %i \n", x);  // TODO: Print number of years
    return 0;
}