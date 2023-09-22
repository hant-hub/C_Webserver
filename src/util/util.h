#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




//safe Types
typedef struct SizedString {
    char* string;
    size_t length;
} SizedString;

enum Error {
    NOERROR = 0
};


//parsing
enum ParseResult {
    BADREQUEST = NOERROR + 1
};

enum ParseResult ParseHTTP(SizedString buffer, SizedString* out);

#endif