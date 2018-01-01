#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int buffer_size = 2048;

void cat(char* file_name ,int buffer_size) {
    char* buffer = (char*)malloc(buffer_size);
    int file_descrption = open(file_name, O_RDONLY);
    int r_count;
    if (file_descrption != -1) {
        while ( r_count = read(file_descrption, buffer, buffer_size) ) {
            write(1, buffer, r_count);
        }
        close(file_descrption);
    }
    else {
        if (buffer_size > 1) {
            printf("cat: %s: Cannot open file\n", file_name);
        } else {
            printf("cat: -u: %s: Cannot open file\n", file_name);
        }
    }
    free(buffer);
}

int main(int argc, char** argv) {
    int i = 1;
    if (argv[1][0] == '-' && argv[1][1] == 'u') {
        buffer_size = 1;
        i = 2;
    }
    for (i; i < argc; i++) {
        cat(argv[i], buffer_size);
    }
     return 0;
}
