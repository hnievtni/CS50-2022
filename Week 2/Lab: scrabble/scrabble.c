#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word); //returns the value of word 
int charValue(char character); //return the character value that is assigned to each letter

int main(void)
{

    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");


    int score1 = compute_score(word1); //get player1s score
    int score2 = compute_score(word2); //get player2s score
    //check who won
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    if (score1 == score2)
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{
    char *pointer = word;
    int sum = 0;
    for (int counter = 0; counter < strlen(word); counter++)
    {
        char character = pointer[counter];
        //make the letter upper case becuase charValue checks them in upper case
        if (islower(character))
        {
            character = toupper(character);
        }
        sum += charValue(character);
    }
    return sum;
}
int charValue(char character)
{
    int value;
    switch (character)
    {
        case 'A':
        {
            value = POINTS[0];
        }
        break;
        case 'B':
        {
            value = POINTS[1];
        }
        break;
        case 'C':
        {
            value = POINTS[2];
        }
        break;
        case 'D':
        {
            value = POINTS[3];
        }
        break;
        case 'E':
        {
            value = POINTS[4];
        }
        break;
        case 'F':
        {
            value = POINTS[5];
        }
        break;
        case 'G':
        {
            value = POINTS[6];
        }
        break;
        case 'H':
        {
            value = POINTS[7];
        }
        break;
        case 'I':
        {
            value = POINTS[8];
        }
        break;
        case 'J':
        {
            value = POINTS[9];
        }
        break;
        case 'K':
        {
            value = POINTS[10];
        }
        break;
        case 'L':
        {
            value = POINTS[11];
        }
        break;
        case 'M':
        {
            value = POINTS[12];
        }
        break;
        case 'N':
        {
            value = POINTS[13];
        }
        break;
        case 'O':
        {
            value = POINTS[14];
        }
        break;
        case 'P':
        {
            value = POINTS[15];
        }
        break;
        case 'Q':
        {
            value = POINTS[16];
        }
        break;
        case 'R':
        {
            value = POINTS[17];
        }
        break;
        case 'S':
        {
            value = POINTS[18];
        }
        break;
        case 'T':
        {
            value = POINTS[19];
        }
        break;
        case 'U':
        {
            value = POINTS[20];
        }
        break;
        case 'V':
        {
            value = POINTS[21];
        }
        break;
        case 'W':
        {
            value = POINTS[22];
        }
        break;
        case 'X':
        {
            value = POINTS[23];
        }
        break;
        case 'Y':
        {
            value = POINTS[24];
        }
        break;
        case 'Z':
        {
            value = POINTS[25];
        }
        break;
        default:
        {
            value = 0;
        }
        break;
    }
    return value;
}
