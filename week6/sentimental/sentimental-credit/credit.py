"""
References
Gaurav, S. (2022, June 27). int() Function in Python. Scaler. Retrieved August 4, 2023, from https://www.scaler.com/topics/int-python/
"""

from cs50 import get_int


# TODO
def main():
    # Promps for input
    cardNum = get_int("Number: ")
    # Runs checksum on card number
    isValid = cardValid(cardNum)
    # Checks card type if checksum is valid
    if isValid == True:
        type = cardType(cardNum)

        if type == "a":
            print("AMEX")

        elif type == "m":
            print("MASTERCARD")

        elif type == "v":
            print("VISA")

        else:
            print("INVALID")

    else:
        print("INVALID")


# Calculate checksum
def cardValid(cardNum):
    i = 0
    # (n / 100) % 10 = second last digit
    # Divide by 100 to altermate digits
    n = int(cardNum / 10)
    while n > 0:
        i = int((i * 10) + (2 * (n % 10)))
        n = int(n / 100)

    k = 0
    # Adds i's digits together
    # // Divide by 10 to go to next digit
    m = int(i)
    while m > 0:
        k = int(k + (m % 10))
        m = int(m / 10)

    # (n / 10) % 10 = last digit
    # Divide by 100 to altermate digits
    j = int(cardNum)
    while j > 0:
        k += int(j % 10)
        j = int(j / 100)

    # If totals last digit is 0, card is valid
    if int(k % 10) == 0:
        return True
    else:
        return False


def cardType(cardNum):
    # Checks if card is American Express
    if cardNum > 339999999999999 and cardNum < 350000000000000:
        return "a"
    elif cardNum > 369999999999999 and cardNum < 380000000000000:
        return "a"

    # Checks if card is Mastercard
    elif cardNum > 5099999999999999 and cardNum < 5600000000000000:
        return "m"

    # Checks if card is visa
    elif cardNum > 3999999999999 and cardNum < 5000000000000:
        return "v"
    elif cardNum > 3999999999999999 and cardNum < 5000000000000000:
        return "v"

    else:
        return "i"


main()
