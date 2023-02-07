#include <stdio.h>
#include <cs50.h>

int getPositiveInt(void); //to check if the integer we got is positive or not

int main(void)
{
    printf("Please enter a positive integer for Height.\n");
    int height = getPositiveInt(); //get the positive integer for height
    
    //for each row
    for (int rowCounter = 1; rowCounter <= height; rowCounter++)
    {
        //blank spaces before first column
        int i = rowCounter;
        while (height - i != 0)
        {
            printf(" ");
            i++;
        }
        //for each column
        for (int counter = 0; counter < rowCounter; counter++)
        {
            printf("#");
        }
        //blank space between sections
        printf("  ");
        //second section
        for (int counter = 0; counter < rowCounter; counter++)
        {
            printf("#");
        }
        printf("\n");
    }
}

int getPositiveInt(void)
{
    int n;
    do
    {
        //ask for a positive integer for height & try again if it wasn't
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}
