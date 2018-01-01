//
// Created by Artem Kupriyanov on 11/12/2016.
//

#ifndef LOCK_FREE_QUEUE_LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_LOCK_FREE_QUEUE_H

#include <atomic>

using namespace std;

template <class T>
class lock_free_queue {
public:
    lock_free_queue();
    ~lock_free_queue();
    void enqueue(T e);
    bool dequeue(T& e);
private:
    class Node {
    public:
        Node(): next(NULL) {}
        Node(T e): data(e), next(NULL) {}
        T data;
        atomic<Node*> next;
    };
    atomic<Node*> head;
    atomic<Node*> tail;
    atomic<Node*> tmp;
    atomic<Node*> nd;
};

template <class T>
lock_free_queue<T>::lock_free_queue() {
    Node* new_node = new Node();
    head.store(new_node);
    tail.store(new_node);
    nd.store(new_node);

}

template <class T>
lock_free_queue<T>::~lock_free_queue() {
    Node* t = nd.load();
    Node* k;
    while (t != NULL) {
        k = t->next;
        delete t;
        t = k;
    }
}

template <class T>
void lock_free_queue<T>::enqueue(T e) {
    Node* new_node = new Node(e);
    Node* t;
    while (true) {
        Node* t = tail;
        Node* next = t->next;
        if (next == NULL) {
            if ((tail.load())->next.compare_exchange_strong(next, new_node)){
                break;
            }
        }
        else {
            tail.compare_exchange_strong(t, next);
        }
    }
    tail.compare_exchange_strong(t, new_node);
}

template <class T>
bool lock_free_queue<T>::dequeue(T& e) {
    while (true) {
        Node* h = head;
        Node* t = tail;
        Node* next = h->next;
        if (h == t){
            if (next == NULL) {
                return false;
            }
            else {
                tail.compare_exchange_strong(h, next);
            }
        }
        else if (head.compare_exchange_strong(h, next)) {
            e = next->data;
            break;
        }
    }
    return true;
}

#endif //LOCK_FREE_QUEUE_LOCK_FREE_QUEUE_H
