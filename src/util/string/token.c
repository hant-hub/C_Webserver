#include "util_string.h"
#include <string.h>





SizedString tokenizeBuffer(char* buffer) {
    
    static char* input;
    static size_t bufferpos;
    const char delim = ' ';
    


    if (buffer != NULL) { 
        input = buffer;
        bufferpos = 0;
    } 
    if (input == NULL)
        return (SizedString){"\0", 0};

    size_t len = 0;  
    
    if (input[bufferpos] == delim) {
        while (input[bufferpos] == delim) {
            bufferpos += 1;
        }
        if (input[bufferpos] == '\0') {
            return (SizedString){"\0", 0};
        }
    }
    
    while (input[bufferpos] != delim) {
        len += 1;
        bufferpos += 1;
    }
    
    char out[len]; 
    for (int i = 1; i<=len; i++) {
       out[len-i] = input[bufferpos - i]; 
    }
    out[len] = '\0';

//    int result = removeTrailingSpace(&out);
//    if (result != NOERROR) {
//        printf("REALLOC Error\n");
//        return (SizedString){0,0};
//    }

    return (SizedString){out, len};
}
