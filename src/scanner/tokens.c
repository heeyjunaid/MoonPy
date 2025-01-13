#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"

void print_token(MPY_TOKEN *token)
{
    // prints token object
    printf("\nMPY_TOKEN{\n");
    printf("\ttype: %d\n", token->token_type);
    printf("\tlexeme: %s\n", token->lexeme);
    printf("\tloc: (%d, %d)\tlen: %d", token->line, token->col, token->len);
    printf("}\n");
}

void print_tokens(MPY_TOKENS *tokens)
{
    while (tokens != NULL && tokens->token != NULL)
    {
        print_token(tokens->token);
        tokens = tokens->next;
    }
}

// token memory management
void free_token(MPY_TOKEN *token)
{
    // free(token->token_type);
    free(token->lexeme);
    // free(token->line);
    // free(token->col);
    // free(token->len);
    free(token);
}

void free_tokens(MPY_TOKENS *tokens)
{
    while (tokens != NULL)
    {
        free(tokens->token);
        tokens = tokens->next;
    }
}

/**
 * token scan works recursive way, scanner does depth first search to figure out type of token
 * '===' this gets scanned into '=' and '=='
 * '===!=' this gets scanned into ''
 */
MPY_TOKEN_TYPE scan_char_token_type(char *token)
{
    switch (*token)
    {
    case '(':
        return LEFT_PAREN;
    case ')':
        return RIGHT_PAREN;
    case '{':
        return LEFT_BRACE;
    case '}':
        return RIGHT_BRACE;
    case '[':
        return LEFT_BRACKET;
    case ']':
        return RIGHT_BRACKET;
    case ',':
        return COMMA;
    case '.':
        return DOT;
    case ';':
        return SEMICOLON;
    case '/':
        return SLASH;
    case '+':
        return PLUS;
    case '-':
        return MINUS;
    case '%':
        return MODULO;
    case '*':
        return STAR;
    case ' ':
        return SPACE;
    case '#':
        return HASH;
    case '"':
        return STRING;
    case '\'':
        return CHAR;
    case '\\':
        return ESCAPE;
    case '>':{
        MPY_TOKEN_TYPE nxt_token = scan_char_token_type(token + 1);
        if (nxt_token == EQ)
            return GREATER_THAN_EQUALS;
        else if (nxt_token == GREATER_THAN)
            return BIT_SHIFT_RIGHT;
        return GREATER_THAN;}
    case '<':{
        MPY_TOKEN_TYPE nxt_token = scan_char_token_type(token + 1);
        if (nxt_token == EQ)
            return LESS_THAN_EQUALS;
        else if (nxt_token == LESS_THAN)
            return BIT_SHIFT_LEFT;
        return LESS_THAN;}
    case '!':
        if (scan_char_token_type(token + 1) == EQ)
            return NOT_EQUALS;
        return NOT;
    case '=':
        if (scan_char_token_type(token + 1) == EQ)
            return EQ_EQ;
        return EQ;
    case '\t':
        return TAB;
    case '\n':
        return NEXT_LINE;
    case '\0':
        return END_OF_FILE;
    default:
        printf("default case reachde");
        return UNK;
    }

    return UNK;
}

int is_in_list(int x, int list[], int size) {
    for (int i = 0; i < size; i++) {
        if (list[i] == x) {
            return 1; // x is found in the list
        }
    }
    return 0; // x is not in the list
}

int get_token_len(MPY_TOKEN_TYPE token_type)
{

    MPY_TOKEN_TYPE token_len_two[] = {EQ_EQ, GREATER_THAN_EQUALS, LESS_THAN_EQUALS, NOT_EQUALS, BIT_SHIFT_LEFT, BIT_SHIFT_RIGHT};
    int size = sizeof(token_len_two) / sizeof(token_len_two[0]);
    
    for(int i=0; i<size;i++){
        if (token_len_two[i] == token_type){
            return 2;
        }
    }

    return 1;
}