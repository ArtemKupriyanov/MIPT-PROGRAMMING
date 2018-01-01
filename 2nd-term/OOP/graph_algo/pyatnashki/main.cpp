#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <algorithm>
#include <assert.h>

using namespace std;

void init_vector(vector<vector<int> >& vect, int size) {
    vect.resize(size);
    for (int i = 0; i < size; ++i) {
        vect[i].resize(size, 0);
    }
}

class  vertex {
public:
    vertex(int _field_size);
    vertex(vertex* parent);
    vertex(vertex* parent, char movie);

    vector <vector <int> > state; //конфигурация кубиков
    vertex* parent; //указател  на вершину - родителя

    int field_size; //размер поля
    int cost; //цена
    int heuristics; //эвристика

    char was_create_move; //был создан движением {D, U, L, R}

    void recalcHeuristics(); //вычислить эвристику на основе данных state
    //эвристика манхеттенская: abs(x - xцели) + abs(y - yцели)

    void print(); //вывести на экран содержимое вершины
};

vertex::vertex(int _field_size)
        : field_size(_field_size) {
    init_vector(state, _field_size);
}

vertex::vertex(vertex *parent) {
    this->parent = parent;
    this->field_size = parent->field_size;
    this->cost = parent->cost + 1;
    this->state = parent->state;
    //this->was_create_move = movie;
}

vertex::vertex(vertex *parent, char movie) {
    this->parent = parent;
    this->field_size = parent->field_size;
    this->cost = parent->cost + 1;
    this->state = parent->state;
    this->was_create_move = movie;
}

void vertex::recalcHeuristics() {
    heuristics = 0;
    int col[16];
    int str[16];
    if (field_size == 4) {
        //int col1[] = {3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2};
        //int str1[] = {3, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3};
        for (int i = 0; i < 16; ++i) {
            if (i % 4 == 0) {
                col[i] = 3;
            } else if (i % 4 == 1) {
                col[i] = 0;
            } else if (i % 4 == 2) {
                col[i] = 1;
            } else {
                col[i] = 2;
            }
        }
        for (int i = 0; i < 16; ++i) {
            if (i == 0  || i > 12) {
                str[i] = 3;
            } else if (i >= 1 && i <= 4) {
                str[i] = 0;
            } else if (i > 4 && i <= 8) {
                str[i] = 1;
            } else {
                str[i] = 2;
            }
        }
    } else {
        //int col1[] = {2, 0, 1, 2, 0, 1, 2, 0, 1};
        //int str1[] = {2, 0, 0, 0, 1, 1, 1, 2, 2};
        for (int i = 0; i < 9; ++i) {
            if (i % 3 == 0) {
                col[i] = 2;
            } else if (i % 3 == 1) {
                col[i] = 0;
            } else {
                col[i] = 1;
            }
        }
        for (int i = 0; i < 9; ++i) {
            if (i == 0  || i >= 7) {
                str[i] = 2;
            } else if (i >= 1 && i <= 3) {
                str[i] = 0;
            } else {
                str[i] = 1;
            }
        }
    }
    for (int i = 0; i < field_size; ++i) {
        for (int j = 0; j < field_size; ++j) {
            if (state[i][j] != 0) {
                heuristics += abs( str[ state[i][j] ] - i) + abs(col[state[i][j]] - j);
            }
        }
    }
}

void vertex::print() {
    for (int i = 0; i < field_size; ++i) {
        for (int j = 0; j < field_size; ++j) {
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//для сортировки элементов в очереди
struct  comp_in_queue {
    bool operator()(vertex *l, vertex *r) {
        return ((l->heuristics) > (r->heuristics));
    }
};

void initialization (priority_queue <vertex*, deque <vertex*>, comp_in_queue>& que, set<vertex*>& vertexes) {
    int field_size;
    cin >> field_size;
    vertex* starting_state = new vertex(field_size);
    for (int i = 0; i < field_size; ++i) {
        for (int j = 0; j < field_size; ++j) {
            cin >> starting_state->state[i][j];
        }
    }
    starting_state->cost = 0;
    starting_state->recalcHeuristics();
    starting_state->parent = NULL;
    que.push(starting_state);
    vertexes.insert(starting_state);
}

bool my_find(set<vertex*>& vertexes, vertex* vert) {
    int field_size = vert->field_size;
    bool finded = false;
    for (auto it = vertexes.begin(); it != vertexes.end(); ++it) {
        vertex vert_now = *it;
        bool one_equal = true;
        for (int i = 0; i < field_size; ++i) {
            if (!one_equal) {
                break;
            }
            for(int j = 0; j < field_size; ++j) {
                if(vert_now.state[i][j] != vert->state[i][j]) {
                    one_equal = false;
                    break;
                }
            }
        }
        if (one_equal) {
            finded = true;
            break;
        }
    }
    return finded;
}

void addNeighbours(vertex* game_state, set<vertex*>& vertexes,
                   priority_queue <vertex*, deque <vertex*>, comp_in_queue>& que) {
    int field_size = game_state->field_size;
    //ищем пустую клетку
    int zi, zj; //координаты
    for (int i = 0; i < field_size; ++i) {
        for (int j = 0; j < field_size; ++j) {
            if (game_state->state[i][j] == 0) {
                zi = i;
                zj = j;
                break;
            }
        }
    }
    //нулевой кубик можно сдвинуть в любую из 4рех сторон
    int di[] = {-1, 0, 1, 0};
    int dj[] = {0, -1, 0, 1};
    char movies[] = {'D', 'R', 'U', 'L'};
    for (int k = 0; k < 4; ++k) {
        //i, j - новые координаты пустой клетки
        int i = zi + di[k];
        int j = zj + dj[k];
        /*
         *  если нулевой кубик пошел вниз - то произошло движение вверх
         *  если нулевой кубик пошел вправо - то влево
         */

        //если пустая клетка не вышла за пределы поля
        if (i >= 0 && j >= 0 && i < field_size && j < field_size) {
            vertex* vert = new vertex(game_state, movies[k]);
            swap(vert->state[i][j], vert->state[zi][zj]); //новая позиция пустой клетки
            vert->recalcHeuristics();

            if (!my_find(vertexes, vert)) {
                que.push(vert);
                vertexes.insert(vert);
            } else {
                delete vert;
            }
        }
    }
}

bool isFinish (vertex* conf) {
    int field_size = conf->field_size;
    vector <vector <int> > lastConf(field_size);
    for (int i = 0; i < field_size; ++i) {
        lastConf[i].resize(field_size);
    }
    //lastConf = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0} };
    for (int i = 1; i < field_size * field_size; ++i) {
        int zi = (i - 1) / field_size, zj = (i - 1) % field_size;
        lastConf[zi][zj] = i;
    }
    for (int i = 0; i < field_size; ++i) {
        for (int j = 0; j < field_size; ++j) {
            if (lastConf[i][j] != conf->state[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void solve() {
    priority_queue <vertex*, deque <vertex*>, comp_in_queue> que;
    set<vertex*> vertexes;
    initialization(que, vertexes);
    int iter = 0;
    int field_size = (*vertexes.begin())->field_size;
    while(!que.empty()) {
        vertex* vert = que.top();
        que.pop();
        ++iter;
        if (isFinish(vert)) {
            while(vert != NULL) {
                vert->print();
                cout << vert->was_create_move << " ";
                vert = vert->parent;
            }
            cout << "вершин рассмотрено: " << iter << endl;
        } else {
            addNeighbours(vert, vertexes, que);
        }
    }
    if (!que.empty()) {
        cout << "нет решения" << endl;
    }
}

int main(int argc, char** argv) {
    solve();
    return 0;
}