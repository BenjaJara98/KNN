#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <cmath>

using namespace std;

// Función para generar números aleatorios con distribución normal (aproximación simple)
double randn(double mean, double stddev) {
    static bool hasSpare = false;
    static double spare;

    if (hasSpare) {
        hasSpare = false;
        return mean + stddev * spare;
    }

    hasSpare = true;
    static double u, v, s;
    do {
        u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        s = u * u + v * v;
    } while (s >= 1.0 || s == 0.0);

    s = sqrt(-2.0 * log(s) / s);
    spare = v * s;
    return mean + stddev * u * s;
}

int main() {
    // Inicializar la semilla del generador de números aleatorios
    srand(time(0));

    // Rango para las coordenadas X e Y
    int rangoTotal = pow(2, 14);
    cout << "Rango total: " << rangoTotal << endl;

    int minX = 0;
    int maxX = rangoTotal - 1;
    int minY = 0;
    int maxY = rangoTotal - 1;

    // Número de coordenadas que quieres generar
    const int nPuntos = 5;
    const int totalPuntos = (rangoTotal * rangoTotal) * 1;
    const int numCoordenadas = (totalPuntos);
    cout << "Total de coordenadas: " << numCoordenadas << endl;

    // Conjunto para almacenar coordenadas únicas
    set<pair<int, int>> coordenadasUnicas;

    // Generar coordenadas aleatorias únicas con distribución gaussiana
    while (coordenadasUnicas.size() < numCoordenadas) {
        int coordenadaX = static_cast<int>(randn((minX + maxX) / 2.0, (maxX - minX) / 4.0));
        int coordenadaY = static_cast<int>(randn((minY + maxY) / 2.0, (maxY - minY) / 4.0));

        // Asegurarse de que las coordenadas estén dentro del rango
        coordenadaX = max(minX, min(maxX, coordenadaX));
        coordenadaY = max(minY, min(maxY, coordenadaY));

        coordenadasUnicas.insert({coordenadaX, coordenadaY});
    }

    // Abrir un archivo para escritura
    ofstream archivo("pruebaNormal3.txt");

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Guardar las coordenadas en el archivo
    for (const auto &coordenada : coordenadasUnicas) {
        archivo << coordenada.first << " " << coordenada.second << endl;
    }

    // Cerrar el archivo
    archivo.close();

    cout << "Coordenadas guardadas en coordenadas.txt." << endl;

    return 0;
}