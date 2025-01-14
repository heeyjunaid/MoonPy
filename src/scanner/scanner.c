#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "../common/strops.h"

int is_end(char code)
{
    return code == '\0';
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

MPY_TOKENS *add_new_node(MPY_TOKEN *node)
{
    MPY_TOKENS *tokens = create_new_tokens_node();
    tokens->token = node;
    return tokens;
}

void move_pointer_next_line(int *line, int *col)
{
    *col = 0;
    *line += 1;
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

        MPY_TOKEN *token = scan_token(curr_pointr,line,col);

        if (token->token_type == END_OF_FILE)
            break;

        running_token_list->next = add_new_node(token);
        running_token_list = running_token_list->next;
        cnt += token->len; // increment pointer
        col += token->len;

        if (token->token_type == NEXT_LINE)
        {
            line++;
            col = 0;
        }
    }
    print_tokens(tokens->next);

    return tokens->next; // init token is null
}