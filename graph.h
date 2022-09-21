#pragma once

#include <string>
#include <map>
#include <vector>
using namespace std;


struct videoInfo {
    string uploader;
    double age;
    string category;
    double length;
    double views;
    double rate;
    double ratings;
    double comments;
    double currentRank;
    double newRank;
    vector<string> related_IDs; //  destination airport, edge between nodes
};

class Graph{
    public:
    /*
    ToDo:
        traversal(Hongkun will implement this, don't worry about it)

    Completed ADT methods:
        constructor
        adjacent: tests whether there is an edge from the vertex x to the vertex y;
        addEdge: add edge from vertex x to vertex y
        removeEdge: removes the edge from the vertex x to the vertex y, if it is there;        
        setVertexValue: sets the value associated with the vertex x 
        addVertex: adds the vertex x, if it is not there;
        neighbors: lists all vertices y such that there is an edge from the vertex x to the vertex y;
        removeVertex: removes the vertex x, if it is there;
        get_vertex_value: returns the value associated with the vertex x;
        getVertices: returns a list of all vertex labels in the graph
        removeVertex: removes the vertex x, if it is there;


    */
        Graph();
        Graph(map<string, vector<string>> &videos);
        
        //vertex related methods
        void setVertexValue(string videoID, vector<string> &InfoVec);
        
        //edge related methods
        bool areAdjacent(string videoID1, string videoID2);
        void addEdge(string videoID1, string videoID2);
        videoInfo getVertexValue(string videoID);
        vector<string> getVertices();
        void removeEdge(string videoID1, string videoID2); 
        //void addVertex(string videoID1);
        vector<string> neighbors(string videoID1);
        void removeVertex(string videoID1);
        int getNumVertices();
        vector<string> BFS(string videoID1, string videoID2);

        vector<pair<string, double>> makePageRank(double _decayFactor, double _epsilon);
        void printPageRank(vector<pair<string, double>> pageRank, string outputFileName);

    private:
        int numVertices;
        map<string, videoInfo> adjLists;
        double decayFactor;
        double epsilon;
        
        bool checkConvergence();
        void initPageRank(double _decayFactor, double _epsilon);
        void updatePageRank();
};