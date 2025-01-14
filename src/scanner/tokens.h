#ifndef TOKENS_H
#define TOKENS_H

typedef enum MPY_TOKEN_TYPE {
    //keywords -> [0,12]
    IF, ELSE, ELSEIF,
    OR, AND, EQUALS, NOT,
    TRUE, FALSE, NONE,
    FOR, IN, WHILE,

    //types -> [13, 16]
    INT, DOUBLE, CHAR, STRING,

    //comparison -> [17, 22]
    EQ_EQ, GREATER_THAN, LESS_THAN,
    GREATER_THAN_EQUALS, LESS_THAN_EQUALS,
    NOT_EQUALS,

    //assignment -> 23
    EQ,

    BIT_SHIFT_RIGHT, BIT_SHIFT_LEFT,

    //expression
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,LEFT_BRACKET, RIGHT_BRACKET,
    COMMA, DOT, SEMICOLON, SLASH, PLUS, MINUS, STAR,
    MODULO, ESCAPE,
    
    UNK, // unkown token
    HASH,  // for comments
    SPACE, TAB,// any white space
    NEXT_LINE, START_OF_FILE, END_OF_FILE, //end of file

    LIT, //literal
    //TODO: Add type checking
}MPY_TOKEN_TYPE;


typedef struct MPY_TOKEN
{
    MPY_TOKEN_TYPE token_type;
    char *lexeme;  // actual value of token
    int line;
    int col;  
    int len;   //length of the token
} MPY_TOKEN;


// linked list to store all tokens in program
typedef struct MPY_TOKENS
{
    MPY_TOKEN *token;
    struct MPY_TOKENS *next;
    // maybe double linked list?
}MPY_TOKENS;

void print_token(MPY_TOKEN *token);
void print_tokens(MPY_TOKENS *tokens);

//memory management
void free_token(MPY_TOKEN *token);
void free_tokens(MPY_TOKENS *tokens);

MPY_TOKEN_TYPE scan_char_token_type(char *token);
int get_token_len(MPY_TOKEN_TYPE token_type);
MPY_TOKEN *scan_token(char *token, int line, int col);
#endif