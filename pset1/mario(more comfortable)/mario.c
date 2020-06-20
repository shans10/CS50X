#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    // Initailizing the variable to 0 so that do-while executes atleast once.
    int h = 0;

    // do-while reprompts user to enter the height as long as its not within range. 
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    // This for loop is for changing the line at each iteration.
    for (int i = 0; i < h; i++)
    {
        // This for loop prints the spaces at the beginning of pyramid at each line.
        for (int j = h - (i + 1); j > 0; j--)
        {
            printf(" ");
        }
        // This for loop prints the first set of hashes.   
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // This statements prints spaces equal to hashes in between.
        printf("  ");

        // This for loop prints the last set of hashes at each line. 
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // This printf is used to change the line after every iteration.
        printf("\n");
    }
}
