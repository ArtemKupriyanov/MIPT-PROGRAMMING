//
// Created by artem on 23.05.16.
//
#define GETTOK(str) strtok(str, " \n")

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
#include <sys/stat.h>
#include <fcntl.h>

#include "support_commands.h"

int BUFFERSIZE = 512;

char* start_directory_in_support;

void get_start_directory_for_support_commands(char* start_directory) {
    start_directory_in_support = start_directory;
}

int get_line(int sock, char* buf, int size) {
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n')) {
        n = (int) recv(sock, &c, 1, 0);
        if (n > 0) {
            if (c == '\r') {
                n = (int) recv(sock, &c, 1, MSG_PEEK);
                if ((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
            buf[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buf[i] = '\0';

    return(i);
}

char* read_file(char* file_name) {
    int fd = open(file_name, O_RDONLY);
    char *buffer = (char*)malloc(BUFFERSIZE * sizeof(char));
    int size = BUFFERSIZE;
    int len = 0;
    int size_part;
    while ((size_part = read(fd, buffer + len, BUFFERSIZE)) > 0) {
        buffer = realloc(buffer, size + BUFFERSIZE);
        size += BUFFERSIZE;
        len += size_part;
    };

    buffer[len] = '\0';

    close(fd);
    return buffer;
}

//разбиваем строку по пробелам
char** string_parser(char *str) {
    /**cnt_words = 0;
    char* str_const = (char*)malloc(strlen(str) * sizeof(char));
    strcpy(str_const, str);
    char* token = GETTOK(str);
    while (token != NULL) {
        *cnt_words += 1;
        token = GETTOK(NULL);
    }
    char **answer = (char**)(malloc((*cnt_words) * sizeof(char*)));
    strcpy(str, str_const);
    token = GETTOK(str);
    *cnt_words = 0;
    while (token != NULL) {
        strcpy(answer[(*cnt_words)], token);
        *cnt_words += 1;
        token = GETTOK(NULL);
    }
    return answer;*/
    int counter;
    counter = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (!isspace(str[i])) {
            if (i == 0 || isspace(str[i - 1])) {
                ++counter;
            }
        }
    }

    char **answer = (char**)malloc( counter * sizeof(char*));
    counter = 0;
    int start_iter = 0;

    for (int i = 0; i < strlen(str); ++i) {
        if ( !isspace(str[i]) ) {
            if ( isspace(str[i + 1]) || (i + 1 == strlen(str)) ) {
                answer[counter] = (char *)malloc((i - start_iter + 2) * sizeof(char));
                answer[counter][i - start_iter + 1] = '\0';
                memcpy(answer[counter], str + start_iter, i - start_iter + 1);
                ++counter;
            }
        }
        if (!isspace(str[i]) ) {
            if ( (i == 0) || isspace(str[i - 1]) ) {
                start_iter = i;
            }
        }
    }

    return answer;
}

char type(char *file_name) {
    char answer;
    if (strlen(file_name) >= 9) {
        char *first_symbols = (char*)malloc(9 * sizeof(char));
        memcpy(first_symbols, file_name, 9 * sizeof(char));

        if (strcmp(first_symbols, "/cgi-bin/") == 0) {
            free(first_symbols);
            answer = 's';
            return answer;
        }
        free(first_symbols);
    }
    char full_file_name[1024];
    strcpy(full_file_name, start_directory_in_support);
    strcat(full_file_name, file_name);
    struct stat st;
    stat(full_file_name, &st);
    if (S_ISDIR(st.st_mode))
        answer = 'd';
    else
        answer = 'f';
    return answer;
}

int my_find(char* full_file_name) {
    struct stat st;
    int founded = stat(full_file_name, &st);
    if (founded >= 0) {
        return 1;
    }
    return 0;
}


void make_html(char *html, char *index) {
    char *file_content = read_file(index);
    strcat(html, file_content);
}