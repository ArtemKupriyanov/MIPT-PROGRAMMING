#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int array_size = 101;
const int INFTY = 1000000000;

int n, s, t, c;

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
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        edge_vector.clear();
        cin >> s >> t >> c;
        --s;
        --t;
        for (int i = 0; i < n; ++i) {
            graph_index[i].clear();
        }
        for (int i = 0; i < c; ++i) {
            int vert1, vert2, vol;
            cin >> vert1 >> vert2 >> vol;
            --vert1;
            --vert2;
            add_edge(vert1, vert2, vol);
            add_edge(vert2, vert1, vol);
        }
        dinic_algo();
    }
    return 0;
}