#include "knnir.hpp"
#include "basic.h"
#include "kTree.h"
#include<unistd.h>
#include <iostream>
#include <unistd.h>
#include "bitrankw32int.h"
#include "Count.hpp"
using namespace std;

//se define la funcion knnir que recibe como parámetro un árbol, coordenadas x e y, el valor k y el radio
vector<pair<int, int>> knnir::knn(MREP *rep, int x, int y, uint k, uint radius){
  //Se declara vector de pares de enteros que almacenará los puntos encontrados como vecinos más cercanos.
  vector<pair<int, int>> points;

  int min_radius = 0;
  int max_radius = radius;
  int stepCount = 0;
  bool growUp = true;

  int x_min, y_min, x_max, y_max; // Created to rangue query
  int lastStepRadius;

  int max_border = rep->numberOfNodes;

  Count countFunction;

  //controla la búsqueda de vecinos más cercanos en función del radio especificado.
  while (min_radius <= max_radius)
  { 
    //Se calculan los valores mínimos y máximos con el radio especificado.
    x_min = x - (int)radius;
    y_min = y - (int)radius;
    x_max = x + (int)radius;
    y_max = y + (int)radius;

    //Se llama a la función compactCount para contar la cantidad de elementos en el radio.
    stepCount = countFunction.compactCount(rep, x_min, x_max, y_min, y_max);

    /*Se verifica si la cantidad de elementos en el radio es igual a k o si el radio excede el valor. 
    Si es asi, se obtienen los puntos usando getPointsinRadius y se devuelven como resultado de la función knn.*/
    if (stepCount == k || (radius > max_border*2))
    {
      points = getPointsinRadius(rep, x_min, y_min, x_max, y_max, k);
      return points;
    }
    
    //Se verifica si la búsqueda está en modo growUp(aumentando el radio de búsqueda).
    if (growUp)
    {
    
      /*Dependiendo del resultado de `stepCount`, el radio de búsqueda se ajusta para 
      aumentarlo o reducirlo. Si se alcanza el valor `k`, el algoritmo cambia al modo 
      de búsqueda binaria (`growUp` se establece en `false`).*/
      if (stepCount < k)
      {
        lastStepRadius = radius;
        radius = radius * 2;
      }
      else if (stepCount > k)
      {
        min_radius = lastStepRadius;
        max_radius = radius;
        radius = (max_radius + min_radius) / 2;
        
        growUp = false;
      }
    }
    else
    {
      // si k de mayor = k de menor return lo que haya
      //Búsqueda binaria
      if((max_radius - min_radius) == 1){
        return getPointsinRadius(rep, x - (int)max_radius, y - (int)max_radius, x + (int)max_radius, y + (int)max_radius, k);
      }

      if(stepCount > k){
        max_radius = radius;
        radius = (min_radius + radius) / 2;
        
      }
      else if(stepCount < k){
        min_radius = radius;
        radius = (max_radius + radius) /2;
      }
    }
  }
  points = getPointsinRadius(rep, x_min, y_min, x_max, y_max, k);
  return points;
};

//Función búsqueda de puntos en radio
vector<pair<int, int>> knnir::getPointsinRadius(MREP *rep, int x1, int y1, int x2, int y2, int k)
{
  vector<pair<int, int>> points;

  //valores no negativos
  x1 = x1 < 0 ? 0 : x1;
  y1 = y1 < 0 ? 0 : y1;
  
  //obtiene una matriz de puntos dentro del rango definido por las coordenadas.
  uint ** point_matrix = compactRangeQuery(rep, y1, y2, x1, x2); 

  //Se calcula el valor máximo entre `k` y la cantidad de puntos encontrados en el rango.
  int maximun = k > point_matrix[0][0] ? point_matrix[0][0] : k;

  //Se recorren los puntos encontrados y se almacenan en el vector points
  for(int i=0; i < maximun; i++){
    points.push_back(make_pair(point_matrix[1][i+1], point_matrix[0][i+1]));
  }

  return points;
};


