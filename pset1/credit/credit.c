#include <stdio.h>
#include <cs50.h>

// Function declarations
int d(long long n, int l);
bool validity1(int l);
bool validity2(long long n, int l);


int main(void)
{
    // Variable declaration
    int length, digit = 0;

    // User input card number
    long long number = get_long_long("Enter credit card number\n");     //input
    printf("\n");
    long long n = number;
    bool v1, v2;

    // Calculating length of card number
    for (length = 0; n > 0; length++)                           //length
    {
        n = n / 10;
    }
    printf("the length is %i \n", length);

    // Initial digits calculator
    int digits = d(number, length);                                 //first digits

    printf("the first digits are: %i \n", digits);

    // Validity length
    v1 = validity1(length);                                    //validity1

    if (v1 == 1)
    {
        // Validity of formula
        v2 = validity2(number, length);                        //validity2
        if (v2 == 1)
        {
            printf("checked\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }

    // Amex
    if (length == 15)
    {
        if (digits == 34 || digits == 37)
        {
            printf("AMEX\n");
        }
    }



    if (v1 == 1 && v2 == 1)
    {
        if (length == 13)
        {
            // Visa
            digit = digits / 10;
            if (digit == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        else if (length == 16)
        {
            digit = digits / 10;
            // Mastercard
            if (digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55)
            {
                printf("MASTERCARD\n");
            }
            // Visa
            else if (digit == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");

            }
        }
    }


    return 0;
}







int d(long long n, int l)                                        //first digits
{
    for (int i = 0; i < n / (l - 2); i++)
    {
        n = n / 10;
    }
    return n;
}

// Validity length
bool validity1(int l)                                           //validity1 function
{
    if (l == 13 || l == 15 || l == 16)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Validity formula
bool validity2(long long n, int l)                              //validity2 function
{
    int sum = 0;
    long long a, a1, a2;
    long long b, b1, b2;
    if (l % 2 != 0)                 //for odd
    {

        for (int i = 0; i <= l / 2; i++)
        {
            a = n % 10;
            if (a < 5)
            {
                a = 2 * a;
            }
            else
            {
                a = 2 * a;
                a1 = a % 10;
                a = a / 10;
                a2 = a % 10;
                a = a1 + a2;
            }
            n = n / 10;
            b = n % 10;
            sum = sum + a + b;
            n = n / 10;
        }
    }

    else                                                    //for even
    {
        for (int i = 0; i < l / 2; i++)
        {
            a = n % 10;
            n = n / 10;
            b = n % 10;
            if (b < 5)
            {
                b = 2 * b;
            }
            else
            {
                b = 2 * b;
                b1 = b % 10;
                b = b / 10;
                b2 = b % 10;
                b = b1 + b2;
            }
            sum = sum + a + b;
            n = n / 10;
        }
    }
    printf("the sum is %i\n", sum);

    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}