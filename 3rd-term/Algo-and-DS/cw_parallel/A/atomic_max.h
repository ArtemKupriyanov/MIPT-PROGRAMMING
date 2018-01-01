//
// Created by Artem Kupriyanov on 09/12/2016.
//

#include <atomic>

#ifndef A_ATOMIC_MAX_H
#define A_ATOMIC_MAX_H

int fetch_and_set_max(std::atomic <int>& x, int y) {
    if (x.load() > y) {
        return x.load();
    }
    x.exchange(y);
    return y;
}

#endif //A_ATOMIC_MAX_H
