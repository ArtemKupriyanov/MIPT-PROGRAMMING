//
// Created by Artem Kupriyanov on 03/11/2016.
//

#ifndef THREAD_POOL_THREAD_POOL_H
#define THREAD_POOL_THREAD_POOL_H

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

template <class Value>
class thread_pool {
public:
    explicit thread_pool(std::size_t numWorkers);
    std::future<Value> submit(std::function<Value()> exe);
    void shutdown();

private:
    std::size_t numWorkers;
    std::queue<std::packaged_task<Value()>> pool;
    std::vector<std::thread> executors;
    std::mutex queueMtx;
    std::condition_variable notFull;
    volatile bool isShutdown;
    bool execute(int maxWait);
};

template <class Value>
thread_pool<Value>::thread_pool(size_t numWorkers) :
        isShutdown(false) {
    for (size_t i = 0; i < numWorkers; ++i) {
        executors.emplace_back([this]() { while (execute(-1)); });
    }
}

template <class Value>
bool thread_pool<Value>::execute(int maxWait) {
    std::unique_lock<std::mutex> lock(queueMtx);
    if (maxWait == -1) {
        notFull.wait(lock, [this]() { return isShutdown || !pool.empty(); });
    } else {
        notFull.wait_for(lock, maxWait * std::chrono::milliseconds(),
                         [this]() { return isShutdown || !pool.empty(); });
    }
    if (pool.empty()) {
        return false;
    }
    std::packaged_task<Value()> exe = std::move(pool.front());
    pool.pop();
    lock.unlock();
    exe();
    return true;
}

template <class Value>
std::future<Value> thread_pool<Value>::submit(std::function<Value()> exe) {
    if (isShutdown) {
        throw std::exception();
    }
    std::unique_lock<std::mutex> lock(queueMtx);
    pool.emplace(exe);
    std::future<Value> myFuture = pool.back().get_future();
    notFull.notify_one();
    return myFuture;
}

template <class Value>
void thread_pool<Value>::shutdown() {
    isShutdown = true;
    std::unique_lock<std::mutex> lock(queueMtx);
    lock.unlock();
    notFull.notify_all();
    for (auto & exec : executors) {
        exec.join();
    }
}

#endif //THREAD_POOL_THREAD_POOL_H
