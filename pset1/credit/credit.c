#include <stdio.h>
#include <cs50.h>
// For using strlen() function.
#include <string.h>

// Prototype of a function luhn that applies Luhn's Algorithm.
int luhn(string c);

int main(void)
{
    int n, flag = 0;
    string c;
    // This do-while loop prompts user for a valid number which comprises of only digits 0-9.
    do
    {
        c = get_string("Number: ");
        n = strlen(c);
        for (int i = 0; i < n; i++)
        {
            // Rejecting all char symbols other than digits 0-9.
            if (c[i] < 48 || c[i] > 57)
            {
                flag = 0;
                break;
            }
            else
            {
                flag = 1;
            }
        }
    }
    while (flag == 0);
    // Printing "INVALID" for all credit card number which do not satisfy the given size constraints.
    if (n < 13 || n > 16)
    {
        printf("INVALID\n");
    }
    // Checking for AMEX card.
    else if (n == 15)
    {
        if (c[0] == '3' && (c[1] == '4' || c[1] == '7'))
        {
            int v = luhn(c);
            if (v == 1)
            {
                printf("AMEX\n");
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
    }
    else if (n == 16)
    {
        // Checking for MASTERCARD.
        if (c[0] == '5' && (c[1] == '1' || c[1] == '2' || c[1] == '3' || c[1] == '4' || c[1] == '5'))
        {
            int v = luhn(c);
            if (v == 1)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // Checking for VISA card with 16 digit number.
        else if (c[0] == '4')
        {
            int v = luhn(c);
            if (v == 1)
            {
                printf("VISA\n");
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
    }
    // Checking for VISA card with 13 digit number.
    else if (n == 13)
    {
        if (c[0] == '4')
        {
            int v = luhn(c);
            if (v == 1)
            {
                printf("VISA\n");
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
    }
}

// Function to implement Luhn's Algorithm on a credit card number which passes all other checks.
int luhn(string c)
{
    int n = strlen(c);
    int a[8], b[8];
    int j = 0, k = 0;
    int sum = 0;
    // Converting every other char of credit card number starting from last second into int and storing it into an int array.
    for (int i = n - 2; i >= 0; i -= 2)
    {
        a[j] = c[i] - '0';
        j++;
    }
    // Converting every other char of credit card number starting from last into int and storing it into an int array.
    for (int i = n - 1; i >= 0; i -= 2)
    {
        b[k] = c[i] - '0';
        k++;
    }
    for (int i = 0; i < 8; i++)
    {
        // Multiplying every other number by 2 starting from last second.
        a[i] *= 2;
        // Adding the digits of doubled numbers as well as adding remaining numbers.
        sum = sum + a[i] / 10 + a[i] % 10 + b[i];
    }
    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
