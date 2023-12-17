#include <iostream>

#include "libs/knnirBeta.hpp"
#include "libs/kTree.h"

using namespace std;

int main(int argc, char * argv[]) {
    // Supongamos que tienes una instancia MREP *rep y un punto de consulta Point puntoConsulta
    // cout << "PRUEBA 1" << endl;
    MREP *rep = loadRepresentation(argv[1]); // Inicializa tu instancia de MREP
	
	Point q;
	q.x = std::stod(argv[2]);
    q.y = std::stod(argv[3]);
	int k = atoi(argv[4]);  // Puedes cambiar las coordenadas según tus necesidades

    // cout << "PRUEBA2" << endl;
    // int k = 4;  // Número de puntos más cercanos que deseas encontrar

    vector<pair<int, int>> resultadoPuntos;
    vector<double> distancias;
    
    // cout << "Antes de llamar a knn.knn" << endl;
	knnirNew knn;
    // Llama a la función knn con la instancia rep, el punto de consulta, el valor de k y los vectores para los resultados
    resultadoPuntos = knn.knn(rep, q, k);

    // Imprime los resultados
    cout << "Puntos más cercanos a (" << q.x << ", " << q.y << "):" << endl;
    // for (int i = 0; i < resultadoPuntos.size(); i++) {
    //     cout << "Punto: (" << resultadoPuntos[i].first << ", " << resultadoPuntos[i].second << ") ";
    //     cout << "Distancia: " << distancias[i] << endl;
    // }
    for(pair<int,int> point : resultadoPuntos){
		cout << "(" << point.first << "," << point.second << ")\n";
	}

    return 0;
}