#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

float countLetters(string txt); //returns letters count
float countWords(string txt); //returns words count
float countSentences(string txt); //returns sentences count
int readabilityCheck(string txt); //returns the grade level

int main(void)
{
    string text = get_string("Please enter your Text: ");
    int gradeLevel = readabilityCheck(text); //get the grade level
    if (gradeLevel >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        if (gradeLevel < 1)
        {
            printf("Before Grade 1\n");

        }
        else
        {
            printf("Grade %d\n", gradeLevel);
        }
    }
}
float countLetters(string txt)
{
    float lettersCount = 0;
    char *pointer = txt;
    for (int counter = 0; counter < strlen(txt); counter++)
    {
        char character = pointer[counter];
        if (islower(character))
        {
            character = toupper(character);
        }
        if ((character == 'A') || (character == 'B') || (character == 'C') || (character == 'D') || (character == 'E') ||
            (character == 'F') || (character == 'G') || (character == 'H') || (character == 'I') || (character == 'J') ||
            (character == 'K') || (character == 'L') || (character == 'M') || (character == 'N') || (character == 'O') ||
            (character == 'P') || (character == 'Q') || (character == 'R') || (character == 'S') || (character == 'T') ||
            (character == 'U') || (character == 'V') || (character == 'W') || (character == 'X') || (character == 'Y') ||
            (character == 'Z'))
        {
            //only count letters not other characters like ?,!,@,...
            lettersCount ++;
        }
    }
    return lettersCount;
}
float countWords(string txt)
{
    char *pointer = txt;
    float blankSpaces = 0;
    for (int counter = 0; counter < strlen(txt); counter++)
    {
        if (pointer[counter] == ' ')
        {
            //separates words by balnk space
            blankSpaces++;
        }
    }
    float wordsCount = blankSpaces + 1; //blank spaces are between words so it didn't count the first words so it should go up by 1
    return wordsCount;
}
float countSentences(string txt)
{
    char *pointer = txt;
    float sentencesCount = 0;
    for (int counter = 0; counter < strlen(txt); counter++)
    {
        char character = pointer[counter];
        if ((character == '.') || (character == '!') || (character == '?'))
        {
            //separates sentences by . or ! or ? as they come at th end of the sentences
            sentencesCount++;
        }
    }
    return sentencesCount;
}
int readabilityCheck(string txt)
{
    float lettersCount = countLetters(txt), wordsCount = countWords(txt), sentencesCount = countSentences(txt);
    float L = (lettersCount * 100) / wordsCount;
    float S = (sentencesCount * 100) / wordsCount;
    float readabilityIndex = (0.0588 * L) - (0.296 * S) - 15.8;
    int grade = round(readabilityIndex); //round the float into integer
    return grade;
}
