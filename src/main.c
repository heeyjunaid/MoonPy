#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "common/strops.h"
#include "common/fops.h"
#include "scanner/scanner.h"
#include "scanner/tokens.h"
/**
 * Start of interpreter
 * 
 * ./jpy -> this will invoke repl/interactive shell
 * ./jpy <program-name>.py -> this will run the script 
 */

int run(char *code){
    MPY_TOKENS *tokens = scan_tokens(code);

    if (tokens == NULL){
        return 41;
    }
    
    // parse code
    return 1;
}


int main(int argc, char **argv){
    if (argc > 1){
        char *file_path = argv[1];
        char *file = read_file(file_path);
        return run(file);
    }
    else{
        printf("MPY interactive shell\ntype :q to quit\n");
        while (1)
        {   
            char *line = 0x0;
            size_t size = 0;
            size_t length = 0;

            printf(">>> ");
            length = getline(&line, &size, stdin);
            if (length == -1){
                // handle exception
            }

            if (strcmp(line,"\n") == 0){
                continue;
            }

            remove_nextline_char(line);

            if (strcmp(line,":q") == 0){
                printf("exit..");
                return -1;
            }

            // parser

            printf("%s\n", line);
            free(line);
        }
        
    }

    return 1;
}