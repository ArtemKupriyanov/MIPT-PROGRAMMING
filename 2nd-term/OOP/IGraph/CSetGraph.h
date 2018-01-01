//
// Created by artem on 17.04.16.
//

#ifndef IGRAPH_CSETGRAPH_H
#define IGRAPH_CSETGRAPH_H

#include "IGraph.h"
#include <vector>
#include <set>

using namespace std;

class CSetGraph : public IGraph {
public:
    CSetGraph(int n);
    CSetGraph(IGraph* graph);

    ~CSetGraph();

    void AddEdge(int from, int to);

    vector <int> GetNextVertexes(int vertex) const;
    vector <int> GetPrevVertexes(int vertex) const;

    int VertexCount() const { return  _vertex_count; }

    void print_graph();

protected:
    int _vertex_count;
    vector <set <int> > graph_set;
};


#endif //IGRAPH_CSETGRAPH_H
