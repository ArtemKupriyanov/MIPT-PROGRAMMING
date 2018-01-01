#include <iostream>
#include <vector>

using namespace std;

typedef long long int lli;

lli dp(lli n) {
    vector < vector <lli> > matrix(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        matrix[i].resize(n + 1, 0);
    }
    for (int i = 0; i < n + 1; ++i) {
        matrix[0][i] = 1;
    }
    for (int j = 1; j < n + 1; ++j) {
        for (int i = 1; i < n + 1; ++i) {
            //matrix[j][i]
            lli sum1, sum2;
            if (j - i < 0) {
                sum1 = 0;
            } else {
                sum1 = matrix[j - i][i];
            }
            sum2 = matrix[j][i - 1];
            //matrix[j][i] = matrix[j - i][i] + matrix[j][i - 1]
            matrix[j][i] = sum1 + sum2;
        }
    }
    return matrix[n][n];
}

int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    lli answ = dp(n);
    cout << answ;
    return 0;
}
