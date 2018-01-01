//
// Created by artem on 17.05.16.
//

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include <error.h>
#include <stdbool.h>

int main (int argc, char** argv) {
    int arr_size = 4096;
    char from_server[arr_size];
    char to_server[arr_size];

    int my_socket;
    struct sockaddr_in info;

    if ( (my_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("sock");
        exit(1);
    }

    info.sin_family = AF_INET;
    info.sin_port = htons(8080);
    info.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(my_socket, (struct sockaddr*)& info, sizeof(info)) == -1) {
        perror("not connected");
        exit(2);
    }

    printf("client connect!\n");
    printf("write command: \n");

    char symbol_now = getchar();
    int iter = 0;

    while (symbol_now != EOF && symbol_now != '\n') {
        to_server[iter] = symbol_now;
        ++iter;
        symbol_now = getchar();
    }

    to_server[iter] = '\n';

    send(my_socket, to_server, sizeof(to_server), 0);
    recv(my_socket, from_server, sizeof(from_server), 0);


    printf("%s", from_server);

    close(my_socket);
    return 0;
}
