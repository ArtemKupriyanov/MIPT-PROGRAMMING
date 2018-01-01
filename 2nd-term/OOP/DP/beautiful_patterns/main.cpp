#include <iostream>
#include <vector>

using namespace std;

void make_matrix (vector < vector <int> >& matrix, int n, int m) {
    matrix.resize(n);
    for (int i = 0; i < n; ++i) {
        matrix[i].resize(m, 0);
    }
}

void make_eye_matrix(vector<vector <int> >& matrix, int size_matrix) {
    matrix.resize(size_matrix);
    for (int i = 0; i < size_matrix; ++i) {
        matrix[i].resize(size_matrix, 0);
        matrix[i][i] = 1;
    }
}


vector<vector <int> > matrix_multiplication(vector<vector <int> > matrix1,
                           vector<vector <int> > matrix2, int size_matrix) {
    vector<vector <int> > answer(size_matrix);
    make_matrix(answer, size_matrix, size_matrix);
    for (int i = 0; i < size_matrix; ++i) {
        for (int j = 0; j < size_matrix; ++j) {
            int answ = 0;
            for (int k = 0; k < size_matrix; ++k) {
                answ += ( matrix1[i][k] * matrix2[k][j] ) % 10000;
            }
            answer[i][j] = answ % 10000;
        }
    }
    return answer;
}

vector<vector <int> > matrix_pow (vector<vector <int> > matrix, int pow, int size_matrix) {

    if (pow == 0) {
        vector <vector <int> > eye_matrix(size_matrix);
        make_eye_matrix(eye_matrix, size_matrix);
        return eye_matrix;
    }
    if (pow % 2 == 1)
        return matrix_multiplication(matrix_pow(matrix, pow - 1, size_matrix), matrix, size_matrix);
    else {
        vector<vector <int> > matrix_tmp(size_matrix);
        make_matrix(matrix_tmp, size_matrix, size_matrix);
        matrix_tmp = matrix_pow(matrix, pow / 2, size_matrix);
        return matrix_multiplication(matrix_tmp, matrix_tmp, size_matrix);
    }
}

int compare_profiles(int pr1, int pr2, int h) {
    int byte1, byte2;
    for (int i = 0; i < h - 1; ++i) {
        if (pr1 % 2 == pr2 % 2 && (pr1 >> 1) % 2 == (pr2 >> 1) % 2
                && (pr1 >> 1) % 2 == pr1 % 2) {
            return 0;
        }
        pr1 = pr1 >> 1;
        pr2 = pr2 >> 1;
    }
    return 1;
}

int prof(int w, int h) {
    int size_table = 1 << h;
    vector < vector < int > > opportune(size_table);
    for (int i = 0; i < size_table; ++i) {
        opportune[i].resize(size_table, 0);
    }
    for (int j = 0; j < size_table; ++j) {
        for (int i = 0; i < size_table; ++i) {
            opportune[j][i] = compare_profiles(j, i, h);
        }
    }
    int answer = 0;
    vector <vector <int> > matrix_answer(size_table);
    for (int i = 0; i < size_table; ++i) {
        matrix_answer[i].resize(size_table, 0);
        matrix_answer[i] = opportune[i];
    }
    matrix_answer = matrix_pow(opportune, w - 1, size_table);
    answer = 0;
    for (int i = 0; i < size_table; ++i) {
        for (int j = 0; j < size_table; ++j) {
            answer += matrix_answer[i][j];
            answer %= 10000;
        }
    }
    cout << answer << endl;
}


int main(int argc, char *argv[]) {
    int w, h;
    cin >> h >> w;
    prof(w, h);
    return 0;
}
