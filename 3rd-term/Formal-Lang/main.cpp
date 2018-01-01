#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include <queue>
#include <set>

using namespace std;

const int INFTY = 10000000;

class NFA {
public:
    NFA(char symbol);

    NFA(vector<vector<char> >& matrix, int n_state_);

    int get_n_state() {
        return n_state;
    }

    int get_start_vertex() {
        return start_vertex;
    };

    int get_finish_vertex() {
        return finish_vertex;
    }


    vector<vector<char> > NFA_matrix;
private:
    int start_vertex, finish_vertex;
    int n_state;
};

NFA::NFA(char symbol)
        : n_state(2) {
    if (symbol == '1') {
        --n_state;
        NFA_matrix.resize(n_state);
        for (int i = 0; i < n_state; ++i) {
            NFA_matrix[i].resize(n_state, ' ');
        }
        start_vertex = finish_vertex = 0;
    } else {
        NFA_matrix.resize(n_state);
        for (int i = 0; i < n_state; ++i) {
            NFA_matrix[i].resize(n_state, ' ');
        }
        start_vertex = 0;
        finish_vertex = 1;
        NFA_matrix[start_vertex][finish_vertex] = symbol;
    }
}

NFA::NFA(vector<vector<char> > &matrix, int n_state_)
        : n_state(n_state_) {
    NFA_matrix.resize(n_state_);
    for(int i = 0; i < matrix.size(); ++i) {
        NFA_matrix[i].resize(n_state_, ' ');
        copy(matrix[i].begin(), matrix[i].end(), NFA_matrix[i].begin());
    }
    start_vertex = 0;
    finish_vertex = n_state_ - 1;
}

NFA pls(NFA& first_NFA, NFA& second_NFA) {
    int new_state = first_NFA.get_n_state() + second_NFA.get_n_state() + 2;
    vector<vector<char> > new_NFA_matrix;
    new_NFA_matrix.resize(new_state);
    for (int i = 0; i < new_state; ++i) {
        new_NFA_matrix[i].resize(new_state, ' ');
    }
    int first_start_vertex = first_NFA.get_start_vertex(), first_finish_vertex = first_NFA.get_finish_vertex();
    int second_start_vertex = second_NFA.get_start_vertex(), second_finish_vertex = second_NFA.get_finish_vertex();
    new_NFA_matrix[0][first_start_vertex+1] = 'e';
    new_NFA_matrix[0][second_start_vertex+1+first_NFA.get_n_state()] = 'e';
    for(int i = 1; i < new_state - 1; ++i) {
        if (i <= first_NFA.get_n_state()) {
            copy(first_NFA.NFA_matrix[i-1].begin(), first_NFA.NFA_matrix[i-1].end(), new_NFA_matrix[i].begin() + 1);
            if (i - 1 == first_finish_vertex) {
                new_NFA_matrix[i][new_state-1] = 'e';
            }
        } else {
            copy(second_NFA.NFA_matrix[i-1-first_NFA.get_n_state()].begin(),
                 second_NFA.NFA_matrix[i-1-first_NFA.get_n_state()].end(), new_NFA_matrix[i].begin() + first_NFA.get_n_state() + 1);
            if (i - 1 - first_NFA.get_n_state() == second_finish_vertex) {
                new_NFA_matrix[i][new_state-1] = 'e';
            }
        }
    }
    return NFA(new_NFA_matrix, new_state);
}

NFA klini(NFA& first_NFA) {
    int new_state = first_NFA.get_n_state() + 2;
    vector<vector<char> > new_NFA_matrix;
    new_NFA_matrix.resize(new_state);
    for (int i = 0; i < new_state; ++i) {
        new_NFA_matrix[i].resize(new_state, ' ');
    }
    int first_start_vertex = first_NFA.get_start_vertex(), first_finish_vertex = first_NFA.get_finish_vertex();
    new_NFA_matrix[0][first_start_vertex+1] = 'e';
    for(int i = 1; i < new_state - 1; ++i) {
        copy(first_NFA.NFA_matrix[i-1].begin(), first_NFA.NFA_matrix[i-1].end(), new_NFA_matrix[i].begin() + 1);
        if (i - 1 == first_finish_vertex) {
            new_NFA_matrix[i][new_state - 1] = 'e';
        }
     }
    new_NFA_matrix[new_state-1][0] = 'e';
    new_NFA_matrix[0][new_state-1] = 'e';
    return NFA(new_NFA_matrix, new_state);
}

NFA concat(NFA& first_NFA, NFA& second_NFA) {
    int new_state = first_NFA.get_n_state() + second_NFA.get_n_state();
    vector<vector<char> > new_NFA_matrix;
    new_NFA_matrix.resize(new_state);
    for (int i = 0; i < new_state; ++i) {
        new_NFA_matrix[i].resize(new_state, ' ');
    }
    int first_start_vertex = first_NFA.get_start_vertex(), first_finish_vertex = first_NFA.get_finish_vertex();
    int second_start_vertex = second_NFA.get_start_vertex(), second_finish_vertex = second_NFA.get_finish_vertex();
    for (int i = 0; i < new_state; ++i) {
        if (i < first_NFA.get_n_state()) {
            copy(first_NFA.NFA_matrix[i].begin(),
                 first_NFA.NFA_matrix[i].end(), new_NFA_matrix[i].begin());
        } else {
            copy(second_NFA.NFA_matrix[i - first_NFA.get_n_state()].begin(),
                 second_NFA.NFA_matrix[i- first_NFA.get_n_state()].end(), new_NFA_matrix[i].begin() + first_NFA.get_n_state());
        }
    }
    new_NFA_matrix[first_finish_vertex][second_start_vertex + first_NFA.get_n_state()] = 'e';
    return NFA(new_NFA_matrix, new_state);
}

void calc_dist(vector< vector<char> >& graph_char, vector<vector<int> >& dists) {
    int n = graph_char.size();
    dists.resize(n);
    for (int i = 0; i < n; ++i) {
        dists[i].resize(n, INFTY);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph_char[i][j] == 'e') {
                dists[i][j] = 0;
            } else if (graph_char[i][j] == 'a' || graph_char[i][j] == 'b' || graph_char[i][j] == 'c') {
                dists[i][j] = 1;
            }
            if (i == j) {
                dists[i][j] = 0;
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
            }
        }
    }
}

struct triple {
    triple (int s_vert, int f_vert, int l)
            : start_vertex(s_vert),
              finish_vertex(f_vert),
              len(l) {};

    int start_vertex;
    int finish_vertex;
    int len;
};

void find_path(vector<vector<char> >& graph_char, vector<vector<int> >& dists, char x, int k) {
    int n = graph_char.size();
    vector<triple> good_ways;
    for(int start_vertex = 0; start_vertex < n; ++start_vertex) {
        queue<pair<int, int>> que;
        set<pair<int, int>> unique;
        que.push(make_pair(start_vertex, 0));
        unique.insert(make_pair(start_vertex, 0));
        while(!que.empty()) {
            pair<int, int> top = que.front();
            int vertex = top.first, len = top.second;
            que.pop();
            if (len == k) {
                good_ways.push_back(triple(start_vertex, vertex, len));
                continue;
            }
            for (int i = 0; i < n; ++i) {
                if (graph_char[vertex][i] == x) {
                    if(unique.find(make_pair(i, len + 1)) == unique.end()) {
                        que.push(make_pair(i, len + 1));
                        unique.insert(make_pair(i, len + 1));
                    }
                } else if (graph_char[vertex][i] == 'e') {
                    if (i == start_vertex and len == 0) {
                        continue;
                    } else {
                        if(unique.find(make_pair(i, len)) == unique.end()) {
                            que.push(make_pair(i, len));
                            unique.insert(make_pair(i, len));
                        }
                    }
                }
            }
        }
    }
    int min_word = INFTY;
    for (int i = 0; i < good_ways.size(); ++i) {
        min_word = min(min_word, dists[0][good_ways[i].start_vertex] + good_ways[i].len +
        dists[good_ways[i].finish_vertex][n-1]);
    }
    if (min_word == INFTY) {
        cout << "INF" << endl;
    } else {
        cout << min_word << endl;
    }
}

int main() {
    int k;
    string alpha;
    char x;
    cin >> alpha >> x >> k;
    stack<NFA> stack_NFA;
    vector<vector<int> > dists;
    bool error = false;
    for (int i = 0; i < alpha.size(); ++i) {
        if (alpha[i] == 'a' || alpha[i] == 'b' || alpha[i] == 'c' || alpha[i] == '1') {
            stack_NFA.push(NFA(alpha[i]));
        } else if (alpha[i] == '.') {
            if (stack_NFA.empty()) {
                error = true;
                break;
            }
            NFA second_NFA = stack_NFA.top();
            stack_NFA.pop();
            if (stack_NFA.empty()) {
                error = true;
                break;
            }
            NFA first_NFA = stack_NFA.top();
            stack_NFA.pop();
            stack_NFA.push(concat(first_NFA, second_NFA));
        } else if (alpha[i] == '+') {
            if (stack_NFA.empty()) {
                error = true;
                break;
            }
            NFA second_NFA = stack_NFA.top();
            stack_NFA.pop();
            if (stack_NFA.empty()) {
                error = true;
                break;
            }
            NFA first_NFA = stack_NFA.top();
            stack_NFA.pop();
            stack_NFA.push(pls(first_NFA, second_NFA));
        } else if (alpha[i] == '*') {
            if (stack_NFA.empty()) {
                error = true;
                break;
            }
            NFA first_NFA = stack_NFA.top();
            stack_NFA.pop();
            stack_NFA.push(klini(first_NFA));
        } else {
            error = true;
            break;
        }
    }
    if (stack_NFA.size() != 1) {
        error = true;
    } else {
        NFA final_NFA = stack_NFA.top();
        calc_dist(final_NFA.NFA_matrix, dists);
    }
    if (error) {
        cout << "ERROR";
        return 0;
    }
    NFA final_NFA = stack_NFA.top();
    find_path(final_NFA.NFA_matrix, dists, x, k);
    return 0;
}