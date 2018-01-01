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

/*void solve () {
  while (1) {
        //printf("1");
        client = accept(sock, NULL, NULL);
        if (client == -1) {
            perror("no accept");
            exit(2);
        }
        //printf("2");
        recv(client, request_str, 1024, 0);
        //printf("3");
        int k = fork();
        //printf("k = %d", k);
        if (k == 0) {
            //printf("6");
            dup2(client, 1);
            struct args arguments = make_args(request_str);
            //printf("arguments!!!!:\n");
            //print_args(arguments);
            if (strcmp(arguments.name, "ls") == 0) {
                //printf("arguments1!!!!:\n");
                //printf("ls!!!!!!\n");
                execlp(arguments.name, arguments.name, arguments.arg1, NULL);
                perror(arguments.name);
            } else if (strcmp(arguments.name, "grep") == 0){
                //printf("arguments2!!!!:\n");
                execlp(arguments.name, arguments.name, arguments.arg1, arguments.arg2, NULL);
                perror(arguments.name);
            } else {
                //printf("arguments3!!!!:\n");
            }
            close(client);
            exit(1);
        } else {
            wait(&k);
            close(client);
            break;
        }
    }
} */

struct args {
    char *name; //название функции (ls или grep)
    char *arg1; //аргумент (для grep - шаблон, для ls - директория)
    char *arg2; //только grep - имя файла, ls - NULL

};

void print_args (struct args arg) {
    printf("name: %s\n", arg.name);
    printf("arg1: %s\n", arg.arg1);
    printf("arg2: %s\n", arg.arg2);
}

struct args make_args (char* client_str) {
    //char* tmp = "in make_args";
    //printf("%s\n", tmp);
    struct args answer;
    int last_iter = 0, iter = 0;
    while (!isspace(client_str[iter]) && iter < strlen(client_str)) {
        ++iter;
    }
    //printf("name last_iter=%d, iter=%d, str_len=%d\n", last_iter, iter, (int)strlen(client_str));
    answer.name = (char*)malloc((iter - last_iter)* sizeof(char));
    for (; last_iter < iter; ++last_iter) {
        answer.name[last_iter] = client_str[last_iter];
    }
   // printf("client_str %s\n", client_str);
    //printf("answer.name %s\n", answer.name);
    if (strcmp(answer.name, "ls") != 0 && strcmp(answer.name, "grep")) {
        perror("bad request");
        exit(4);
    }
    ++iter;
    last_iter = iter;
    while (!isspace(client_str[iter]) && iter < strlen(client_str)) {
        ++iter;
    }
    //printf("check last_iter=%d, iter=%d, str_len=%d\n", last_iter, iter, (int)strlen(client_str));
    if (last_iter == iter) {
        answer.arg1 = NULL;
    } else {
        answer.arg1 = (char *) malloc((iter - last_iter) * sizeof(char));
    }
    //printf("arg1 last_iter=%d, iter=%d, str_len=%d\n", last_iter, iter, (int)strlen(client_str));
    int start = last_iter;
    for (; last_iter < iter; ++last_iter) {
        //printf("%c", client_str[last_iter]);
        answer.arg1[last_iter - start] = client_str[last_iter];
        //printf("%c", answer.arg1[last_iter - start]);
    }
    //printf("after arg1 last_iter=%d, iter=%d, str_len=%d\n", last_iter, iter, (int)strlen(client_str));
    ++iter;
    last_iter = iter;

    while (!isspace(client_str[iter]) && iter < strlen(client_str)) {
        ++iter;
    }
    //printf("arg2 last_iter=%d, iter=%d, str_len=%d\n", last_iter, iter, (int)strlen(client_str));
    if (last_iter == iter) {
        answer.arg2 = NULL;
    } else {
        answer.arg2 = (char *) malloc((iter - last_iter) * sizeof(char));
    }
    start = last_iter;
    for (; last_iter < iter; ++last_iter) {
        answer.arg2[last_iter - start] = client_str[last_iter];
    }
    //printf("after arg2 last_iter=%d, iter=%d, str_len=%d\n", last_iter, iter, (int)strlen(client_str));
    //print_args(answer);
    return answer;
}

int main(int argc, char** argv) {
    int reqiest_str_size = 65536;
    char * request_str = (char*)malloc(reqiest_str_size * sizeof(char));

    struct sockaddr_in server_info;
    int client = -1;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &server, sizeof(int));

    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(8080);
    server_info.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr *) &server_info, sizeof(server_info)) == -1) {
        perror("bind");
        close(sock);
        exit(1);
    }

    listen(sock, 1);
    printf("server running on port %d\n", 8080);
    while (1) {
        //printf("1");
        client = accept(sock, NULL, NULL);
        if (client == -1) {
            perror("no accept");
            exit(2);
        }
        //printf("2");
        recv(client, request_str, 1024, 0);
        //printf("3");
        int k = fork();
        //printf("k = %d", k);
        if (k == 0) {
            //printf("6");
            dup2(client, 1);
            struct args arguments = make_args(request_str);
            //printf("arguments!!!!:\n");
            //print_args(arguments);
            if (strcmp(arguments.name, "ls") == 0) {
                //printf("arguments1!!!!:\n");
                //printf("ls!!!!!!\n");
                execlp(arguments.name, arguments.name, arguments.arg1, NULL);
                perror(arguments.name);
            } else if (strcmp(arguments.name, "grep") == 0){
                //printf("arguments2!!!!:\n");
                execlp(arguments.name, arguments.name, arguments.arg1, arguments.arg2, NULL);
                perror(arguments.name);
            } else {
                //printf("arguments3!!!!:\n");
            }
            close(client);
            exit(1);
        } else {
            wait(&k);
            close(client);
            break;
        }
    }
    return 0;
}