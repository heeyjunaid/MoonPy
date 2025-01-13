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

int peak_till_eol(char *code, int cnt)
{
    // this function moves pointer to end of line or '\n' char
    while (*(code + cnt) != '\n')
    {
        cnt++;
    }
    return ++cnt;
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

        MPY_TOKEN_TYPE token_type = scan_char_token_type(curr_pointr);
        if (token_type == END_OF_FILE)
        {
            break;
        }
        int token_len = get_token_len(token_type);

        switch (token_type)
        {
        case UNK:
            continue;
        case HASH:
        {
            cnt = peak_till_eol(code, cnt);
            move_pointer_next_line(&line, &col);
            continue;
        }
        case NEXT_LINE:
            move_pointer_next_line(&line, &col);
            cnt++;
            continue;
        default:
            break;
        }
        running_token_list->next = add_new_node(token_type, curr_pointr, line, col, token_len);
        running_token_list = running_token_list->next;
        col += token_len;
        cnt += token_len; // increment pointer
    }
    running_token_list->next = add_new_node(END_OF_FILE, "EOF", line, col, 3);
    print_tokens(tokens->next);

    return tokens->next; // init token is null
}