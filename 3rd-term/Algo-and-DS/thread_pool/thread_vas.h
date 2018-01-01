//
// Created by Artem Kupriyanov on 04/11/2016.
//

#ifndef THREAD_POOL_THREAD_VAS_H
#define THREAD_POOL_THREAD_VAS_H

#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>

template <typename T>
class thread_pool {
 public:
  explicit thread_pool(size_t worker_count);

  std::future<T> submit(std::function<T()> task);

  void shutdown();

  T wait(std::future<T> &future);

 private:
  bool execute_task(int max_wait = -1);

  bool shutdown_;
  std::mutex mutex_;
  std::condition_variable task_cond_;
  std::queue<std::packaged_task<T()>> tasks_;
  std::vector<std::thread> workers_;
};

template <typename T>
thread_pool<T>::thread_pool(size_t worker_count) : shutdown_(false) {
  auto worker = [this]() { while (execute_task()); };

  for (size_t i = 0; i < worker_count; ++i) {
    workers_.emplace_back(worker);
  }
}

template <typename T>
T thread_pool<T>::wait(std::future<T> &future) {
  auto timeout = std::chrono::milliseconds::zero();

  while (future.wait_for(timeout) != std::future_status::ready) {
    execute_task(10);
  }
}

template <typename T>
bool thread_pool<T>::execute_task(int max_wait) {
  std::unique_lock<std::mutex> lock(mutex_);

  auto pred = [this]() { return shutdown_ || !tasks_.empty(); };
  if (max_wait < 0) {
    task_cond_.wait(lock, pred);
  } else {
    task_cond_.wait_for(lock, max_wait * std::chrono::milliseconds(), pred);
  }

  if (tasks_.empty()) {
    return false;
  }

  auto task = std::move(tasks_.front());
  tasks_.pop();
  lock.unlock();

  task();

  return true;
}

template <typename T>
std::future<T> thread_pool<T>::submit(std::function<T()> task) {
  std::unique_lock<std::mutex> lock(mutex_);
  if (shutdown_) {
    throw std::runtime_error("Submitted task to shut down pool");
  }

  tasks_.emplace(task);
  auto future = tasks_.back().get_future();

  task_cond_.notify_one();

  return future;
}

template <typename T>
void thread_pool<T>::shutdown() {
  std::unique_lock<std::mutex> lock(mutex_);
  shutdown_ = true;
  lock.unlock();
  task_cond_.notify_all();

  for (auto &worker : workers_) {
    worker.join();
  }
}


#endif //THREAD_POOL_THREAD_VAS_H
