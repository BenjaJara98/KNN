#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <cmath>
using namespace std;

int main() {
    // Distribución uniforme
    // Inicializar la semilla del generador de números aleatorios
    srand(time(0));

    // Rango para las coordenadas X e Y
    
    int rangoTotal = pow(2, 16);
    cout << "Rango total: "<< rangoTotal << endl;

    int minX = 0;
    int maxX = rangoTotal-1;
    int minY = 0;
    int maxY = rangoTotal-1;

    // Número de coordenadas que quieres generar
    const int nPuntos = 5;
    const int totalPuntos = (rangoTotal*rangoTotal)*5;
    const int numCoordenadas = (totalPuntos)/100;
    cout << "Total de coordenadas: "<< numCoordenadas << endl;


    // Conjunto para almacenar coordenadas únicas
    set<pair<int, int>> coordenadasUnicas;

    // Generar coordenadas aleatorias únicas
    while (coordenadasUnicas.size() < numCoordenadas) {
        int coordenadaX = rand() % (maxX - minX + 1) + minX;
        int coordenadaY = rand() % (maxY - minY + 1) + minY;
        coordenadasUnicas.insert({coordenadaX, coordenadaY});
    }

    // Abrir un archivo para escritura
    ofstream archivo("pruebaUniforme9.txt");

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Guardar las coordenadas en el archivo
    for (const auto& coordenada : coordenadasUnicas) {
        archivo << coordenada.first << " " << coordenada.second << endl;
    }

    // Cerrar el archivo
    archivo.close();

    cout << "Coordenadas guardadas en coordenadas.txt." << endl;

    return 0;
}