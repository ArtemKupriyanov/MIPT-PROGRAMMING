#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <limits.h>
#include <queue>

using namespace std;

struct point {
    int x;
    int y;

    point(int _x, int _y)
            : x(_x),
              y(_y) {}
};

void read_labirint (vector <vector <int> >& labirint, int& n) {
    cin >> n;
    labirint.resize(n);
    for (int  i = 0; i < labirint.size(); ++i) {
        labirint[i].resize(n, 0);
    }
    string line, numb_str;
    vector <int> borders;
    getline(cin, line);
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        for (int j = 0; j < line.length(); ++j) {
            if (line[j] == ' ') {
                borders.push_back(atoi(numb_str.c_str()));
                numb_str.clear();
            } else {
                numb_str = numb_str + line[j];
            }
        }
        if (numb_str.length() != 0) {
            borders.push_back(atoi(numb_str.c_str()));
            numb_str.clear();
        }
        for (int j = 0; j < borders.size() - 1; j += 2) {
            int start = borders[j], finish = borders[j + 1];
            for (int k = start; k < finish; ++k) {
                labirint[i][k] = -1; //or INT_MAX
            }
        }
        borders.clear();
    }
}

void print_labirint(vector <vector <int> >& labirint) {
    cout << "labirint now. 1 - wall, 0 - way" << endl;
    for (int i = 0; i < labirint.size(); ++i) {
        for (int j = 0; j < labirint.size(); ++j) {
            cout << labirint[i][j] << " ";
        }
        cout << endl;
    }
}

void mark_neig_sells(vector <vector <int> >& labirint, queue < point >& que, point now_point, int d_last) {
    int x = now_point.x, y = now_point.y;
    //top
    if (x - 1 >= 0 && labirint[x-1][y] == 0) {
        labirint[x-1][y] =  d_last + 1;
        que.push(point(x-1, y));

    }
    //bottom
    if (x + 1 < labirint.size() && labirint[x+1][y] == 0) {
        labirint[x+1][y] =  d_last + 1;
        que.push(point(x+1, y));
    }
    //right
    if (y + 1 < labirint.size() && labirint[x][y+1] == 0) {
        labirint[x][y+1] =  d_last + 1;
        que.push(point(x, y+1));
    }
    //left
    if (y - 1 >= 0 && labirint[x][y-1] == 0) {
        labirint[x][y-1] =  d_last + 1;
        que.push(point(x, y-1));
    }
}

void LI_algo (vector <vector <int> >& labirint, point p_start, point p_finish) {
    int max_iter = labirint.size() * labirint.size();
    int iter = 0;
    bool flag = true;
    if (labirint[p_start.x][p_start.y] == -1 || labirint[p_finish.x][p_finish.y] == -1) {
        cout << "Нет пути" << endl;
        flag = false;
    }
    labirint[p_start.x][p_start.y] = 1;
    point now_point(0, 0);
    queue < point > que;
    que.push(p_start);
    while (iter < max_iter && flag) {
        if (que.empty()) {
            //cout << "Нет пути" << endl;
            break;
        }
        now_point = que.front();
        que.pop();
        mark_neig_sells(labirint, que, now_point, labirint[now_point.x][now_point.y]);
        ++iter;
        if (labirint[p_finish.x][p_finish.y] > 0) {
            break;
        }
        //print_labirint(labirint);
    }
    if (labirint[p_finish.x][p_finish.y] > 0) {
        cout << labirint[p_finish.x][p_finish.y] - 1 << endl;
    } else {
        cout << "Нет пути" << endl;
    }
}

int main() {
    int n;
    vector <vector <int> > labirint;
    read_labirint(labirint, n);
    int start_x, start_y, finish_x, finish_y;
    cout << endl << "Start and finish: " << endl;
    cin >> start_x >> start_y >> finish_x >> finish_y;
    print_labirint(labirint);
    LI_algo(labirint, point(start_x, start_y), point(finish_x, finish_y));
    return 0;
}
