#include "FileIO.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <map>
#include <vector>
namespace FileIO{

  std::map<std::string, std::vector<std::string>>readFromFile(std::string file){
      
      std::map<std::string, std::vector<std::string>> videos_;
      std::vector<std::string> videoInfo_;
      std::string line;
      std::string key;

      std::string word;

      std::ifstream fileIn(file);

      if(fileIn.is_open()){
          //get a line from the file
          while(getline(fileIn, line)){

            int i = 0;

            std::istringstream f(line);

            while(f>>word){
                if(i == 0){
                    //video ID
                    videoInfo_.clear();
                    videos_[word] = videoInfo_;
                    key = word;

                }else{
                    //video info
                    if(word == "&"){
                        f>>word>>word;
                    }
                    videos_[key].push_back(word);   
                }
                i++;
            }
          }
      }else{
          std::cout<<"file not found"<<std::endl;
      }
      return videos_;
  }





}