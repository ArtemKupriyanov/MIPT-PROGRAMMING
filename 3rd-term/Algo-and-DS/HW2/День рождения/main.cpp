#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <memory.h>
#include <math.h>

using namespace std;

struct edge {
    int to, cap, flow, reverseInd;
};

const int INFTY = 1000000000;
int n, m;
int max_flow;
int v_start, v_finish;

vector< vector<edge> > graph;
vector<int> skip;
vector<int> dist;
vector<vector <int> > graph2;
vector<int> colors_arr;
vector<int> boys_arr;
vector<int> girls_arr;

void push_edge_to_graph(int from, int to, int cap, int flow, int reverseInd) {
    edge e = { to, cap, flow, reverseInd};
    graph[from].push_back(e);
}

int dinic_algo(int vertex, int flow) {
    if (vertex == v_finish) {
        max_flow += flow;
        return flow;
    }
    for (int i = skip[vertex]; i < graph[vertex].size(); ++i) {
        if ((dist[vertex] + 1 == dist[graph[vertex][i].to]) && (graph[vertex][i].cap - graph[vertex][i].flow > 0)) {
            int flow_now = dinic_algo(graph[vertex][i].to, min(flow, graph[vertex][i].cap - graph[vertex][i].flow));
            if (flow_now > 0) {
                graph[vertex][i].flow += flow_now;
                graph[graph[vertex][i].to][graph[vertex][i].reverseInd].flow -= flow_now;
                return flow_now;
            }
            else {
                ++skip[vertex];
            }
        }
    }
    return 0;
}

void find_max_flow(int n) {
    skip.assign(n + 1, 0);
    while (true) {
        queue<int> que;
        dist.assign(n + 1, INFTY);
        skip.assign(n + 1, 0);
        que.push(v_start);
        dist[v_start] = 0;
        while (!que.empty()) {
            int to_elem = que.front();
            que.pop();
            for (edge  e : graph[to_elem]) {
                if ((dist[e.to] > dist[to_elem] + 1) && (e.cap - e.flow > 0)) {
                    dist[e.to] = dist[to_elem] + 1;
                    que.push(e.to);
                }
            }
        }
        if (dist[v_finish] == INFTY) {
            break;
        }
        int dinic = dinic_algo(v_start, INFTY);
        while (dinic > 0) {
            dinic = dinic_algo(v_start, INFTY);
        }
    }
    dist.clear();
    skip.clear();
}

void dfs(int vertex) {
    colors_arr[vertex] = 1;
    for (int i : graph2[vertex]) {
        if (colors_arr[i] == 0) {
            dfs(i);
        }
    }
    colors_arr[vertex] = 2;
}

void print_answer(int m, int n) {
    int n_col1 = 0, n_col2 = 0;
    cout << m + n - max_flow << endl;
    for (int i = 1; i <= m; ++i) {
        if (colors_arr[i]) {
            ++n_col1;
        }
    }
    for (int i = m + 1; i <= m + n; ++i) {
        if (!colors_arr[i]) {
            ++n_col2;
        }
    }
    cout << n_col1 << " " << n_col2 << endl;
    for (int i = 1; i <= m; ++i) {
        if (colors_arr[i]) {
            cout << i << ' ';
        }
    }
    cout << endl;
    for (int i = m + 1; i <= m + n; ++i) {
        if (!colors_arr[i]) {
            cout << i - m << ' ';
        }
    }
    cout << endl;
}

void refresh_all() {
    girls_arr.clear();
    boys_arr.clear();
    colors_arr.clear();
    graph2.clear();
    graph.clear();
    max_flow = 0;
}

void reading() {
    for (int i = 1; i <= m; ++i) {
        girls_arr.resize(n + 1, 0);
        int number_girl;
        cin >> number_girl;
        while (number_girl) {
            girls_arr[number_girl] = 1;
            cin >> number_girl;
        }
        for (int j = 1; j <= n; ++j) {
            if (girls_arr[j] == 0) {
                push_edge_to_graph(i, m+j, 1, 0, graph[m + j].size());
                push_edge_to_graph(m+j, i, 0, 0, graph[i].size() - 1);
            }
        }
        girls_arr.clear();
    }
    for (int i = 1; i <= m; ++i) {
        push_edge_to_graph(0, i, 1, 0, graph[i].size());
        push_edge_to_graph(i, 0, 0, 0, graph[0].size() - 1);
    }
    for (int i = 1; i <= n; ++i) {
        push_edge_to_graph(m+i, m+n+1, 1, 0, graph[m + n + 1].size());
        push_edge_to_graph(m+n+1, m+i, 0, 0, graph[m + i].size() - 1);
    }
}

void preprocessing() {
    cin >> m >> n;
    v_start = 0;
    v_finish = m + n + 1;
    graph.resize(v_finish + 1);
    boys_arr.resize(m + 2, 0);
    graph2.resize(v_finish);
    reading();
}
void make_graph2() {
    for (int i = 1; i <= m; ++i) {
        for (edge e : graph[i]) {
            if (e.cap == 1 && e.flow == 1) {
                graph2[e.to].push_back(i);
                boys_arr[i] = 1;
            }
            if (e.cap == 1 && e.flow == 0) {
                graph2[i].push_back(e.to);
            }
        }
    }
}

void solve() {
    find_max_flow(v_finish + 1);
    make_graph2();
    colors_arr.resize(v_finish + 2, 0);
    for (int i = 1; i <= m; ++i) {
        if (boys_arr[i] == 0 && colors_arr[i] == 0) {
            dfs(i);
        }
    }
}

int main() {
    int k;
    cin >> k;
    for (int tmp = 0; tmp < k; ++tmp) {
        preprocessing();
        solve();
        print_answer(m, n);
        refresh_all();
    }
    return 0;
}