#include <iostream>
#include <vector>
#include <list>
#include "IGraph.h"
#include "CMatrixGraph.h"
#include "CListGraph.h"
#include "CArcGraph.h"
#include "CSetGraph.h"

using namespace std;

void make_transport_graph(CMatrixGraph* graph, CMatrixGraph*& graph_tr) {
    graph_tr = new CMatrixGraph(graph);
    for (int i = 0; i < graph->_vertex_count; ++i) {
        for (int j = graph->_vertex_count - 1; j > i; --j) {
            swap(graph_tr->_adjency_matrix[i][j], graph_tr->_adjency_matrix[j][i]);
        }
    }
}

void count_stoks(vector < vector <int> >& accuracy_matrix, vector<int>& stoks) {
    vector<bool> is_stoks(accuracy_matrix.size(), true);
    int vertex_1 = 0, vertex_2 = 1;
    while(vertex_1 != accuracy_matrix.size() && vertex_2 != accuracy_matrix.size()) {
        if (accuracy_matrix[vertex_1][vertex_2] == accuracy_matrix[vertex_2][vertex_1]) {
            is_stoks[vertex_1] = false;
            is_stoks[vertex_2] = false;
            vertex_1 = vertex_2 + 1;
            vertex_2 += 2;
        } else {
            if (accuracy_matrix[vertex_1][vertex_2] == 0) {
                is_stoks[vertex_2] = false;
                vertex_2++;
            } else {
                is_stoks[vertex_1] = false;
                vertex_1 = vertex_2;
                vertex_2++;
            }
        }
    }
    if (vertex_1 < accuracy_matrix.size()) {
        for (int i = 0; i < accuracy_matrix.size(); ++i) {
            if (accuracy_matrix[vertex_1][i] == 1) {
                is_stoks[vertex_1] = false;
                break;
            }
        }
    }
    for (int i = 0; i < is_stoks.size(); ++i) {
        if (is_stoks[i]) {
            stoks.push_back(i);
        }
    }
}

void count_istoks(vector < vector <int> >& accuracy_matrix, vector<int>& istoks) {
    vector<bool> is_istoks(accuracy_matrix.size(), true);
    int vertex_1 = 0, vertex_2 = 1;
    while(vertex_1 != accuracy_matrix.size() && vertex_2 != accuracy_matrix.size()) {
        if (accuracy_matrix[vertex_1][vertex_2] == accuracy_matrix[vertex_2][vertex_1]) {
            is_istoks[vertex_1] = false;
            is_istoks[vertex_2] = false;
            vertex_1 = vertex_2 + 1;
            vertex_2 += 2;
        } else {
            if (accuracy_matrix[vertex_1][vertex_2] == 0) {
                is_istoks[vertex_1] = false;
                vertex_1 = vertex_2;
                vertex_2++;
            } else {
                is_istoks[vertex_2] = false;
                vertex_2++;
            }
        }
    }
    if (vertex_1 < accuracy_matrix.size()) {
        for (int i = 0; i < accuracy_matrix.size(); ++i) {
            if (accuracy_matrix[vertex_1][i] == 1) {
                is_istoks[vertex_1] = false;
                break;
            }
        }
    }
    for (int i = 0; i < is_istoks.size(); ++i) {
        if (is_istoks[i]) {
            istoks.push_back(i);
        }
    }
}

int main() {
    int v, e;
    cin >> v >> e;
    CMatrixGraph* gr = new CMatrixGraph(v);
    int from, to;
    for (int i = 0; i < e; ++i) {
        cin >> from >> to;
        gr->AddEdge(from, to);
    }
    vector<int> stoks;
    vector<int> istoks;
    count_stoks(gr->_adjency_matrix, stoks);
    count_istoks(gr->_adjency_matrix, istoks);
    for (int i = 0; i < stoks.size(); ++i) {
        cout << "stoks:" << stoks[i] << endl;
    }
    for (int i = 0; i < istoks.size(); ++i) {
        cout << "istoks:" << istoks[i] << endl;
    }
    return 0;
}