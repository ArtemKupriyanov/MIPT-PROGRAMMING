//
// Created by artem on 17.04.16.
//
#ifndef IGRAPH_CLISTGRAPH_H
#define IGRAPH_CLISTGRAPH_H

#include <list>
#include <vector>
#include "IGraph.h"

using namespace std;

class CListGraph : public IGraph {
public:
    CListGraph(int n);
    CListGraph(IGraph* graph);
    ~CListGraph();

    void AddEdge(int from, int to);

    vector<int> GetNextVertexes (int vertex) const;
    vector<int> GetPrevVertexes (int vertex) const;

    int VertexCount() const { return  _vertex_count; };

    void print_graph();

protected:
    vector <list <int> > _adjacency;
    int _vertex_count;
};


#endif //IGRAPH_CLISTGRAPH_H
