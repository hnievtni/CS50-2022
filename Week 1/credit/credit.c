#include <stdio.h>
#include <cs50.h>
#include <math.h>

void checkCard(void); //check the type of the credit card number
bool checkValidity(long num); //check the validity of credit card number according to Luhn's algorithm
int digitsNumber(long number); //returns the numbers digit count
int digits(long num, int digitNum); //returns the digit with digitNum index in num

int main(void)
{
    //we get the credit card number to check if it's valid or not
    checkCard();
}

void checkCard(void)
{
    long num;
    do
    {
        num = get_long("Please enter your credit card number: ");
    }
    while (num < 0); //only positive and none zero numbers are acceptable
    int digitsNum = digitsNumber(num); //get the credit cards digits count

    switch (digitsNum)
    {
        case 15: //to check if it's AMEX card or not
        {
            int firstDigit = digits(num, 1);
            int secondDigit = digits(num, 2);

            if (checkValidity(num) && (firstDigit == 3) && (secondDigit == 4 || secondDigit == 7))
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        break;
        case 13: //to check if it's VISA card or invalid
        {
            if (checkValidity(num))
            {
                int firstDigit = digits(num, 1);
                if (firstDigit == 4)
                {
                    printf("VISA\n");

                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        break;
        case 16: //to check if it's MASTERCARD or VISA card or invalid
        {
            if (checkValidity(num))
            {
                int firstDigit = digits(num, 1);
                if (firstDigit == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    int secondDigit = digits(num, 2);
                    if ((firstDigit == 5) && ((secondDigit == 1) || (secondDigit == 2) ||
                                              (secondDigit == 3) || (secondDigit == 4) || (secondDigit == 5)))
                    {
                        printf("MASTERCARD\n");
                    }
                    else
                    {
                        printf("INVALID\n");
                    }
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        break;
        default:
        {
            printf("INVALID\n");
        }
        break;
    }
}
bool checkValidity(long num)
{
    int digitsNum = digitsNumber(num); //get the credit cards digits count
    int digit, sum1 = 0, sum2 = 0;

    for (int digitNum = 1; digitNum <= digitsNum; digitNum++)
    {
        digit = digits(num, digitNum); //get the digit with digitNum index in num
        if (digitsNum % 2 == 0) //if credit card number is even
        {
            if (digitNum % 2 == 0)
            {
                sum2 += digit;
            }
            else
            {
                int i = digit * 2;
                for (int counter = 1; counter <= digitsNumber(i); counter++)
                {
                    int iDigit = digits(i, counter); //get the digit with counter index in i
                    sum1 += iDigit;
                }
            }
        }
        else //if credit card number is odd
        {
            if (digitNum % 2 == 0)
            {
                int i = digit * 2;
                for (int counter = 1; counter <= digitsNumber(i); counter++)
                {
                    int iDigit = digits(i, counter); //get the digit with counter index in i
                    sum1 += iDigit;
                }
            }
            else
            {
                sum2 += digit;
            }
        }
    }
    int checkSum = sum1 + sum2;
    if (checkSum % 10 == 0)
    {
        return true; //credit card number is valid
    }
    else
    {
        return false; //credit card is not valid
    }
}
int digitsNumber(long number)
{
    int digits = 0;
    while (number > 0)
    {
        digits++;
        number /= 10;
    }
    return digits;
}
int digits(long num, int digitNum)
{
    int digitsNum = digitsNumber(num);
    int digits[digitsNum];
    int digit;
    for (int i = 1; i <= digitsNum; i++)
    {
        digits[i] = num / (pow(10, (digitsNum - i)));
        num -= digits[i] * (pow(10, (digitsNum - i)));
        if (i == digitNum)
        {
            digit = digits[i];
        }
    }
    return digit;
}
