#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> prefix_func(n, 0);
    std::vector<int> Z_function(n, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> prefix_func[i];
    }
    for(int i = 1; i < n; ++i) {
        if (prefix_func[i]) {
            Z_function[i - prefix_func[i] + 1] = prefix_func[i];
        }
    }
    Z_function[0] = n;
    if(Z_function[1]) {
        for(int i = 1; i < Z_function[1]; ++i) {
            Z_function[i + 1] = Z_function[1] - i;
        }
    }
    int k;
    for(int i = Z_function[1] + 1; i < n - 1; ++i) {
        k = i;
        if (Z_function[i] && !Z_function[i + 1]) {
            for (int j = 1; j < Z_function[i] && Z_function[i + j] <= Z_function[j]; ++j) {
                Z_function[i + j] = std::min(Z_function[j], Z_function[i] - j);
                k = i + j;
            }
        }
        i = k;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << Z_function[i] << " ";
    }
    return 0;
}