#include <iostream>
#include <chrono>
#include "libs/knnpq.hpp"
#include "libs/kTree.h"

#define N 100

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

    auto start = chrono::high_resolution_clock::now();
	auto finish = chrono::high_resolution_clock::now();
	long KNNPQTime;

	knnpq knn;
    	
    start = chrono::high_resolution_clock::now();

    for(int i = 0; i<N ; i++){
	    vector<pair<int,int>> points = knn.knn(rep, x, y, k);
    }
    
	finish = chrono::high_resolution_clock::now();

	KNNPQTime = chrono::duration_cast<chrono::microseconds> (finish - start).count();
    KNNPQTime /= N;

	cout << argv[1] << " " << KNNPQTime << endl;

	return 0;
}
