#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"

void print_token(MPY_TOKEN *token){
    // prints token object
    printf("\nMPY_TOKEN{\n");
    printf("\ttype: %d\n", token->token_type);
    printf("\tlexeme: %s\n", token->lexeme);
    printf("\tloc: (%d, %d)\tlen: %d", token->line, token->col, token->len);
    printf("}\n");
}


void print_tokens(MPY_TOKENS *tokens){
    while (tokens != NULL && tokens->token != NULL)
    {
        print_token(tokens->token);
        tokens = tokens->next;
    }
    
}

// token memory management
void free_token(MPY_TOKEN *token){
    // free(token->token_type);
    free(token->lexeme);
    // free(token->line);
    // free(token->col);
    // free(token->len);
    free(token);
}

void free_tokens(MPY_TOKENS *tokens){
    while (tokens != NULL)
    {
        free(tokens->token);
        tokens = tokens->next;
    }
    
}