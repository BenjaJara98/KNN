#include "knnirBeta.hpp"
#include "knnir.hpp"
#include "basic.h"
#include "kTree.h"
#include <unistd.h>
#include "bitrankw32int.h"
#include "Count.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> knnirNew::knn(MREP *rep, Point q, int k) {
    vector<pair<int, int>> C;

    double epsilon = 0.0;
    int m = 1;

    while (k > 4 * (m * m + m)) {
        m++;
    }

    epsilon = static_cast<double>(m);
    double a = std::sqrt(2);

    double radio = epsilon * a;
    double r = std::ceil(radio);
    // cout << "Nuestro primer radio:" << r << endl;

    Count countFunction;

    while ((countFunction.compactCount(rep, q.x - r, q.x + r, q.y - r, q.y + r)) < k) {
        double radioNuevo = r * 2;
        cout << "Radio aumentado en 2" <<endl;
        r = std::ceil(radioNuevo);
    }

    // Ajuste final del radio
    double radioFinal = r * a;
    r = std::ceil(radioFinal);

    // Establecer coordenadas finales
    double minX = std::max(0.0, q.x - r);
    double maxX = q.x + r;
    double minY = std::max(0.0, q.y - r);
    double maxY = q.y + r;

    // cout << "Radio final:" << r << endl;
    // cout << "X Max:" << maxX << endl;
    // cout << "X Min:" << minX << endl;
    // cout << "Y Max:" << maxY << endl;
    // cout << "Y Min:" << minY << endl;

    uint p1 = minX;
    uint p2 = maxX;
    uint q1 = minY;
    uint q2 = maxY;

    uint **rangeResult = compactRangeQuery(rep, p1, p2, q1, q2);

    uint totalPoints = rangeResult[0][0];
    vector<pair<int, int>> rangePoints;

    for (uint i = 1; i <= totalPoints; ++i) {
        int x = rangeResult[0][i];
        int y = rangeResult[1][i];
        rangePoints.push_back(make_pair(y, x));
    }

    // Calcular la distancia y ordenar los puntos
    sort(rangePoints.begin(), rangePoints.end(), [q](const pair<int, int> &point1, const pair<int, int> &point2) {
        Point p1 = {static_cast<double>(point1.first), static_cast<double>(point1.second)};
        Point p2 = {static_cast<double>(point2.first), static_cast<double>(point2.second)};
        return calculateDistance(p1, q) < calculateDistance(p2, q);
    });

    // Limitar el número de puntos devueltos según el parámetro k
    if (rangePoints.size() > static_cast<size_t>(k)) {
        rangePoints.resize(k);
    }

    // Imprimir los puntos ordenados por distancia
    for (const auto &point : rangePoints) {
        int x = point.first;
        int y = point.second;
        double distancia = calculateDistance(Point{static_cast<double>(x), static_cast<double>(y)}, q);
        // cout << "Punto: (" << x << ", " << y << ") Distancia: " << distancia << endl;
    }

    return rangePoints;
}

vector<pair<int, int>> knnirNew::getPointsinRadio(MREP *rep, int x1, int y1, int x2, int y2, int k, Point q) {
    // Realizar la consulta de rango en el K2-tree
    uint p1 = x1;
    uint p2 = x2;
    uint q1 = y1;
    uint q2 = y2;

    uint **rangeResult = compactRangeQuery(rep, p1, p2, q1, q2);

    // Obtener la información de los puntos encontrados
    uint totalPoints = rangeResult[0][0];
    vector<pair<int, int>> rangePoints;

    for (uint i = 1; i <= totalPoints; ++i) {
        int x = rangeResult[0][i];
        int y = rangeResult[1][i];
        rangePoints.push_back(make_pair(y, x));
    }

    // Calcular la distancia entre el punto encontrado y q (usando alguna fórmula)
    sort(rangePoints.begin(), rangePoints.end(), [q](const pair<int, int> &point1, const pair<int, int> &point2) {
        Point p1 = {static_cast<double>(point1.first), static_cast<double>(point1.second)};
        Point p2 = {static_cast<double>(point2.first), static_cast<double>(point2.second)};
        return calculateDistance(p1, q) < calculateDistance(p2, q);
    });

    // Limitar el número de puntos devueltos según el parámetro k
    if (rangePoints.size() > static_cast<size_t>(k)) {
        rangePoints.resize(k);
    }

    return rangePoints;
}

double calculateDistance(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}