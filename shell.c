

/*
ssh reads the line inputed into the shell 
finds the arguements inside the inputted into the shell
*/
void shell(){
    char *line;
    char **argument;
    int status;
    do{
        printf("~ ");
        line=read();
        argument=interpret(line);
        status=execute(argument);

        free(line);
        free(argument);
    }while(status);


}