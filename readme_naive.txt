- To compile and run naiveTSP:       
	a. "make"
	b. ./naiveTSP <input file name> (the file can be named as you like)
	c. <input file name> is a well-formed file that contains an adjacency matrix for
	   a complete undirected graph with weight that has exactly one edge between every city
	   (graph doesn't have to be complete but the problem pretty much entails it).
	   Take a look at the example text files if you want to test it without creating anything.
	d. "make clean" if you want to remove all object and binary files

- Data structures used in naiveTSP:
	Most important is the adjacency list used to represent the cities and the distances
	between them. Since we are considering the problem set as a dense graph, it makes sense
	to use an adjacency matrix, which has constant Theta(1) access for the value of the weight
	of an edge between any two points. The matrix is symmetrical across its diagonal since the
	graph is undirected; space could be saved by only representing half of it, but we didn't think
	of this until after. Aside from this matrix, we use an array to keep track of the best permutations
	and the clock_t structure for timing the program.

- Discussion of time and space complexity in naiveTSP:
	This algorithm's simplicity comes at the price of efficiency and time consumption. The
	algorithm runs at Theta((n-1)!), since every permutation must be visited from the start
	node. Not only that, but there is no work put into shaving off time in this naive algorithm,
	which is why it is tightly bound by (n-1)!. Since the algorithm has to calculate so many
	different permutations and it puts no effort into being efficient, it runs on Theta((n-1)!)
	The algorithm's space complexity is good in that it only needs significant space to hold 
	the adjacency matrix, the solution, and the current permutation (though this is still
	O(n^2), which is not great).
	
- Classes used in bnbTSP:
	N/A
