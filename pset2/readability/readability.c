#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string s, int n);
int count_words(string s, int n);
int count_sentences(string s, int n);

int main(void)
{
    string s = get_string("Text: ");
    int n = strlen(s);
    float L = ((float)count_letters(s, n) / count_words(s, n)) * 100;
    float S = ((float)count_sentences(s, n) / count_words(s, n)) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index > 1 && index <= 16)
    {
        printf("Grade %.0f\n", round(index));
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}

int count_letters(string s, int n)
{
    int letters = 0;
    for (int i = 0; i < n; i++)
    {
        if ((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string s, int n)
{
    int words = 1;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ' ')
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string s, int n)
{
    int sentences = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;
}
