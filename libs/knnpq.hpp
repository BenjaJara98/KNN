#ifndef KNNPQ_H
#define KNNPQ_H

#include <utility>
#include <queue>
#include <cmath>

#include "iostream"

#include "kTree.h"
#define K 2

using namespace std;

struct knnpqElement;
class Quadrant;

class knnpq
{
public:

	knnpq() {}
	~knnpq() {}
	int64_t minDist(pair<int, int> point, Quadrant quadrant);
	vector<knnpqElement> getChildrenOfElement(knnpqElement element, pair<int, int> point, uint max_level, bitRankW32Int *btl); // Returns the K^2 childrens of element
	vector<pair<int, int>> knn(MREP *rep, int x, int y, int k);


private:
};

#endif