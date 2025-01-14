#include <stdio.h>
#include <stdlib.h>

void throw_error(char *message){
    printf("Error| %s", message);
    exit(EXIT_FAILURE);
}