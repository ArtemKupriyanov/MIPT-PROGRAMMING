//
// Created by artem on 23.05.16.
//

#ifndef HTTP_SERVER_STRING_PARSER_H
#define HTTP_SERVER_STRING_PARSER_H

char **string_parser(char *str);
char* read_file(char* file_name);
char type(char *obj);
int my_find(char *full_file_name);
void get_start_directory_for_support_commands(char* start_directory);
void make_html(char *html_code, char *index_html);
int get_line(int sock, char* buf, int size);

#endif //HTTP_SERVER_STRING_PARSER_H
