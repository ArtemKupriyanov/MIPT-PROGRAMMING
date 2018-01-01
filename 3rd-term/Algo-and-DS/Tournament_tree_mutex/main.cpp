#include <iostream>
#include "tree_mutex.h"

int main() {
    tree_mutex mtx(150);
    for(int i = 0; i < 150; ++i) {
        mtx.lock(i);
        mtx.unlock(i);
    }
    return 0;
}