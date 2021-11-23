#include <stdio.h>
#include <stdlib.h>
#define SIZE 1024       // Defines SIZE for standard input of 1024 characters, it is used for the commented out read() function
#define WORD 128        // Defines WORD as the int of 128
#define check " \t\r\n\a"
/*
This Code is an older implementation of getting input from the user and reallocates memory using the buffer
*/
// char *read(){
//     int position=0;
//     char *buffer= malloc(sizeof(char)*SIZE);
//     int character;
//     int size=SIZE;

//     // if buffer is null, then report to user of allocation error and exit the program 
//     if(!buffer){
//         fprintf(stderr, 'shell: allocation error\n');
//         exit(EXIT_FAILURE);
//     }
//     /*
//     Infinite loop to get character from the user, each letter at a time 
//     It will realloc new memory space with more space and return a pointer assigned to buffer
//     */
//     while(1){
//         character=getchar();
//         //checks if the character is a end of the line or "/n" since it is a integer the EOF can be checked
//         if(character==EOF || character=="\n"){
//             buffer[position]="\0";
//             return buffer;
//         }
//         buffer[position]=character;
//         position++;

//         if(position>=size){
//             size+=SIZE;
//             buffer=realloc(buffer, size);
//             if(!buffer){
//                 fprintf(stderr, 'shell: allocation error\n');
//                 exit(EXIT_FAILURE);
//             }
//         }
//     }
// }
char *read(){
    char *line;
    int buffer=0;

    if(getline(&line,&buffer,stdin)==-1){
        
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
        perror("readline");
        exit(EXIT_FAILURE);

    }
return line;

}
char **interpret(char* line){
    int buffer=WORD;
    int position=0;
    char **words=malloc(WORD*sizeof(char*));
    char *word;

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
            words=realloc(words, buffer*sizeof(char*));
            //if words is NULL then there was a memory allocation error in the realloc function call
            if(!words){
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

int execute(char **argument){


}