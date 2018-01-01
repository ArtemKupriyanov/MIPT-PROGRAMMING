#include <iostream>
#include <vector>

using namespace std;

const int INFTY = 1000000;

int main() {
    int n;
    cin >> n;
    int matrix[301][301];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> matrix[i][j];
        }
    }
    int potential_u[301], potential_v[301], parosoch[301], way[301];
    for (int n_str = 1; n_str <= n; ++n_str) {
        parosoch[0] = n_str;
        int empty_row = 0;
        vector<int> minv(n + 1, INFTY);
        vector<char> used(n + 1, false);
        do {
            used[empty_row] = true;
            int str_in_parosoch = parosoch[empty_row], min_in_str = INFTY, row_with_min;
            for (int n_row = 1; n_row <= n; ++n_row) {
                if (!used[n_row]) {
                    int cur = matrix[str_in_parosoch][n_row] - potential_u[str_in_parosoch] - potential_v[n_row];
                    if (cur < minv[n_row]) {
                        minv[n_row] = cur, way[n_row] = empty_row;
                    }
                    if (minv[n_row] < min_in_str) {
                        min_in_str = minv[n_row], row_with_min = n_row;
                    }
                }
            }
            for (int n_row = 0; n_row <= n; ++n_row) {
                if (used[n_row]) {
                    potential_u[parosoch[n_row]] += min_in_str;
                    potential_v[n_row] -= min_in_str;
                }
                else {
                    minv[n_row] -= min_in_str;
                }
                empty_row = row_with_min;
            }
        } while (parosoch[empty_row] != 0);
        do {
            int row_with_min = way[empty_row];
            parosoch[empty_row] = parosoch[row_with_min];
            empty_row = row_with_min;
        } while (empty_row);
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += matrix[parosoch[i]][i];
    }
    cout << sum << endl;
    for (int i = 1; i <=n; ++i) {
        cout << parosoch[i] << " " << i << endl;
    }
    return 0;
}