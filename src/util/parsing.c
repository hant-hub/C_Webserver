#include "string/util_string.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>









enum ParseResult ParseHTTP(SizedString buffer, SizedString* out) {
    SizedString method = tokenizeBuffer(buffer.string); 
    const static char header[] = 
        "HTTP/1.0 200 OK\r\n"
        "Server: webserver-c\r\n"
        "Connection: closed\r\n"
        "Content-Type: text/html\r\n"
        "\r\n";
    printf("method: %s\n", method.string); 

    char* asset;
    if (strcmp(method.string, "GET") == 0){
        SizedString resource = tokenizeBuffer(NULL);
        char path[resource.length + strlen("./html")];
        strcpy(path, "./html");
        strcat(path, resource.string);


        if (strcmp(resource.string, "/") == 0) {
           char filepath[resource.length + 10];
           strcpy(filepath, path);
           strcat(filepath, "/index.html");
           asset = DumpFile(filepath); 

        } else {
            
            return UNKNOWNREQUEST; 
        }

    } else {
        printf("Bad Request\n");
        return BADREQUEST;
    }

    size_t headlen = strlen(header);
    size_t reqsize = headlen + strlen(asset);

    char *request = calloc(reqsize, sizeof(char));
    strcat(request, header);
    
    for (int i = headlen; i < reqsize; i++) {
        request[i] = asset[i-headlen];
    }

    out->string = request;
    out->length = reqsize;
    if (asset != 0)  free(asset);
    return (enum ParseResult)NOERROR;
}
