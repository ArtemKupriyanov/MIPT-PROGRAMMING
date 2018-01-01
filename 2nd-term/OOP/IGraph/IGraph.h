//
// Created by artem on 17.04.16.
//

#ifndef IGRAPH_IGRAPH_H
#define IGRAPH_IGRAPH_H

#include <vector>

using namespace std;

class IGraph {
public:
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VertexCount() const  = 0;
    virtual std::vector<int> GetNextVertexes(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertexes(int vertex) const = 0;
};

#endif //IGRAPH_IGRAPH_H
