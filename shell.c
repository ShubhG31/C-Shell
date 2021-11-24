#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "commands.h"
#include "functions.h"
#include "shell.h"
/*
ssh reads the line inputed into the shell 
finds the arguements inside the inputted into the shell
*/
void shell(){
    char *line;
    char **argument;
    int status;
    char *name;
    do{
        printf("~ ");
        line=shell_read();
        argument=interpret(line);
        status=execute(argument);

        free(line);
        free(argument);
    }while(status);


}