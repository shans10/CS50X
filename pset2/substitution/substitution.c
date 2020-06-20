#include <stdio.h>
#include <cs50.h>
#include <string.h> // For using strlen function.
#include <ctype.h> // For using isupper/islower and toupper/tolower functions.

int main(int argc, string argv[])
{
    // Verifying if user has input 2 arguments(including ./substitution) or not.
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Checking the length of key(Accept if 26).
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Checking if key is as per requirement or not..
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // Checking if key contains any character beside uppercase or lowercase letters.
        if (argv[1][i] < 65 || (argv[1][i] > 90 && argv[1][i] < 97) || argv[1][i] > 122)
        {
            printf("Invalid Key!\n");
            return 1;
        }
        for (int j = i + 1; j < n; j++)
        {
            // Checking key for any repeated values.
            if (argv[1][i] == argv[1][j])
            {
                printf("Key has repeated values. Invalid!\n");
                return 1;
            }
        }
    }
    // Getting plaintext input from user.
    string s = get_string("plaintext: ");
    // Creating ciphertext.
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Checking if plaintext char is uppercase. If yes then it is substituted by corresponding uppercase letter from key.
        if (isupper(s[i]))
        {
            int j = s[i] - 65;
            s[i] = toupper(argv[1][j]);
        }
        // Checking if plaintext char is lowercase. If yes then it is substituted by corresponding lowercase letter from key.
        else if (islower(s[i]))
        {
            int j = s[i] - 97;
            s[i] = tolower(argv[1][j]);
        }
    }
    // Printing the generated ciphertext.
    printf("ciphertext: %s\n", s);
}
