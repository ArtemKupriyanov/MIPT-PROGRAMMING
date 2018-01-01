#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int INFTY = 1000000000;

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
vector<int> skip, dist;
vector<task> tasks_vect;
int max_flow;
int v_start, v_finish;
int n;

int manhattan_metricks(task start, task finish) {
    return abs(finish.x - start.x) + abs(finish.y - start.y) + start.min_arrive;
}

int manhattan_metricks(int x, int y, int x_0, int y_0, int weight_constant) {
    return abs(x - x_0) + abs(y - y_0) + weight_constant;
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

void read() {
    cin >> n;
    tasks_vect.push_back(task());
    graph.resize(static_cast<unsigned long> (2 * n + 2));
    int x, y, x1, y1;
    int hour, min, time_now;
    char delim;
    for(int i = 0; i < n; ++i) {
        cin >> hour >> delim >> min >> x >> y >> x1 >> y1;
        time_now = hour * 60 + min;
        tasks_vect.push_back(task(time_now, 1, x, y));
        tasks_vect.push_back(task(manhattan_metricks(x, y, x1, y1, time_now), 2, x1, y1));
    }
}

void make_graph () {
    for(int i = 1; i < tasks_vect.size(); ++i) {
        if (i % 2) {
            for (int j = 1; j < tasks_vect.size(); ++j) {
                if (tasks_vect[j].type == 2) {
                    if (manhattan_metricks(tasks_vect[i + 1], tasks_vect[j - 1]) < tasks_vect[j - 1].min_arrive) {
                        graph[i].push_back(edge(i, j, 1, 0, static_cast<int>(graph[j].size())));
                        graph[j].push_back(edge(j, i, 0, 0, static_cast<int>(graph[i].size() - 1)));
                    }
                }
            }
        }
        if(tasks_vect[i].type == 1) {
            graph[0].push_back(edge(0, i, 1, 0, static_cast<int>(graph[i].size())));
            graph[i].push_back(edge(i, 0, 0, 0, static_cast<int>(graph[0].size() - 1)));
        }
        else {
            graph[i].push_back(edge(i, static_cast<int>(tasks_vect.size()), 1, 0, static_cast<int>(graph[tasks_vect.size()].size())));
            graph[tasks_vect.size()].push_back(edge(static_cast<int>(tasks_vect.size()), i, 0, 0, static_cast<int>(graph[i].size() - 1)));
        }
    }
}

int main() {
    read();
    make_graph();
    v_start = 0;
    v_finish = static_cast<int>(tasks_vect.size());
    find_max_flow(static_cast<int>(tasks_vect.size() + 1));
    std::cout << n - max_flow << std::endl;
    return 0;
}
