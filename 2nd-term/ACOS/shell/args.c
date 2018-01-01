#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define DEFAULT_CAPACITY 4

char directory[256];

void update_directory (char* directory_main) {
    char *check = directory;
    strcpy(directory_main, directory);
}

void get_directory (char* directory_main) {
    strcpy(directory, directory_main);
    *directory_main = *directory;
}

int try_open_directory(char* str) {
    char* dirname = (char*) malloc(256 * sizeof(char));
    if (str[0] =='.') {
        if (str[0]=='/') {
            *str = *(str + 2);
            strcpy(dirname, directory);
            strcat(dirname, str);
        }
    } else {
        dirname = str;
    }
    DIR *dir;
    dir = opendir(dirname);
    if( !dir ) {
        return 0;
    }
    return 1;
}

void run_cd (char** argv) {
    char * way = argv[1];
    char* new_directory = (char*) malloc(256 * sizeof(char));
    strcpy(new_directory, directory);
    if (new_directory[strlen(new_directory) - 1] != '/') {
        strcat(new_directory, "/");
    }
    if (way[0] == '/') {
        strcpy(new_directory, way);
    }
    else if (way[0] == '.' && way[1] == '/') {
        strcpy(way, way + 2);
        strcat(new_directory, way);
    }
    if ( try_open_directory(new_directory) ) {
        strcpy(directory, new_directory);
    } else {
        perror("No such directory");
    }
}

void args_new(args_t *args) {
    args->argv = (char **) malloc((DEFAULT_CAPACITY + 1) * sizeof(char *));
    args->argv[0] = NULL;
    args->argc = 0;
    args->capacity = DEFAULT_CAPACITY;
}

void args_add(args_t *args, const char *arg) {
    if (args->argc == args->capacity) {
        args->argv = (char **) realloc(args->argv,
                                       (args->capacity + 1) * 2 * sizeof(char *));
        args->capacity *= 2;
    }

    args->argv[args->argc] = (char *) malloc(strlen(arg));
    strcpy(args->argv[args->argc], arg);
    ++args->argc;
    args->argv[args->argc] = NULL;
}

void args_exterminate(args_t *args) {
    int i;

    for (i = 0; i < args->argc; ++i) {
        free(args->argv[i]);
    }
}

/*
void try_make_directory(char* file_name) {

}*/