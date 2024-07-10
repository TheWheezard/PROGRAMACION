/*
El archipiélago de Tombuctú, está formado por un número indeterminado de islas,
cada una de las cuales tiene, a su vez, un número indeterminado de ciudades. En
cambio, sí es conocido el número total de ciudades de Tombuctú (podemos llamarlo N,
por ejemplo).
Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
las ciudades de la isla. Se dispone de las coordenadas cartesianas (x, y) de todas y cada
una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en
el que se indica si existe carretera directa entre cualesquiera dos ciudades del
archipiélago. El objetivo de nuestro problema es encontrar qué ciudades de Tombuctú
pertenecen a cada una de las islas del mismo y cuál es el coste mínimo de viajar entre
cualesquiera dos ciudades de una misma isla de Tombuctú.
Así pues, dados los siguientes datos:
- Lista de ciudades de Tombuctú representada cada una de ellas por sus
coordenadas cartesianas.
- Matriz de adyacencia de Tombuctú, que indica las carreteras existentes en
dicho archipiélago.

Implementen un subprograma que calcule y devuelva la distribución en islas de las
ciudades de Tombuctú, así como el coste mínimo de viajar entre cualesquiera dos
ciudades de una misma isla del archipiélago.
*/

#include "Grafo.hpp"
#include "GrafoP.hpp"
#include "particion.hpp"
#include "matriz.hpp"
#include "Floyd.hpp"
#include <vector>
#include <cmath>

struct coordenadas {
    double x, y;
    coordenadas(double x_, double y_): x(x_), y(y_) {}
};

double calcularDistancia(coordenadas c1, coordenadas c2) {
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

matriz<double> islasTombuctu(Grafo& carreteras, std::vector<coordenadas> ciudades, Particion& P) {
    GrafoP<double> distancias(ciudades.size());
    for (size_t i = 0; i < carreteras.numVert(); ++i) {
        for (size_t j = 0; j < carreteras.numVert(); ++j) {
            if (carreteras[i][j]) {// se podría simplificar, pero como no encuentro mejor forma de recorrerlo, así se queda
                if (P.encontrar(i) != P.encontrar(j))
                    P.unir(i, j);
                distancias[i][j] = calcularDistancia(ciudades[i], ciudades[j]);
            }
        }
    }
    matriz<GrafoP<double>::vertice> caminos(distancias.numVert());
    matriz<double> costeMin = Floyd(distancias, caminos);
    return costeMin;
}