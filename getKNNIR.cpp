#include <iostream>

#include "libs/knnir.hpp"
#include "libs/kTree.h"

using namespace std;

int main(int argc, char * argv[]){

    /* Verifica si se proporcionaron menos de 5 argumentos en la línea de comandos. 
	Si es el caso, muestra un mensaje de uso que indica la forma correcta de usar el 
	programa y devuelve -1 para indicar un error.*/
	if(argc < 5){
		printf("%s <PATH> <X_1> <Y_1> <K>\n", argv[0]);
		return -1;
	}


    /* Declara un puntero rep de tipo MREP y lo inicializa con el resultado de 
	la función loadRepresentation que toma el primer argumento argv[1] 
	(representación de datos utilizada en el algoritmo KNN).*/
	MREP *rep = loadRepresentation(argv[1]);

	/*Convierte los demás argumentos a un entero y lo almacena en 
	las variables (x,y) y 'k'.*/
	int x = atoi(argv[2]);
	int y = atoi(argv[3]);
	int k = atoi(argv[4]);

    /*Crea una instancia del objeto knnir llamado knn.*/
	knnir knn;

	/*Llama al método knn del objeto knn con los argumentos rep, x, y, k, y 1, 
	y almacena el resultado en un vector de pares de enteros llamado points. 
	Este método realiza la clasificación de puntos cercanos utilizando 
	el algoritmo KNN.*/
	vector<pair<int,int>> points = knn.knn(rep, x, y, k, 1);

	/*Itera los elementos del vector points, que contiene pares de enteros, 
	y para cada par, imprime las coordenadas en el formato (x, y).*/
	for(pair<int,int> point : points){
		cout << "(" << point.first << "," << point.second << ")\n";
	}


	return 0;
}
