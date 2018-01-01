#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int bufferSize = 1024;

struct pieceOfPattern {
    int serve[256];
    unsigned char mode;
};

struct pieceOfPattern* pattern;
int patter_size;
unsigned char mode = 'n';

void doPointMode (unsigned char now_symbol) {
    if (mode == 'n') {
        for (unsigned char x = 0; x < 256; ++x) {
            if (x != '\n') {
                pattern[patter_size].serve[x] = 1;
            } else {
                pattern[patter_size].serve[now_symbol] = 1;
            }
        }
    }
}

void doOpenSquareBracketMode(unsigned char now_symbol) {
    if (mode == 'n') {
        mode = '[';
    } else {
        pattern[patter_size].serve[now_symbol] = 1;
    }
}

void doCloseSquaresBracketMode(unsigned char now_symbol) {
    if (mode == '[') {
        mode = 'n';
        pattern[patter_size].mode = 'n';
        ++patter_size;
    } else {
        pattern[patter_size].serve[now_symbol] = 1;
    }
}

void doMinusMode(unsigned char now_symbol, const unsigned char* str, int* i) {
    if (mode == 'n') {
        pattern[patter_size].serve[now_symbol] = 1;
    } else {
        if ((str[*i + 1] == ']') || (*i + 1 >= strlen(str)) || (*i == 0)) {
            perror("Incorrect pattern3\n");
            exit(1);
        }
        if (str[*i - 1] > str[*i + 1]) {
            perror("Incorrect pattern4\n");
            exit(1);
        }
        for (int j = str[*i - 1]; j <= str[*i + 1]; ++j) {
            pattern[patter_size].serve[j] = 1;
        }
        *i += 1;
    }
}

void doQuestionMarkMode(unsigned char now_symbol) {
    if (mode == 'n') {
        if (patter_size == 0) {
            perror("Incorrect pattern2\n");
            exit(1);
        }
        pattern[patter_size - 1].mode = '?';
    } else {
        pattern[patter_size].serve[now_symbol] = 1;
    }
}

void doStarMode(unsigned char now_symbol) {
    if (mode == 'n') {
        if (patter_size == 0) {
            perror("Incorrect pattern1\n");
            exit(1);
        }
        pattern[patter_size - 1].mode = '*';
    } else {
        pattern[patter_size].serve[now_symbol] = 1;
    }
}

void makePattern(const unsigned char* str) {
    int is_slash = 0;
    patter_size = 0;
    pattern = (struct pieceOfPattern*)malloc(strlen(str) * sizeof(struct pieceOfPattern));
    for (int i = 0; i < strlen(str); ++i) {
        for (int j = 0; j < 256; ++j) {
            pattern[i].serve[j] = 0;
        }
    }
    for (int i = 0; i < strlen(str); ++i) {
        unsigned char now_symbol = str[i];
        if (is_slash != 0) {
            pattern[patter_size].serve[now_symbol] = 1;
            is_slash = 0;
            if (mode == 'n') {
                patter_size++;
            }
            continue;
        }
        if (now_symbol == '[') {
            doOpenSquareBracketMode(now_symbol);
            continue;
        }
        if (now_symbol == '.') {
            doPointMode(now_symbol);
            continue;
        }
        if (now_symbol == ']') {
            doCloseSquaresBracketMode(now_symbol);
            continue;
        }
        if (now_symbol == '\\') {
            is_slash = 1;
            continue;
        }
        if (now_symbol == '*') {
            doStarMode(now_symbol);
            continue;
        }
        if (now_symbol == '?') {
            doQuestionMarkMode(now_symbol);
            continue;
        }
        if (now_symbol == '-') {
            doMinusMode(now_symbol, str, &i);
            continue;
        }
        pattern[patter_size].serve[now_symbol] = 1;
        if (mode == 'n') {
            pattern[patter_size].mode = 'n';
            patter_size++;
        }
    }
    if (mode != 'n') {
        perror("incorrect pattern5\n");
        exit(1);
    }
}

int checkStringFromPlace(const unsigned char* str, int pos_s, int pos_p, int str_len) {
    if (pos_p == patter_size) {
        return 1;
    }
    if (pos_s == str_len) {
        return 0;
    }
    if (pattern[pos_p].mode == 'n') {
        return pattern[pos_p].serve[str[pos_s]] * checkStringFromPlace(str, pos_s + 1, pos_p + 1, str_len);
    }
    if (pattern[pos_p].mode == '*') {
        if (pattern[pos_p].serve[str[pos_s]]) {
            return checkStringFromPlace(str, pos_s + 1, pos_p, str_len) +
                   checkStringFromPlace(str, pos_s + 1, pos_p + 1, str_len);
        }
        if (checkStringFromPlace(str, pos_s, pos_p + 1, str_len)) {
            return 1;
        }
        return 0;
    }
    if (pattern[pos_p].mode == '?') {
        if (pattern[pos_p].serve[str[pos_s]]) {
            return checkStringFromPlace(str, pos_s + 1, pos_p + 1, str_len);
        }
        if (checkStringFromPlace(str, pos_s, pos_p + 1, str_len)) {
            return 1;
        }
        return 0;
    }
    return 1;
}

int stringToPattern(const unsigned char* str, int strLen) {
    for (int i = 0; i < strLen; ++i) {
        if (checkStringFromPlace(str, i, 0, strLen)) {
            return 1;
        }
    }
    return 0;
}

void fileToPattern(const unsigned char* file_name) {
    FILE* my_file = fopen(file_name, "r");
    unsigned char* str = (unsigned char*)malloc(bufferSize);
    unsigned char now_symbol;
    int len = 0;
    int memory = bufferSize;
    while (!feof(my_file)) {
        now_symbol = fgetc(my_file);
        if (len == memory) {
            memory += bufferSize;
            str = realloc(str, memory);
        }
        str[len++] = now_symbol;
        if (now_symbol == '\n') {
            if (stringToPattern(str, len)) {
                write(1, str, len);
            }
            len = 0;
        }
    }
    free(str);
}

int main(int argc, unsigned char** argv) {
    if (argc < 2) {
        perror("No pattern\n");
        exit(1);
    }
    makePattern(argv[1]);
    for (int i = 2; i < argc; i++) {
        fileToPattern(argv[i]);
    }
    return 0;
}