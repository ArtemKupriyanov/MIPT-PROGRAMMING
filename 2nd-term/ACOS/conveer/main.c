#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

int** file_descriptor;
int size_file_descr;

void son(char *str, int n) {
    int k = fork(), i;
    if (k < 0) {
        perror("error");
        exit(1);
    }
    if (k == 0) {
        if (n == 0) {
            dup2(file_descriptor[n][1], 1);
        } else {
            dup2(file_descriptor[n][1], 1);
            dup2(file_descriptor[n - 1][0], 0);
        }
        for (i = 0; i < size_file_descr; ++i) {
            close(file_descriptor[i][0]);
            close(file_descriptor[i][1]);
        }
        execlp(str, str, NULL);
        perror(str);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    size_file_descr = argc - 2;
    file_descriptor = (int**)malloc((size_file_descr + 1) * sizeof(int*));
    int i, n;
    for (i = 0; i < size_file_descr + 1; ++i) {
        file_descriptor[i] = (int*)malloc(2 * sizeof(int));
    }
    for (i = 0; i < size_file_descr; ++i) {
        pipe(file_descriptor[i]);
    }
    for (i = 1; i < argc; ++i) {
        son(argv[i], i - 1);
    }

    for (i = 0; i < size_file_descr; ++i) {
        close(file_descriptor[i][0]);
        close(file_descriptor[i][1]);
    }
    for (i = 1; i < argc; ++i) {
        wait(&n);
    }
    return 0;
}
