from cs50 import get_string
import re


def main():
    text = get_string("Text: ")

    # get the number of characters ([a, z], [A-Z])
    num_letters = 0
    for i in range(len(text)):
        if text[i].isalpha():
            num_letters += 1

    # get the number of words (separated by spaces)
    num_words = len(text.split())

    # get the number of sentences (separated by '.', '!', '?')
    num_sentences = 0
    for i in range(len(text)):
        if text[i] in ['.', '!', '?']:
            num_sentences += 1
    # num_sentences = len(re.split('[.!?]', text))

    index = calculate_index(num_letters, num_words, num_sentences)

    print_grade(index)


def calculate_index(num_letters, num_words, num_sentences):
    # Calculate average number of letters per 100 words
    L = num_letters / num_words * 100

    # Calculate average number of sentences per 100 words
    S = num_sentences / num_words * 100

    # Calculate the index
    return round(0.0588 * L - 0.296 * S - 15.8)


def print_grade(index):
    if (index < 1):
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()