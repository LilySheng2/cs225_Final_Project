#include "UndirectedGraph.h"
#include <queue>
#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;


UndirectedGraph:: UndirectedGraph(string filename){
    
    std::map<std::string, std::vector<std::string>> videos_map = FileIO::readFromFile(filename); 
    
    for (auto it = videos_map.begin(); it != videos_map.end(); ++it) {
        for (size_t i = 8; i < it->second.size(); i++) {
            if(it->second.size() < 8){
                std::cout<< "not valid video information!" << std::endl;
                break;
            }else{
                Edge edge(it->first, it->second[i]); 
                Edge edge2(it->second[i], it->first);
                edges.push_back(edge);
                edges.push_back(edge2);
            }
        }
    }
    for(auto video: videos_map){
        vertices.push_back(video.first);
        if(video.second.size() < 8){
            std::cout<<"not valid video information!" << std::endl;
        }
        for(unsigned long i = 8; i < video.second.size(); i++){
            vertices.push_back(video.second[i]);
        }
    }
    void repeatedVertices();
    numEdges = edges.size();
    numVertices = vertices.size();
    
    for(auto i = videos_map.begin(); i != videos_map.end(); ++i){
        if(i->second.size() < 8){
                std::cout<< "not valid video information!" << std::endl;
                break;
        }else{
            categories[i->first] = i->second.at(2);
        }
    }
    for(auto i = vertices.begin(); i != vertices.end(); ++i){
        if(categories.find(*i) == categories.end() ){
            categories[*i] = "unknown";
        }
    }
}


UndirectedGraph::UndirectedGraph(vector<UndirectedGraph::Edge> edges, vector<string> vertices){
    numVertices = vertices.size();
    numEdges = edges.size();
    edges = edges;
    vertices = vertices;
}

void UndirectedGraph::repeatedVertices(){
    map<string, int> map;
    for(auto vertice: vertices){
        if(map.find(vertice) != map.end()){
            map[vertice] = 1;
        }else{
            map[vertice] += 1;
        }
    }
    vertices.clear();
    for(auto pair: map){
        vertices.push_back(pair.first);
    }
}
bool UndirectedGraph:: areAdjacent(string start, string end){
    bool appear = false;
    for(auto edge: edges){
        if(edge.start == start && edge.end == end){
            appear = true;
        }
    }
    return appear;
}

        
//removeEdge: removes the edge from between vertex a and vertex b   
void UndirectedGraph:: removeEdge(string start, string end){
    for(auto edge = edges.begin(); edge != edges.end(); edge++){
        if((*edge).start == start){
            edges.erase(edge);
            numEdges--;
            break;
        }
    }
    for(auto edge = edges.begin(); edge != edges.end(); edge++){
        if((*edge).start == end){
            edges.erase(edge);
            numEdges--;
            break;
        }
    }
}


//getVertices: returns a list of all vertex labels in the graph
vector<string> UndirectedGraph::getVertices(){
    return vertices;
}

vector<UndirectedGraph::Edge> UndirectedGraph::getEdges(){
    return edges;
}

//neighbors: lists all vertices y such that there is an edge from the vertex x to the vertex y;
vector<string> UndirectedGraph::neighbors(string start) {
    vector<string> adj_vertices;
    for(auto edge: edges){
        if(edge.start == start){
            adj_vertices.push_back(edge.end);
        }
    }
    return adj_vertices;
}

int UndirectedGraph::getNumVertices() {
    return vertices.size();
}

int UndirectedGraph:: getNumEdges(){
    return edges.size();
}
