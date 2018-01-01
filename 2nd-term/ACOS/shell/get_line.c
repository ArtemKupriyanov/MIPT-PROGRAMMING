#include "get_line.h"

#include <stdio.h>
#include <stdlib.h>

int get_line(char **line, FILE *file) {
    int c;
    int size = 0;
    int capacity = 42; // default buffer size

    *line = (char *) malloc(capacity * sizeof(char));
    if (!*line) {
        return -1;
    }

    while ((c = fgetc(file)) != EOF && c != '\n') {
        (*line)[size] = c;
        ++size;
        if (size == capacity) {
            char *tmp;
            capacity *= 2;
            tmp = (char *) realloc(*line, capacity * sizeof(char));
            if (!tmp) {
                return -1;
            }
            *line = tmp;
        }
    }
    (*line)[size] = '\0';

    return size;
}