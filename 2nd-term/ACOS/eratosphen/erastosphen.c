//
// Created by artem on 04.05.16.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include <stdbool.h>
#include <math.h>
#include "limits.h"

typedef long long int lli;

/*
 * Первое:
 *       знание 2 - простое, четных простых > 2 нет
 *       зная простые число до n, мы без труда можем найти простые числа до n^2
 * Второе:
 *        Пусть посчитали все простые числа на отрезке [1, n],  далее берем отрезок [n+1, n^2] и считаем простые на нем
 *        Как считаем простые числа на [n+1, n^2]?
 * Ответ: Разбиваем на k нитей. Каждая нить запускается на своем отрезке.
 *
*/

//какой-то глобальный массив с уже известными мне простыми числами

lli min(lli param1, lli param2) {
    if (param1 < param2) {
        return param1;
    }
    return param2;
}

struct vector * primes;

lli max_numer_global;
lli max_size = 10000000;

typedef struct to_thread {
    lli left_with;
    lli right_without;
    lli n;
    //len = right_without - left_with;
} args;


void create(struct vector* arr);
void del(struct vector* arr);
void * for_one_thread(void * args);
lli count_thread(lli thread_cnt, lli n_start);

void cr_part(struct to_thread * args, lli n_start, lli n_finish, lli cnt_threads) {
    lli len = n_finish - n_start;
    lli now_number = n_start + 1;
    lli thread_residue = cnt_threads;
    lli i;
    for (i = 0; i < cnt_threads; ++i) {
        lli len_one = len / thread_residue;
        thread_residue--;
        len = len - len_one;
        //printf("%s%d%s%d\n", "left: ", now_number, "right: ", now_number + len_one);
        args[i].left_with = now_number;
        args[i].right_without = now_number + len_one;
        args[i].n =n_start;
        now_number = now_number + len_one;
    }
}

typedef struct vector {
    char* buffer;
    lli buffer_size;
    lli real_size;
};

void create(struct vector* arr) {
    arr->buffer_size = max_size;
    arr->buffer = ( char* ) malloc(arr->buffer_size * sizeof(char));

    arr->buffer[0] = false;
    arr->buffer[1] = false;
    for (int i = 2; i < max_size; ++i) {
        arr->buffer[i] = true;
    }
}

void del(struct vector* arr) {
    free(arr->buffer);
}

void print_answer(lli start, lli finish) {
    lli i = start;
    char* check = primes->buffer;
    while (finish >= i ) {
        if (primes->buffer[i]) {
            printf("%lli\n", i);
        }
        ++i;
    }
}

void *for_one_thread(void * args) {
    struct to_thread *arg = (struct to_thread*) args;
    lli len = arg->right_without - arg->left_with;
    lli i;
    lli n = arg->n;
    lli left = arg->left_with;
    lli j;
    if (left > max_numer_global) {
        pthread_exit(0);
    }
    for (i = 2; i <= n; ++i) {
        if (primes->buffer[i]) {
            for (j = arg->left_with; j < arg->right_without; ++j) {
                if (j > max_numer_global) {
                    break;
                }
                if (j % i == 0 && primes->buffer[j] != 0) {
                    primes->buffer[j] = false;
                    lli step = 2;
                    while (j * step < max_numer_global && j * step < max_size) {
                        lli check = j * step;
                        primes->buffer[j * step] = false;
                        ++step;
                    }
                }
            }
        }
    }
    //printf("%lli,%lli", arg->left_with, arg->right_without);
    pthread_exit(0);
    //return 0;
}

lli count_thread(lli thread_cnt, lli n_start) {
    if (n_start * (n_start - 1) >= thread_cnt) {
        return thread_cnt;
    }
    return n_start * (n_start - 1);
}

void print_args (struct to_thread * args, int threads) {
    printf("func: print_args, size_thread:%d\n", threads);
    int i;
    for (i = 0; i < threads; ++i) {
        printf("left: %lli, right: %lli\n", args[i].left_with, args[i].right_without);
    }
}

int main (int argc, char* argv[]) {
    if (argc == 1) {
        perror("arguments");
        exit(1);
    }
    lli thread_cnt = atoi(argv[1]); //количество нитей
    lli max_number;
    if (argc > 2) {
        max_number = atoi(argv[2]); //макс число решета
    } else {
        max_number = max_size; //решето до бесконечности
    }
    max_numer_global = max_number;
    printf("thread_cnt=%lli, max_number=%lli\n", thread_cnt, max_number);
    primes = (struct vector*)malloc(sizeof(struct vector));
    create(primes);
    //print_vector(primes);
    lli n_start = 2;
    lli n = 2;
    bool infinity = (max_number == -1);

    while (max_number >= n || infinity) {
        n_start = n;
        n = n * n;

        if (n > max_numer_global) {
            n = max_numer_global + 1;
        }

        lli now_cnt_thread = count_thread(thread_cnt, n_start);
        pthread_t *threads = (pthread_t*)malloc(now_cnt_thread * sizeof(pthread_t));
        struct to_thread *args = (struct to_thread*)malloc(now_cnt_thread * sizeof(struct to_thread));
        cr_part(args, n_start, n, now_cnt_thread);
        //print_args(args, now_cnt_thread);
        lli i;
        /*if (n_start == 65536) {
            printf("65536");
        }*/
        for (i = 0; i < now_cnt_thread; ++i) {
            int status = pthread_create(threads + i, NULL, for_one_thread, args + i);
            if (status != 0) {
                printf("main error: can't create thread, status = %d\n", status);
                return 1;
            }
        }
        int status_addr;
        for (i = 0; i < now_cnt_thread; ++i ) {
            pthread_join(threads[i], (void **) status_addr);
        }
        free(args);
        free(threads);

        print_answer(n_start, min(n, max_numer_global));
    }
    del(primes);
    return 0;
}
