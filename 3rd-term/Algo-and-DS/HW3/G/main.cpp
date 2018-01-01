#include<iostream>
#include<vector>
#include<set>

using namespace std;

const int INFTY = 10000000;

struct edge {
    edge(int _from, int _to, int _cap, int _flow, int _reverseInd, int _cost, int _num)
            : from(_from),
              to(_to),
              cap(_cap),
              flow(_flow),
              reverseInd(_reverseInd),
              cost(_cost),
              num(_num) {};

    int from;
    int to;
    int cap;
    int flow;
    int reverseInd;
    int cost;
    int num;
};

vector<vector<edge> > graph;
vector<int> dist;
vector<pair<int, int>> parents_pair_vect;
vector<int> min_flow_vect;
vector<int> potenc;
vector<int> used;
vector<int> dfs_vect;
vector<int> ans;
set<int> bad_egges;
int v_start;
int v_finish;
long long int max_flow;
long long int min_cost;
int n, m, k;

void algo_dejkstra(int n) {
    dist[v_start] = 0;
    used.assign(static_cast<unsigned long>(n + 1), 0);
    while (true) {
        int position = -1;
        int minimum = INFTY;
        for (int i = v_start; i <= v_finish; ++i) {
            if (dist[i] < minimum && used[i] == 0) {
                minimum = dist[i];
                position = i;
            }
        }
        if (position == -1) {
            break;
        }
        used[position] = 1;
        for (int i = 0; i < graph[position].size(); ++i) {
            int children = graph[position][i].to;
            if (graph[position][i].cap > graph[position][i].flow && used[children] == 0) {
                int new_dist = dist[position] + graph[position][i].cost + potenc[position] - potenc[children];
                if (new_dist < dist[children]) {
                    dist[children] = min (new_dist, dist[children]);
                    parents_pair_vect[children] = make_pair(position, i);
                    min_flow_vect[children] = min(min_flow_vect[position], graph[position][i].cap - graph[position][i].flow);
                }
            }
        }
    }
    for (int i = v_start; i <= n; ++i) {
        if (used[i] == 1) {
            potenc[i] += dist[i];
        } else {
            potenc[i] += dist[v_finish];
        }
    }
}

bool dfs(int vertex) {
    dfs_vect[vertex] = 1;
    if (vertex == v_finish) {
        return true;
    }
    for (int i = 0; i < graph[vertex].size(); ++i) {
        if (bad_egges.count(graph[vertex][i].num) == 0) {
            if (graph[vertex][i].num > 0 && graph[vertex][i].flow > 0 && dfs_vect[graph[vertex][i].to] == 0) {
                if (dfs(graph[vertex][i].to)) {
                    ans.push_back(graph[vertex][i].num);
                    bad_egges.insert(graph[vertex][i].num);
                    graph[vertex][i].flow = 0;
                    return true;
                }
            }
        }
    }
    return false;
}

void push_back (int from, int to, int cost, int i) {
    graph[from].push_back(edge(from, to, 1, 0, static_cast<int>(graph[to].size()), cost, i + 1 ));
    graph[to].push_back(edge( to, from, 0, 0, static_cast<int>(graph[from].size() - 1), -cost, 0 ));
    graph[to].push_back(edge( to, from, 1, 0, static_cast<int>(graph[from].size()), cost, i + 1 ));
    graph[from].push_back(edge( from, to, 0, 0, static_cast<int>(graph[to].size() - 1), -cost, 0 ));
}

void read_and_make_graph() {
    cin >> n >> m >> k;
    v_start = 1;
    v_finish = n;
    graph.resize(static_cast<unsigned long>(n + 1));
    for (int i = 0; i < m; ++i) {
        int from, to, cost;
        cin >> from >> to >> cost;
        push_back(from, to, cost, i);
    }
}

int update_if_min(int last_value, int new_value) {
    if (new_value < last_value) {
        return new_value;
    }
    return last_value;
}

int main() {
    read_and_make_graph();
    potenc.assign( static_cast<unsigned long>(n + 1), INFTY);
    potenc[v_start] = 0;
    for (int tmp = 0; tmp < n; ++tmp) {
        for (int i = v_start; i <= v_finish; ++i) {
            for (int j = 0; j < graph[i].size(); ++j) {
                if (graph[i][j].cap > 0) {
                    potenc[graph[i][j].to] = min(potenc[graph[i][j].to], potenc[i] + graph[i][j].cost);
                }
            }
        }
    }
    for(;;) {
        if (max_flow == k) {
            break;
        }
        dist.assign( static_cast<unsigned long>(n + 1), INFTY);
        parents_pair_vect.assign( static_cast<unsigned long>(n + 1), {-1, -1 });
        min_flow_vect.assign( static_cast<unsigned long>(n + 1), INFTY);
        algo_dejkstra(n);
        if (dist[v_finish] == INFTY) {
            break;
        }
        max_flow += min_flow_vect[v_finish];
        int v_x = parents_pair_vect[v_finish].first;
        int v_y = parents_pair_vect[v_finish].second;
        int flow = min_flow_vect[v_finish];
        while (v_x != -1) {
            graph[v_x][v_y].flow += flow;
            graph[graph[v_x][v_y].to][graph[v_x][v_y].reverseInd].flow -= flow;
            min_cost += graph[v_x][v_y].cost * flow;
            v_y = parents_pair_vect[v_x].second;
            v_x = parents_pair_vect[v_x].first;
        }
        dist.clear();
        parents_pair_vect.clear();
        min_flow_vect.clear();
    }
    if (max_flow == k) {
        printf("%.5f\n", static_cast<double>(min_cost) / k);
        for (int i = 0; i < k; ++i) {
            dfs_vect.assign( static_cast<unsigned long>(n + 1), 0);
            dfs(v_start);
            printf("%lu%s", ans.size(), " ");
            for (int j = static_cast<int>(ans.size() - 1); j >= 0; --j) {
                printf("%d%s", ans[j], " ");
            }
            printf("\n");
            ans.clear();
        }
    } else {
        printf("%d", -1);
    }
    return 0;
}