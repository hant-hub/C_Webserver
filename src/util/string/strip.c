#include "util_string.h"
#include <stdlib.h>
#include <string.h>



enum StringError removeTrailingSpace(SizedString* buffer) {
    
    printf("buffer: %s\n", buffer->string);
    if (buffer->string[0] == '\0') {
        printf("EmptyString\n");
        return EMPTYSTRING;
    }



    size_t index = buffer->length;
    while (buffer->string[index] == ' ' || buffer->string[index] == '\0') {
        index--;
    }
    index++;
    buffer->length = index;
    char* tmp = realloc(buffer->string, index*sizeof(char));
    if (tmp) buffer->string = tmp;

    if (buffer->string == NULL) { 
        printf("ALLOCFAIL\n");
        return ALLOCFAIL;
    }
    buffer->string[index] = '\0';
    return (enum StringError)NOERROR;
}




