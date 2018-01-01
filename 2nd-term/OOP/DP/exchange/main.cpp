#include <iostream>
#include <vector>

using namespace std;

const int max_sum = 10001;

bool dp(vector<int> P, vector<int> R, int s, int n, int m) {
    vector <bool> can_pay(max_sum, false);
    vector <bool> can_give(max_sum, false);

    can_give[0] = true;
    can_pay[0] = true;
    for (int i = 0; i < n; ++i) {
        for (int j = max_sum - 1; j >= 0; --j) {
            if (can_pay[j] == true) {
                can_pay[j + P[i]] = true;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = max_sum - 1; j >= 0; --j) {
            if (can_give[j] == true) {
                can_give[j + R[i]] = true;
            }
        }
    }
    for (int i = 0; i < max_sum - s; ++i) {
        if (can_pay[i + s] == true && can_give[i] == true) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    int s, n, m;
    cin >> n;
    vector<int> P(n);
    for (int i = 0; i < n; ++i) {
        cin >> P[i];
    }
    cin >> m;
    vector<int> R(m);
    for (int i = 0; i < m; ++i) {
        cin >> R[i];
    }
    cin >> s;
    if ( dp(P, R, s, n, m) == true) {
        cout << "yes";
    } else {
        cout << "no";
    }
    return 0;
}
