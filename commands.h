int shell_cd(char **argument);
int ls_help(char **argument);
int shell_exit(char **argument);


char *strings[]={
    "help",
    "cd",
    "exit"
};

char (*function[]) (char**)= {
    &shell_cd,
    &ls_help,
    &shell_exit
};

int number_calls(){
    return (sizeof(strings)/sizeof(char*));
}