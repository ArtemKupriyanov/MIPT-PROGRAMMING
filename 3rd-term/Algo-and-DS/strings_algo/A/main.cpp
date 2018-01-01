#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAX = 10010;

//Vars block.
string s;
int n, minimalSum, suitableIndex, currentSum;
pair<int, int> answer(0, 0);
vector<vector<short>> dp;
int Z[2 * MAX];

//Z-function.
void zFunction(const string &s, int shift) {
    int n = (int) s.length() - shift;
    Z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        Z[i] = 0;
        if (i <= r)
            Z[i] = min (r - i + 1, Z[i - l]);
        while (i + Z[i] < n && s[shift + Z[i]] == s[shift + i + Z[i]])
            ++Z[i];
        if (i + Z[i] - 1 > r)
            l = i,  r = i + Z[i] -1;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> s;
    n = (int) s.length();
    s = s + "#" + s;

    minimalSum = n;

    dp.resize(n);
    for (int i = 0; i < n; ++i) {
        dp[i].resize(n - i + 1, 1);
    }

    for (int i = 0; i < n; i++) {
        suitableIndex = i - 1;
        zFunction(s, i);
        for (int length = 1; length <= min(i, n - i); length++) {
            if (suitableIndex < 0) {
                break;
            } else {
                suitableIndex = min(suitableIndex, i - length);
                while (suitableIndex >= 0) {
                    if (Z[n - i + suitableIndex + 1] >= length) {
                        break;
                    }
                    suitableIndex--;
                }
                dp[i][length] = ((suitableIndex < 0) ? 1 : (dp[suitableIndex][length] + 1));
                currentSum = length + n - (length - 1) * dp[i][length];
                if (currentSum < minimalSum) {
                    minimalSum = currentSum;
                    answer = {i, length};
                }
            }
        }
    }

    for (int i = answer.first; i < answer.first + answer.second; i++) {
        cout << s[i];
    }

    cout << endl;

    if (answer.second == 0) {
        for (int i = 0; i < n; i++) {
            cout << s[i];
        }
        return 0;
    }

    zFunction(s, answer.first);
    for (int i = n - answer.first + 1; i < 2 * n - answer.first + 1; i++) {
        if (Z[i] >= answer.second) {
            cout << "A";
            i += answer.second - 1;
        } else {
            cout << s[i - (n - answer.first + 1)];
        }
    }
    cout << endl;
    return 0;
}
