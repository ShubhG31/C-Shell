#include <stdio.h>
#include <stdlib.h>
#define SIZE 1024
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

        */
        if(feof(stdin)){
            exit(EXIT_SUCCESS);
        }
        perror("readline");
        exit(EXIT_FAILURE);

    }
return line;

}
char interpret(char* line){
    
}

int execute(int status){


}