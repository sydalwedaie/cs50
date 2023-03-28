#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

bool is_delimiter(char character, char type);
int get_count(string text, char type);
int calc_index(int sentence_count, int word_count, int letter_count);

int main(void)
{
    string text = get_string("Text: ");

    int sentence_count = get_count(text, 's');
    int word_count = get_count(text, 'w');
    int letter_count = get_count(text, 'l');
    int index = calc_index(sentence_count, word_count, letter_count);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// get the boolean expression required to decide when to count based on the
// parameter we're counting
bool is_delimiter(char character, char type)
{
    switch (type)
    {
        case 's':
            return character == '.' || character == '!' || character == '?';
        case 'w':
            return isblank(character);
        case 'l':
            return isalpha(character);
        default:
            return false; // unused branch, but necessary to silence a warning
    }
}

// get the count for the parameter type we're counting
int get_count(string text, char type)
{
    int count = 0;
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        if (is_delimiter(text[i], type))
        {
            count++;
        }
    }
    // the word count is based on a space after the word, so the last one is
    // not counted in the for loop above. Here I manually increment the count.
    return type == 'w' ? count + 1 : count;
}

int calc_index(int sentence_count, int word_count, int letter_count)
{
    // type casting is necessary to get floating point results
    float L = (float) letter_count / (float) word_count * 100;
    float S = (float) sentence_count / (float) word_count * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    return round(index);
}
