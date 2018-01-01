#include <iostream>
#include "lock_free_queue.h"

int main() {
    lock_free_queue<int> *que = new lock_free_queue();
    que->dequeue(1);
    que->enqueue(1);
    return 0;
}