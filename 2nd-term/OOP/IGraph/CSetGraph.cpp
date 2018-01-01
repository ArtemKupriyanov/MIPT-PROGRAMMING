//
// Created by artem on 17.04.16.
//

#include <iostream>
#include "CSetGraph.h"

CSetGraph::CSetGraph(int n)
        : _vertex_count(n) {
    graph_set.resize(n);
}

CSetGraph::CSetGraph(IGraph *graph) {
    _vertex_count = graph->VertexCount();
    graph_set.resize(_vertex_count);
    for (int i = 0; i < _vertex_count; ++i) {
        vector <int> next = graph->GetNextVertexes(i);
        for (int j = 0; j < next.size(); ++j) {
            graph_set[i].insert( next[j] );
        }
    }
}

CSetGraph::~CSetGraph() {
    for (int i = 0; i < _vertex_count; ++i) {
        graph_set[i].clear();
    }
    graph_set.clear();
}

void CSetGraph::AddEdge(int from, int to) {
    graph_set[from].insert(to);
}

vector<int> CSetGraph::GetNextVertexes(int vertex) const {
    vector <int> answer;
    for(auto it =graph_set[vertex].begin(); it !=graph_set[vertex].end(); ++it) {
        answer.push_back(*it);
    }
    return answer;
}

vector<int> CSetGraph::GetPrevVertexes(int vertex) const {
    vector <int> answer;
    for (int i = 0; i < graph_set.size(); ++i) {
        if ( *graph_set[i].find(vertex) > 0 )  {
            answer.push_back(i);
        }
    }
    return answer;
}

void CSetGraph::print_graph() {
    cout << "graph size: " << _vertex_count << endl;
    for (int i = 0; i < _vertex_count; ++i) {
        for(auto it =graph_set[i].begin(); it !=graph_set[i].end(); ++it) {
            cout << "кто: " << i << "c кем: " << *it;
        }
        cout << endl;
    }
}













