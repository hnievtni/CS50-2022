import math
from cs50 import get_int


def main():
    checkCard()


def digitsNumber(number): 
    #returns the numbers digit count
    digits = 0
    while number > 0:
        digits += 1
        number //= 10
    return digits


def digits(num, digitNum): 
    #returns the digit with digitNum index in num
    digitsNum = digitsNumber(num) + 1
    digits = [None] * digitsNum
    for i in range(1, digitsNum):
        digits[i] = num // pow(10, digitsNum - 1 - i)
        num -= digits[i] * pow(10, digitsNum - 1 - i)
    return digits[digitNum]


def checkValidity(num): 
    #check the validity of credit card number according to Luhn's algorithm
    digitsNum = digitsNumber(num)
    sum1 = 0
    sum2 = 0
    for digitNum in range(1, digitsNum + 1):
        digit = digits(num, digitNum)
        if digitsNum % 2 == 0:
            if digitNum % 2 == 0:
                sum2 += digit
            else:
                i = digit * 2
                for counter in range(1, digitsNumber(i) + 1):
                    iDigit = digits(i, counter)
                    sum1 += iDigit
        else:
            if digitNum % 2 == 0:
                i = digit * 2
                for counter in range(1, digitsNumber(i) + 1):
                    iDigit = digits(i, counter)
                    sum1 += iDigit
            else:
                sum2 += digit
    checkSum = sum1 + sum2
    return checkSum % 10 == 0


def checkCard(): 
    #check the type of the credit card number
    num = -1
    while num < 0:
        num = get_int("Please enter your credit card number: ")
    digitsNum = digitsNumber(num)
    firstDigit = digits(num, 1)
    secondDigit = digits(num, 2)
    if checkValidity(num) and digitsNum == 15 and firstDigit == 3 and (secondDigit == 4 or secondDigit == 7):
        print("AMEX")
    elif checkValidity(num) and digitsNum == 13 and firstDigit == 4:
        print("VISA")
    elif checkValidity(num) and digitsNum == 16 and firstDigit == 4:
        print("VISA")
    elif checkValidity(num) and digitsNum == 16 and firstDigit == 5 and (secondDigit == 1 or secondDigit == 2 or secondDigit == 3 or secondDigit == 4 or secondDigit == 5):
        print("MASTERCARD")
    else:
        print("INVALID")


main()
