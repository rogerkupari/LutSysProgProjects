#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include<sys/wait.h>

#define MAX_ARGUMENT_NUMBER 50

char *path;

extern int errno;

void error(int e);
void cmdExec(char *cmd[]);
void shell(void);
void parseInput(char *input);

void error(int e){
    free(path);
    fprintf(stderr, "%s", "An error has occured \n");
    exit(e);
    
}

int main(int argv, char *argc[])
{
    path = malloc(strlen("/bin/") +1);
    if(path == NULL){
        error(ENOMEM);
    }
    if(sprintf(path, "%s", "/bin/") < 0){
        error(1);
    }

    if (argv > 1)
    {
        
        FILE *inputFile;
        inputFile = fopen(argc[1], "r");
        if (inputFile == NULL)
        {
            error(errno);
        }
            
        char *content = NULL;
        size_t lineSize = 0;
        int lineData = 0;
        while (lineData != -1)
        {
            lineData = getline(&content, &lineSize, inputFile);
           
            if(strcmp("\n", content) != 0){
                parseInput(strtok(content, "\n"));

            }
        }

        if (fclose(inputFile) != 0)
        {
            error(ETXTBSY);
        }

        exit(0);
    }
    else {
        shell();
        free(path);
    }

    return 0;
}

void cmdExec(char *cmd[]){


    if(strcmp("exit", cmd[0]) == 0){
        exit(0);
        free(path);
    }
    if(strcmp("cd", cmd[0]) == 0){
        if(cmd[1] == NULL || cmd[2] != NULL ){
            error(1);
        } else {
            chdir(cmd[1]);
            return;
        }
    }
    if(strcmp("path", cmd[0]) == 0){
        if(cmd[1] == NULL){
            fprintf(stdout, "%s\n", path);
            return;
        }else {
            path = malloc(strlen(cmd[1]) +1);
            if(path == NULL){
                error(ENOMEM);
            }
            if(sprintf(path, "%s", cmd[1]) < 0){
                error(1);
                 
            }
        }
    }






    pid_t pid;
    char *s_cmd = malloc(strlen("/bin/") + strlen(cmd[0]) +1);
    if(s_cmd == NULL){
        error(ENOMEM);
    }
    
   
    if(sprintf(s_cmd, "%s%s", path, cmd[0]) < 0){
        error(1);
    }


    

    pid = fork();
    if(pid == 0){
        execv(s_cmd, cmd);
        exit(0);
        
    }
    else if(pid == -1){
        free(s_cmd);
        error(errno);
    }
    else {
        wait(NULL);
    }

    free(s_cmd);
   

}

void parseInput(char *input){
    char *args[MAX_ARGUMENT_NUMBER];
    int count = 0;

    char *argInput = strtok(input, " ");
    while(argInput != NULL){
        if(count == MAX_ARGUMENT_NUMBER){
            error(1);
        }
        args[count] = argInput;
        count++;
        argInput = strtok(NULL, " ");
    }
    args[count] = NULL;
    cmdExec(args);
    
   

}

void shell(){

    char *content = NULL;
    size_t lineSize = 0;

    while(1){
        printf("wish>");
        getline(&content, &lineSize, stdin);
        if(strcmp("\n", content) != 0){
             parseInput(strtok(content, "\n"));
        }
       
        
    }


}