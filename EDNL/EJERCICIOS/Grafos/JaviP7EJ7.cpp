/**
 * @file JaviP7EJ7.cpp
 * @author Javier López Sierra
 * @brief Problema EDNL, Grafos, taxis en huelga, dos transbordos
 * @version 0.1
 * @date 2023-06-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <iostream>
#include <vector>
#include <map>
#include "../ImplementacionesEDNL/GrafoP.hpp"
#include "../ImplementacionesEDNL/Floyd.hpp"
#include "../ImplementacionesEDNL/Dijkstra.hpp"
#include "../ImplementacionesEDNL/Kruskal.hpp"
#include "../ImplementacionesEDNL/particion.hpp"
#include "../ImplementacionesEDNL/matriz.hpp"

typedef size_t vertice;
/* Se dispone de dos grafos (matriz de costes) que representan los costes de viajar entre
N ciudades españolas utilizando el tren (primer grafo) y el autobús (segundo grafo).
Ambos grafos representan viajes entre las mismas N ciudades.
Nuestro objetivo es hallar el camino de coste mínimo para viajar entre dos ciudades
concretas del grafo, origen y destino, en las siguientes condiciones:
 La ciudad origen sólo dispone de transporte por tren.
 La ciudad destino sólo dispone de transporte por autobús.
 El sector del taxi, bastante conflictivo en nuestros problemas, sigue en huelga,
por lo que únicamente es posible cambiar de transporte en dos ciudades del
grafo, cambio1 y cambio2, donde las estaciones de tren y autobús están
unidas.
Implementa un subprograma que calcule la ruta y el coste mínimo para viajar entre
las ciudades Origen y Destino en estas condiciones. */

template <typename tCoste>
tCoste precioYRutaViaje(const GrafoP<tCoste>& tren, const GrafoP<tCoste>& bus, vertice origen, vertice destino, vertice cambio1, vertice cambio2, std::vector<typename GrafoP<tCoste>::vertice>& P) {
    size_t n = tren.numVert();
    GrafoP<tCoste> transportes = new GrafoP<tCoste>(2*n);
    rellenarSuperGrafo(transportes, tren, bus, n);
    agregarTransbordos(transportes, cambio1, cambio2, n);
    // La ciudad Destino solo es accesible a través de bus, en el supergrafo será entonces destino + n
    std::vector<tCoste> res = Dijkstra(transportes, origen, P);

    return res[destino + n];
}

/**
 * @brief Función que crea un supergrafo a partir de los grafos tren y bus. Se introducirán los datos en ese orden específico. 
 * Para acceder a los datos de bus en el supergrafo habrá que hacer i+N, siendo N el numVert de uno de los grafos.
 *
 * @tparam tCoste
 * @param transportes supergrafo (referencia)
 * @param tren grafo con los datos de estaciones de tren.
 * @param bus grafo con los datos de líneas de bus.
 * @param n tamaño de un grafo estándar.
 */
template <typename tCoste>
void rellenarSuperGrafo(GrafoP<tCoste>& transportes, const GrafoP<tCoste>& tren, const GrafoP<tCoste>& bus, size_t n) {
    // Datos trenes
    for (vertice i = 0; i < n; i++) {
        for (vertice j = 0; j < n; j++) {
            transportes[i][j] = tren[i][j];
        }
    }

    // Datos buses
    for (vertice i = 0; i < n; i++) {
        for (vertice j = 0; j < n; j++) {
            transportes[i+n][j+n] = bus[i][j];
        }
    }
}

/**
 * @brief Función que recibe un supergrafo de tamaño 2n, dos vértices y el tamaño n; pone a 0 las posiciones marcadas por
 * los vértices en los dos subgrafos, creando así dos caminos de coste 0 entre los subgrafos mencionados, en las posiciones
 * señaladas por ambos parámetros.
 * 
 * @tparam tCoste 
 * @param transportes supergrafo.
 * @param cambio1 vértice de un grafo.
 * @param cambio2 vértice de un grafo.
 * @param n tamaño de un grafo.
 */
template <typename tCoste>
void agregarTransbordos(GrafoP<tCoste>& transportes, vertice cambio1, vertice cambio2, size_t n) {
    // Añadimos transbordo 1:
    transportes[cambio1][cambio1+n] = transportes[cambio1+n][cambio1] = 0;
    //Añadimos transbordo 2:
    transportes[cambio2][cambio2+n] = transportes[cambio2+n][cambio2] = 0;
}