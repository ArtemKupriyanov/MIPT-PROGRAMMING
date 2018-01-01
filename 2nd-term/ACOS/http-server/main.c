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

//не стал реализовывать ..  , потому что есть браузерная функция <-

char *NOT_FOUND_404 = "404\n\0";
char *FORBIDDEN_403 = "403\n\0";
char *START = "" "HTTP/1.0 200 OK\r\n" "Server: httpd\r\n" "Content-Type: text/html\r\n" "Content-Length: 65536\r\n" "\r\n";

const int BUFFER_SIZE = 16000;

char *start_directory;
int client, sock;
struct sockaddr_in server_info;

void send_error_page(int client, const char* problem, const char* definition) {
    char buf[1024];

    sprintf(buf, "HTTP/1.0 %s %s\r\n", problem, definition);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Server: jdbhttpd/0.1.0\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>%s</TITLE>\r\n", definition);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>The server has problems with your query %s\r\n", problem);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}


//скрипты
void run_script(char* full_file_name) {
    int result = execlp(full_file_name, full_file_name, NULL);
    if (result == -1) {
        send(client, NOT_FOUND_404, strlen(NOT_FOUND_404), 0);
        exit(404);
    }
}

/*
void make_hyperlink(struct dirent * current, char** html_code, char** dir_name) {
    strcat(*html_code, "<a href = ");
    strcat(*html_code, *dir_name);
    if ((strlen((*current).d_name) > 0) && (*html_code[strlen(*html_code) - 1] != '/')) {
        strcat(*html_code, "/");
    }
    strcat(*html_code, (*current).d_name);
    strcat(*html_code, "> ");
    strcat(*html_code, (*current).d_name);
    strcat(*html_code, "</a>\n<br>\n");
}*/

void make_dir(char *html_code, char *full_dir_name, char *dir_name) {
    DIR * dir = opendir(full_dir_name);
    struct dirent current, *answer;
    do {
        answer = NULL;
        readdir_r(dir, &current, &answer);
        if (answer == NULL) {
            break;
        }
        if (current.d_name[0] == '.') {
            continue;
        }
        //make hyperlink
        //make_hyperlink(&current, &html_code, &dir_name);
        strcat(html_code, "<a href = ");
        strcat(html_code, dir_name);
        if (strlen(current.d_name) > 0) {
            if (html_code[strlen(html_code) - 1] != '/') {
                strcat(html_code, "/");
            }
        }
        strcat(html_code, (current).d_name);
        strcat(html_code, "> ");
        strcat(html_code, (current).d_name);
        strcat(html_code, "</a>\n<br>\n");
    } while (answer != NULL);
    closedir(dir);
}

/*
void send_directory(int client, const char* path) {
    struct dirent **namelist;
    int n = scandir(path, &namelist, 0, alphasort);
    if (n < 0) {
        send_error_page(client, "404", "Not Found");
    }
    char buf[65534] = "\r\n <html> <head> <title>Index</title> </head> <body>\n"
            "<h1>Index</h1>\n <table>\n <tr><th>Name</th><th>"
            "\n <tr><th colspan=\"4\"><hr></th></tr>\n";
    int i = 0;
    for (i = 0; i < n; ++i) {
        char filename[65536] = "";
        sprintf(filename, "%s/%s", path, namelist[i]->d_name);

        char* row_pattern = "<tr>"
                "<td><a href=\"%s\">%s</a></td></tr>\n";
        char row[65536];
        sprintf(row, row_pattern, filename, namelist[i]->d_name);
        strcat(buf, row);
    }
    free(namelist);


    strcat(buf, "</table>\n");
    strcat(buf, "</body></html>\n");

    char* response_header = ""
            "HTTP/1.0 200 OK\r\n"
            "Server: httpd\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %d\r\n"
            "\r\n";

    char header_buf[65536];
    sprintf(header_buf, response_header, strlen(buf));
    send(client, header_buf, strlen(header_buf)*sizeof(char), 0);
    send(client, buf, strlen(buf)*sizeof(char), 0);
}*/

char* show_dir(char* full_dir_name, char *dir_name) {
    char html[65536];
    strcpy(html, START); //начальный html-код
    char index[BUFFER_SIZE];
    strcpy(index, full_dir_name);
    if (index[strlen(index) - 1] != '/') {
        strcat(index, "/");
    }
    strcat(index, "index.html");
    // выдаем index.html - если он есть
    if ( my_find(index) ) {
        make_html(html, index);
    }
    else {
        make_dir(html, full_dir_name, dir_name);
    }
    strcat(html, "\0");
    return html;
}

//отправить файл
//забил - вывожу катом
void send_file(int client, const char* path) {
    FILE* resource = NULL;
    resource = fopen(path, "r");
    if (resource == NULL) {
        send_error_page(client, "403", "Forbidden");
    }
    else {
        char buf[BUFFER_SIZE];
        fgets(buf, sizeof(buf), resource);
        while ( !feof(resource) ) {
            send(client, buf, strlen(buf), 0);
            fgets(buf, sizeof(buf), resource);
        }
    }
    fclose(resource);
}

char* show_file(char *full_name) {
    int fd = open("show_file.txt", O_WRONLY | O_TRUNC);
    dup2(fd, 1);
    int k = execlp("cat", "cat", full_name, NULL);
    close(fd);
    if (k >= 0) {
        char *ans = read_file("show_file.txt");
        return ans;
    } else {
        perror("forbidden");
        return FORBIDDEN_403;
    }
}

void accept_request(char *request) {
    char **words = string_parser(request);
    char *name;
    name = "/";
    //words[0][0] = get
    if (words[1][0] == '/') {
        name = words[1];
    }
    char type_element = type(name);

    char *full_name = (char *)malloc(strlen(name) * sizeof(char));
    strcpy(full_name, name);


    char full_name_of_obj[BUFFER_SIZE];
    strcpy(full_name_of_obj, start_directory);
    strcat(full_name_of_obj, full_name);
    if (!my_find(full_name_of_obj)) {
        send(client, NOT_FOUND_404, strlen(NOT_FOUND_404), 0);
        free(words);
        return;
    }

    char *answer;
    if (type_element == 'f') {
        answer = show_file(full_name_of_obj);
    } else if (type_element == 's') {
        run_script(full_name_of_obj);
    } else if (type_element == 'd') {
        answer = show_dir(full_name_of_obj, name);
    }
    send(client, answer, strlen(answer), 0);

    free(words);
}

int main(int argc, char **argv) {
    int one = 1;

    struct sockaddr_in client_name;
    int client_name_len = sizeof(client_name);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

    if (sock == -1) {
        perror("socket");
        exit(1);
    }

    if (argc != 3) {
        printf("INCORRECT:\n1st arg is port\n2nd arg is start directory!\n");
        exit(1);
    }

    int port = atoi(argv[1]);
    start_directory = argv[2];

    get_start_directory_for_support_commands(start_directory);


    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(port);
    server_info.sin_addr.s_addr = htonl(INADDR_ANY);

    int bnd = bind(sock, (struct sockaddr *)&server_info, sizeof(server_info));

    if (bnd == -1) {
        perror("bind");
        exit(2);
    }

    listen(sock, 1);

    printf("http running on port %d\n", port);

    while (1) {
        client = accept(sock, (struct sockaddr*) &client_name, (socklen_t*) &client_name_len);
        if (client == -1) {
            perror("accept");
            exit(3);
        }
        char *buffer = (char*)malloc(BUFFER_SIZE * sizeof(char));
        int bytes_read = recv(client, buffer, BUFFER_SIZE, 0);
        int k = fork();

        if (k == 0) {
            dup2(client, 1);
            accept_request(buffer);
            close(client);
            free(buffer);
            exit(1);
        }
        else {
            wait(&k);
            close(client);
        }
    }
    close(sock);
    return 0;
}
