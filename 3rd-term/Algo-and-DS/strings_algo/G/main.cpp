#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <iterator>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#include <cstdio>

using namespace __gnu_pbds;
using namespace std;


tree <string, null_type, less<string>, rb_tree_tag, tree_order_statistics_node_update> dict;

bool is_int(std::string str) {
    return '0' <= str[0] && str[0] <= '9';
}

int main() {
    int n;
    cin >> n;
    std::string request_str;
    for (int i = 0; i < n; ++i) {
        std::cin >> request_str;
        if (is_int(request_str)) {
            int k = atoi(request_str.c_str());
            cout << * dict.find_by_order(k-1) << endl;
        } else {
            dict.insert(request_str);
        }
    }
    return 0;
}