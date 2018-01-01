#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>

using namespace std;

double sqr (double a) {
    return a*a;
}

double dist(pair <int, int> point1, pair <int, int> point2) {
    double answ = sqrt( sqr(point1.first - point2.first) +
                 sqr(point1.second - point2.second) );
    return answ;
}

void init_matrix(double**& matrix, int size_matrix) {
    matrix = new double*[size_matrix];
    for (int i = 0; i < size_matrix; ++i) {
        matrix[i] = new double[size_matrix];
        for (int j = 0; j < size_matrix; ++j) {
            matrix[i][j] = -1;
        }
    }
}

void delete_matrix(double**& matrix, int size_matrix) {
    for (int i = 0; i < size_matrix; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void print_answer(double**& matrix, int size_matrix) {
    cout << matrix[0][size_matrix - 1] << endl;
}

void dp(vector <pair <int, int> > polygon, int n) {
    double ** min_len;
    init_matrix(min_len, n);
    for (int polygon_size = 2; polygon_size < n; ++polygon_size) {
        for (int i = 0; i + polygon_size < n; ++i) {
            int j = i + polygon_size;
            if (polygon_size == 2) {
                min_len[i][j] = 0;
            } else {
                min_len[i][j] = INT_MAX;
                //разбиение на 1 треугольник и какой-то многоугольник
                min_len[i][j] = min(min_len[i][j], min_len[i][j - 1] + dist(polygon[i], polygon[j - 1]));
                min_len[i][j] = min(min_len[i][j], min_len[i + 1][j] + dist(polygon[i + 1], polygon[j]));
                for (int k = i + 2; k < j - 1; ++k) {
                    //разбиение на 1 треугольник и 2 каких-то многоугольника
                    min_len[i][j] = min(min_len[i][j], min_len[i][k] + min_len[k][j] + dist(polygon[i], polygon[k]) + dist(polygon[k], polygon[j]));
                }
            }
        }
    }
    print_answer(min_len, n);
    delete_matrix(min_len, n);
}

int main() {
    int n;
    cin >> n;
    vector < pair <int, int> > polygon(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        polygon[i] = make_pair(a, b);
    }
    dp(polygon, n);
    return 0;
}
