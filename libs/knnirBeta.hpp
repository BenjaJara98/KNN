#ifndef KNN_IR_HPP
#define KNN_IR_HPP

#include <utility>
#include <queue>
#include <cmath>

// Definición de la estructura Point para representar puntos en 2D
struct Point {
    double x;
    double y;
};

#include "knnir.hpp"
#include "kTree.h"
#include "Count.hpp"
// #define K 2

using namespace std;

// Función para calcular la distancia euclidiana entre dos puntos
double calculateDistance(Point p1, Point p2);


class knnirNew {
public:

    knnirNew() {}
    ~knnirNew() {}
    vector<pair<int, int>> knn(MREP * rep, Point q, int k);
    vector<pair<int, int>> getPointsinRadio(MREP *rep, int x1, int y1, int x2, int y2, int k, Point q);

private:
};


#endif
