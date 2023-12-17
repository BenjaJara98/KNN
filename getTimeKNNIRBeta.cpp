#include <iostream>
#include <chrono>
#include "libs/knnirBeta.hpp"
#include "libs/kTree.h"

#define N 100

using namespace std;

int main(int argc, char * argv[]){

	if(argc < 5){
		printf("%s <PATH> <X_1> <Y_1> <K>\n", argv[0]);
		return -1;
	}

	MREP *rep = loadRepresentation(argv[1]);

    Point q;
	q.x = std::stod(argv[2]);
    q.y = std::stod(argv[3]);
	int k = atoi(argv[4]);

	auto start = chrono::high_resolution_clock::now();
	auto finish = chrono::high_resolution_clock::now();
	long KNNIRTime;

	knnirNew knn;


	start = chrono::high_resolution_clock::now();
    for(int i = 0; i<N ; i++){
	    vector<pair<int,int>> points = knn.knn(rep, q, k);
    }
	finish = chrono::high_resolution_clock::now();

	KNNIRTime = chrono::duration_cast<chrono::microseconds> (finish - start).count();
    KNNIRTime /= N;

	cout << argv[1] << " " << KNNIRTime << endl;

	return 0;
}
