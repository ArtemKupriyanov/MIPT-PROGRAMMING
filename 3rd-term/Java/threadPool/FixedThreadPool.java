package ru.mipt.java2016.homework.g596.kupriyanov.threadPool;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Created by Artem Kupriyanov on 15/12/2016.
 */

public class FixedThreadPool {
    private final Queue<Runnable> tasks = new ArrayDeque<Runnable>();
    private final Lock lock = new ReentrantLock();
    private final List<Thread> workers;

    public FixedThreadPool(int nThread) {
        workers = new ArrayList<>(nThread);
        for (int i = 0; i < nThread; ++i) {
            workers.add(new MyThread(i));
        }
    }

    private class MyThread extends Thread {
        private Integer index;

        public Integer getIndex() {
            return index;
        }

        MyThread(Integer ind) {
            index = ind;
        }

        @Override
        public void run() {
            while (true) {
                Runnable task;
                lock.lock();
                try {
                    while (tasks.isEmpty()) {
                        try {
                            lock.wait();
                        } catch (InterruptedException e) {
                            System.out.println("thread was interrupted");
                        }
                    }
                    task = tasks.poll();
                } finally {
                    lock.unlock();
                }
                try {
                    task.run();
                } catch (Exception e) {
                    System.out.println("Can't run this task");
                }
            }
        }
    }

    public void start() {
        workers.forEach(Thread::start);
    }

    public void execute(Runnable runnable) {
        tasks.add(runnable);
        lock.notify();
    }
}
