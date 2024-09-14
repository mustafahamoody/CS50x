"""
References
rituraj_jain. (2023, March 16). Iterate over a dictionary in Python. GeeksforGeeks. Retrieved August 4, 2023, from https://www.geeksforgeeks.org/iterate-over-a-dictionary-in-python/
user3194712. (2015, March 3). Reading column names alone in a csv file. Stack Overflow. Retrieved August 4, 2023, from https://stackoverflow.com/questions/28836781/reading-column-names-alone-in-a-csv-file
"""

import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable

    csvFile = open(sys.argv[1], "r")
    csvReader = csv.DictReader(csvFile)

    # TODO: Read DNA sequence file into a variable

    txtFile = open(sys.argv[2], "r")
    dna_sequence = txtFile.read()

    # TODO: Find longest match of each STR in DNA sequence
    longest_Sequence = dict()

    for type in csvReader.fieldnames[1:]:
        longest_Sequence[type] = int(longest_match(dna_sequence, type))

    keys = longest_Sequence.keys()
    # print(longest_Sequence)
    # print(len(longest_Sequence))
    # print()

    # TODO: Check database for matching profiles
    for suspect in csvReader:
        count = 0
        for i in keys:
            # print(suspect[i])
            # print(longest_Sequence[i])
            # print()
            if int(suspect[i]) == longest_Sequence[i]:
                count += 1
        # print(count)
        if count == len(longest_Sequence):
            print(suspect["name"])
            return

    print("No match")


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
