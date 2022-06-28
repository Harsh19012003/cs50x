#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int k;
    // Exactly two command line arguments
    if (argc != 2)
    {
        // Usage
        printf("./caesar key");
        return 1;
    }
    else
    {
        if (isdigit(*argv[1]))
        {
            printf("success.The key is %s", argv[1]);
        }
        else
        {
            printf("./caesar key");
            return 1;
        }
    }
    printf("Key is: %s\n", argv[1]);

    // Converting string key to integer
    k = atoi(argv[1]);

    // User input text to be encrypted
    string pt = get_string("planintext: ");
    int l = strlen(pt);
    char ct[100];

    // Loop through all characers of string
    for (int i = 0; i <= l; i++)
    {
        if (isalpha(pt[i]))     // Character is an Alphabet
        {
            if (isupper(pt[i]))     // Character is an Uppercase letter
            {
                if ((pt[i] + k) > 90)
                {
                    if ((pt[i] + k) < 116)
                    {
                        ct[i] = 64 + (pt[i] + k - 90);
                    }
                    else
                    {
                        if ((pt[i] + k) < 142)
                        {
                            ct[i] = 64 + (pt[i] + k - 116);
                        }
                        else
                        {
                            ct[i] = 64 + (pt[i] + k - 142);
                        }
                    }
                }
                else
                {
                    ct[i] = pt[i] + k;
                }
            }
            else    // Character is an Lowercase letter
            {
                if ((pt[i] + k) > 122)
                {
                    if ((pt[i] + k) < 148)
                    {
                        ct[i] = 96 + (pt[i] + k - 122);
                    }
                    else
                    {
                        if ((pt[i] + k) < 174)
                        {
                            ct[i] = 96 + (pt[i] + k - 148);
                        }
                        else
                        {
                            ct[i] = 96 + (pt[i] + k - 174);
                        }
                    }
                }
                else
                {
                    ct[i] = pt[i] + k;
                }
            }
        }
        else    // character is not an alphabet
        {
            ct[i] = pt[i];
        }
    }

    // Display encrypted text as output
    printf("ciphertext: %s\n", ct);
    return 0;
}
