//
// Created by Artem Kupriyanov on 04/11/2016.
//

#ifndef THREAD_POOL_PAR_SORT_VAS_H
#define THREAD_POOL_PAR_SORT_VAS_H

#include <stack>
#include "thread_vas.h"

class parallel_sort {
public:
    explicit parallel_sort(size_t worker_count);

    ~parallel_sort();

    template <typename It, typename Compare>
    void sort(It first, It last, Compare comp);

private:
    static const int DECOMPOSITION_MIN = 1024;

    thread_pool<void> pool_;
};

parallel_sort::parallel_sort(size_t worker_count) : pool_(worker_count) {}

parallel_sort::~parallel_sort() {
    pool_.shutdown();
}

template <typename It, typename Compare>
void parallel_sort::sort(It first, It last, Compare comp) {
    std::stack<It> firsts;
    std::stack<std::future<void>> futures;

    while (last - first > DECOMPOSITION_MIN) {
        It middle = first + (last - first) / 2;
        auto future = pool_.submit(std::bind(&parallel_sort::sort<It, Compare>, this,
                                             first, middle, comp));
        futures.emplace(std::move(future));
        firsts.push(first);
        first = middle;
    }
    std::sort(first, last, comp);

    while (!firsts.empty()) {
        pool_.wait(futures.top());
        futures.pop();

        std::inplace_merge(firsts.top(), first, last, comp);
        first = firsts.top();
        firsts.pop();
    }
}

#endif //THREAD_POOL_PAR_SORT_VAS_H
