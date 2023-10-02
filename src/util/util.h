#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string/util_string.h"
#include "Error.h"


//parsing
enum ParseResult {
    BADREQUEST = NOERROR + 1,
    UNKNOWNREQUEST
};

enum ParseResult ParseHTTP(SizedString buffer, SizedString* out);



//File Handling ----------------------------------------
char* DumpFile(const char* filepath);

#endif
