/**
 * Private:
 * - totalPages
 * - decayFactor
 *
 * On each vertex
 * - currentRank
 * - newRank
 * 
 * Helper Functions:
 * - checkConvergence
 * - initPageRank
 * - updatePageRank
 * 
 * Main Function:
 * - makePageRank
 * - printPageRank
 *    
 **/


#include "graph.h"
#include <queue>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void Graph::initPageRank(double _decayFactor, double _epsilon){
    decayFactor = _decayFactor;
    epsilon = _epsilon;
    map<string, videoInfo>::iterator it;
    for (it = adjLists.begin(); it != adjLists.end(); ++it){
      videoInfo & info = it->second;
      info.currentRank = 1/double(numVertices);
      info.newRank = 0;
    }
}

void Graph::updatePageRank(){
    map<string, videoInfo>::iterator it;
    for (it = adjLists.begin(); it != adjLists.end(); ++it){
      videoInfo & info = it->second;
      info.newRank = 0;
    }

    for (it = adjLists.begin(); it != adjLists.end(); ++it){
      videoInfo & info = it->second;
      vector<string> relatedVids = info.related_IDs;
      int uniqueLinks = relatedVids.size();

      for(size_t i = 0; i<relatedVids.size() ; i++){
        if(adjLists.find(relatedVids[i])==adjLists.end())continue;
         videoInfo & neighborInfo = adjLists[relatedVids[i]];
         double addition; 
         if(uniqueLinks == 0){
             addition = double(decayFactor) * (info.currentRank / double(numVertices));
            neighborInfo.newRank += addition;
        }else{
            addition = double(decayFactor) * (info.currentRank / double(uniqueLinks));
            neighborInfo.newRank += addition;
        }
      }
    }
    for (it = adjLists.begin(); it != adjLists.end(); ++it){
      videoInfo & info = it->second;
      info.newRank += double(1-decayFactor)/double(numVertices);
    }
}

bool Graph::checkConvergence(){
    map<string, videoInfo>::iterator it;
    bool converged = true;
    for (it = adjLists.begin(); it != adjLists.end(); ++it){
      videoInfo & info = it->second;
      double diff = info.currentRank - info.newRank;
      if(diff<0) diff = -diff;
      if(diff >= epsilon){
          converged = false;
          break;
      }
    }
    if(converged) return true;
    else{
        for (it = adjLists.begin(); it != adjLists.end(); ++it){
            videoInfo & info = it->second;
            info.currentRank = info.newRank;
        }
        return false;
    }
}



vector<pair<string,double>> Graph::makePageRank(double _decayFactor, double _epsilon){
    std::cout<<"PageRank"<<std::endl;
    initPageRank(_decayFactor,_epsilon);
    int cnt = 0;
    do{
         updatePageRank();
    }
    while(!checkConvergence());
    vector<pair<string,double>> result;

    map<string, videoInfo>::iterator it;
    for (it = adjLists.begin(); it != adjLists.end(); ++it){
      string key = it->first;
      videoInfo info = it->second;
      result.push_back(std::make_pair(key,info.currentRank));
    }

    std::sort(result.begin(), result.end(), [] (const auto &x, const auto &y) { return x.second > y.second; });

    return result;
}

void Graph::printPageRank(vector<pair<string, double>> pageRank, string outputFileName){
    ofstream pageRankDetails;
    pageRankDetails.open (outputFileName.append(".txt"));
    for(size_t i = 0; i<pageRank.size();i++){
        videoInfo info = adjLists[pageRank[i].first];
        pageRankDetails << "Rank "<<i<<" "<<pageRank[i].first<<"|| PageRank Score: "<<pageRank[i].second<<"|| Category: "<<info.category<<"|| Length: "<<info.length<<"|| Views: "<<info.views<<"|| Ratings: "<<info.ratings<<"|| Rate: "<<info.rate<<"|| Comments: "<<info.comments<<std::endl;
    }
    pageRankDetails.close();
}

