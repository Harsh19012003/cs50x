#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Enter your name.");           //user input
    printf("hello, %s.\n", name);                           //console output
}