# lilys3-hzeng21-sutanto4

# Final Project Proposal (Due March 25th)

## Leading Question 

We are hoping to learn more about the Youtube algorithm. We can learn from the dataset about how to jump from Video A to Video B with the least amount of video jumps using Modified BFS; and in addition, we could determine whether there are patterns in the video categories or other aspects of the video after clustering the data using the Highly Connected Subgraph clustering algorithm. We would like to know whether there are relationships between highly related videos. We would also like to know which videos are of a higher importance than others using the Page Rank algorithm.

## Dataset Acquisition and Processing 


### Data format

The dataset source comes from YouTube, where each video is a node in the graph. If video b is related to a, then there is a directed edge from a to b. The dataset roughly contains 750,000 videos, that comes from about 15 subsets, where each subset contains videos from one specific day. The input format of the dataset is CSV. We plan to use one or two subsets that include 50,000 videos.  

### Data Correction

We will parse the data in as a map, where the video ID will be the key and the value will be a list of categories and related IDs. We will implement methods to print out the map and compare it with the original dataset to ensure we parse in the correct data.

One column of data has one video, one category of the video and 20 related videos. When we parse the data, if the data length is less than 20, then this column of data is incorrect or is missing some key data, we should discard it.

### Data Storage

We will store the data as an adjacency list where each video is stored as a node and a list of pointers to other nodes. We expect our data to be sparsely connected. We expect the total storage costs to be O(n). During the processing of the table, we will also be using a map in order to filter out the videos that we will not be including due to it not being in our dataset. 

## Graph Algorithms and Time Efficiency

To tackle the question of how to go from video A to B with the least amount of video jumps, we would use a Modified Breadth First Search Algorithm. The time complexity of the Modified BFS Algorithm on an Adjacency List is O(E+V) with E being the number of edges and V being the number of Vertices. We chose this algorithm because it is the most efficient for the unweighted nature of our graph. 

Furthermore, to tackle the target of learning more about how Youtube recommends its videos we are going to first use Highly Connected Subgraph(HCS) Clustering to find subgraphs that are highly correlated, a characteristic that (in this case) indicates Youtube recommending similar videos in this group of videos. HCS Clustering runs wi

The running time of the HCS clustering algorithm is bounded by O(N × f(n, m)). f(n, m) is the time complexity of computing a minimum cut in a graph with n vertices and m edges, and N is the number of clusters found. 

After that, to analyze the correlation of videos in these subgraphs, we would do subgraph traversal using Breadth First Traversal, and while traversing we will take note of a few video characteristics and print out the similarity statistics of each subgraph. The time complexity of each BFT is O(v) where v is the number of vertices.

To determine how important a video is, we would use the Page Rank algorithm. The time complexity is O(K * N) where K is the number of iterations.

### Function Inputs 

The expected inputs for our algorithm will be videos and their related information. We delete data that does not have enough information(for example, a standard data should have 20 related videos, if the data has less than 20 related videos, we will discard it). In addition, we convert the dataset to a map, where the key is the video ID and the value is a list containing the video information(i.e. Categories, age, etc). After that, we implement the graph using an adjacency list based on the map. The input to the BFS are the two video IDS that we are trying to find the shortest path for. The input to HCS clustering would be the file which contains the data that we want to cluster. The input for Page Rank would be the already implemented graph. 

### Function Outputs 

For the function that uses Modified Breadth First Search, we expect the shortest path as a vector of video IDs. For the function that uses the Highly Connected Subgraph Clustering algorithm, we expect a graph with the separated subgraphs as the output. For the function that uses the BFS Traversal, we expect our data analysis as the output. For the function that uses the Page Rank algorithm, we expect to have an output file with the rankings and the video details.


## Timeline 

As a team, identify a list of tasks such as data acquisition, data processing, completion of each individual algorithm, production of final deliverables, etc… and write a proposed timeline for the completion of these tasks. You are not required to adhere strictly to this timeline but it should represent a reasonable set of benchmarks to strive for. For example, stating that you will finish all graph algorithms over the span of a single week is not reasonable. At least one proposed task must be completed before the mid-project checkin – part of the mid-project grade will be based on whether or not this target goal was met.


* April 1th : Data acquisition and data processing
* April 8th : Graph implementation
* April 15th : Finished Modified Breadth-First Search code as well as testing (mid-project) 
* April 22st : Start implementing Page Rank and HCS Clustering
* April 29th : Finish Page Rank and HCS Clustering
* May 6th: Finish analyzing data, report, and presentation video.

### Signatures
Lily Sheng (lilys3), Hongkun Zeng(hzeng21),Michael Sutanto(sutanto4)
