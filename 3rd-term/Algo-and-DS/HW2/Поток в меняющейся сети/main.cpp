#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int array_size = 155;
const int INFTY = 1000000000;

int n, s, t, m;

struct edge {
    int from, to, cap, flow;
};

vector<edge> edge_vector;
vector<int> graph_index[array_size];
int ptr[array_size];
int d[array_size];

queue<int> que;

void add_edge(int from, int to, int cap) {
    edge e1 = {from, to, cap, 0};
    edge e2 = {to, from, 0, 0};
    edge_vector.push_back(e1);
    graph_index[from].push_back(edge_vector.size() - 1);
    edge_vector.push_back(e2);
    graph_index[to].push_back(edge_vector.size() - 1);
}


void update_cap(int vert1, int vert2, int upd) {

    for (int i = 0; i < edge_vector.size(); ++i) {
        edge_vector[i].flow = 0;
        if(edge_vector[i].from == vert1 && edge_vector[i].to == vert2 && i % 2 == 0) {
            edge_vector[i].cap += upd;
        }
    }
    return;
}

bool bfs() {
    for (int i = 0; i < n; ++i) {
        d[i] = INFTY;
    }
    d[s] = 0;
    que.push(s);
    while (que.empty() == false) {
        int vertex = que.front();
        que.pop();
        for (int i = 0; i < graph_index[vertex].size(); ++i) {
            int id_edge = graph_index[vertex][i];
            int to_vertex = edge_vector[id_edge].to;
            if ( d[to_vertex] > d[vertex] + 1 && edge_vector[id_edge].flow < edge_vector[id_edge].cap ) {
                que.push(to_vertex);
                d[to_vertex] = d[vertex] + 1;
            }
        }
    }
    return d[t] != INFTY;
}

int dfs(int vertex, int flow) {
    if (flow == 0) {
        return 0;
    }
    if (vertex == t) {
        return flow;
    }
    while ( ptr[vertex] < graph_index[vertex].size() ) {
        int i = graph_index[vertex][ptr[vertex]];
        int to = edge_vector[i].to;
        if (d[to] != d[vertex] + 1) {
            ++ptr[vertex];
            continue;
        }
        int pushed = dfs(to, min(flow, edge_vector[i].cap - edge_vector[i].flow));
        if (pushed > 0) {
            edge_vector[i].flow += pushed;
            edge_vector[i^1].flow -= pushed;
            return pushed;
        }
        ++ptr[vertex];
    }
    return 0;
}

void dinic_algo() {
    int flow = 0;
    while (bfs() == true) {
        for (int i = 0; i < n; ++i) {
            ptr[i] = 0;
        }
        while (int pushed = dfs (s, INFTY)) {
            flow += pushed;
        }
    }
    cout << flow << endl;
}

int main() {
    cin >> n >> m;
    s = 0;
    t = n - 1;
    for (int i = 0; i < n; ++i) {
        graph_index[i].clear();
    }
    for (int i = 0; i < m; ++i) {
        int vert1, vert2, vol;
        cin >> vert1 >> vert2 >> vol;
        --vert1;
        --vert2;
        add_edge(vert1, vert2, vol);
    }
    dinic_algo();
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        while (!que.empty()) {
            que.pop();
        }
        int operation, vert1_mod, vert2_mod;
        cin >> operation >> vert1_mod >> vert2_mod;
        --vert1_mod;
        --vert2_mod;
        if (operation == 1) {
            update_cap(vert1_mod, vert2_mod, 1);
        }
        if (operation == 2) {
            update_cap(vert1_mod, vert2_mod, -1);
        }
        dinic_algo();
    }
    return 0;
}