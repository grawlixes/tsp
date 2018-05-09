#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <algorithm>

#define MAX_DIGITS 5
#define INFINITY 2147483647

/*best is the total weight of the shortest tour found*/
int best = INFINITY;

/*first_min finds the minimum edge cost adjacent to vertex i
 * i is the vertex we want the minumum edge from
 * n is the number of cites
 * adj is the adjacency matrix of the graph of cities
 */
int first_min(int **adj, int i, int n){
	int min = INFINITY;
	for(int j = 0; j < n; ++j){
		if(adj[i][j] < min && i != j){
			min = adj[i][j];
		}
	}
	return min;
}

/*second_min finds the second minimum edge cost adjacent to vertex i
 * i is the vertex we want the minumum edge from
 * n is the number of cites
 * adj is the adjacency matrix of the graph of cities
 */
int second_min(int **adj, int i, int n){
	int first = INFINITY;
	int second = INFINITY;
	for(int j = 0; j < n; ++j){
		if(i == j){
			continue;
		}
		if(adj[i][j] <= first){
			second = first;
			first = adj[i][j];
		}else if(adj[i][j] <= second && adj[i][j] != first){
			second = adj[i][j];
		}
	}
	return second;
}

/*Recursive function that prunes the state-space tree of city choices
 * adj is the adjacency matrix of the graph of cities
 * current_bound is the current lower bound for the shortest path possible
 * current_weight is the current distance travelled on the tour so far
 * level is the current level in the state-space tree
 * current_path is the current path of vertices we have travelled to so far
 * min_path is the current minimum path of cities
 * visited keeps track of already visited nodes in a particular path
 * n is the number of cities
 */
void tsp_recursive(int **adj,int current_bound, int current_weight, int level, int *current_path, int *min_path, bool *visited, int n){

	/*in the base case, we are at the bottom of the state-space tree*/
	if (level == n){
			/*calculate the total weight of the solution we've reached*/
			int current_best = current_weight + adj[current_path[level-1]][current_path[0]];

			/*Update the best weight and path if it is not as good as the current best we just found*/
			if(current_best < best){
				for(int i = 0; i < n;++i){
					min_path[i] = current_path[i];
				}
				min_path[n] = current_path[0];
				best = current_best;
			}
		return;
	}

	/*for levels other than the bottom one, iterate through all vertices and recursively build the state-space tree*/
	for(int i= 0; i < n; ++i){
		if(adj[current_path[level-1]][i] != 0 && visited[i] == false){

			int temp = current_bound;
			current_weight += adj[current_path[level-1]][i];

			/*computation for level 2 of the state-space tree is different from others*/
			if(level == 1){
				current_bound -= ((first_min(adj, current_path[level-1],n) + first_min(adj, i,n))/2);
			}else{
				current_bound -= ((second_min(adj, current_path[level-1],n) + first_min(adj, i,n))/2);
			}

			/*current_bound + current_weight is the bound based on the city we chose to travel to*/
			/*if the bound is better than the best weight we have so far, continue traversing the state-space tree*/
			if(current_bound + current_weight < best){
				current_path[level] = i;
				visited[i] = true;

				tsp_recursive(adj,current_bound,current_weight,level+1,current_path,min_path,visited,n);
			}

			/*if not, we prune the node and reset the current weight, bound, and visited array*/
			current_weight -= adj[current_path[level-1]][i];
			current_bound = temp;

			memset(visited,false,sizeof(bool)*n);
			for(int j =0;j <= level-1; ++j){
				visited[current_path[j]] = true;
			}
		}
	}
}

/*This function sets up the minimum path
 * adj is the adjacency matrix of the graph of cities
 * n is the total number of cities
 * min_path is the current minimum path of cities
 */
void travelling_salesman(int **adj,int n, int *min_path){
	/*current_path will keep track of the current path of vertices we have travelled to so far*/
	/*visited keeps track of already visited nodes in a particular path*/
	/*current_bound is the current lower bound for the shortest path possible*/
	int *current_path = new int[n+1];
	bool *visited = new bool[n];
	int current_bound = 0;
	memset(current_path,-1,(n+1)*sizeof(int));
	memset(visited,false,sizeof(bool)*n);
	/*compute the lower bound by looping through each vertex and finding its two minimum edges*/
	for(int i=0;i < n; ++i){
		current_bound += (first_min(adj,i,n) + second_min(adj,i,n));
	}

	/*round lower bound to an integer*/
	current_bound = (current_bound&1)? current_bound/2+1 : current_bound/2;

	/*We begin at vertex 1, so the first vertex in  the current path is 0*/
	visited[0] = true;
	current_path[0] = 0;

	/*call the recursive function with no current weight and level 1*/
	tsp_recursive(adj, current_bound,0,1,current_path,min_path,visited,n);

	delete [] current_path;
	delete [] visited;
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

	int *min_path = new int[n+1];
	
	/*create the timer for the function*/
	clock_t t;
	t = clock();
	//travelling_salesman(adj,n,start_node,min_path);
	travelling_salesman(adj,n,min_path);
	t = clock() - t;
	/*measure the running time of the function*/
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	
	std::cout << "Shortest path weight: " << best << std::endl;

	std::cout << "Vertices: ";
	for(int i = 0; i < (n+1);++i){
		if(i < n) std::cout << min_path[i] << "->";
		else std::cout << min_path[i];
	}
	std::cout << std::endl;

	std::cout << "Running time: " << time_taken << "s" << std::endl;
	
	for (int i = 0; i < n; ++i)
		delete [] adj[i];
	delete [] adj;
	delete [] min_path;
}
