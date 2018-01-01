#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

int word_in_buffer_now = 0;
int buffer_size = 0;
int word_size = 0;

char** buffer = NULL;
char* word = NULL;

int max (int a, int b) {
    if (a > b)
        return a;
    return b;
}

void flushToArray() {
    if (word_in_buffer_now + 1 > buffer_size) {
        buffer_size = max(buffer_size * 2, 1);
        buffer = realloc(buffer, buffer_size*sizeof(char*));
    }
    addSymbolInWord('\0');
    buffer[word_in_buffer_now] = word;
    word_in_buffer_now = word_in_buffer_now + 1;
}

char* newWord() {
    char* word = (char*)malloc(sizeof(char));
    word_size = 0;
    return word;
}

void addSymbolInWord(char symbol_now) {
    word[word_size] = symbol_now;
    word_size = word_size + 1;
    word = realloc(word, word_size + 1);
}

int isLexem(char symbol) {
    if (symbol == '&' || symbol == '|' || symbol == ';') {
        return 1;
    }
    return 0;
}

int compare(const void * s1, const void * s2) {
    return strcmp(*(char**) s1, *(char**) s2);
}

int main(void) {
    char symbol_now;
    char symbol_next;
    int have_symbol_next = 0;
    int have_open_quote = 0;
    int error = 0;
    char quote_first;
    word = newWord(&word_size);
    symbol_now = getchar();

    while (symbol_now != EOF) {
        if (symbol_now == '"' || symbol_now == '\'') {
            quote_first = symbol_now;
            have_open_quote = 1;
            symbol_now = getchar();
            while (symbol_now != EOF && symbol_now != quote_first) {
                addSymbolInWord(symbol_now);
                symbol_now = getchar();
            }
            if (symbol_now == quote_first) {
                have_open_quote = 0;
                symbol_now = getchar();
            } else {
                printf("%s\n", "error");
                error = 1;
            }
        } else {
            if (isspace(symbol_now)) {
                if (word_size > 0) {
                    //сбрасываем полученную лексему
                    flushToArray(word);
                }
                word = newWord();  //создаем пустое слово
            }
            else {
                if ( isLexem(symbol_now) ) {
                    if (word_size > 0) {
                        flushToArray();
                    }
                    word = newWord();
                    if (symbol_now == ';') {
                        addSymbolInWord(symbol_now);
                        if (word_size > 0) {
                            flushToArray();
                        }
                        word = newWord();
                        have_symbol_next = 0;
                    } else {
                        symbol_next = getchar();
                        have_symbol_next = 1;
                        if (symbol_now == symbol_next) {
                            addSymbolInWord(symbol_now);
                            addSymbolInWord(symbol_next);
                            if (word_size > 0) {
                                flushToArray();
                            }
                            word = newWord();
                            have_symbol_next = 0;
                        }
                        else {
                            addSymbolInWord(symbol_now);
                            if (word_size > 0) {
                                flushToArray();
                            }
                            word = newWord();
                        }
                    }
                } else {
                    addSymbolInWord(symbol_now);
                }
            }
            if (have_symbol_next == 0) {
                symbol_now = getchar();
            } else {
                symbol_now = symbol_next;
                have_symbol_next = 0;
            }
        }
    }
    if (word_size > 0) {
        flushToArray(word);
    }
    if (error == 0) {
        int i;
        qsort(buffer, word_in_buffer_now, sizeof(char**), compare);
        for (i = 0; i < word_in_buffer_now; i++) {
            printf("%c%s%c",'"',buffer[i],'"');
            printf("\n");
        }
        //очищаем выделенную память
        for (i = 0; i < buffer_size; i++) {
            free(buffer[i]);
        }
        free(buffer);
    }
    free(word);
    return 0;
}
