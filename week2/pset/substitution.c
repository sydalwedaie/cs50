/*
Get key as CLA
    check arg present
    print usage example
    case insensetive
Validate key
    check 26 char long
    check only alpha
    check no repeated char
    print rule
Get plaintext
    print "plaintext: <input>"
Encipher
    get the mapped char
    preserve case
    ignor non-alpah char
Print ciphertext
    print "ciphertext: <output>"

*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool has_repeated_char(string text);
bool has_non_alpha(string text);
bool is_valid_key(string key);
string encipher(string plaintext, string key);

int main(int argc, string argv[])
{
    string key = argv[1];
    // check if argument was supplied
    if (argc != 2)
    {
        printf("Usage: %s KEY\n", argv[0]);
        return 1;
    }
    else if (is_valid_key(key))
    {
        string plaintext = get_string("plaintext: ");
        string ciphertext = encipher(plaintext, key);

        printf("ciphertext: %s\n", ciphertext);
    }
    else
    {
        return 1;
    }
}

bool has_repeated_char(string text)
{
    int text_len = strlen(text);
    // array of counters for each char of alphabet
    // must be initialized to zero, otherwise won't work
    int char_count[26] = {0};

    // loop over each character of supplied text
    for (int i = 0; i < text_len; i++)
    {
        char current_char = tolower(text[i]);
        // get the alphabatical index of the current character
        //int char_index = char_count[current_char - 97];
        // if the counter for current char is 1, it has been seen before,
        // otherwise increment it by one.
        if (char_count[current_char - 'a'] == 1)
        {
            return true;
        }
        else
        {
            char_count[current_char - 'a']++;
        }
    }
    return false;
}

bool has_non_alpha(string text)
{
    int text_len = strlen(text);
    for (int i = 0; i < text_len; i++)
    {
        if (!isalpha(text[i]))
        {
            return true;
        }
    }
    return false;
}

bool is_valid_key(string key)
{
    int key_len = strlen(key);

    if (key_len != 26)
    {
        printf("Key must be 26 char long\n");
        return false;
    }
    else if (has_repeated_char(key))
    {
        printf("key must not have repeated key\n");
        return false;
    }
    else if (has_non_alpha(key))
    {
        printf("key must not have non-alpha\n");
        return false;
    }
    return true;
}

string encipher(string plaintext, string key)
{
    int plaintext_len = strlen(plaintext);

    for (int i = 0; i < plaintext_len; i++)
    {
        char cipher_char;
        char current_char = plaintext[i];

        if (islower(current_char))
        {
            cipher_char = toupper(key[current_char - 'a']);
            plaintext[i] = cipher_char + 32;
        }
        else if ((isupper(current_char)))
        {
            cipher_char = toupper(key[current_char - 'A']);
            plaintext[i] = cipher_char;
        }
    }
    return plaintext;
}