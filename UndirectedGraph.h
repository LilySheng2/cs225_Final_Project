#pragma once

#include "FileIO.h"

#include <string>
#include <map>
#include <vector>
using namespace std;

class UndirectedGraph{
    public:
        struct Edge {
            string start, end; 
            Edge(string x, string y){
                start = x; 
                end = y;
            }
        }; 

        UndirectedGraph(string filename);
        UndirectedGraph(vector<Edge> edges, vector<string> vertices);

        bool areAdjacent(string start, string end);
        vector<string> getVertices();
        vector<Edge> getEdges();
        void removeEdge(string start, string end); 
        vector<string> neighbors(string start);
        int getNumVertices();
        int getNumEdges();
        map<string, string> categories;



    private:
        int numVertices;
        int numEdges;
        vector<Edge> edges; 
        vector<string> vertices;
        void repeatedVertices();

};