#pragma
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// #include "commands.h"
// #include "functions.h"
// #include "shell.h"

#define SIZE 1024       // Defines SIZE for standard input of 1024 characters, it is used for the commented out read() function
#define WORD 64        // Defines WORD as the int of 128
#define check " \t\r\n\a"
char *shell_read();

char **interpret(char *line);

int launch(char **argument);

int execute(char **argument);

void shell(void);

int shell_cd(char **argument);
int ls_help(char **argument);
int shell_exit(char **argument);

char *strings[]={
    "help",
    "cd",
    "exit"
};

int (*function[]) (char**)= {
    &shell_cd,
    &ls_help,
    &shell_exit
};

int number_calls(){
    return (sizeof(strings)/sizeof(char*));
}
int shell_cd(char **argument){
    if (argument[1]==NULL){
        fprintf(stderr,"shell: expected argument to \'cd\'\n");
    }
    else{
        //chdir command is a system function (system call) which is used to change the current 
        //working directory.
        if(chdir(argument[1])!=0){
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
        printf("    %s\n",strings[counter]);
    }
    printf("Use the man command or information on other programs. \n");
    return 1;
}
int shell_exit(char **argument){
    return 0;
}

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

char *shell_read(void){
    char *line=NULL;
    size_t buffer=0;

    if(getline(&line, &buffer, stdin)==-1){
        
        /*
        feof:   The C library function int feof(FILE *stream) tests the end-of-file indicator for the given stream.
                https://www.tutorialspoint.com/c_standard_library/c_function_feof.htm

                This function returns a non-zero value when End-of-File indicator 
                associated with the stream is set, else zero is returned.


        stdin:  standard input, reads the values from the keyboard, it is a file pointer\
                https://www.tutorialspoint.com/cprogramming/c_input_output.htm


        perror: prints a descriptive error message to stderr. First the string str is printed, 
                followed by a colon then a space.

        EXIT_SUCCESS: The value is 0, meanining the program is successful 

        EXIT_FAILURE: The value is 8, meaning the program is unsuccessful

        */
        if(feof(stdin)){
            exit(EXIT_SUCCESS);
        }
        else{
        perror("shell: getline\n");
        exit(EXIT_FAILURE);
        }

    }
return line;
 
}
char **interpret(char* line){
    int buffer=WORD;
    int position=0;
    char **words=malloc(WORD*sizeof(char*));
    char *word, **backup;

    //if words is NULL then allaocation of memory did not work
    if(!words){
        fprintf(stderr,"shell: allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    // word stores the word found by the strtok which looks for certain key words inside "check" 's definiton
    //strtok returns a pointer to the word
    word=strtok(line,check);
    while(word !=NULL){
        words[position]=word;
        position++;

        if(position>=buffer){
            buffer+=WORD;
            backup=words;
            words=realloc(words, buffer*sizeof(char*));
            //if words is NULL then there was a memory allocation error in the realloc function call
            if(!words){
                free(backup);
                fprintf(stderr,"shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        // Null in the function call tells it to use the same the string used earlier in the function call 
        //with the same progress made in the last call
        word=strtok(NULL, check);
    }
    words[position]=NULL;
    return words;
}

int launch(char **argument){
    pid_t pid, wpid;
    int status;
    
    //makes a duplicate of the program-> a child to the parent program call

    pid=fork();
    if(pid==0){
        if(execvp(argument[0],argument)==-1){
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid<0){
        perror("shell");
        //if there is an error in forking
    }
    else{
        do{
            //waitpid: is a function that checks the process function is used to request status 
            //information from a child process whose process ID is pid. Normally, the calling 
            //process is suspended until the child process makes status information available by terminating.

            //WUNTRACED: This flag specifies that waitpid should report the status of any child processes 
            //that have been stopped as well as those that have terminated.


            wpid=waitpid(pid, &status,WUNTRACED);

        }while(!WIFEXITED(status) && !WIFSIGNALED(status) );
    }

    return 1;
}

int execute(char **argument){
    //if empty arguement is put in
    if (argument==NULL){
        return 1;
    }

    for(int i=0; i< number_calls();i++){
        if(strcmp(argument[0],strings[i])==0){
            return (*function[i])(argument);
        }
    }
    return launch(argument);

}

int main(){

shell();

return EXIT_SUCCESS;
}
