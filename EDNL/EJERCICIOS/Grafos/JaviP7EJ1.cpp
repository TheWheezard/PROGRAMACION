/**
 * @file JaviP7EJ1.cpp
 * @author Javier López Sierra
 * @brief Práctica 7, ejercicio 1. Problema EDNL, Grafos, viaje más caro posible.
 * @version 0.1
 * @date 2023-09-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 /* Tu agencia de viajes “OTRAVEZUNGRAFO S.A.” se enfrenta a un curioso cliente.
 Es un personaje sorprendente, no le importa el dinero y quiere hacer el viaje más caro
 posible entre las ciudades que ofertas. Su objetivo es gastarse la mayor cantidad de
 dinero posible (ojalá todos los clientes fueran así), no le importa el origen ni el destino
 del viaje.
 Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente
 el grafo de tu agencia de viajes resultó ser acíclico, devolver el coste, origen y destino
 de tan curioso viaje. Se parte de la matriz de costes directos entre las ciudades del grafo. */

#include <iostream>
#include <vector>
#include <map>
#include "../ImplementacionesEDNL/GrafoP.hpp"
#include "../ImplementacionesEDNL/Floyd.hpp"
#include "../ImplementacionesEDNL/Dijkstra.hpp"
#include "../ImplementacionesEDNL/Kruskal.hpp"

typedef size_t vertice;

template <typename tCoste>
tCoste viaje_mas_caro(GrafoP<tCoste>& grafo, vertice& origen, vertice& destino) {
    GrafoP<tCoste> grafoEspejo = grafo_espejo(grafo);
    matriz<vertice> P;
    matriz<tCoste> caminosMaximos = Floyd(grafo_espejo, P); // En este punto tenemos los costes en negativo
    tCoste coste = 0;
    vertice i = 0;
    vertice j = 0;
    while (i < caminosMaximos.dimension()) {
        while (j < caminosMaximos.dimension()) {
            if (coste > caminosMaximos[i][j]) { // El valor absoluto del más pequeño será el más grande
                coste = caminosMaximos[i][j];
                origen = i;
                destino = j;
            }
            j++;
        }
        i++;
    }

    return coste * -1;
}

template <typename tCoste>
GrafoP<tCoste> grafo_espejo(GrafoP<tCoste>& grafo) {
    GrafoP<tCoste> res = grafo;
    for (vertice i = 0; i < res.numVert(); i++) {
        for (vertice j = 0; j < res.numVert(); j++) {
            res[i][j] = res[i][j] * -1;
        }
    }
}

