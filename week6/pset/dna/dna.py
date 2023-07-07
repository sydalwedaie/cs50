import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python DATABASE SEQUENCE")

    # Read database file into a variable
    database_list = []
    with open(sys.argv[1]) as file:
        file_reader = csv.DictReader(file)
        for row in file_reader:
            database_list.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence #
    #   load the list of STRs
    database_first_row = database_list[0]
    database_keys = dict(database_first_row).keys()
    STR_list = list(database_keys)[1:]

    #   load the STR counts of the sequence
    STR_counts = {}
    for STR in STR_list:
        STR_counts[STR] = longest_match(sequence, STR)

    # Check database for matching profiles #
    """ For each person in the database, we'll iterate over the list of STRs.
        Any time a match is found, we'll update the match_count.
        If the count equals the number of STRs, that means that person's entire
        STR matches the sequence.
        We'll return immediately to prevent "No match" from printing.
    """
    for person in database_list:
        match_count = 0
        for STR in STR_list:
            if int(person[STR]) == STR_counts[STR]:
                match_count += 1

        if match_count == len(STR_list):
            print(person['name'])
            return

    print("No match")

# This function was given
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
