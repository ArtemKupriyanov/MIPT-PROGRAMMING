//
// Created by Artem Kupriyanov on 04/11/2016.
//

#ifndef THREAD_POOL_PARALLEL_SORT_H
#define THREAD_POOL_PARALLEL_SORT_H

#include <functional>
#include <stack>
#include <mutex>
#include <stack>
#include <queue>
#include <condition_variable>
#include <exception>
#include <utility>
#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

template <class Value>
class thread_pool {
public:
    explicit thread_pool(size_t numWorkers);
    std::future<Value> submit(std::function<Value()> task);
    void shutdown();
    Value wait(std::future<Value> &future);

private:
    bool execute(int numWorkers);

    std::mutex queueMtx;
    std::condition_variable notFull;
    std::queue<std::packaged_task<Value()>> task_queue;
    std::vector<std::thread> executors;
    volatile bool shutDown;
};

template <class Value>
thread_pool<Value>::thread_pool(size_t numWorkers)
        : shutDown(false) {
    auto exec = [this]() { while (execute(-1)); };
    for (size_t i = 0; i < numWorkers; ++i) {
        executors.emplace_back(exec);
    }
}

template <class Value>
Value thread_pool<Value>::wait(std::future<Value> &future) {
    auto out = std::chrono::milliseconds::zero();
    while (std::future_status::ready != future.wait_for(out)) {
        execute(10);
    }
}

template <class Value>
bool thread_pool<Value>::execute(int numWorkers) {
    std::unique_lock<std::mutex> lock(queueMtx);
    if (numWorkers < 0) {
        notFull.wait(lock, [this]() {
            return shutDown || !task_queue.empty();
        } );
    } else {
        notFull.wait_for(lock, numWorkers * std::chrono::milliseconds(),
                            [this]() {
                                return shutDown || !task_queue.empty();
                            });
    }
    if (task_queue.empty()) {
        return false;
    }
    auto task = std::move(task_queue.front());
    task_queue.pop();
    lock.unlock();
    task();
    return true;
}

template <class Value>
void thread_pool<Value>::shutdown() {
    std::unique_lock<std::mutex> lock(queueMtx);
    shutDown = true;
    lock.unlock();
    notFull.notify_all();
    for (auto &exec : executors) {
        exec.join();
    }
}

template <class Value>
std::future<Value> thread_pool<Value>::submit(std::function<Value()> task) {
    std::unique_lock<std::mutex> lock(queueMtx);
    if (shutDown) {
        throw std::exception();
    }
    task_queue.emplace(task);
    auto future = task_queue.back().get_future();
    notFull.notify_one();
    return future;
}


class parallel_sort {
public:
    explicit parallel_sort(size_t numWorkers)
            : task_queue(numWorkers) {};
    template <typename RandomAccessIterator, typename Compare>
    void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
    ~parallel_sort() {
        task_queue.shutdown();
    };

private:
    static const int L = 4096;
    thread_pool<void> task_queue;
};

template <typename RandomAccessIterator, typename Compare>
void parallel_sort::sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    std::stack<RandomAccessIterator> firstDeque;
    std::stack<std::future<void>> futureDeque;

    while (last - first > this->L) {
        RandomAccessIterator mid = (last - first) / 2 + first;
        auto futu = task_queue.submit(std::bind(
                &parallel_sort::sort<RandomAccessIterator, Compare>,
                this,
                first,
                mid,
                comp)
        );
        firstDeque.push(first);
        futureDeque.emplace(std::move(futu));
        first = mid;
    }
    std::sort(first, last, comp);

    while (!firstDeque.empty()) {
        task_queue.wait(futureDeque.top());
        futureDeque.pop();
        std::inplace_merge(firstDeque.top(), first, last, comp);
        first = firstDeque.top();
        firstDeque.pop();
    }
}

#endif //THREAD_POOL_PARALLEL_SORT_H
