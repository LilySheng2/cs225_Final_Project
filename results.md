# Final Report
Leading Question: We hope to learn more about the Youtube algorithm by examining the videos and the related videos that are recommended by the algorithm. Are there any patterns to the algorithm?

## Outputs and Corrrectness
### BFS Traversal and Shortest Path

This algorithm uses BFS Traversal to find the shortest path from a source video a to a targeted video b.
It uses a queue to maintain the queue of vertices to be searched. In addition, it uses a prev vector to keep track of the last video that is related to the current video. When the targeted video b is found, we traverse back from it through the prev vector and push the videos to a res vector. We reverse the res vector eventually and return it.

The result is outputted in BFS.txt.

The testing for BFS to find shortest path is done by using two random video IDs in largeIO.txt as the source and destination videos. If we trace the solution printed out in BFS.txt, that is indeed the shortest path to travel from video a to video b.

### Highly Connected Subgraphs Clustering
The algorithm uses Karger's algorithm for finding the minimum cut and then cuts the graph into smaller subgraphs based on the minimum cut edges found. 
The subgraphs are then recursively cut into smaller and smaller subgraphs until there are no edge cuts and the subgraph is highly connected. 

Clustering is mainly done in the function clustering which does not output anything but edits the private variable graph. 
This private variable saves the graph that has the edges removed, the subgraphs, for access when analyzing is done on the clustering.

Analyzing is done using the function percentSimilar which goes through each subgraph. For each subgraph, the function finds the highest category percentage and the second highest category percentage. 
The results are outputted in a file as indicated by the passed in filename parameter. 

The final results after running the largeIO.txt are saved in largeIO_clustering.txt. Each line is a subgraph and the data for that subgraph as described before. 

The testing for HCS is done by using basicIO.txt and video_10_lines.txt. The first test uses basicIO.txt which has three videos that are not connected. 
Since they are not connected, HCS will cluster the three videos into three different clusters. 
If we check the number of subgraphs, there are indeed three subgraphs. The outputed file, basicIO_clustering.txt, also has three lines. 

The second test uses videos_10_lines.txt which is highly connected. If we look at each of videoIDS in the list, we see that it exists as a related video in several other videos.
Thus, we expect the result to be only one cluster. If we check the number of subgraphs, there is indeed only one subgraph. 
The outputted file, video_10_lines_clustering.txt, also only has one line. 

### Page Rank
PageRank is the algorithm used by Google Search to rank pages by order of importance. It counts the number and quality of links leading to a page to estimate how important the page is. In our case videos are our pages. We used this graph algorithm to find which youtube videos are “most important”, thus giving us further insight to Youtube’s recommendation algorithm.
The PageRank algorithm uses an 3-Step iterative approach that consists of:
1) Initialize Step:
   a) Initialize rank of each page to 1/N (N = Number of total pages/vertices) 
2) Update Step:
   a)Give each page a new page rank of 0 
   b)For each page, use its old rank and add (page old rank/total number of neighbors) to each neighbors' new rank.
3) Convergence Check Step:
   a)Check if the difference between old rank and new is  less than a user defined value(epsilon). 
   b)If it is not, the old rank is replaced with the new rank and the algorithm does another iteration.
After converging, we return an array that is sorted in order of ranking and print out the details of each video to a file(pageRankLargeIo.txt) in rank descending order.

The final results after running PageRank on largeIO.txt are saved in pageRank.txt. And from seeing this file there are a few trends that we caught from the ranking. The most obvious of these trends is that videos with the categories Sports and Comedy are ranked significantly higher than videos from any other category, thus showing that Youtube Recommendation Algorithm biases on certain categories. Another thing that we observed is that videos that are outliers of the category trend, e.g. an Entertainment category video placed in the top 15 which is greatly dominated Sports and Comedy, usually have a significantly greater video duration and high ratings. 

For testing this algorithm, we used a 5 vertice graph with relatively complex connections(Source File pageRankTestIo.txt), and manually calculated the supposed outputted rank of the algorithm(Figure below). We then inputted this graph into our pageRank algorithm and compared the output to the correct ranks. The rankings did match with the supposed rankings.(Can be checked on the output file pageRankTest.txt)
![image](https://media.github-dev.cs.illinois.edu/user/10070/files/d0757192-5e9e-4c97-b81e-692c2a777e1a)

In terms of design decisions and possible optimizations, if we used adjacency matrices to represent the graph, we could use a markov matrice and matrix multiplication approach to derive the page rank which using matrix multiplication optimizations, will lead to a faster runtime. However, we had to compromise on this implementation due to our datasets' graphs being sparse and thus making adjacency lists the space-saving choice.


## Final Conclusion : Answer to Our Leading Question


### BFS Traversal and Shortest Path
When examining the outputted file BFS.txt, we can figure out the number of minimum clicks on the recommended videos we need to reach video b from video a. All the videos in the dataset are published on that day, however, their related videos might be videos that are published previously. Most of the time there is no path between two random videos we selected, which means that Youtube is more likely to recommend videos published previously than videos published on that day. 

### Highly Connected Subgraphs Clustering
When examining the outputted file, largeIO_clustering, we can see that all of the first categories are the unknowns. The unknowns are the videos not in that day's data. This tells us that Youtube is more likely to recommend videos published previously than videos published on that day. 

### Page Rank
Youtube definitely prioritizes  some categories in their recommendation(e.g. Sports and Comedy), which we could see due to videos having certain tags being ranked very high in the page rank.
