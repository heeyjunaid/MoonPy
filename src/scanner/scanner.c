#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "../common/strops.h"

int is_end(char code)
{
    return code == '\0';
}

MPY_TOKEN *create_new_node(MPY_TOKEN_TYPE token_type, char *lexeme, int line, int col, int len)
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

MPY_TOKENS *create_new_tokens_node()
{
    MPY_TOKENS *tokens = (MPY_TOKENS *)malloc(sizeof(MPY_TOKENS));

    if (tokens == NULL)
    {
        printf("Not able to assign memory for new node for `MPY_TOKENS`");
        return NULL;
    }

    tokens->token = NULL;
    tokens->next = NULL;
    return tokens;
}

MPY_TOKENS *add_new_node(MPY_TOKEN_TYPE token_type, char *lexeme, int line, int col, int len)
{
    MPY_TOKEN *node = create_new_node(token_type, lexeme, line, col, len);
    MPY_TOKENS *tokens = create_new_tokens_node();
    tokens->token = node;
    return tokens;
}

int match(char code, char expected)
{
    if (is_end(code))
        return 0;
    if (code == expected)
        return 1; // check value
    return 0;
}

int match_next(char code, char expected)
{
    code = *(&code + 1); // peak next
    if (is_end(code))
        return 0;
    if (code == expected)
        return 1; // check value
    return 0;
}

/**
 * function to scan program and returns
 * pointer to linked list with tokens
 */
MPY_TOKENS *scan_tokens(char *code)
{
    int col = 0;
    int line = 0;
    int cnt = 0;
    MPY_TOKENS *tokens = create_new_tokens_node();
    MPY_TOKENS *running_token_list = tokens;
    while (!is_end(*(code + cnt)) && running_token_list != NULL)
    {
        char *curr_pointr = code + cnt;
        char curr_char = *curr_pointr;
        if (match(curr_char, '='))
        {
            // todo: handle assignment, comparison
            running_token_list->next = add_new_node(EQ, curr_pointr, line, col, 1);
        }
        else if (match(curr_char, '\n'))
        {
            running_token_list->next = add_new_node(NEXT_LINE, curr_pointr, line, col, 1);
            line++;
            col = -1;
        }

        running_token_list = running_token_list->next;
        col++;
        cnt++; // increment pointer
    }
    print_tokens(tokens->next);

    return tokens->next; // init token is null
}