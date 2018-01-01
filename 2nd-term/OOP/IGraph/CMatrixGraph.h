//
// Created by artem on 17.04.16.
//

#ifndef IGRAPH_CMATRIXGRAPH_H
#define IGRAPH_CMATRIXGRAPH_H

#include <vector>
#include "IGraph.h"

using namespace std;

class CMatrixGraph : public IGraph {
public:
    CMatrixGraph(int n);
    CMatrixGraph(IGraph* graph);

    ~CMatrixGraph();

    void AddEdge(int from, int to);

    vector <int> GetNextVertexes(int vertex) const;
    vector <int> GetPrevVertexes(int vertex) const;

    int VertexCount() const { return  _vertex_count; }

    void print_graph();

    vector <vector <int> > _adjency_matrix;
    int _vertex_count;
};


#endif //IGRAPH_CMATRIXGRAPH_H
