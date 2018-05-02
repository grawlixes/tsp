#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <algorithm>

#define MAX_DIGITS 5
#define INFINITY 2147483647


int travelling_salesman(int **adj,int n, int start_node, int *min_path){
	int *permutation = new int[n-1];
	int start_found = 0;
	/*get the vertices discluding the start node*/
	for(int i = 0; i < (n-1); ++i){
		if(!start_found && i != start_node){
			permutation[i] = i;
		}else if(start_found){
			permutation[i] = i+1;
		}else if(i == start_node){
			start_found = 1;
			permutation[i] = i+1;
		}
	}
	int best = INFINITY;
	do{
		int current_best = 0;
		int k = start_node;
		for(int i = 0; i < (n-1); i++){
			current_best += adj[k][permutation[i]];
			k = permutation[i];
		}
		current_best += adj[k][start_node];

		if(current_best < best){
			best = current_best;
			for(int i = 0; i < (n-1);++i){
				min_path[i] = permutation[i];
			}
		}
	}while(std::next_permutation(permutation,permutation+(n-1)));
	
	delete [] permutation;
	return best;
}

int main(int argc, char **argv){
	int start_node;
	if(argc == 3){
		start_node = atoi(argv[2]);
	}else{
		std::cout << "invalid arguments." << std::endl;
		std::cout << "./naiveTSP <input file> <starting node>" << std::endl;
		return -1;
	}
	std::ifstream input_file;
	input_file.open(argv[1]);
	if(!input_file){
		perror(argv[1]);
		return -1;
	}
	std::string line;

	int n;
	int **adj = NULL;
	int i = 0;
	while(std::getline(input_file,line)){
		/*make our adjacency matrix if we havent yet*/
		if(!adj){
			/*matrix is nxn, get number of nodes by getting number of spaces +1*/
			n = 1;
			for(int i = 0; i < (int)line.size(); ++i){
				if(line[i] == ' ') n++;
			}
			if (start_node >= n){
				std::cout << "Invalid start node (vertex indexing begins at zero)." << std::endl;
				return -1;
			}
			/*Create the matrix adj*/
			adj = new int*[n];
			for (int i = 0; i < n; ++i)
				adj[i] = new int[n];
		}
		std::istringstream stream(line);
		char num[MAX_DIGITS];
		int j;
		j = 0;
		while(stream.getline(num,MAX_DIGITS,' ')){
			adj[i][j] = atoi(num);
			j++;
		}
		i++;
	}
	input_file.close();
	/*Finally, we have our adjacency matrix*/
	for (int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			std::cout << adj[i][j] << " ";
		}
		std::cout << std::endl;
	}

	int *min_path = new int[n-1];
	
	/*create the timer for the function*/
	clock_t t;
	t = clock();
	int solution = travelling_salesman(adj,n,start_node,min_path);
	t = clock() - t;
	/*measure the running time of the function*/
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	
	std::cout << "Shortest path weight: " << solution << std::endl;

	std::cout << "Vertices: " << start_node << "->";
	for(int i = 0; i < (n-1);++i){
		std::cout << min_path[i] << "->";
	}
	std::cout << start_node << std::endl;

	std::cout << "Running time: " << time_taken << "s" << std::endl;
	
	for (int i = 0; i < n; ++i)
		delete [] adj[i];
	delete [] adj;
	delete [] min_path;
}
