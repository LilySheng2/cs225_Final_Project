#pragma once

#include "UndirectedGraph.h"
#include <vector>
#include "FileIO.h"
#include <map>
#include <string>
#include <queue>

using namespace std;
class HighlyConnected {
    struct Edge {
        string start, end; 
        Edge(string x, string y) {
            start = x; 
            end = y;
        }
    }; 

    struct Subset {
        string parent; 
        int rank;
        Subset(string x, int y) {
            parent = x;
            rank = y;
        }
    };

    public:
    HighlyConnected(string filename); 
    ~HighlyConnected();
    string find(string element, map<string, Subset*>& subsets);
    void subsetUnion(string x, string y, map<string, Subset*>& subsets);
    vector<UndirectedGraph::Edge> minEdgeCut(UndirectedGraph* subgraph); 
    void clustering(UndirectedGraph* subgraph); 
    void percentSimilar(string filename); 
    vector<vector<string>> BFS();
    vector<string> BFS(string video, map<string, bool> & visited);
    UndirectedGraph* getGraph();

    private:
    vector<UndirectedGraph::Edge> edges; 
    vector<string> vertices;
    UndirectedGraph* graph; 

    int num_vertices; 
    int num_edges; 
    
};