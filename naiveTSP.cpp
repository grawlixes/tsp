#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <algorithm>

#define MAX_DIGITS 5
#define INFINITY 2147483647


int travelling_salesman(int **adj,int n, int *min_path){
	int *permutation = new int[n-1];
	/*get the vertices excluding the start node*/
	for(int i = 0; i < (n-1); ++i){
		permutation[i] = i+1;
	}
	int best = INFINITY;
	do{
		int current_best = 0;
		int k = 0;
		for(int i = 0; i < (n-1); i++){
			current_best += adj[k][permutation[i]];
			k = permutation[i];
		}
		current_best += adj[k][0];

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
	int solution = travelling_salesman(adj,n,min_path);
	t = clock() - t;
	/*measure the running time of the function*/
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	
	std::cout << "Shortest path weight: " << solution << std::endl;

	std::cout << "Vertices: " << 0 << "->";
	for(int i = 0; i < (n-1);++i){
		std::cout << min_path[i] << "->";
	}
	std::cout << 0 << std::endl;

	std::cout << "Running time: " << time_taken << "s" << std::endl;
	
	for (int i = 0; i < n; ++i)
		delete [] adj[i];
	delete [] adj;
	delete [] min_path;
}
