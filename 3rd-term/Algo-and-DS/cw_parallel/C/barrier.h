//
// Created by Artem Kupriyanov on 09/12/2016.
//

#include <atomic>
#include "semaphore.h"

#ifndef C_BARRIER_H
#define C_BARRIER_H

class barrier {
public:
    explicit barrier()
            : count_of_thread_which_are_waiting(0),
              no_thread(0),
              mtx(1),
              turnstile(0),
              turnstile2(0)
            {}

    void enter();

private:
    std::atomic<int> count_of_thread_which_are_waiting, no_thread;
    semaphore mtx;
    semaphore turnstile;
    semaphore turnstile2;
};

void barrier::enter() {
    std::atomic<int> local_for_each_thread;
    mtx.aquire();
    local_for_each_thread.store(no_thread.load());
    count_of_thread_which_are_waiting.fetch_add(1);
    if (count_of_thread_which_are_waiting.load() == 2) {
        std::atomic<int> tmp;
        tmp.store(1);
        while (tmp.load() <= 2) {
            if (local_for_each_thread.load() == 0)
                turnstile.release();
            else
                turnstile2.release();
            tmp.fetch_add(1);
        }
        count_of_thread_which_are_waiting.store(0);
        no_thread.exchange(1 - no_thread.load());
    }
    mtx.release();
    if (local_for_each_thread.load() == 0) {
        turnstile.aquire();
    }
    else {
        turnstile2.aquire();
    }
}

#endif //C_BARRIER_H
