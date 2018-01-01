//
// Created by artem on 17.04.16.
//

#include "CListGraph.h"
#include <vector>
#include <list>
#include <iostream>

CListGraph::CListGraph(int n)
        : _vertex_count(n)
{
    _adjacency.resize(n);
    for (int i = 0; i < n; ++i) {
        _adjacency.resize(0);
    }
}

CListGraph::CListGraph(IGraph *graph) {
    _vertex_count = graph->VertexCount();
    _adjacency.resize(_vertex_count);
    for (int i = 0; i < _vertex_count; ++i) {
        _adjacency.resize(0);
    }
    for (int i = 0; i < _vertex_count; ++i) {
        vector <int> next = graph->GetNextVertexes(i);
        for (int j = 0; j < next.size(); ++j) {
            _adjacency[i].push_front(next[j]);
        }
    }
}

CListGraph::~CListGraph() {
    for(int i = 0; i < _vertex_count; ++i) {
        _adjacency[i].clear();
    }
    _adjacency.clear();
}

void CListGraph::AddEdge(int from, int to) {
    _adjacency[from].push_front(to);
}

vector<int> CListGraph::GetNextVertexes(int vertex) const {
    vector <int> answer;
    for (auto it = _adjacency[vertex].begin(), end = _adjacency[vertex].end(); it != end; ++it) {
        answer.push_back(*it);
    }
    return answer;
}

vector<int> CListGraph::GetPrevVertexes(int vertex) const {
    vector <int> answer;
    for (int i = 0; i < _adjacency.size(); ++i) {
        for (auto it = _adjacency[i].begin(), end = _adjacency[i].end(); it != end; ++it) {
            if (*it == vertex) {
                answer.push_back(i);
                continue;
            }
        }
    }
    return answer;
}

void CListGraph::print_graph() {
    cout << "graph size: " << _vertex_count << endl;
    for (int i = 0; i < _vertex_count; ++i) {
        cout << "Next vetexes for vertex " << i << ": ";
        for (auto it = _adjacency[i].begin(), end = _adjacency[i].end(); it != end; ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
}
