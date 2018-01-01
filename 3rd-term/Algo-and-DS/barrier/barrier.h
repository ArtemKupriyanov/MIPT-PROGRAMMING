//
// Created by Artem Kupriyanov on 06/10/2016.
//

#ifndef BARRIER_BARRIER_H
#define BARRIER_BARRIER_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

class barrier {
public:
    explicit barrier(size_t num_threads);
    void enter();

private:
    size_t capacity;
    size_t current_size;
    condition_variable first_block;
    condition_variable second_block;
    mutex barrier_mutex;
    bool leaving;
};

barrier::barrier(size_t num_threads)
        : capacity(num_threads),
          current_size(0),
          leaving(0) {}

void barrier::enter() {
    unique_lock<mutex> lock(barrier_mutex);
    first_block.wait(lock, [this](){ return !leaving; } );
    ++current_size;
    second_block.wait(lock, [this](){ return (capacity == current_size) || (leaving == 1); } );
    leaving = 1;
    --current_size;
    second_block.notify_all();
    if (current_size == 0) {
        leaving = 0;
        first_block.notify_all();
    }
}

#endif //BARRIER_BARRIER_H
