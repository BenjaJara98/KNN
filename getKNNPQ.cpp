#include <iostream>

#include "libs/knnpq.hpp"
#include "libs/kTree.h"

using namespace std;

int main(int argc, char * argv[]){

	if(argc < 5){
		printf("%s <PATH> <X_1> <Y_1> <K>\n", argv[0]);
		return -1;
	}

	MREP *rep = loadRepresentation(argv[1]);
	int x = atoi(argv[2]);
	int y = atoi(argv[3]);
	int k = atoi(argv[4]);

	knnpq knn;
	vector<pair<int,int>> points = knn.knn(rep, x, y, k);
	
	for(pair<int,int> point : points){
		cout << "(" << point.first << "," << point.second << ")\n";
	}

	return 0;
}
