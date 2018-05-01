#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define MAX_DIGITS 5

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
	for (int i = 0; i < n; ++i)
		delete [] adj[i];
	delete [] adj;
}
