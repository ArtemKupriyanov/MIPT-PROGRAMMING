#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<iomanip>

using namespace std;

const long long int INFTY = 100000000000;

struct edge {
    edge(long long int _from, long long int _to, long long int _cap, long long int _flow, long long int _cost, long long int _reverseInd)
            : from(_from),
              to(_to),
              cap(_cap),
              flow(_flow),
              cost(_cost),
              reverseInd(_reverseInd) {};

    long long int from;
    long long int to;
    long long int cap;
    long long int flow;
    long long int cost;
    long long int reverseInd;
};

vector<vector<edge> > graph;
vector<long long int> dist;
vector<pair<long long int, long long int> > parents_pair_vect;
vector<long long int> min_flow_vect;
vector<long long int> potenc;
vector<long long int> used;
vector<vector<edge> > pars;
vector<long long int> skip;
vector<vector<long long int>> answer_way;
long long int v_start, v_finish, max_flow, min_cost, n, k, ans;


void pair_push_back (long long int from, long long int to, long long int cost) {
    graph[from].push_back(edge(from, to, 1, 0, cost, static_cast<long long int>(graph[to].size() )));
    graph[to].push_back(edge(to, from, 0, 0, -cost, static_cast<long long int>(graph[from].size() - 1 )));
}

void pair_push_back_pars (long long int from, long long int to) {
    pars[from].push_back(edge(from, to, 1, 0, 0, static_cast<long long int>(pars[to].size() )));
    pars[to].push_back(edge(to, from, 0, 0, 0, static_cast<long long int>(pars[from].size() - 1 )));
}

void graph_push_back(int i) {
    graph[0].push_back(edge( 0, i, k, 0, 0, static_cast<long long int>(graph[i].size() )));
    graph[i].push_back(edge( i, 0, 0, 0, 0, static_cast<long long int>(graph[0].size() - 1 )));
    graph[n + i].push_back(edge( (n + i), 2 * n + 1, k, 0, 0, static_cast<long long int>(graph[2 * n + 1].size() )));
    graph[2 * n + 1].push_back(edge( 2 * n + 1, n + i, 0, 0, 0, static_cast<long long int>(graph[n + i].size() - 1 )));
}

void pars_push_back(int i) {
    pars[0].push_back(edge(0, i, 1, 0, 0, static_cast<long long int>(pars[i].size())));
    pars[i].push_back(edge( i, 0, 0, 0, 0, static_cast<long long int>(pars[0].size() - 1 )));
    pars[n + i].push_back(edge( n + i, 2 * n + 1, 1, 0, 0, static_cast<long long int>(pars[2 * n + 1].size() )));
    pars[2 * n + 1].push_back(edge( 2 * n + 1, n + i, 0, 0, 0, static_cast<long long int>(pars[n + i].size() - 1 )));
}

void algo_dejkstra(long long int n) {
    dist[v_start] = 0;
    used.assign(static_cast<unsigned long>(n + 1), 0);
    while (true) {
        long long int position = -1;
        long long int minimum = INFTY;
        for (long long int i = v_start; i <= v_finish; ++i) {
            if (dist[i] < minimum && used[i] == 0) {
                minimum = dist[i];
                position = i;
            }
        }
        if (position == -1) {
            break;
        }
        used[position] = 1;
        for (long long int i = 0; i < graph[position].size(); ++i) {
            long long int children = graph[position][i].to;
            if (graph[position][i].cap > graph[position][i].flow && used[children] == 0) {
                long long int new_dist = dist[position] + graph[position][i].cost + potenc[position] - potenc[children];
                if (new_dist < dist[children]) {
                    dist[children] = min(new_dist, dist[children]);
                    parents_pair_vect[children] = make_pair(position, i);
                    min_flow_vect[children] = min(min_flow_vect[position], graph[position][i].cap - graph[position][i].flow);
                }
            }
        }
    }
    for (long long int i = v_start; i <= n; ++i) {
        if (used[i] == 1) {
            potenc[i] += dist[i];
        } else {
            potenc[i] += dist[v_finish];
        }
    }
}

int init_min_cost_for_max_flow(long long int n) {
    potenc.assign(static_cast<unsigned long> (n + 1), INFTY);
    potenc[v_start] = 0;
    for (long long int tmp = 0; tmp < n; ++tmp) {
        for (long long int i = v_start; i <= v_finish; ++i) {
            for (long long int j = 0; j < graph[i].size(); ++j) {
                if (graph[i][j].cap > 0) {
                    potenc[graph[i][j].to] = min(potenc[i] + graph[i][j].cost, potenc[graph[i][j].to]);
                }
            }
        }
    }
}

void min_cost_for_max_flow(long long int n) {
    init_min_cost_for_max_flow(n);
    for (;;) {
        dist.assign(static_cast<unsigned long> (n + 1), INFTY);
        parents_pair_vect.assign(static_cast<unsigned long> (n + 1), {-1, -1 });
        min_flow_vect.assign(static_cast<unsigned long> (n + 1), INFTY);
        algo_dejkstra(n);
        if (dist[v_finish] == INFTY) {
            break;
        }
        max_flow += min_flow_vect[v_finish];
        long long int i = parents_pair_vect[v_finish].first;
        long long int j = parents_pair_vect[v_finish].second;
        long long int flow = min_flow_vect[v_finish];
        while (i != -1) {
            graph[i][j].flow += flow;
            graph[graph[i][j].to][graph[i][j].reverseInd].flow -= flow;
            min_cost += graph[i][j].cost * flow;
            j = parents_pair_vect[i].second;
            i = parents_pair_vect[i].first;
        }
        dist.clear();
        parents_pair_vect.clear();
        min_flow_vect.clear();
    }
}


long long int dinic_algo(long long int vertex, long long int flow) {
    if (vertex == v_finish) {
        max_flow += flow;
        return flow;
    }
    for (long long int i = skip[vertex]; i < pars[vertex].size(); ++i) {
        if ((dist[vertex] + 1 == dist[pars[vertex][i].to]) && (pars[vertex][i].cap - pars[vertex][i].flow > 0)) {
            long long int flow_now = dinic_algo(pars[vertex][i].to, min(flow, pars[vertex][i].cap - pars[vertex][i].flow));
            if (flow_now > 0) {
                pars[vertex][i].flow += flow_now;
                pars[pars[vertex][i].to][pars[vertex][i].reverseInd].flow -= flow_now;
                return flow_now;
            }
            else {
                ++skip[vertex];
            }
        }
    }
    return 0;
}

void find_max_flow(long long int n) {
    skip.assign(static_cast<unsigned long> (n + 1), 0);
    while (true) {
        queue<long long int> que;
        dist.assign(static_cast<unsigned long> (n + 1), INFTY);
        skip.assign(static_cast<unsigned long> (n + 1), 0);
        que.push(v_start);
        dist[v_start] = 0;
        while (!que.empty()) {
            long long int to_elem = que.front();
            que.pop();
            for (edge  e : pars[to_elem]) {
                if ((dist[e.to] > dist[to_elem] + 1) && (e.cap - e.flow > 0)) {
                    dist[e.to] = dist[to_elem] + 1;
                    que.push(e.to);
                }
            }
        }
        if (dist[v_finish] == INFTY) {
            break;
        }
        long long int dinic = dinic_algo(v_start, INFTY);
        while (dinic > 0) {
            dinic = dinic_algo(v_start, INFTY);
        }
    }
    dist.clear();
    skip.clear();
}

void graph_preproc () {
    cin >> n >> k;
    graph.resize(static_cast<unsigned long> (2 * n + 2));
    for (long long int i = 1; i <= n; ++i) {
        for (long long int j = 1; j <= n; ++j) {
            long long int cost;
            cin >> cost;
            pair_push_back(i, n + j, cost);
        }
        graph_push_back(i);
    }
}

void mcmf_for_graph() {
    v_start = 0;
    v_finish = 2 * n + 1;
    min_cost_for_max_flow(2 * n + 2);
    ans = 0;
    ans += min_cost;
}

void pars_preproc() {
    answer_way.resize(k);
    pars.resize(2 * n + 2);
    for (long long int i = 1; i <= n; ++i) {
        for(long long int j = 0; j < graph[i].size(); ++j) {
            if (graph[i][j].cap > 0 && graph[i][j].flow == graph[i][j].cap) {
                graph[i][j].flow = 0;
                graph[graph[i][j].to][graph[i][j].reverseInd].flow = 0;
                pair_push_back_pars(i, graph[i][j].to);
            }
        }
    }
    for (long long int i = 1; i <= n; ++i) {
        pars_push_back(i);
    }
}

void pars_dinic() {
    max_flow = 0;
    min_cost = 0;
    cout << ans << endl;
    for (long long int t = 0; t < k; ++t) {
        find_max_flow(2 * n + 2);
        for (long long int i = 0; i <= 2 * n + 1; ++i) {
            for (long long int j = 0; j < pars[i].size(); ++j) {
                if (i >= 1 && i <= n && pars[i][j].cap > 0 && pars[i][j].flow == pars[i][j].cap) {
                    answer_way[t].push_back(pars[i][j].to - n);
                    pars[i][j].cap = 0;
                    pars[pars[i][j].to][pars[i][j].reverseInd].cap = 0;
                }
                pars[i][j].flow = 0;
            }
        }
        max_flow = 0;
    }
}

int main() {
    graph_preproc();
    mcmf_for_graph();
    pars_preproc();
    pars_dinic();
    for (long long int i = 0; i < k; ++i) {
        for (long long int j = 0; j < n; ++j) {
            cout << answer_way[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}