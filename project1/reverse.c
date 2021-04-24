#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int errno;

void e(char *s, int e)
{
    fprintf(stderr, "%s\n%s\n", s, strerror(e));
    exit(e);
}

void ee(char *s, char *ar, int e)
{
    fprintf(stderr, "%s %s \n%s\n", s, ar, strerror(e));
    exit(e);
}

int main(int argv, char *argc[])
{

    if (argv != 3)
    {
        e("Usage:./reverse <inputfile> <outputfile>", 1);
    }

    if (strcmp(argc[1], argc[2]) == 0)
    {
        e("Input and output file must differ", 1);
    }

    FILE *inputFile;
    FILE *outputFile;
    inputFile = fopen(argc[1], "r");
    outputFile = fopen(argc[2], "w");
    if (inputFile == NULL)
    {
        ee("error: cannot open file", argc[1], errno);
    }
    if (outputFile == NULL)
    {
        ee("error: cannot open file", argc[2], errno);
    }

    char c;
    unsigned int lastLine = 0;
    while (c != EOF)
    {
        c = fgetc(inputFile);
        if (c == '\n')
        {
            lastLine++;
        }
    }
    rewind(inputFile);
    c = 1;

    unsigned int currentLine = 0;

    while (1)
    {
        c = fgetc(inputFile);

        if (currentLine == lastLine - 1)
        {
            fprintf(outputFile, "%c", c);
            //printf("%C", c);
        }
        if (c == '\n')
        {
            currentLine++;
        }
        if (c == EOF)
        {
            --lastLine;
            currentLine = 0;
            rewind(inputFile);
            c = 1;
            if (lastLine == 0)
            {
                break;
            }
        }
    }

    if (fclose(outputFile) != 0 || fclose(inputFile) != 0)
    {
        e("Input or output file close operation failed", 3);
    }

    return 0;
}