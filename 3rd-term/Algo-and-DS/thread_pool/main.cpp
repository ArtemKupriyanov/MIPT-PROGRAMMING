#include <iostream>
#include <future>
#include <vector>
#include <condition_variable>
#include <queue>

#include "parallel_sort.h"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<int> test;
    for (int i = 10; i >= 0; --i) {
        test.push_back(i);
    }
    parallel_sort* a = new parallel_sort(3);
    a->sort(test.begin(), test.end(), std::less<int>());
    for (int i = 0; i < test.size(); ++i) {
        std::cout << test[i] << " ";
    }
    delete a;
}
