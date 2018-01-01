#include <iostream>
#include <limits.h>

using namespace std;

void func(int n, int& l, int& r) {
    long long int max_pref, prev_max_pref;
    long long int global_max = LONG_MIN;
    int l_in_sums_last = 0, tmp_l = 0;
    int element;
    cin >> element;
    prev_max_pref = max_pref = element;
    l = 0; r = 0;
    for (int i = 1; i < n; ++i) {
        cin >> element;
        if (prev_max_pref + element >= element) {
            max_pref = prev_max_pref + element;
            tmp_l = l_in_sums_last;
        } else {
            max_pref = element;
            tmp_l = i;
        }
        if (global_max < max_pref) {
            global_max = max_pref;
            r = i;
            l = tmp_l;
        }
        l_in_sums_last = tmp_l;
        prev_max_pref = max_pref;
    }
}

int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    int l, r;
    func(n, l, r);
    cout << l << endl << r;
    return 0;
}
