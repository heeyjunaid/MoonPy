#include <stdlib.h>
#include <stdio.h>

#include "../scanner/scanner.h"

//TODO: Make this more dynamic
// #define MAX_LINE_LENGTH 256  // max length of line allowed

long get_file_size(FILE *file){
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    return file_size;
}


/**
 * reads file and store file buffer on heap
 * needs to free memory used by buffer manually by calling free()
 */
char *read_file(char *file_path){    
    FILE *fptr= fopen(file_path, "rb");
    char *buffer;
    long file_size;

    if (fptr == NULL){
        printf("Can't open file at %s", file_path);
        return NULL;
    }

    file_size = get_file_size(fptr);
    buffer = (char *)malloc(file_size + 1);  // +1 for the null terminator
    if (buffer == NULL) {
        perror("Memory allocation failed for file buffer");
        fclose(fptr);
        return NULL;
    }

    // Read the file into the buffer
    fread(buffer, 1, file_size, fptr);
    buffer[file_size] = '\0';  // Null-terminate the buffer

    fclose(fptr);
    return buffer;
}