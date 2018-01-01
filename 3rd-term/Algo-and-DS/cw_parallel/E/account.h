//
// Created by Artem Kupriyanov on 09/12/2016.
//
#include <mutex>
#include <condition_variable>

#ifndef E_ACCOUNT_H
#define E_ACCOUNT_H

class account {
public:
    account() {
        sum.exchange(0);
    }

    void deposit( unsigned int x);
    void withdraw(unsigned int y);
private:
    std::mutex m_;
    std::condition_variable cv_;
    std::atomic<int> sum;
};

void account::deposit(unsigned int x) {
    sum.fetch_add(x);
    cv_.notify_one();
}

void account::withdraw(unsigned int y) {
    std::unique_lock<std::mutex> lock(m_);
    cv_.wait(lock, [&] { return sum.load() - y > 0; });
    sum.fetch_add(-y);
}

#endif //E_ACCOUNT_H
