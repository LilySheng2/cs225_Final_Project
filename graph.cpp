#include "graph.h"
#include <queue>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

// graph: implement an empty graph
Graph::Graph(){
    numVertices = 0;
}

//graph: implement a graph using a map
Graph::Graph(map<string, vector<string>> &videos){
    numVertices = videos.size();
    for(auto it = videos.begin(); it != videos.end(); ++it){
       setVertexValue(it->first, it->second);      
    }
}

//setVertexValue: sets the value associated with the vertex x to v.
void Graph:: setVertexValue(string videoID, vector<string> &InfoVec){
    videoInfo videoInfo_;
    bool isValid = true;
    unsigned long size = InfoVec.size();
    if(size < 9){
        isValid = false;
    }
    if(isValid){
        videoInfo_.uploader = InfoVec[0];
        videoInfo_.age = stod(InfoVec[1]);
        videoInfo_.category = InfoVec[2];
        videoInfo_.length = stod(InfoVec[3]);
        videoInfo_.views = stod(InfoVec[4]);
        videoInfo_.rate = stod(InfoVec[5]);
        videoInfo_.ratings = stod(InfoVec[6]);
        videoInfo_.comments = stod(InfoVec[7]);

        for(unsigned i = 8; i < InfoVec.size(); i++){
            videoInfo_.related_IDs.push_back(InfoVec[i]);
        }

        adjLists[videoID] = videoInfo_;
    }
}

//BFS: use BFS to find the shortest path between videoID1 and videoID2
/*
*/
vector<string> Graph:: BFS(string videoID1, string videoID2){

    //res vector
    vector<string> res;

    //initialize prev and visited
    map<string, string> prev;
    for(auto it = adjLists.begin(); it != adjLists.end(); ++it){
        prev[it->first] = "";
    }

    //set prev value and visited value of videoID1
    //push videoID1 onto queue
    prev[videoID1] = videoID1;
    bool find = false;
    
    queue<string> q;
    q.push(videoID1);

    while(!q.empty()){
        string curr_video = q.front();
        q.pop();

        //if find, return
        if(curr_video == videoID2){
            res.push_back(curr_video);
            find = true;
            break;
        }

        //if not visited, push to queue
        vector<string> related_videos = adjLists[curr_video].related_IDs; 
        for(auto it = related_videos.begin(); it != related_videos.end(); ++it){
            if(prev[*it] == ""){
                q.push(*it);
                prev[*it] = curr_video;
            }
        }
    }

    //no path
    if(!find){
        res.push_back("there is no path between " + videoID1 + " and " + videoID2);
        return res;
    }else{
        string video = prev[videoID2];
        while(video != videoID1){
            res.push_back(video);
            video = prev[video];
        }
        res.push_back(videoID1);
        reverse(res.begin(), res.end());
    
        ofstream BFSout;
        BFSout.open ("BFS.txt");
        BFSout << "Path from "<<videoID1<< " to "<<videoID2<<" : "<<"\n";
        for(size_t i = 0; i < res.size(); i++){
            if(i != res.size() - 1){
                BFSout << res[i] << " -> ";
            }else{
                BFSout << res[i] << endl;
            }
            
        }
        BFSout.close();
    }


    


    return res;
}





//adjacent: tests whether there is an edge from the vertex x to the vertex y;
bool Graph:: areAdjacent(string videoID1, string videoID2){
    unsigned long size = adjLists[videoID1].related_IDs.size();
    for(unsigned i = 0; i < size; i++){
        if(videoID2 == adjLists[videoID1].related_IDs[i]){
            return true;
        }
    }
    return false;
}

//addEdge: add edge from vertex x to vertex y
void Graph:: addEdge(string videoID1, string videoID2){
    adjLists[videoID1].related_IDs.push_back(videoID2);
}
        
//removeEdge: removes the edge from the vertex x to the vertex y, if it is there;        
void Graph:: removeEdge(string videoID1, string videoID2){
    unsigned long size = adjLists[videoID1].related_IDs.size();
    for(unsigned i = 0; i < size; i++){
        if(videoID2 == adjLists[videoID1].related_IDs[i]){
            adjLists[videoID1].related_IDs.erase(adjLists[videoID1].related_IDs.begin() + i);
        }
    }
}

//get_vertex_value: returns the value associated with the vertex x;
videoInfo Graph::getVertexValue(string videoID){
    return adjLists[videoID];
}

//getVertices: returns a list of all vertex labels in the graph
vector<string> Graph::getVertices(){
    vector<string> vertices;
    for(auto it = adjLists.begin(); it != adjLists.end(); ++it) {
        vertices.push_back(it->first);
       // std::cout << it->first << std::endl;
    }
    return vertices;
}

//addVertex: adds the vertex x, if it is not there;
/*void Graph::addVertex(string videoID1) {
    if (adjLists.find(videoID1) == adjLists.end()) {
        videoInfo videoInfo_;
        adjLists[videoID1] = videoInfo_;
    }
}
*/

//neighbors: lists all vertices y such that there is an edge from the vertex x to the vertex y;
vector<string> Graph::neighbors(string videoID1) {
    return adjLists[videoID1].related_IDs;
}

//removeVertex: removes the vertex x, if it is there;
void Graph::removeVertex(string videoID1) {
    auto it = adjLists.find(videoID1);
    if (it != adjLists.end()) {
        adjLists.erase(it);
    }
}

int Graph::getNumVertices() {
    return numVertices;
}

