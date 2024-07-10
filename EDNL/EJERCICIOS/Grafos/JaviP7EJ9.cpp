/**
 * @file JaviP7EJ9.cpp
 * @brief Implementación de funciones para calcular el camino y el coste mínimo para ir de una ciudad origen a una ciudad destino.
 */

#include <iostream>
#include <vector>
#include <map>
#include "../ImplementacionesEDNL/GrafoP.hpp"
#include "../ImplementacionesEDNL/Floyd.hpp"
#include "../ImplementacionesEDNL/Dijkstra.hpp"
#include "../ImplementacionesEDNL/Kruskal.hpp"

/** @brief Calcula el coste mínimo para ir de la ciudad origen a la ciudad destino.
 * @tparam tCoste Tipo de dato para representar los costes.
 * @param gTren Grafo que representa los costes de viajar en tren.
 * @param gBus Grafo que representa los costes de viajar en autobús.
 * @param taxi Coste del taxi para cambiar de una estación a otra dentro de cualquier ciudad.
 * @param origen Ciudad de origen.
 * @param destino Ciudad de destino.
 * @return Coste mínimo para ir de la ciudad origen a la ciudad destino.
 */
template <typename tCoste>
tCoste costeMinimo(GrafoP<tCoste>& gTren, GrafoP<tCoste>& gBus, tCoste taxi, int origen, int destino) {
    GrafoP<tCoste> gCompleto = superGrafo(gTren, gBus);
    costesTaxi(gCompleto, taxi);

    std::vector<GrafoP<tCoste>::vertice> P;
    std::vector<tCoste> res = Dijkstra(gCompleto, origen, P);

    return res[destino];
}

/**
 * @brief Crea un grafo que representa la unión de dos grafos.
 * @tparam tCoste Tipo de dato para representar los costes.
 * @param g1 Grafo 1.
 * @param g2 Grafo 2.
 * @return Grafo que representa la unión de g1 y g2.
 */
template <typename tCoste>
GrafoP<tCoste> superGrafo(GrafoP<tCoste>& g1, GrafoP<tCoste>& g2) {
    GrafoP<tCoste> g(g1.numVert() + g2.numVert()); // N+N
    for (int i = 0; i < g1.numVert(); i++) {
        for (int j = 0; j < g1.numVert(); j++) {
            g[i][j] = g1[i][j];
        }
    }
    for (int i = 0; i < g2.numVert(); i++) {
        for (int j = 0; j < g2.numVert(); j++) {
            g[i+g1.numVert()][j+g1.numVert()] = g2[i][j];
        }
    }

    return g;
}

/**
 * @brief Asigna el coste del taxi para cambiar de una estación a otra dentro de cualquier ciudad.
 * @tparam tCoste Tipo de dato para representar los costes.
 * @param g Grafo.
 * @param taxi Coste del taxi.
 * @return Grafo g actualizado con los costes del taxi. 
 */
template <typename tCoste>
void costesTaxi(GrafoP<tCoste>& g, tCoste taxi) {
    for (int i = 0; i < g.numVert()/2; i++) {
        g[i][i+g.numVert()/2] = g[i+g.numVert()/2][i] = taxi;
    }
}