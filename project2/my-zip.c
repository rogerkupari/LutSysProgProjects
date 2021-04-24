#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

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

    if (argv < 2)
    {
        e("Usage:./my-zip <original file> > <copressed file>", 1);
    }

    FILE *inputFile;
    inputFile = fopen(argc[1], "r");
    if (inputFile == NULL)
    {
        ee("error: cannot read file", argc[1], errno);
    }

   

    char currentChar = 0;
    char prevChar = 0;
    int charCount = 0;

    while(currentChar != EOF){
        

        currentChar = fgetc(inputFile);
        if(currentChar != EOF){
            if(prevChar != currentChar){
                if(prevChar != 0)
                    fprintf(stdout, "%d%c", charCount, prevChar);
                charCount = 1;
                prevChar = currentChar;
            } else {
                charCount++;
            }
            
            
        }
    }

    if (fclose(inputFile) != 0)
    {
        e("Input file close operation failed", 3);
    }

    return 0;
}