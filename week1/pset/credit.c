#include <cs50.h>
#include <stdio.h>

int count_digits(long number);
int get_nth_digit(long number, int nth);
int calc_checksum(long number);
string get_type(long number);

int main(void)
{
    // Prompt for input.
    long card_number = get_long("Enter card number: ");

    // Calculate checksum and store validity as a boolean
    int checksum = calc_checksum(card_number);
    bool is_valid_checksum = checksum % 10 == 0;

    // Check for card type
    string card_type = get_type(card_number);

    // Print AMEX, MASTERCARD, VISA, or INVALID.
    // The right branch runs if the checksum was invalid, so get_type never runs
    is_valid_checksum ? printf("%s\n", card_type) : printf("INVALID\n");
}

// Helper function; returns the number of digits
int count_digits(long number)
{
    int count = 0;
    do
    {
        count++;
        number /= 10;
    }
    while (number > 0);
    return count;
}

// Helper function; returns the nth digit from the left.
// nth = 1 refers to first digit
int get_nth_digit(long number, int nth)
{
    int digit_count = count_digits(number);

    // repeatedly divide the number by 10 until the nth digit
    for (int i = 0; i < digit_count - nth; i++)
    {
        number /= 10;
    }
    return number % 10;
}

// Auxillary function: calculates a card's checksum based on Luhn’s Algorithm
int calc_checksum(long number)
{
    int checksum = 0;
    int digit_count = count_digits(number);

    for (int i = 0; i < digit_count; i++)
    {
        // Start from the last digit (rightmost)
        // (digit_count - i) counts from the end
        int current_digit = get_nth_digit(number, (digit_count - i));

        // Digits in odd places are multiplied by 2
        if (i % 2 == 1)
        {
            current_digit *= 2;
        }

        // Add current_digit to checksum, but make sure to add the individual
        // Digits if it's a 2 digit number.
        if (current_digit > 9)
        {
            checksum += (current_digit % 10) + (current_digit / 10);
        }
        else
        {
            checksum += current_digit;
        }
    }

    return checksum;
}

// Auxillary function; returns a string denoting a card's type, or INVALID
string get_type(long number)
{
    int digit_count = count_digits(number);
    int first_digit = get_nth_digit(number, 1);
    int second_digit = get_nth_digit(number, 2);

    // store matching criteria as boolean values
    bool is_amex = digit_count == 15 && first_digit == 3 &&
                   (second_digit == 4 || second_digit == 7);
    bool is_mastercard = digit_count == 16 && first_digit == 5 &&
                         second_digit > 0 && second_digit < 6;
    bool is_visa = (digit_count == 13 || digit_count == 16) && first_digit == 4;

    if (is_amex)
    {
        return "AMEX";
    }
    else if (is_mastercard)
    {
        return "MASTERCARD";
    }
    else if (is_visa)
    {
        return "VISA";
    }
    // this branch runs if the checksum is valid but card type was invalid
    else
    {
        return "INVALID";
    }
}
