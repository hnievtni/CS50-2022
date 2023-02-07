#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw");
        return 1;
    }

    FILE *input = fopen(argv[1], "r"); //input
    FILE *output = NULL;

    if (input == NULL)
    {
        //if input file exists
        printf("Could not open file");
        return 1;
    }

    unsigned char buffer[512];
    int imageCount = 0;

    char *fileName = malloc(8 * sizeof(char));

    while (fread(buffer, sizeof(char), 512, input) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //image check
            if (imageCount != 0)
            {
                //close the last output file before new image
                fclose(output);
            }
            sprintf(fileName, "%03i.jpg", imageCount);
            output = fopen(fileName, "w");
            imageCount++;
        }
        if (output != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output);
        }
    }

    free(fileName);
    fclose(output);
    fclose(input);

    return 0;
}
