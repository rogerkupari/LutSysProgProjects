#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

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
        e("Usage:./my-unzip <compressed file> > <uncompressed file>", 1);
    }

    FILE *inputFile;
    inputFile = fopen(argc[1], "r");
    if (inputFile == NULL)
    {
        ee("error: cannot read file", argc[1], errno);
    }

   
    int countArray[1];
    char currentChar;


    while(fscanf(inputFile, "%d", &countArray[0]) != EOF){
        currentChar = fgetc(inputFile);
        for(int i = 0; i<countArray[0]; i++){
            fprintf(stdout, "%c", currentChar);
        }
    }
 


    if (fclose(inputFile) != 0)
    {
        e("Input or file close operation failed", 3);
    }

    return 0;


}