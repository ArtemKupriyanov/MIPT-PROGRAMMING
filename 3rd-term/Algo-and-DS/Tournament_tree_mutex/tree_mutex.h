//
// Created by Artem Kupriyanov on 09/09/2016.
//
#include <iostream>
#include <array>
#include <thread>
#include <vector>
#include <cmath>

#ifndef TOURNAMENT_TREE_MUTEX_TREE_MUTEX_H
#define TOURNAMENT_TREE_MUTEX_TREE_MUTEX_H

class PetersonMutex {
public:
    PetersonMutex() {
        want_[0].store(false);
        want_[1].store(false);
        victum_.store(0);
    }

    void lock(int t) {
        want_[t].store(true);
        victum_.store(t);
        while (want_[1-t].load() && victum_.load() == t) {
            std::this_thread::yield();
        }
    }

    void unlock(int t) {
        want_[t].store(false);
    }

private:
    std::array<std::atomic<bool>, 2> want_;
    std::atomic<int> victum_;
};

class tree_mutex {
public:
    tree_mutex(std::size_t _num_threads);

    void lock(std::size_t thread_index);
    void unlock(std::size_t thread_index);
    std::size_t num_threads;

private:
    std::size_t calc_tree_size(std::size_t _num_threads);
    std::size_t get_parent(std::size_t children_index);
    std::size_t get_left_children(std::size_t parent_index);
    std::size_t get_right_children(std::size_t parent_index);

    std::vector<PetersonMutex> tree_;

};

std::size_t tree_mutex::get_parent(std::size_t children_index) {
    return std::size_t((children_index - 1) / 2);
}

std::size_t tree_mutex::get_left_children(std::size_t parent_index) {
    return std::size_t( 2 * parent_index + 1 );
}

std::size_t tree_mutex::get_right_children(std::size_t parent_index) {
    return std::size_t( 2 * parent_index + 2 );
}

tree_mutex::tree_mutex(std::size_t _num_threads)
        : num_threads(_num_threads),
          tree_(calc_tree_size(_num_threads))
{}

std::size_t tree_mutex::calc_tree_size(std::size_t _num_threads) {
    int expon = int(ceil(log2(_num_threads)));
    return std::size_t(pow(2, expon) - 1);
}

void tree_mutex::lock(std::size_t thread_index) {
    std::size_t now_thread_number = thread_index;
    std::size_t now_ind = tree_.size() + thread_index;
    while (now_ind > 0) {
        now_ind = this->get_parent(now_ind);
        tree_[now_ind].lock(now_thread_number % 2);
        now_thread_number = now_thread_number / 2;
    }
}

void tree_mutex::unlock(std::size_t thread_index) {
    std::size_t residue = thread_index;
    std::size_t height = std::size_t(log2(tree_.size() + 1));
    std::vector <std::size_t> bin_thread_index(height, 0);
    for(std::size_t i = 0; i < bin_thread_index.size(); ++i) {
        if (residue == 0) {
            continue;
        }
        bin_thread_index[i] = residue % 2;
        residue = residue / 2;
    }
    std::size_t now_ind = 0;
    for (auto it = bin_thread_index.end(), begin = bin_thread_index.begin(); it != begin; --it) {
    //for(int i = bin_thread_index.size() - 1; i >= 0; --i) {
        tree_[now_ind].unlock(std::size_t(*it));
        if ((*it) == 0) {
            now_ind = get_left_children(now_ind);
        } else {
            now_ind = get_right_children(now_ind);
        }
    }
}



#endif //TOURNAMENT_TREE_MUTEX_TREE_MUTEX_H
