#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
#include "../common/strops.h"

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
    free(token->lexeme);
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

int peak_till_eol(char *code)
{
    int cnt = 0;
    // this function moves pointer to end of line or '\n' char
    while (*(code + cnt) != '\n')
    {
        cnt++;
    }
    return ++cnt;
}

int is_digit(char *token)
{
    if ('0' <= *token & *token <= '9')
    {
        return 1;
    }
    return 0;
}

int is_alpha(char *token)
{
    if (('a' <= *token & *token <= 'z') ||
        ('A' <= *token & *token <= 'Z'))
    {
        return 1;
    }
    return 0;
}

int is_alpha_numeric(char *code)
{
    if (is_alpha(code) || is_digit(code) || *code == '_')
    {
        return 1;
    }
    return 0;
}

MPY_TOKEN *create_new_token(MPY_TOKEN_TYPE token_type, char *lexeme, int line, int col, int len)
{
    MPY_TOKEN *node = (MPY_TOKEN *)malloc(sizeof(MPY_TOKEN));
    if (node == NULL)
    {
        printf("Memory allocation failed for MPY_TOKEN");
        return NULL;
    }
    node->lexeme = copy_substring(lexeme, len);
    // node->lexeme = copy_substring(lexeme, len);
    node->token_type = token_type;
    node->line = line;
    node->col = col;
    node->len = len;
    return node;
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
    case '>':
    {
        MPY_TOKEN_TYPE nxt_token = scan_char_token_type(token + 1);
        if (nxt_token == EQ)
            return GREATER_THAN_EQUALS;
        else if (nxt_token == GREATER_THAN)
            return BIT_SHIFT_RIGHT;
        return GREATER_THAN;
    }
    case '<':
    {
        MPY_TOKEN_TYPE nxt_token = scan_char_token_type(token + 1);
        if (nxt_token == EQ)
            return LESS_THAN_EQUALS;
        else if (nxt_token == LESS_THAN)
            return BIT_SHIFT_LEFT;
        return LESS_THAN;
    }
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
        return UNK;
    }

    return UNK;
}
/**
 * valid numbers -> 1, 2, 3.11
 */
MPY_TOKEN *scan_number_token(char *token, int line, int col)
{
    int cnt = 0;
    while (is_digit(token + cnt))
    {
        cnt++;
    }

    char curr_char = *(token + cnt);

    // TODO: how to handle invalid number like 1ar3 
    // if ( curr_char != '.' || curr_char != ' ' || curr_char != '\0' || curr_char != 'e' || curr_char != '\n')
    // {
    //     printf("hhh--%c|\n", curr_char);
    //     printf("Invalid number defination\n");
    //     exit(EXIT_FAILURE);
    // }

    // handling for double value
    if (*(token + cnt) == '.' || *(token + cnt) == 'e')
    {
        cnt++;
        while (is_digit(token + cnt))
        {
            cnt++;
        }
        return create_new_token(DOUBLE, token, line, col, cnt);
    }
    else
    {
        return create_new_token(INT, token, line, col, cnt);
    }
}

/**
 * Try matching substring with space to any resevered token
 * if it's not matched assume it to be literal
 */
MPY_TOKEN_TYPE try_match_reserved_token(char *token, int len)
{
    if (match_substring_with_str(token, len, "if"))
    {
        return IF;
    }
    else if (match_substring_with_str(token, len, "else"))
    {
        return ELSE;
    }
    // TODO: handle else  if
    else if (match_substring_with_str(token, len, "elif"))
    {
        return ELSEIF;
    }
    else if (match_substring_with_str(token, len, "or"))
    {
        return OR;
    }
    else if (match_substring_with_str(token, len, "and"))
    {
        return AND;
    }
    else if (match_substring_with_str(token, len, "True"))
    {
        return TRUE;
    }
    else if (match_substring_with_str(token, len, "False"))
    {
        return FALSE;
    }
    else if (match_substring_with_str(token, len, "None"))
    {
        return NONE;
    }
    else if (match_substring_with_str(token, len, "for"))
    {
        return FOR;
    }
    else if (match_substring_with_str(token, len, "in"))
    {
        return IN;
    }
    else if (match_substring_with_str(token, len, "while"))
    {
        return WHILE;
    }

    return LIT;
}

MPY_TOKEN *scan_alphanumeric_token(char *token, int line, int col)
{
    int cnt = 0;
    while (is_alpha_numeric(token + cnt))
    {
        cnt++;
    }
    MPY_TOKEN_TYPE token_type = try_match_reserved_token(token, cnt);
    return create_new_token(token_type, token, line, col, cnt);
}

MPY_TOKEN *scan_token(char *token, int line, int col)
{
    MPY_TOKEN_TYPE token_type = scan_char_token_type(token);

    if (token_type == HASH)
    {
        int cnt = peak_till_eol(token);
        return create_new_token(token_type, token, line, col, cnt);
    }
    else if (token_type == UNK)
    {
        if (is_digit(token))
        {
            return scan_number_token(token, line, col);
        }
        else if (is_alpha_numeric(token))
        {
            return scan_alphanumeric_token(token, line, col);
        }
        else
        {
            printf("NO valid token found\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int token_len = get_token_len(token_type);
        return create_new_token(token_type, token, line, col, token_len);
    }
}

int is_in_list(int x, int list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (list[i] == x)
        {
            return 1; // x is found in the list
        }
    }
    return 0; // x is not in the list
}

int get_token_len(MPY_TOKEN_TYPE token_type)
{

    MPY_TOKEN_TYPE token_len_two[] = {EQ_EQ, GREATER_THAN_EQUALS, LESS_THAN_EQUALS, NOT_EQUALS, BIT_SHIFT_LEFT, BIT_SHIFT_RIGHT};
    int size = sizeof(token_len_two) / sizeof(token_len_two[0]);

    for (int i = 0; i < size; i++)
    {
        if (token_len_two[i] == token_type)
        {
            return 2;
        }
    }

    return 1;
}