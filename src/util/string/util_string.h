#ifndef UTIL_STRING_H
#define UTIL_STRING_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Error.h"




//Strings ----------------------------------------------
typedef struct SizedString {
    char* string;
    size_t length;
} SizedString;

enum StringError {
    ALLOCFAIL = NOERROR + 1,
    EMPTYSTRING
};

SizedString tokenizeBuffer(char* buffer); 
enum StringError removeTrailingSpace(SizedString* buffer);






#endif
