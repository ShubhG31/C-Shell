#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "commands.h"
#include "functions.h"
#include "shell.h"


int shell_cd(char **argument){
    if (argument[1]==NULL){
        fprintf(stderr,"shell: expected argument to \'cd\'\n");
    }
    else{
        //chdir command is a system function (system call) which is used to change the current 
        //working directory.
        if(chdir(argument[1]!=0)){
            perror("shell");
        };
    }
    return 1;
}
int ls_help(char **argument){
    printf("Shubh's Shell:\n");
    printf("Type program names and arguments, and press enter");
    printf("builtins include:\n");

    for(int counter=0; counter<number_calls();counter++ ){
        printf(" %s\n",strings[counter]);
    }
    printf("Use the man command or information on other programs. \n");
    return 1;
}
int shell_exit(char **argument){
    return 0;
}
