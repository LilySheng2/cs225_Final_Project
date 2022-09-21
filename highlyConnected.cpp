#include "highlyConnected.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;


/**
* Constructor for HighlyConnected
* First creates the graph from the file. 
* Then it creates edges from each video to its related videos. 
**/
HighlyConnected::HighlyConnected(string filename) {
    std::map<std::string, std::vector<std::string>> videos_map = FileIO::readFromFile(filename); 
    graph = new UndirectedGraph(filename);
    //creating Edges for each video ids and its related videos

    edges = graph->getEdges();
    vertices = graph->getVertices();
    num_vertices = (int) vertices.size();
    num_edges = (int) edges.size();
}

/**
* Destructor 
**/
HighlyConnected::~HighlyConnected() {
    delete graph; 
}


/**
* Clusters the highly connected subgraphs based on the minimum edge cuts. 
* For each of the minimum edges returned by calling the function minEdgeCut() on the graph, remove the edge from the graph.
* Return the graph. 
**/

void HighlyConnected::clustering(UndirectedGraph* subgraph) {
    vector<UndirectedGraph::Edge> minCut = minEdgeCut(subgraph);        //gets the minimum edges cuts for the subgraph
    unsigned numEdgeCuts = minCut.size();
    if (numEdgeCuts == 0) {
        return;
    }

    if ((int) numEdgeCuts > subgraph->getNumVertices()/ 2) {            //if highly connected, then return
        return;
    } else {
        for (size_t i = 0; i < numEdgeCuts; i++) {
            subgraph->removeEdge(minCut[i].start, minCut[i].end);       //remove the edge cuts from the graph
            graph->removeEdge(minCut[i].start, minCut[i].end);          //reflect the removals in the private variable to access later
        }

        //get the two subgraphs after removal of edge cuts
        string parent1 = minCut[0].start;
        string parent2 = minCut[0].end;
        map<string, bool> visited1; 
        map<string, bool> visited2; 
        vector<string> vertices_1 = BFS(parent1, visited1);     //gets vertices in each subgraph
        vector<string> vertices_2 = BFS(parent2, visited2); 
        vector<UndirectedGraph::Edge> edges_1; 
        vector<UndirectedGraph::Edge> edges_2; 

        for (size_t i = 0; i < vertices_1.size(); i++) {
            for (size_t j = 0; j < vertices_1.size(); j++) {
                if (subgraph->areAdjacent(vertices_1[i], vertices_1[j])) {
                    UndirectedGraph::Edge edge(vertices_1[i], vertices_1[j]);
                    edges_1.push_back(edge);
                }
            }
        }

        for (size_t i = 0; i < vertices_2.size(); i++) {
            for (size_t j = 0; j < vertices_2.size(); j++) {
                if (subgraph->areAdjacent(vertices_2[i], vertices_2[j])) {
                    UndirectedGraph::Edge edge(vertices_2[i], vertices_2[j]);
                    edges_2.push_back(edge);
                }
            }
        }

        UndirectedGraph* subgraph_1 = new UndirectedGraph(edges_1 , vertices_1);    
        UndirectedGraph* subgraph_2 = new UndirectedGraph(edges_2, vertices_2);
        clustering(subgraph_1); //recursively do clustering on the smaller subgraphs
        clustering(subgraph_2);     
    }

}


/**
* Finds the minimum edge cuts.
* Unions two vertices together into a subset until there is only two large vertices left.
* The edges left between the two large vertices are the mininmum edge cuts. 
* Returns a vector of edges which are the minimum edges. 
**/
vector<UndirectedGraph::Edge> HighlyConnected::minEdgeCut(UndirectedGraph* subgraph) {
    int num_v = subgraph->getNumVertices(); 
    int num_e = subgraph->getNumEdges();
    vector<string> sub_vertices = subgraph->getVertices();
    vector<UndirectedGraph::Edge> sub_edges = subgraph->getEdges();
    map<string, Subset*> subsets;
    //creates a subset for each vertex
    for (int i = 0; i < subgraph->getNumVertices(); i++) {
        string vertex = sub_vertices[i];
        Subset* subset = new Subset(vertex, 0);
        subsets[sub_vertices[i]] = subset;
    }

    int v = num_v;
    int i = 0;
    while (v > 2) {
        if (i >= num_e) {
            break;
        }  
        //int i = rand() % num_edges; //picks a random edge
        
        
        //find the subsets of the two ends of the same edge
        string subset1 = find(sub_edges[i].start, subsets); 
        string subset2 = find(sub_edges[i].end, subsets);
        
        
        if (subset1 == subset2) { 
            //if they are in the same subset, then we continue
            i++;
            continue;
        } else {
            //otherwise, we combine the endpoints into one vertex
            i++;
            v--;
           // cout << vertices << endl;
            subsetUnion(subset1, subset2, subsets);
        }
    }

    //we only have 2 subsets left 
    //we need to count the number of edges betweeen these two subsetst
    vector<UndirectedGraph::Edge> cut_edges;
    for (int i = 0; i < num_e; i++) {
        //for each edge, if it is not in the same subset, add to num of cut_edges
        string subset1 = find(sub_edges[i].start, subsets);
        string subset2 = find(sub_edges[i].end, subsets);
        if (subset1 != subset2) {
            cut_edges.push_back(sub_edges[i]);
        }
    }
    return cut_edges;

}

/**
* Finds the set of element by recursively going back to the parent
*/
string HighlyConnected::find(string element, map<string, Subset*>& subsets) {
    //finds the root and makes it the parent of the element
    if (subsets[element]->parent != element) {
        subsets[element]->parent = find(subsets[element]->parent, subsets);
    }
    return subsets[element]->parent; 
}


/**
* Unions two sebsets using their ranks
* Ranks are at first initialized to 0 in when constructing the subset
**/
void HighlyConnected::subsetUnion(string elem1, string elem2, map<string, Subset*>& subsets) {
    string elem1_root = find(elem1, subsets);
    string elem2_root = find(elem2, subsets);

    if (subsets[elem1]->rank < subsets[elem2]->rank) {
        subsets[elem1]->parent = elem2_root;
    } else if (subsets[elem1]->rank > subsets[elem2]->rank) {
        subsets[elem2]->parent = elem1_root;
    } else { //if ranks are the same
        subsets[elem2]->parent = elem1_root;
        subsets[elem1]->rank++; 
    }
}

void HighlyConnected::percentSimilar(string filename) {
    vector<vector<string>> subgraphs = BFS();               //gets all of the subgraphs
    vector<map<string, int>> map_cat;                       //maps each category with its count for each subgraph
    map<string, string> categories = graph->categories;     //gets the categories
    vector<std::pair<string, double>> max_categories;       //the categories with the most counts
    vector<std::pair<string, double>> max_categories2;      //the categories with the second most counts

    
    for (size_t i = 0; i < subgraphs.size(); i++) {         //for each subgraph
        map<string, int> subCat;
        for (size_t j = 0; j < subgraphs[i].size(); j++) {                     //for each vertex in the subgraph
            auto lookup = subCat.find(categories[subgraphs[i][j]]);            //if category already in map then increment 
            if (lookup != subCat.end()) {                                      //if not then add to map
                subCat[categories[subgraphs[i][j]]]++;
            } else {
                subCat[categories[subgraphs[i][j]]] = 1;
            }
        }

        map_cat.push_back(subCat);
        int max = 0;
        string max_cat = "";
        int max2 = 0; 
        string max_cat2= "";
        //finds the max and second max category in each subgraph 
        for (auto it = subCat.begin(); it != subCat.end(); ++it) {
            if (it -> second > max) {
                max2 = max; 
                max_cat2 = max_cat; 
                max = it -> second;
                max_cat = it -> first; 
            }
        }

        //calculates the percentages
        double max_percent = ((double) max) / ((double) subgraphs[i].size());
        double max_percent2 = ((double) max2 / ((double) subgraphs[i].size()));

        //add to vectors
        max_categories.push_back(std::pair<string, double> (max_cat, max_percent));
        max_categories2.push_back(std::pair<string, double> (max_cat2, max_percent2));

    }


    //puts the results in the file indicated by the passed in parameter
    ofstream resultsFile;   
    resultsFile.open(filename);
    for (size_t i = 0; i < max_categories.size(); i++) {
        resultsFile << "First category: " << max_categories[i].first << ": " << max_categories[i].second * 100 << "%"
        << "    Second Category: " <<  max_categories2[i].first << ": " << max_categories2[i].second * 100 << "%\n";
    }

    resultsFile.close(); 
}

/**
* Helper function to analyze the data after clustering.
* Gets each the vertices in each subgraph in vectors. 
*/
vector<vector<string>> HighlyConnected::BFS() {
    map<string, bool> visited;
    vector<vector<string>> subgraphs; 
    for (size_t i = 0; i < vertices.size(); i++) {  //marking each vertex as false (unexplored)
        visited[vertices[i]] = false;
    }

    for (size_t i = 0; i < vertices.size(); i++) {
        auto lookup = visited.find(vertices[i]); 
        vector<string> subgraph;
        if (lookup->second == false) {
            subgraph = BFS(vertices[i], visited);
            subgraphs.push_back(subgraph);
        }

    }

    return subgraphs; 
}

/**
*  Helper function that does BFS on each vertex
**/
vector<string> HighlyConnected::BFS(string video, map<string, bool> & visited) {
    vector<string> subgraph;
    queue<string> q; 
    visited[video] = true;
    q.push(video);

    while (!q.empty()) {
        string v = q.front();
        q.pop();
        subgraph.push_back(v);
        vector<string> adj = graph->neighbors(v);
        for (size_t i = 0; i < adj.size(); i++) {
            if (visited[adj[i]] == false) {
                visited[adj[i]] = true;
                q.push(adj[i]);
            }
        }
    }  
    return subgraph;   
}

UndirectedGraph* HighlyConnected::getGraph() {
    return graph; 
}