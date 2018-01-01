#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void read(vector <vector <float> >& graph, int n) {
    graph.resize(n);
    for (int i = 0; i < n; ++i) {
        graph[i].resize(n, -1);
    }
    float weight;
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            if (i == j) {
                continue;
            }
            cin >> weight;
            if (weight < 0) {
                graph[i][j] = -1;
            } else {
                graph[i][j] = weight;
            }
        }
    }
}


void print_graph (vector <vector <float> >& graph) {
    for (int  i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool checkForNegCircle (vector <vector <float > > graph) {
    //print_graph(graph);
    for (int k = 0; k < graph.size(); ++k) {
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph.size(); ++j) {
                if (graph[i][j] < graph[i][k] * graph[k][j]) { //если путь через К - короче
                    graph[i][j] = graph[i][k] * graph[k][j];
                }
            }
        }
    }
    //print_graph(graph);
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[i][i] > 1) {
            return true;
        }
    }
    return false;
}


int main() {
    int n;
    cin >> n;
    vector <vector <float> > graph;
    read(graph, n);
    //print_graph(graph);
    if (checkForNegCircle(graph)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}