#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <stack>
#include <limits.h>

using namespace std;

struct edgeInfo {
    edgeInfo()
            : first_vertex(0),
              second_vertex(0),
              weight(0),
              price(0) {};

    edgeInfo (int _first_vertex, int _to, int _weight, int _price)
            :
            first_vertex(_first_vertex),
            second_vertex(_to),
            weight(_weight),
            price(_price)
    {};

    edgeInfo (const edgeInfo& edge) {
        this->first_vertex = edge.first_vertex;
        this->second_vertex = edge.second_vertex;
        this->weight = edge.weight;
        this->price = edge.price;
    }

    bool operator < (edgeInfo& r) {
        return ((price * weight) < (r.price * r.weight));
    }

    int first_vertex;
    int second_vertex;
    int weight;
    int price;
};

class Graph {
public:
    Graph(int n);


    void read(int cnt_edge);
    bool cycle_in_vertex(int vertex);
    bool add_edge(edgeInfo& edge);
    void del_edge();

    void recalc_characteristic();

    int vertex_cnt;
    int all_weight;
    int all_price;
    int characteristic;
    vector < edgeInfo > adjency;
};

Graph::Graph(int n)
        : vertex_cnt(n),
          all_weight(0),
          all_price(0),
          characteristic(0)
{}

void Graph::read(int cnt_edge) {
    int first_vertex, second_vertex, weight, price;
    for (int i = 0; i < cnt_edge; ++i) {
        cin >> first_vertex >> second_vertex >> weight >> price;
        adjency.push_back( edgeInfo(first_vertex, second_vertex, weight, price) );
        all_weight += weight;
        all_price += price;
    }
    recalc_characteristic();
}

bool Graph::cycle_in_vertex(int vertex) {
    stack <pair <int, int> > vertexes;
    vector < edgeInfo > was_used;
    vertexes.push(make_pair(vertex, vertex));
    int parent_vertex = vertex;
    while (!vertexes.empty()) {
        int now_vertex = vertexes.top().first;
        parent_vertex = vertexes.top().second;
        vertexes.pop();
        for (int i = 0; i < adjency.size(); ++i) {
            if (now_vertex == adjency[i].first_vertex && parent_vertex != adjency[i].second_vertex) {
                vertexes.push(make_pair(adjency[i].second_vertex, now_vertex));
                if (adjency[i].second_vertex == vertex) {
                    return true;
                }
            }
            if (now_vertex == adjency[i].second_vertex && parent_vertex != adjency[i].first_vertex) {
                vertexes.push(make_pair(adjency[i].first_vertex, now_vertex) );
                if (adjency[i].first_vertex == vertex) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Graph::recalc_characteristic() {
    characteristic = all_price * all_weight;
}

bool Graph::add_edge(edgeInfo& edge) {
    adjency.push_back(edge);
    all_price += edge.price;
    all_weight += edge.weight;
    recalc_characteristic();
    if (cycle_in_vertex(edge.first_vertex)) {
        del_edge();
        return false;
    } else {
        return true;
    }
}

void Graph::del_edge() {
    //нужно удалить только последнее
    edgeInfo* edge = new edgeInfo( *(adjency.end() - 1) );
    adjency.erase(adjency.end() - 1);
    all_weight -= edge->weight;
    all_price -= edge->price;
    recalc_characteristic();
}

int try_add(Graph& answer, edgeInfo& edge) {
    if (answer.add_edge(edge) ) {
        int ans = answer.characteristic;
        answer.del_edge();
        return ans;
    }
    return INT_MAX;
}

bool vertex_in_graph(Graph*& answer, edgeInfo& edge) {
    for (int i = 0; i < answer->adjency.size(); ++i) {
        if ((answer->adjency[i].first_vertex == edge.first_vertex &&
                                              answer->adjency[i].second_vertex == edge.second_vertex)) {
            return true;
        }
        if ((answer->adjency[i].second_vertex == edge.first_vertex &&
                                              answer->adjency[i].first_vertex == edge.second_vertex)) {
            return true;
        }
    }
    return false;
}

void algo_Kruskal(Graph*& graph, Graph*& answer) {
    answer = new Graph(0);
    vector < edgeInfo > edges;
    edges = graph->adjency;
    edgeInfo* this_add = NULL;
    int  all_characteristic = 0, min_characteristic, this_characteristic, min_place = -1;
    while (!edges.empty()) {
        min_characteristic = INT_MAX;
        for (int i = 0; i < edges.size(); ++i) {
            this_characteristic = try_add(*answer, edges[i]);
            if ( this_characteristic != INT_MAX) {
                if (min_characteristic > this_characteristic) {
                    this_add = new edgeInfo(edges[i]);
                    min_characteristic = this_characteristic;
                    min_place = i;
                }
            } else {
                edges.erase(edges.begin() + i);
            }
        }
        if (this_add != NULL) {
            if ( !vertex_in_graph(answer, *this_add) ) {
                answer->add_edge(*this_add);
            }
            edges.erase(edges.begin() + min_place);
        }
    }
}

int main() {
    int cnt_vertexes;
    int cnt_edges;
    cin >> cnt_vertexes >> cnt_edges;
    Graph* graph = new Graph(cnt_vertexes);
    Graph* answer;
    graph->read(cnt_edges);
    algo_Kruskal(graph, answer);
    cout << "weight:" << answer->all_weight << "price:" << answer->all_price << endl;
    return 0;
}
