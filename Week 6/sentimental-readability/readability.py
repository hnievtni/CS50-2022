import math
import string
from cs50 import get_string


def main():
    text = get_string("Please enter your Text: ")
    gradeLevel = readabilityCheck(text)
    if gradeLevel >= 16:
        print("Grade 16+")
    elif gradeLevel < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {gradeLevel}")


def readabilityCheck(txt):
    #check the grade level
    lettersCount = 0
    wordsCount = 1
    sentencesCount = 0
    for letter in txt:
        if letter == "!" or letter == "?" or letter == ".":
            sentencesCount += 1
        elif letter in string.punctuation: #if the character is punctuations rather than ! or ? or .
            continue
        elif letter == " ":
            wordsCount += 1
        else:
            lettersCount += 1
    L = (lettersCount * 100) / wordsCount
    S = (sentencesCount * 100) / wordsCount
    readabilityIndex = (0.0588 * L) - (0.296 * S) - 15.8
    return round(readabilityIndex)


main()
