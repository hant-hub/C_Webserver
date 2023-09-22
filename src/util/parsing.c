#include "util.h"





SizedString tokenizeBuffer(SizedString buffer, size_t *bufferPos) {
    SizedString out = {0, 8};
    out.string = calloc(8, sizeof(char));


    for (int i = *bufferPos; i < buffer.length; i++) {
        if (buffer.string[i] == ' ') break;

        if (i >= (out.length - 1)) {
            out.string = realloc(out.string, out.length*2*sizeof(char));
            out.length = out.length*2;
        }

        out.string[i] = buffer.string[i];        
        *bufferPos = i+1;
    }

    return out;
}




enum ParseResult ParseHTTP(SizedString buffer, SizedString* out) {
    size_t bufferPos = 0;
    SizedString method = tokenizeBuffer(buffer, &bufferPos);

    printf("%s \n", method.string);
//    printf("%i\n", 2);

    if (strcmp(method.string, "GET")){
        SizedString resource = tokenizeBuffer(buffer, &bufferPos);
//        printf("Resource: \n%i\n", resource.length);
    } else {
        printf("Bad Request\n");
        return BADREQUEST;
    }

    free(method.string);
    return NOERROR;
}