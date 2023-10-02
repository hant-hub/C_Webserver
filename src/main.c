#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "util/Error.h"
#include "util/util.h"
#include <stdlib.h>


#define PORT 80
#define NUM_CONNECTIONS 128
#define BUF_SIZE 1024

        





  
   
int main() {

    // Create Websocket

    int socketHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (socketHandle == -1) {
        perror("webserver (socket)");
        return 1;
    }
    printf("Socket Successfully Created\n");
    
    //set for testing, forces operating system to quickly drop socket
    int enableReuse = 1;
    if (setsockopt(socketHandle,SOL_SOCKET,SO_REUSEADDR,&enableReuse,sizeof(int)) == -1) {
        perror("webserver (sockopt)");
        return 1;
    }


    // Bind Webstocket
    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(socketHandle, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
        perror("webserver (bind)");
        return 1;
    }
    printf("Socket Successfully Bound\n");


    //Set Socket To Listen
    if (listen(socketHandle, NUM_CONNECTIONS) != 0) {
        perror("webserver (Listen)");
        return 1;
    }
    printf("Server Successfully Set to Listen\n");


    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);


    //server Loop
    char* buffer = calloc(BUF_SIZE, sizeof(char));
    for (;;) {
        //Accept Connection
        int newConnection = accept(socketHandle, (struct sockaddr *)&host_addr, (socklen_t *)&host_addrlen);
        if (newConnection < 0) {
            perror("webserver (connection)");
            continue;
        }
        printf("Connection Accepted\n");

        //Get Client Addr
        int sockGetReturn = getsockname(newConnection, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);    
        if (sockGetReturn < 0) {
            perror("webserver (getsockname)");
            continue;
        }

        //Read Connection 
        int readReturn = read(newConnection, buffer, BUF_SIZE);
        if (readReturn < 0) {
            perror("webserver (read)");
            continue;
        }
        

        //Parse Request

        printf("request:\n%s\n", buffer);
        SizedString resp;
        int result = ParseHTTP((SizedString){buffer, BUF_SIZE}, &resp);
        if (result == NOERROR) {	
            //Write Connection

            int writeReturn = write(newConnection, (void *)resp.string, resp.length);
            if (writeReturn < 0) {
                perror("webserver (write)");
                continue;
            }

            free(resp.string);

        }
        close(newConnection);
    }
    free(buffer);

    return 0;
}
