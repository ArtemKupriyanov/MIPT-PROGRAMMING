//
// Created by Artem Kupriyanov on 03/11/2016.
//

#ifndef THREAD_POOL_THREAD_SAFE_QUEUE_H
#define THREAD_POOL_THREAD_SAFE_QUEUE_H

#include <mutex>
#include <deque>
#include <queue>
#include <condition_variable>
#include <exception>
#include <utility>
#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>

template <typename T, class Container = std::deque<T>>
class thread_safe_queue {
public:
    explicit thread_safe_queue(std::size_t capacity)
            : queueCapacity(capacity),
              isShutdown(false) {}

    void enqueue( T item);
    void pop(T & item);

    void shutdown();

private:
    Container queue;
    std::mutex queueMtx;
    std::condition_variable notEmpty;
    std::condition_variable notFull;
    std::size_t queueCapacity;
    volatile bool isShutdown;
};

template <typename T, class Container>
inline void thread_safe_queue<T, Container>::enqueue(T item) {
    std::unique_lock<std::mutex> lock(queueMtx);
    if (isShutdown) {
        throw std::exception();
    }
    notFull.wait(lock, [this]() { return queue.size() < queueCapacity; });
    queue.push_back(std::move(item));
    notEmpty.notify_one();
}

template <typename T, class Container>
inline void thread_safe_queue<T, Container>::pop(T & item) {
    std::unique_lock<std::mutex> lock(queueMtx);
    notEmpty.wait(lock, [this]() { return !(queue.empty() && !isShutdown); });
    if (isShutdown) {
        throw std::exception();
    }
    if (queue.empty()) {
        throw std::exception();
    }
    item = std::move(queue.front());
    queue.pop_front();
    notFull.notify_one();
}

template <typename T, class Container>
inline void thread_safe_queue<T, Container>::shutdown() {
    std::unique_lock<std::mutex> lock(queueMtx);
    isShutdown = true;
    lock.unlock();
    notFull.notify_all();
    notEmpty.notify_all();
}

#endif //THREAD_POOL_THREAD_SAFE_QUEUE_H
