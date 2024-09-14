"""
References
Python String isalpha() Method. (n.d.). W3Schools. Retrieved August 4, 2023, from https://www.w3schools.com/python/ref_string_isalpha.asp
"""


# TODO
def main():
    text = input("Text: ")

    # print("{} letters".format(count_letters(text)))
    # print("{} words".format(count_words(text)))
    # print("{} sentences".format(count_sentences(text)))

    # Finds letters
    letters = float(count_letters(text))
    # Finds # words
    words = float(count_words(text))
    # Finds # sentences
    sentences = float(count_sentences(text))

    # Finds letters / 100 words
    L = float((letters / words) * 100)

    # Finds sentences / 100 words
    S = float((sentences / words) * 100)

    index = 0.0588 * L - 0.296 * S - 15.8
    # print(index)

    if index < 1:
        grade = "Before Grade 1"
        print(grade)

    elif index > 16:
        grade = "Grade 16+"
        print(grade)

    else:
        grade = round(index)
        print("Grade: {}".format(grade))


def count_letters(text):
    L = 0

    for i in text:
        if i.isalpha() == True:
            L += 1

    return L


def count_words(text):
    W = 1

    for letter in text:
        if letter == " ":
            W += 1

    return W


def count_sentences(text):
    S = 0

    for letter in text:
        if letter == "." or letter == "!" or letter == "?":
            S += 1

    return S


main()
