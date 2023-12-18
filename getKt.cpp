#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

struct Punto {
    double x;
    double y;
    double distancia; // Agregamos un campo para almacenar la distancia
};

bool compararPorDistancia(const Punto& a, const Punto& b) {
    return a.distancia < b.distancia;
}

int main() {
    std::ifstream archivo("test1_prueba.txt");

    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    double x2 = 1.0; // Coordenada x del punto (1,1)
    double y2 = 1.0; // Coordenada y del punto (1,1)

    std::vector<Punto> puntos;

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        Punto punto;
        if (iss >> punto.x >> punto.y) {
            punto.distancia = std::sqrt(std::pow(punto.x - x2, 2) + std::pow(punto.y - y2, 2));
            puntos.push_back(punto);
        } else {
            std::cout << "Error al leer las coordenadas en la línea: " << linea << std::endl;
        }
    }

    archivo.close();

    // Ordenar los puntos por distancia
    std::sort(puntos.begin(), puntos.end(), compararPorDistancia);

    // Imprimir los puntos ordenados
    for (const Punto& punto : puntos) {
        std::cout << "Punto: (" << punto.x << "," << punto.y << ") y distancia " << punto.distancia << std::endl;
    }

    return 0;
}