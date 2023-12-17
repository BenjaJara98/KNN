#ifndef KNNIR_H
#define KNNIR_H

#include <utility>
#include <queue>
#include <cmath>

#include "kTree.h"
#include "Count.hpp"
#define K 2

using namespace std;

class knnir{
	public:

		knnir(){}
		~knnir(){}
		vector<pair<int, int>> knn(MREP * rep, int x, int y, uint k, uint radius);
		vector<pair<int, int>> getPointsinRadius(MREP * rep,int x1, int y1, int x2, int y2, int k);

	private:
};

#endif