#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int keyValidity(string key); //returns the key validity
int duplicate(string key); //check if they are any duplicate letters in key
int cipher(char character); //returns the index of letter in alphabet

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        int validity0 = 1, validity1 = 1;
        do
        {
            if (validity0 == 0 || validity1 == 0)
            {
                printf("The key you entered was invalid, Please try again\n");
                exit(1);

            }
            validity0 = keyValidity(key);
            validity1 = duplicate(key);
        }
        while (validity0 == 0 || validity1 == 0); //check the key validity in different points
        string plainText = get_string("PlainText: "); //get the plain text 
        char *keyPointer = key;
        char *txtPointer = plainText;
        for (int counter = 0; counter < strlen(plainText); counter++)
        {
            bool upperBoolean = true; //its true when the letter is in upper case
            if (islower(txtPointer[counter]))
            {
                //make the letter  in upper case
                upperBoolean = false;
                txtPointer[counter] = toupper(txtPointer[counter]);

            }
            int index = cipher(txtPointer[counter]); //get the index of each letter in text
            if (index < 26)
            {
                //if its a letter in alphabet
                if (upperBoolean)
                {
                    //check if the letter is in upper or lower case
                    if (islower(keyPointer[index]))
                    {
                        //make the key in upper case
                        txtPointer[counter] = toupper(keyPointer[index]);
                    }
                    else
                    {
                        txtPointer[counter] = keyPointer[index];

                    }

                }
                else
                {
                    if (islower(keyPointer[index]))
                    {
                        txtPointer[counter] = keyPointer[index];
                    }
                    else
                    {
                        //make the key in lower case
                        txtPointer[counter] = tolower(keyPointer[index]);

                    }

                }

            }

        }
        char *cipher = txtPointer;
        printf("ciphertext: %s\n", cipher);
        exit(0);
    }
    else
    {
        printf("You didn't enter right amount of arguments, Please try again.\n");
        exit(1);
    }
}
int keyValidity(string key)
{
    char *pointer = key;
    int validity;
    for (int counter = 0; counter < strlen(key); counter++)
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
            //only letters are valid as key
            validity = 1;
        }
        else
        {
            //if key contains a character that is none letter its not valid
            validity = 0;
            break;
        }
    }
    if (strlen(key) != 26)
    {
        //if its more or less than 26 letters it is not valid
        validity = 0;
    }
    return validity;
}
int duplicate(string key)
{
    char *pointer = key;
    int validity = 1;
    for (int counter = 0; counter < strlen(key); counter++)
    {
        for (int i = 0; i < strlen(key); i++)
        {
            if (i != counter)
            {
                if (pointer[counter] == pointer[i])
                {
                    //check if any of the letters in key is duplicate and if it is then the key is invalid
                    validity = 0;
                }
            }
        }
    }
    return validity;
}
int cipher(char character)
{
    int index;
    switch (character)
    {
        case 'A':
        {
            index = 0;
        }
        break;
        case 'B':
        {
            index = 1;
        }
        break;
        case 'C':
        {
            index = 2;
        }
        break;
        case 'D':
        {
            index = 3;
        }
        break;
        case 'E':
        {
            index = 4;
        }
        break;
        case 'F':
        {
            index = 5;
        }
        break;
        case 'G':
        {
            index = 6;
        }
        break;
        case 'H':
        {
            index = 7;
        }
        break;
        case 'I':
        {
            index = 8;
        }
        break;
        case 'J':
        {
            index = 9;
        }
        break;
        case 'K':
        {
            index = 10;
        }
        break;
        case 'L':
        {
            index = 11;
        }
        break;
        case 'M':
        {
            index = 12;
        }
        break;
        case 'N':
        {
            index = 13;
        }
        break;
        case 'O':
        {
            index = 14;
        }
        break;
        case 'P':
        {
            index = 15;
        }
        break;
        case 'Q':
        {
            index = 16;
        }
        break;
        case 'R':
        {
            index = 17;
        }
        break;
        case 'S':
        {
            index = 18;
        }
        break;
        case 'T':
        {
            index = 19;
        }
        break;
        case 'U':
        {
            index = 20;
        }
        break;
        case 'V':
        {
            index = 21;
        }
        break;
        case 'W':
        {
            index = 22;
        }
        break;
        case 'X':
        {
            index = 23;
        }
        break;
        case 'Y':
        {
            index = 24;
        }
        break;
        case 'Z':
        {
            index = 25;
        }
        break;
        default:
        {
            index = 26;
        }
        break;
    }
    return index;
}
