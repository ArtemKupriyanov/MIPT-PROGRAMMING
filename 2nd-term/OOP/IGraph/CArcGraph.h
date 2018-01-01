//
// Created by artem on 17.04.16.
//

#ifndef IGRAPH_CARCGRAPH_H
#define IGRAPH_CARCGRAPH_H

#include <vector>
#include "IGraph.h"

using namespace std;

struct SPair {
    SPair(int _who, int _with_who)
            : who(_who),
              with_who(_with_who) {}
    int who;
    int with_who;
};

class CArcGraph : public IGraph {
public:
    CArcGraph(int n);
    CArcGraph(IGraph* graph);
    ~CArcGraph();

    void AddEdge(int from, int to);

    int VertexCount() const { return _vertex_count; };

    vector<int> GetNextVertexes(int vertex) const;
    vector<int> GetPrevVertexes(int vertex) const;

    void print_graph();

protected:
    vector < SPair > graph_list;
    int _vertex_count;
};


#endif //IGRAPH_CARCGRAPH_H
