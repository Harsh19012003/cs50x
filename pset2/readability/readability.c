#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <math.h>

float count_letters(string t, int l);
float count_words(string t, int l);
float count_sentences(string t, int l);

int main(void)
{
    // Input from user
    string text = get_string("Text: ");
    int length = strlen(text);

    // Variables declaration
    float letters, words, sentences;

    letters = count_letters(text, length);
    words = count_words(text, length);
    sentences = count_sentences(text, length);

    double L, S;
    int grade;
    L = (letters * 100) / words;
    S = (sentences * 100) / words;
    printf("L %f and S %f", L, S);

    grade = round(0.0588 * L - 0.296 * S - 15.8);

    // Outputting grade exaactly inbetween 1 to 16
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Sentence counter fuction
float count_sentences(string t, int l)
{
    int no = 0;
    for (int i = 0; i < l; i++)
    {
        if (t[i] == '.' || t[i] == '?' || t[i] == '!'/* || t[i] == ':'*/)
        {
            no++;
        }
    }
    printf("sentence(s) %d \n", no);
    return no;
}

// Words counter function
float count_words(string t, int l)
{
    int no = 0;
    for (int i = 0; i < l - 1; i++)                       // i less than l tha maine i lessthan equal to l kiya.
    {
        if (t[i] == ' ' || t[i] == '!' || t[i] == '?' || (t[l] == '.' && t[i + 1] != ' '))
        {
            no++;
        }
    }
    printf("word(s) %d \n", no + 1);
    return no + 1;
}

// Letter counter function
float count_letters(string t, int l)
{
    int no = 0;
    for (int i = 0; i < l; i++)
    {
        if (isalpha(t[i]))
        {
            no++;
        }
    }
    printf("letter(s) %d \n", no);
    return no;
}