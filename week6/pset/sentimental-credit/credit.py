from cs50 import get_int


def main():
    # Prompt for input
    card_number = get_int("Number: ")

    # Calculate checksum
    is_valid_checksum = calculate_checksum(card_number) % 10 == 0

    # Check card length
    digit_count = get_digit_count(card_number)

    # Check starting digits
    first_digit = get_nth_digit(card_number, 1)
    second_digit = get_nth_digit(card_number, 2)

    # Print results
    if not is_valid_checksum:
        print("INVALID")
        return

    if digit_count == 15 and first_digit == 3 and (second_digit in [4, 7]):
        print("AMEX")
    elif digit_count == 16 and first_digit == 5 and (second_digit in [1, 2, 3, 4, 5]):
        print("MASTERCARD")
    elif digit_count in [13, 16] and first_digit == 4:
        print("VISA")
    else:
        print("INVALID")


def get_digit_count(number):
    count = 0

    while number > 1:
        count += 1
        number /= 10

    return count


def get_nth_digit(number, nth):
    digit_count = get_digit_count(number)
    return int(number / 10 ** (digit_count - nth)) % 10


def calculate_checksum(number):
    checksum = 0
    digit_count = get_digit_count(number)

    for i in range(0, digit_count):
        current_digit = get_nth_digit(number, digit_count - i)

        # multiply digits in odd places by two
        if (i % 2 == 1):
            current_digit *= 2

        # if the product itself has two digits, add the individual digits
        if (current_digit > 9):
            checksum += (int(current_digit / 10) + int(current_digit % 10))
        # otherwise jsut add the product
        else:
            checksum += current_digit

    print(checksum)
    return checksum


if __name__ == "__main__":
    main()