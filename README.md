# CS225 Final Project (lilys3-hzeng21-sutanto4)

## Table of Contents
0. [Overview](#Overview)
1. [Code Location](#Code-Location)
2. [Tests](#Tests)
3. [Written Reports](#Written-Report )
4. [Data](#Data)
5. [Presentation Video](#Presentation-Video)
6. [Running Instruction](#Running-Instruction)

## Overview

* Our final projet uses data from Youtube, in which each youtube video is a vertex, if one video is related to another, then there is a directed edge between them. 
    
* First off, we read in the data from the Youtube Dataset, construct a directed graph and an undirected graph based on the data. 
    
* In addition, we use BFS Traversal to find the shortest path from video a to video b, HCS clustering to group the clusters of videos based on categories and find out which category has the highest percentage in the clusters, and Pagerank to determind the importance of the videos.

## Code Location

* Data read in is completed in FileIO.cpp, directed graph implementation is completed in graph.cpp, and undirected graph implementation is completed in UndirectedGraph.cpp. 
    
* BFS traversal is completed in graph.cpp, HCS clustering is completed in highlyConnected.cpp and uses UndirectedGraph.cpp, Pagerank is completed in pageRank.cpp and uses graph.cpp.

## Tests
* All test cases are completed in main.cpp. The test results of BFS traversal, HCS clustering, and Pagerank are in BFS.txt, percentSimilarPercentage.txt, and pageRank.txt, accordingly.

## Written Report
* A written report is completed in results.md.

## Data
* The dataset we use on our program is in basicIO.txt, video_10_lines.txt, and largeIO.txt. More datasets can be found on https://netsg.cs.sfu.ca/youtubedata/

## Presentation Video 

* The presentation video is on https://drive.google.com/file/d/15czhjbOaghBDH85h3ha_6FVRYbr7J0bA/view?usp=sharing
* The presentation slide is on https://docs.google.com/presentation/d/1944MeC6bhDm9US4bzo657gtZI2Jbk_jfaWBsM3v9ufo/edit#slide=id.p

## Running Instruction

1. To download the program, copy and paste the following line to your terminal:

```
git clone https://github-dev.cs.illinois.edu/cs225-sp22/lilys3-hzeng21-sutanto4.git
```

2. To build the program, copy and paste the following line to your terminal:
```
make
```

3. To test the program
```
./main
```

Feel free to midify the test cases and to make the program read in your own dataset!


