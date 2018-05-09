- To compile and run bnbTSP:       
	a. "make"
	b. ./bnbTSP <input file name> (the file can be named as you like)
	c. <input file name> is a well-formed file that contains an adjacency matrix for
	   a complete undirected graph with weight that has exactly one edge between every city
	   (graph doesn't have to be complete but the problem pretty much entails it).
	   Take a look at the example text files if you want to test it without creating anything.
	d. "make clean" if you want to remove all object and binary files

- Data structures used in bnbTSP:
	Again, we use an adjacency matrix to represent our dataset since it's the same as it was
	in the naive solution. We also use current_path and visited, which are arrays of integers
	and booleans respectively; these do exactly what their names entail, and they help us in
	our more sophisticated branch-and-bound solution. We also use another int array, min_path,
	which we compare each permutation possibility to determine whether it's worth investigating or not.
	

- Discussion of time and space complexity in bnbTSP:
	Unfortunately, we haven't improved upon the worst case time complexity of the TSP; this algorithm
	runs on the order of (n-1)! in the worst case, just like the naive solution. However, we can (and
	often do) save time by avoiding unnecessary work in the branch and bound solution. We keep a bound
	on each of the "nodes" in our branch and bound, and if the current weight of any "node" is greater
	than that bound, we don't bother to search through it. In our demo example, the branch and bound
	solution solved in less than 2 seconds what the naive solution couldn't even solve in 45 seconds!
	Though the upper bound is unchanged from the naive solution, this solution is far better in
	the average and best case. Since the worst case is rare, it is worth implementing.
	
- Classes used in bnbTSP:
	N/A
