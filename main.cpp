#include "FileIO.h"
#include "graph.h"
#include "highlyConnected.h"
#include "UndirectedGraph.h"
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    
    //testing FileIO
    std::map<std::string, std::vector<std::string>> videos_;
    videos_ = FileIO::readFromFile("basicIO.txt");

    vector<string> videoInfo = {"cruzadas", "646", "People", "69", "2292", "2.45","11", "11",
     "eoRVsJLwHbU", "gPa1qa25ZNs", "HpVqoNBf5S8", "y-6wDj7nEjA", "7W91DJBX3Ao", "PGkFB9hMzeA",
    "kSB-uZPSOVk",	"gh2EIntCgP0",	"jXZbS6jk_Hs",	"_cqw2TDGqIc",	"Qd4a8zu4CiY",	"qkq0w6ua_Sg",	"i7_N_Li7Ql4",	"p4-8jn7bjJo",
    "atLJ2BxGIkE",	"UyTxWvp8upM",	"4Hmoei0-XdU",	"XZ3gPWSSft8",	"g19ufice33c",	"nLK9nZmYYJc"
    };
    sort(videoInfo.begin(), videoInfo.end());

    vector<string> ans = videos_.find("LdWW73z-uQk")->second;
    sort(ans.begin(), ans.end());

    if(ans == videoInfo){
        std::cout << "Passing test FileIO" << std::endl;
    }
   
    

    std::map<std::string, std::vector<std::string>> videos_map = FileIO::readFromFile("videos_10_lines.txt"); 

    //testing constructor
    Graph videos0(videos_map);
    if (videos0.getNumVertices() == 10) {
        std::cout << "Passing test constructor" << std::endl;
    }

    //testing setVertex Value
    Graph videos1(videos_map);
    vector<string> info = {"CYOadjective", "806", "Entertainment", "15","14", "1", "1",	"0",
    	"4LHNnOQ7smk", "vfYexLGju_E", "AHZFt0WjjH0", "ItjArExrJIE", "t-9F7HOxNK0", "FcZe5oX0qVo", 
        "zk3IzMwyEQ4", "HjVrWF95PvM",	"7wVom03I2_A", "hp0S1hgGB7w", "MeP-AXDnVvk", "FldGLWTgB98", 
        "qM9ZRAyt3HI", "W8-mftv235M", "Rh0c3U4sjH0", "mhXyjr0cEvo", "TAb8yeVucNQ", "paXJDBesw6g", "HtRxML2QyOM", "SqiDzro4wF4"};
        //setting the first vertext to have the same values as the last vertext
    videos1.setVertexValue("4LHNnOQ7smk", info);
    if (videos1.getVertexValue("4LHNnOQ7smk").views == videos1.getVertexValue("BqN0NCM2t6M").views) {
        std::cout << "Passing test setVertexValue" << std::endl;
    }
    
    //testing areAdjacent1
    Graph videos2(videos_map);
    if (videos2.areAdjacent("4LHNnOQ7smk", "HjVrWF95PvM") == true) {
        std::cout << "Passing test areAdjacent1" << std::endl;
    } //checking for an edge between the 1st and 5th video 

    //testing areAdjacent2
    Graph videos3(videos_map);
    if (videos3.areAdjacent("hp0S1hgGB7w", "FcZe5oX0qVo") == true) {
        std::cout << "Passing test areAdjacent2" << std::endl;
    }
    //checking for an edge between the 7th and 3rd video


    //testing areAdjacent3
    Graph videos4(videos_map);
    if (videos4.areAdjacent("7wVom03I2_A", "hp0S1hgGB7w") == false) {
        std::cout << "Passing test areAdjacent3" << std::endl;
        //checking that there isn't an edge between 6th and 7th video 
    }

    //testing addEdge
    Graph videos5(videos_map);
    videos5.addEdge("7wVom03I2_A", "hp0S1hgGB7w"); //addding edge between 6th and 7th video
    if(videos5.areAdjacent("7wVom03I2_A", "hp0S1hgGB7w") == true) {
        std::cout << "Passing test addEdge" << std::endl;
    }

    //testing removeEdge
    Graph videos6(videos_map);
    videos6.removeEdge("4LHNnOQ7smk", "HjVrWF95PvM"); //removing edge between 1st and 5th node
    if (videos6.areAdjacent("4LHNnOQ7smk", "HjVrWF95PvM") == false) {
        std::cout << "Passing test removeEdge" << std::endl;
    }


    //testing getVertices
    Graph videos7(videos_map);
    vector<string> video_ids = {"4LHNnOQ7smk", "vfYexLGju_E", "FcZe5oX0qVo", "zk3IzMwyEQ4", "HjVrWF95PvM", 
    "7wVom03I2_A", "hp0S1hgGB7w", "W8-mftv235M", "MeP-AXDnVvk", "BqN0NCM2t6M"};
    std::sort(video_ids.begin(), video_ids.end());
    if (video_ids == videos7.getVertices()) {
        std::cout << "Passing test getVertices" << std::endl;
    }


    //testing neighbors
    Graph videos8(videos_map);
    vector<string> n = {"Q3hN_nP1Mb4","FvPXIss5Xgs","C0ajS6jSIDo","ycfjblX3aAA", "OUGJBE3GDts",
    "HlfX4ApJ18w","1lHgAMu2iWs","AHZFt0WjjH0","vfYexLGju_E","eoRVsJLwHbU", "LpdmIzL3JoQ", "atXDoZ-CGB4", "FcZe5oX0qVo",
    "ItjArExrJIE", "uJOr-ZgvGkE", "kvSE8CQO68Q", "HjVrWF95PvM", "oHSwoAwBzh4","lN5weaxgp1U","7bbaRyDLMvA"};
    if (n == videos8.neighbors("4LHNnOQ7smk")) {
        std::cout << "Passing test neighbors" << std::endl;

    } //checking neighbors of first video

    //testing BFS
    std::map<std::string, std::vector<std::string>> videos_map2 = FileIO::readFromFile("largeIO.txt"); 
    Graph videos9(videos_map2);
    vector<string> res = videos9.BFS("FcZe5oX0qVo", "BU7nF3XgFs0");
    for(auto it = res.begin(); it != res.end(); ++it){
        cout<<(*it)<<endl;
    }

    std::map<std::string, std::vector<std::string>> videos_map_large = FileIO::readFromFile("largeIO.txt"); 
    Graph videos10(videos_map_large);
    std::cout<<"HERE"<<std::endl;
    vector<pair<string,double>> rank = videos10.makePageRank(0.95,0.000001);
    videos10.printPageRank(rank,"largeIoPageRank");

    std::map<std::string, std::vector<std::string>> pageRankTest = FileIO::readFromFile("pageRankTestIo.txt"); 

    Graph videos11(pageRankTest);
    vector<pair<string,double>> rank1 = videos11.makePageRank(0.95,0.0005);
    vector<string> correctRank = {"A","D","B","C","E"};
    bool ranksMatch = true;
    for(size_t i = 0; i<rank1.size() ; i++){
        if(correctRank[i].compare(rank1[i].first)!= 0){
            ranksMatch = false;
            break;
        }
    }
    if(ranksMatch){
        std::cout<<"PageRank Test Case Passed"<<std::endl;
    }else {
        std::cout<<"PageRank Test Case Failed"<<std::endl;
    }
    videos11.printPageRank(rank1,"pageRankTest");
    //testing constructor of highlyconnected
    /* HighlyConnected cluster("largeIO.txt");
    cluster.clustering(cluster.getGraph());
    cluster.percentSimilar("largeIO_clustering.txt"); */



    //testing clustering with 3 lines
    HighlyConnected cluster_basic("basicIO.txt"); 
    cluster_basic.clustering(cluster_basic.getGraph());
    if (cluster_basic.BFS().size() == 3) {
        cout << "Passed testing basicIO clustering" << endl;
    }
    cluster_basic.percentSimilar("basicIO_clustering.txt");

    //testing clustering with 10 lines
    HighlyConnected cluster_ten("videos_10_lines.txt"); 
    cluster_ten.clustering(cluster_ten.getGraph());
    if (cluster_ten.BFS().size() == 1) {
        cout << "Passed testing 10 lines clustering" << endl;
    }
    cluster_ten.percentSimilar("video_10_lines_clustering.txt");


    /* UndirectedGraph a1("basicIO.txt");
    for(auto i: a1.categories){
        cout<< i.first << " " << i.second << '\n';
    }
 */



    /* Graph videos10(videos_map);
    vector<pair<string,double>> rank = videos10.makePageRank(0.85,0.05);
    videos10.printPageRank(rank);

   */
    return 0;
}
