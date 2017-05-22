#include "thread_pool.hpp"

void thread_safe_queue::enqueue(function<void()> item) {
    unique_lock<mutex> lck(mtx);
    if (is_shutdown.load())
        throw exception();
    Q.push(move(item));
    not_empty_cv.notify_one();
}

void thread_safe_queue::pop(function<void()>& item) {
    unique_lock<mutex> lck(mtx);
    if (is_shutdown.load() && Q.empty())
        throw exception();
    not_empty_cv.wait(lck, [this](){if (is_shutdown.load() && Q.empty()) throw exception(); return !Q.empty();});
    item = move(Q.front());
    Q.pop();
}

void thread_safe_queue::shutdown() {
    is_shutdown.store(true);
    not_empty_cv.notify_all();
}

ThreadPool::ThreadPool (const size_t num_workers): num_workers(num_workers), is_shutdown(false) {
    for (size_t i = 0; i < num_workers; ++i)
        workers.emplace_back(thread( [this]() {
            function<void()> task;
            for(;;)
                try {
                    TSQ.pop(task);
                    task();
                }
            catch(...) {
                return;
            }
        } ));
}

void ThreadPool::submit (function<void()> func) {
    if (is_shutdown.load())
        throw exception();
    TSQ.enqueue(move(func));
}

void ThreadPool::shutdown () {
    is_shutdown.store(true);
    TSQ.shutdown();
    for (auto& t : workers)
        t.join();
}
