//
// Created by artem on 17.04.16.
//

#include <iostream>
#include "CArcGraph.h"

CArcGraph::CArcGraph(int n)
        :_vertex_count(n) {}

CArcGraph::CArcGraph(IGraph *graph) {
    _vertex_count = graph->VertexCount();
    for (int i = 0; i < _vertex_count; ++i) {
        vector <int> next = graph->GetNextVertexes(i);
        for (int j = 0; j < next.size(); ++j) {
            graph_list.push_back( SPair(i, next[j]) );
        }
    }
}

CArcGraph::~CArcGraph() {
    graph_list.clear();
}

void CArcGraph::AddEdge(int from, int to) {
    graph_list.push_back( SPair(from, to) );
}

vector<int> CArcGraph::GetNextVertexes(int vertex) const {
    vector <int> answer;
    for (int i = 0; i < graph_list.size(); ++i) {
        if (graph_list[i].who == vertex) {
            answer.push_back(graph_list[i].with_who);
        }
    }
    return answer;
}

vector<int> CArcGraph::GetPrevVertexes(int vertex) const {
    vector <int> answer;
    for (int i = 0; i < graph_list.size(); ++i) {
        if (graph_list[i].with_who == vertex){
            answer.push_back(graph_list[i].who);
        }
    }
    return answer;
}

void CArcGraph::print_graph() {
    for (int i = 0; i < graph_list.size(); ++i) {
        cout << "кто:" << graph_list[i].who <<" c кем:" << graph_list[i].with_who << endl;
    }
}


