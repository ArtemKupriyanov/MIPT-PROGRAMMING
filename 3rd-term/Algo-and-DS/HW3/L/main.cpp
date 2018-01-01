#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<bool> right_arr, used;
vector<int> match;
vector<vector<bool> > graph;
int n;

void dfs(int vertex) {
    used[vertex] = true;
    for (int i = 0;i < graph[vertex].size(); ++i){
        if (graph[vertex][i] == true) {
            if (!right_arr[i] && !used[match[i]]) {
                dfs(match[i]);
                right_arr[i] = true;
            }
        }
    }
}

bool is_visit(int vertex) {
    used[vertex] = true;
    for (int i = 0; i < n; ++i) {
        if (graph[vertex][i] == true) {
            if (match[i] == -1 || (!used[match[i]] && is_visit(match[i]))) {
                match[i] = vertex;
                return true;
            }
        }
    }
    return false;
}

pair<set<int>, set<int> > get_pair_sets() {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] == false) {
                    if (graph[i][k] == graph[k][j] && graph[i][k] == true) {
                        graph[i][j] = true;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        used.assign(n, 0);
        is_visit(i);
    }
    vector<bool> free;
    free.assign(n, 1);
    for (int i = 0; i < n; ++i) {
        if (match[i] != -1) {
            free[match[i]] = false;
        }
    }
    used.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (free[i]) {
            dfs(i);
        }
    }
    pair<set<int>, set<int> > response_pair;
    for (int i = 0; i < n; ++i) {
        if (match[i] != -1) {
            if (right_arr[i]) {
                response_pair.second.insert(i);
            } else {
                response_pair.first.insert(match[i]);
            }
        }
    }
    return response_pair;
}

void read() {
    cin >> n;
    graph.resize(n);
    for (int i = 0; i < n; ++i) {
        graph[i].resize(n);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int tmp;
            cin >> tmp;
            graph[i][j] = tmp;
        }
    }
    match.assign(n, -1);
    used.assign(n, 0);
    right_arr.assign(n, 0);
}

int main () {
    read();
    pair<set<int>, set<int> > pair_of_sets = get_pair_sets();
    vector<int> answer_vect;
    for (int i = 0; i < n; ++i) {
        if (pair_of_sets.first.count(i) == 0 && pair_of_sets.second.count(i) == 0){
            answer_vect.push_back(i);
        }
    }
    cout << answer_vect.size() << endl;
    for (int i = 0; i < answer_vect.size(); ++i){
        cout << answer_vect[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}