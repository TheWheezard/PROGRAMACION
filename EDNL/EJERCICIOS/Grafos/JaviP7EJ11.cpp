// Disponemos de tres grafos (matriz de costes) que representan los costes directos de
// viajar entre las ciudades de tres de las islas del archipiélago de las Huríes (Zuelandia).
// Para poder viajar de una isla a otra se dispone de una serie de puentes que conectan
// ciudades de las diferentes islas a un precio francamente asequible (por decisión del
// Prefecto de las Huríes, el uso de los puentes es absolutamente gratuito).
// Si el alumno desea simplificar el problema, puede numerar las N1 ciudades de la isla
// 1, del 0 al N1-1, las N2 ciudades de la isla 2, del N1 al N1+N2-1, y las N3 de la última, del
// N1+ N2 al N1+N2+ N3-1.
// Disponiendo de las tres matrices de costes directos de viajar dentro de cada una de
// las islas, y la lista de puentes entre ciudades de las mismas, calculad los costes mínimos
// de viajar entre cualesquiera dos ciudades de estas tres islas.

#include <iostream>
#include <vector>
#include <map>
#include "../ImplementacionesEDNL/GrafoP.hpp"
#include "../ImplementacionesEDNL/Floyd.hpp"
#include "../ImplementacionesEDNL/Dijkstra.hpp"
#include "../ImplementacionesEDNL/Kruskal.hpp"


struct Puente {
    int c1, c2;

    Puente(int a, int b) : c1(a), c2(b){}
};

/**
 * @brief Recibe tres grafos y devuelve el coste mínimo de viajar entre dos ciudades representadas como vértices de los grafos.
 *
 * @tparam tCoste
 * @param g1 Grafo de costes de viajar en la isla 1.
 * @param g2 Grafo de costes de viajar en la isla 2.
 * @param g3 Grafo de costes de viajar en la isla 3.
 * @param puentes Lista de puentes entre ciudades de las islas.
 * @param origen  vertice de origen.
 * @param destino vertice de destino.
 * @return tCoste - Coste mínimo de viajar entre origen y destino.
 */
template <typename tCoste>
matriz<tCoste> costeViajesHuries(GrafoP<tCoste>& g1, GrafoP<tCoste>& g2, GrafoP<tCoste>& g3, std::vector<Puente> puentes) {
    GrafoP<tCoste> gTotal = supergrafo(g1, g2, g3);
    agregarPuentes(gTotal, puentes);

    matriz<GrafoP<tCoste>::vertice> P;
    
    return Floyd(gTotal, P);
}

/**
 * @brief Crea un grafo que representa la unión de tres grafos.
 * @tparam tCoste Tipo de dato para representar los costes.
 * @param g1 Grafo 1.
 * @param g2 Grafo 2.
 * @param g3 Grafo 3.
 * @return Grafo que representa la unión de g1, g2 y g3.
 */
template <typename tCoste>
GrafoP<tCoste> supergrafo(GrafoP<tCoste>& g1, GrafoP<tCoste>& g2, GrafoP<tCoste>& g3) {
    GrafoP<tCoste> g (g1.numVert() + g2.numVert() + g3.numVert()); //N+N+N

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

    for (int i = 0; i < g3.numVert(); i++) {
        for (int j = 0; j < g3.numVert(); j++) {
            g[i+g1.numVert()+g2.numVert()][j+g1.numVert()+g2.numVert()] = g3[i][j];
        }
    }

    return g;
}

/**
 * @brief Añade los puentes al grafo.
 * @tparam tCoste Tipo de dato para representar los costes.
 * @param g Grafo al que se le añadirán los puentes.
 * @param puentes Lista de puentes a añadir.
 */
template <typename tCoste>
void agregarPuentes(GrafoP<tCoste>& g, std::vector<Puente> puentes) {
    for (Puente puente : puentes) {
        g[puente.c1][puente.c2] = g[puente.c2][puente.c1] = 0;
    }
}