#ifndef COUNT_H
#define COUNT_H

#include <utility>
#include <queue>
#include <cmath>

#include "kTree.h"
#define K 2

using namespace std;

class Count{
	public:
		Count(){}
		~Count(){}
		int rangeCount(MREP * rep, int x1, int x2, int y1, int y2);
		int compactCount(MREP * rep, int x1, int x2, int y1, int y2);
		int countMatrix(MREP * rep, int i);
	private:
		
};

#endif