#pragma once 


char *shell_read();

char **interpret(char *line);

int launch(char **argument);

int execute(char **argument);