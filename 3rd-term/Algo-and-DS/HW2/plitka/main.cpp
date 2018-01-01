#include <iostream>
#include <vector>

using namespace std;

int n, m, a, b;
int time_dfs = 0;

vector<vector<int> > work_graph;
vector<int> mt;
vector<int> last_was;
vector<string> floor_releif;

vector<int> d_hor { 1, -1, 0,  0 };
vector<int> d_vert { 0,  0, 1, -1 };

bool dfs(int v) {
    if  (last_was[v] == time_dfs) {
        return false;
    }
    last_was[v] = time_dfs;
    for (int to = 0; to < work_graph[v].size(); ++to) {
        if  (mt[work_graph[v][to]] == -1 || dfs(mt[work_graph[v][to]])) {
            mt[work_graph[v][to]] = v;
            return true;
        }
    }
    return false;
}

bool is_vertex_empty(int i, int j) {
    if ( 0 <= i && i < n && 0 <= j && j < m && floor_releif[i][j] == '*' ) {
        return true;
    }
    return false;
}

void add_edge(int from, int to) {
    work_graph[from].push_back(to);
}

int preprocessing() {
    cin >> n >> m >> a >> b;
    work_graph.resize(n * m);
    floor_releif.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> floor_releif[i];
        floor_releif[i].resize(m);
    }
    int n_broken = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if  (((i + j) % 2 && is_vertex_empty(i, j)) == true) {
                for (int k = 0; k < 4; ++k) {
                    int i_shift = i + d_hor[k];
                    int j_shift = j + d_vert[k];
                    if  (is_vertex_empty(i_shift, j_shift)) {
                        add_edge(i * m + j, i_shift * m + j_shift);
                    }
                }
            }
            n_broken += is_vertex_empty(i, j);
        }
    }
    mt.resize(n * m, -1);
    last_was.resize(n * m, -1);
    return n_broken;
}

void solve() {
    for(int v = 0; v < n * m; ++v) {
        ++time_dfs;
        dfs(v);
    }
}

int main() {
    int n_broken = preprocessing();
    if  (2 * b <= a) {
        cout << b * n_broken;
        return 0;
    }
    solve();
    int n_parosoch = 0;
    for (int to = 0; to < n * m; ++to) {
        if (mt[to] != -1) {
            ++n_parosoch;
        }
    }
    int ans =  n_parosoch * a + (n_broken - 2 * n_parosoch) * b;
    cout << ans;
    return 0;
}