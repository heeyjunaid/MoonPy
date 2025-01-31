#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void remove_nextline_char(char *in){
    // in c string ends with '\0' char
    int ptr=0;
    while (1)
    {
        if (in[ptr] == '\0'){
            if (in[ptr-1] == '\n'){
                in[ptr-1] = '\0';
            }
            break;
        }
        ptr++;
    }

    return;
}

/**
 * copy's substring from current pointer pos 
 * to given number of elements
 */
char *copy_substring(char *str, int n){
    if (str == NULL){
        return NULL;
    }

    // allocating some space on heap
    char* substr = (char *)malloc(n+1);

    for (int i=0;i<n;i++){
        substr[i] = *(str+i);
    }

    substr[n] = '\0'; 
    return substr;
}


/***
 * try to match given string with substring
 * for matching literal 
 */

int match_substring_with_str(char *str, int n, char *substr){
    int cnt = 0;
    while (cnt <= n)
    {   
        if ((*str == ' ' || *str == '\n' || *str == '\0') & (*substr == '\0')){
            return 1;
        }
        if(*str != *substr){
            return 0;
        }

        str++;
        substr++;
        cnt++;
    }
    
    return 0;
}