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

    if (argv < 2)
    {
        e("Usage:./my-grep <word> <file>", 1);
    }

    FILE *inputFile;
    inputFile = fopen(argc[2], "r");
    if (inputFile == NULL)
    {
        ee("error: cannot read file", argc[1], errno);
    }

   

    char *content = NULL;
    size_t lineSize = 0;
    while(getline(&content, &lineSize, inputFile) != -1){
        if (strstr(content , argc[1] )!= NULL)
        {
             printf("%s",content);
        }
    }

    if (fclose(inputFile) != 0)
    {
        e("Input file close operation failed", 3);
    }

    return 0;
}