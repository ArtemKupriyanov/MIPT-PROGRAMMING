#include <iostream>
#include <vector>
#include <string>

using namespace std;

int** left_null_len;
int** nonzero_above;
int** fless_left_len;
int** answer_matrix;

void print_matrix (string s, int** matrix, int n, int m) {
    cout << s << endl;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            cout << matrix[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void create_matrix (int ** &matrix, int n, int m) {
    matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
    }
}

void delete_matrix(int ** &matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void make_left_null_len(int ** & matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        if (matrix[i][0] == 0) {
            left_null_len[i][0] = 1;
        }
        for (int j = 1; j < m; ++j) {
            if (matrix[i][j] == 0) {
                left_null_len[i][j] = left_null_len[i][j - 1] + 1;
            } else {
                left_null_len[i][j] = 0;
            }
        }
    }
}

void make_nonzero_above (int n, int m) {
    for (int j = 0; j < m; ++j) {
        nonzero_above[0][j] = -1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (left_null_len[i -1][j] == 0) {
                nonzero_above[i][j] = i - 1;
            } else {
                nonzero_above[i][j] = nonzero_above[i - 1][j];
            }
        }
    }
}

void make_fless_left_len(int n, int m) {
    for (int i = 0; i < n; ++i) {
        fless_left_len[i][0] = -1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (left_null_len[j][0] <= left_null_len[i][0]) {
                fless_left_len[i][0] = j;
            }
        }
    }
    for (int j = 1; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            if (left_null_len[i][j] != 0) {
                if (nonzero_above[i][j] > fless_left_len[i][j - 1]) {
                    fless_left_len[i][j] = nonzero_above[i][j];
                } else {
                    fless_left_len[i][j] = fless_left_len[i][j - 1];
                }
            } else {
                fless_left_len[i][j] = nonzero_above[i][j];
            }
        }
    }
}

void make_answer_matrix(int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int size_above;
            int k = fless_left_len[i][j];
            if (k == -1) {
                size_above = 0;
            } else {
                size_above = answer_matrix[k][j];
            }
            answer_matrix[i][j] = size_above + left_null_len[i][j] * (i - k);
        }
    }
}

void print_answer(int n, int m) {
    unsigned long long int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            answer += answer_matrix[i][j];
        }
    }
    cout << answer;
}

void dp(int**& matrix, int str, int col) {
    create_matrix(left_null_len, str, col);
    make_left_null_len(matrix, str, col);
    //print_matrix("left_null_len", left_null_len, str, col);
    create_matrix(nonzero_above, str, col);
    make_nonzero_above(str, col);
    //print_matrix("nonzero_above", nonzero_above, str, col);
    create_matrix(fless_left_len, str, col);
    make_fless_left_len(str, col);
    //print_matrix("fless_left_len", fless_left_len, str, col);
    delete_matrix(nonzero_above, str, col);

    create_matrix(answer_matrix, str, col);
    make_answer_matrix(str, col);
    //print_matrix("answer_matrix", answer_matrix, str, col);
    print_answer(str, col);
    delete_matrix(left_null_len, str, col);
    delete_matrix(fless_left_len, str, col);
    delete_matrix(answer_matrix, str, col);
}

int main(int argc, char *argv[]) {
    int n, m;
    cin >> n >> m;
    int** matrix;
    create_matrix(matrix, n, m);
    if (n > m) 	{
        create_matrix(matrix, m, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> matrix[j][i];
            }
        }
        swap(n, m);
    }
    else {
        create_matrix(matrix, n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> matrix[i][j];
            }
        }
    }
    dp(matrix, n, m);
    delete_matrix(matrix, n, m);
    return 0;
}
