#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int INFTY = 1000000000;

struct edge {
    int from;
    int to;
    int cap;
    int flow;
    int reverseInd;
};

struct sector {
    int mount_in;
    int mount_out;
    int type;
};

bool sort_function (edge left, edge right) {
    return (left.<j);
}

std::vector<std::vector<sector>> kings_sectors;
int cnt = 0;
int n, m, k, l;
int x_A, y_A, x_B, y_B;
std::vector<std::vector < edge> > graph;
std::vector<int> skip;
std::vector<int> dist;
std::vector<int> colors_arr, comp_arr;
int max_flow;
int v_start, v_finish;


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
    comp_arr[vertex] = 1;
    for (edge edge_now : graph[vertex]) {
        if (edge_now.flow < edge_now.cap && colors_arr[edge_now.to] == 0) {
            dfs(edge_now.to);
        }
    }
    colors_arr[vertex] = 2;
}

void read() {
    std::cin >> n >> m;
    std::cin >> k >> l;
    graph.resize(n * m * 2 + 1);
    kings_sectors.resize(n + 1);
    for(int i = 0; i <= n; ++i) {
        kings_sectors[i].resize(m + 1, {0, 0, 0});
    }
    int xi, yi;
    for(int i = 0; i < k; ++i) {
        std::cin >> xi >> yi;
        kings_sectors[xi][yi].type = 2;
    }
    int xj, yj;
    for(int i = 0; i < l; ++i) {
        std::cin >> xj >> yj;
        kings_sectors[xj][yj].type = 1;
    }
    std::cin >> x_A >> y_A >> x_B >> y_B;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            kings_sectors[i][j].mount_in = ++cnt;
            kings_sectors[i][j].mount_out = ++cnt;
        }
    }
}

void push_to_graph(int from, int to, int cap) {
    graph[from].push_back({from, to, cap, 0, static_cast<int>(graph[to].size())});
    graph[to].push_back({to, from, 0, 0, static_cast<int>(graph[from].size() - 1)});
}

void push_to_graph2(int from, int x_to, int y_to) {
    graph[from].push_back({from, kings_sectors[x_to][y_to].mount_in, INFTY, 0, static_cast<int>(graph[kings_sectors[x_to][y_to].mount_in].size())});
    graph[kings_sectors[x_to][y_to].mount_in].push_back({kings_sectors[x_to][y_to].mount_in, from, 0, 0, static_cast<int>(graph[from].size() - 1)});
}

void make_graph() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int m_in = kings_sectors[i][j].mount_in, m_out = kings_sectors[i][j].mount_out,
                    x1 = i - 1, y1 = j, x2 = i + 1, y2 = j, x3 = i, y3 = j - 1, x4 = i, y4 = j + 1;
            if(kings_sectors[i][j].type == 0) {
                push_to_graph(m_in, m_out, INFTY);
            }
            if(kings_sectors[i][j].type == 1) {
                push_to_graph(m_in, m_out, 1);
            }

            if(x1 != 0 && y1 != 0 && kings_sectors[x1][y1].type != 2) {
                push_to_graph2(m_out, x1, y1);
            }
            if(x2 <= n && y2 != 0 && kings_sectors[x2][y2].type != 2) {
                push_to_graph2(m_out, x2, y2);
            }
            if(x3 != 0 && y3 != 0 && kings_sectors[x3][y3].type != 2) {
                push_to_graph2(m_out, x3, y3);
            }
            if(x4 != 0 && y4 <= m && kings_sectors[x4][y4].type != 2) {
                push_to_graph2(m_out, x4, y4);
            }
        }
    }
}

int main() {
    read();
    make_graph();
    v_start = kings_sectors[x_A][y_A].mount_out;
    v_finish = kings_sectors[x_B][y_B].mount_in;
    find_max_flow(cnt);
    colors_arr.resize(cnt + 1);
    comp_arr.resize(cnt + 1, 0);
    dfs(v_start);
    if(max_flow < INFTY) {
        printf("%d", max_flow);
        printf("\n");
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if((i != x_A || j != y_A) && (i != x_B || j != y_B)) {
                    if (comp_arr[kings_sectors[i][j].mount_in] != comp_arr[kings_sectors[i][j].mount_out]) {
                        printf("%d%s%d", i, " ", j);
                        printf("\n");
                    }
                }
            }
        }
    } else {
        printf("%d", -1);
    }
    return 0;
}
