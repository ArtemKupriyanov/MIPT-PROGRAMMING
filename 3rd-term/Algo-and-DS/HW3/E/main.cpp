#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>

using namespace std;

const int INFTY = 1000000;

struct edge {
    edge(int _from, int _to, int _cap, int _flow, int _reverseInd)
            : from(_from),
              to(_to),
              cap(_cap),
              flow(_flow),
              reverseInd(_reverseInd) {};

    int from;
    int to;
    int cap;
    int flow;
    int reverseInd;
};

struct task {
    task() {};

    task(int _min_arrive, int _type, int _x, int _y)
            : min_arrive(_min_arrive),
              type(_type),
              x(_x),
              y(_y) {};

    int min_arrive;
    int type;
    int x;
    int y;
};

vector<vector < edge> > graph;
vector<vector<int> > sympathy;
vector<int> skip, dist;
vector<task> tasks_vect;
vector<int> company_boys;
set<int> lucky_girls;
int max_flow, v_start, v_finish, n, k, n_requests, company_size, for_compare;

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

void read() {
    cin >> n >> k;
    sympathy.resize(n + 2);
    for (int i = 1; i <= n; ++i) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            int tmp;
            cin >> tmp;
            sympathy[i].push_back(tmp);
        }
    }
    cin >> n_requests;
}

void work_with_company_boys() {
    cin >> company_size;
    graph.resize(n + k + 3);
    for (int j = 0; j < company_size; ++j) {
        company_boys.resize(company_size);
        cin >> company_boys[j];
        for (int k = 0; k < sympathy[company_boys[j]].size(); ++k) {
            lucky_girls.insert(sympathy[company_boys[j]][k]);
        }
    }
}

void push_back(int from, int to) {
    graph[from].push_back(edge( from, to, 1, 0, static_cast<int>(graph[to].size()) ));
    graph[to].push_back(edge( to, from, 0, 0, static_cast<int>(graph[from].size() - 1) ));
}

void prepare_graph () {
    int start = 1;
    int end_iter = 0;
    for_compare = static_cast<int> (lucky_girls.size());
    for (int j = 0; j < company_size; ++j) {
        end_iter = company_boys[j] - 1;
        for (int iter = start; iter <= end_iter; ++iter) {
            for (int h = 0; h < sympathy[iter].size(); ++h) {
                if (lucky_girls.count(sympathy[iter][h]) != 0) {
                    push_back(iter, n + sympathy[iter][h]);
                }
            }
        }
        for (int iter = 0; iter < sympathy[company_boys[j]].size(); ++iter) {
            lucky_girls.erase(sympathy[company_boys[j]][iter]);
        }
        start = company_boys[j] + 1;
    }
    for (int j = 1; j <= n; ++j) {
        push_back(0, j);
    }
    for (int j = n + 1; j <= n + k; ++j) {
        push_back(j, n +k + 1);
    }
}

void solve() {
    v_start = 0;
    v_finish = n + k + 1;
    find_max_flow(n + k + 2);
    if (max_flow == for_compare) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}

void upd() {
    max_flow = 0;
    company_boys.clear();
    lucky_girls.clear();
    graph.clear();
    skip.clear();
    dist.clear();
}

int main() {
    read();
    for (int number_request = 0; number_request < n_requests; ++number_request) {
        work_with_company_boys();
        prepare_graph();
        solve();
        upd();
    }
    return 0;
}