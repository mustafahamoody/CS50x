/*
References
C/C++ Program to remove alternate digits of an integer. (n.d.). SlayStudy. Retrieved July 5, 2023, from https://slaystudy.com/c-c-program-to-remove-alternate-digits-of-an-integer/
C Program to Find Second Last Digit of a Number. (n.d.). SlayStudy. Retrieved July 5, 2023, from https://slaystudy.com/c-program-to-find-second-last-digit-of-a-number/
*/

#include <cs50.h>
#include <stdio.h>

long getNum(void);
bool cardValid(long cardNumber);
char cardType(long cardNum);

int main(void)
{
    // Prompt for input
    long cardNum = get_long("Number: ");
    // Runs checksum on card number
    bool isValid = cardValid(cardNum);
    // Checks card type if checksum is valid
    if (isValid == true)
    {
        char type = cardType(cardNum);

        if (type == 'a')
        {
            printf("AMEX\n");
        }
        else if (type == 'm')
        {
            printf("MASTERCARD\n");
        }
        else if (type == 'v')
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Calculate checksum
bool cardValid(long cardNum)
{
    long i = 0;
    // (n / 100) % 10 = second last digit
    // Divide by 100 to altermate digits
    for (long n = cardNum / 10; n > 0; n /= 100)
    {
        // Multiplies every other digit by 2 and appends value to i
        i = (i * 10) + (2 * (n % 10));
    }

    long k = 0;
    // Adds i's digits together
    // Divide by 10 to go to next digit
    for (long m = i; m > 0; m /= 10)
    {
        // Add digit to k
        k = k + (m % 10);
        // printf("Step Two: %li\n", k);
    }

    // (n / 10) % 10 = last digit
    // Divide by 100 to altermate digits
    for (long j = cardNum; j > 0; j /= 100)
    {
        // Adds every other digit to i
        k += (j % 10);
        // printf("Step Three: %li\n", k);
    }

    // If totals last digit is 0, card is valid
    if (k % 10 == 0)
    {
        // printf("Number is: %li\n", i);
        return true;
    }

    else
    {
        return false;
    }
}

// Get card type
char cardType(long cardNum)
{
    // Checks if card is American Express
    if (cardNum > 339999999999999 && cardNum < 350000000000000)
    {
        return 'a';
    }

    else if (cardNum > 369999999999999 && cardNum < 380000000000000)
    {
        return 'a';
    }

    // Checks if card is Mastercard
    else if (cardNum > 5099999999999999 && cardNum < 5600000000000000)
    {
        return 'm';
    }

    // Checks if card is Visa
    else if (cardNum > 3999999999999 && cardNum < 5000000000000)
    {
        return 'v';
    }
    else if (cardNum > 3999999999999999 && cardNum < 5000000000000000)
    {
        return 'v';
    }

    else
    {
        return 'i';
    }
}