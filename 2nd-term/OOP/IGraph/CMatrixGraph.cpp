//
// Created by artem on 17.04.16.
//

#include <iostream>
#include <set>
#include "CMatrixGraph.h"

//черновой
CMatrixGraph::CMatrixGraph(int n)
:   _vertex_count(n) {
    _adjency_matrix.resize(n);
    for (int i = 0; i < n; ++i) {
        _adjency_matrix[i].resize(n, 0);
    }
}

CMatrixGraph::CMatrixGraph(IGraph *graph) {
    _vertex_count = graph->VertexCount();
    _adjency_matrix.resize(_vertex_count);
    for (int i = 0; i < _vertex_count; ++i) {
        _adjency_matrix[i].resize(_vertex_count, 0);
    }
    for (int i = 0; i < _vertex_count; ++i) {
        vector<int> next = graph->GetNextVertexes(i);
        for (int j = 0; j < next.size(); ++j) {
            _adjency_matrix[i][next[j]] = 1;
        }
    }
}


CMatrixGraph::~CMatrixGraph() {
    for (int i = 0; i < _vertex_count; ++i) {
        _adjency_matrix[i].clear();
    }
    _adjency_matrix.clear();
}


void CMatrixGraph::AddEdge(int from, int to) {
    _adjency_matrix[from][to] = 1;
}

vector<int> CMatrixGraph::GetNextVertexes(int vertex) const {
    vector <int> answer;
    for (int i = 0; i < _vertex_count; ++i) {
        if ( _adjency_matrix[vertex][i] ) {
            answer.push_back(i);
        }
    }
    return answer;
}

vector<int> CMatrixGraph::GetPrevVertexes(int vertex) const {
    vector <int> answer;
    for (int i = 0; i < _vertex_count; ++i) {
        if ( _adjency_matrix[i][vertex] ) {
            answer.push_back(i);
        }
    }
    return answer;
}

void CMatrixGraph::print_graph() {
    cout << "graph size: " << _vertex_count << endl;
    for (int i = 0; i < _vertex_count; ++i) {
        for (int j = 0; j < _vertex_count; ++j) {
            cout << _adjency_matrix[i][j] << " ";
        }
        cout << endl;
    }
}
















