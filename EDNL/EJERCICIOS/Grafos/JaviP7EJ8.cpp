/***
 * “UN SOLO TRANSBORDO, POR FAVOR”. Este es el título que reza en tu
 * flamante compañía de viajes. Tu publicidad explica, por supuesto, que ofreces viajes
 * combinados de TREN y/o AUTOBÚS (es decir, viajes en tren, en autobús, o usando
 * ambos), entre N ciudades del país, que ofreces un servicio inmejorable, precios muy
 * competitivos, y que garantizas ante notario algo que no ofrece ninguno de tus
 * competidores: que en todos tus viajes COMO MÁXIMO se hará un solo transbordo
 * (cambio de medio de transporte).
 * Bien, hoy es 1 de Julio y comienza la temporada de viajes.
 * ¡Qué suerte! Acaba de aparecer un cliente en tu oficina. Te explica que quiere viajar
 * entre dos ciudades, Origen y Destino, y quiere saber cuánto le costará.
 * Para responder a esa pregunta dispones de dos grafos de costes directos (matriz de
 * costes) de viajar entre las N ciudades del país, un grafo con los costes de viajar en tren y
 * otro en autobús.
 * Implementa un subprograma que calcule la tarifa mínima en estas condiciones.
 */

#include <iostream>
#include <vector>
#include <map>
#include "../ImplementacionesEDNL/GrafoP.hpp"
#include "../ImplementacionesEDNL/Floyd.hpp"
#include "../ImplementacionesEDNL/Dijkstra.hpp"
#include "../ImplementacionesEDNL/Kruskal.hpp"

 /**
  * @brief Recibe dos grafos y devuelve el coste mínimo de viajar entre dos ciudades representadas como vértices de los grafos.
  *
  * @tparam tCoste
  * @param gTren Grafo de costes de viajar en tren.
  * @param gBus  Grafo de costes de viajar en autobús.
  * @param origen  vertice de origen.
  * @param destino vertice de destino.
  * @return tCoste - Coste mínimo de viajar entre origen y destino.
  */
template <typename tCoste>
tCoste tarifaMinima(GrafoP<tCoste>& gTren, GrafoP<tCoste>& gBus, int origen, int destino) {
    GrafoP<tCoste> gCompleto = unirGrafos(gTren, gBus);

    tCoste res = resultadoDijkstra(gTren, origen, destino);
    tCoste aux = resultadoDijkstra(gBus, origen, destino);
    if (res > aux) res = aux;

    for (int i = 0; i < gCompleto.numVert() / 2; i++) {
        aux = resultadoSupergrafo(gCompleto, i, origen, destino);
        if (res > aux)
            res = aux;
    }

    return res;
}

/**
 * @brief Recibe dos grafos y devuelve el grafo que resulta de unir ambos grafos.
 *
 * @tparam tCoste
 * @param grafoA Grafo a unir.
 * @param grafoB Grafo a unir.
 * @return GrafoP<tCoste> - Grafo resultante de unir grafoA y grafoB.
 */
template <typename tCoste>
GrafoP<tCoste> unirGrafos(GrafoP<tCoste>& grafoA, GrafoP<tCoste>& grafoB) {
    GrafoP<tCoste> g(grafoA.numVert() + grafoB.numVert()); // es N+N
    // El grafo al crearse se inicializa a INFINITO

    // Rellenamos la parte correspondiente al primer grafo
    for (int i = 0; i < grafoA.numVert(); i++) {
        for (int j = 0; j < grafoA.numVert(); j++) {
            g[i][j] = grafoA[i][j];
        }
    }

    // Rellenamos la parte correspondiente al segundo grafo
    for (int i = 0; i < grafoB.numVert(); i++) {
        for (j = 0; j < grafoB.numVert(); j++) {
            g[grafoA.numVert() + i][grafoA.numVert() + j] = grafoB[i][j];
        }
    }

    return g;
}

/**
 * @brief Recibe un grafo y devuelve el coste mínimo de viajar entre dos ciudades dadas representadas como vértices del grafo. Se usa el algoritmo de Dijkstra.
 *
 * @tparam tCoste
 * @param g Grafo de costes de viajar.
 * @param origen vertice de origen.
 * @param destino vertice de destino.
 * @return tCoste - Coste mínimo de viajar entre origen y destino.
 */
template <typename tCoste>
tCoste resultadoDijkstra(GrafoP<tCoste>& g, int origen, int destino) {
    vector<typename GrafoP<tCoste>::vertice> P;
    vector<tCoste> res = Dijkstra(g, origen, P);
    return res[destino];
}

/**
 * @brief Recibe un grafo y devuelve el coste mínimo de viajar entre dos ciudades dadas representadas como vértices del grafo. Se usa como llamada a resultadoDijkstra.
 *
 * @tparam tCoste
 * @param g Grafo de costes de viajar.
 * @param origen vertice de origen.
 * @param destino vertice de destino.
 * @return tCoste - Coste mínimo de viajar entre origen y destino.
 */
template <typename tCoste>
tCoste resultadoSupergrafo(GrafoP<tCoste> g, int transbordo, int origen, int destino) {
    g[transbordo][transbordo + g.numVert() / 2] = g[transbordo + g.numVert() / 2][transbordo] = 0;
    tCoste res = resultadoDijkstra(g, origen, destino);
    tCoste aux = resultadoDijkstra(g, origen, destino + g.numVert()/2);
    if (res > aux) res = aux;
    aux = resultadoDijkstra(g, origen + g.numVert()/2, destino);
    if (res > aux) res = aux;
    aux = resultadoDijkstra(g, origen + g.numVert()/2, destino + g.numVert()/2);
    if (res > aux) res = aux;
    return res;
}