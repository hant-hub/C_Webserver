#include "../string/util_string.h"
#include "../util.h"
#include <stdio.h>
#include <string.h>


char* DumpFile(const char* filepath) {
    FILE* fptr; 
    fptr = fopen(filepath, "r");

    if (fptr == NULL) { 
        printf("Failed to open file: %s\n", filepath);
        perror("Error");
        return 0;
    }


    //find length
    if (fseek(fptr, 0L, SEEK_END) != 0) {
        printf("Failed to jump to end of file: %s\n", filepath);
        return 0;
    }
    size_t length = ftell(fptr);
    if (length == -1) {
        printf("Ftell failed: %s\n", filepath);
        return 0;
    }
    rewind(fptr);

    char *out = calloc(length + 1, sizeof(char));
    size_t newlen = fread(out, sizeof(char), length, fptr);
    if (ferror(fptr) != 0) {
        printf("Fread Failed: %s\n", filepath);
        return 0;
    }
    
    out[newlen + 1] = '\0';


    fclose(fptr);

    return out;
}
