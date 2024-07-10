/**
 * @file JaviP7EJ12.cpp
 * @author Javier López Sierra
 * @brief Problema EDNL, Grafos, Huríes (maremoto)
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

/* El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas,
Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2
ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2). Se desea construir un puente
que una ambas islas. Nuestro problema es elegir el puente a construir entre todos los
posibles, sabiendo que el coste de construcción del puente se considera irrelevante. Por
tanto, escogeremos aquel puente que minimice el coste global de viajar entre todas las
ciudades de las dos islas, teniendo en cuenta las siguientes premisas:
1. Se asume que el coste viajar entre las dos ciudades que una el puente es 0.
2. Para poder plantearse las mejoras en el transporte que implica la construcción de
un puente frente a cualquier otro, se asume que se realizarán exactamente el
mismo número de viajes entre cualesquiera ciudades del archipiélago. Por
ejemplo, se considerará que el número de viajes entre la ciudad P de Fobos y la
Q de Deimos será el mismo que entre las ciudades R y S de la misma isla. Dicho
de otra forma, todos los posibles trayectos a realizar dentro del archipiélago son
igual de importantes.
Dadas las matrices de costes directos de Fobos y Deimos y las listas de ciudades
costeras de ambas islas, implementa un subprograma que calcule las dos ciudades que
unirá el puente. */

template <typename tCoste>
struct puente {
    size_t a, b, coste;
    puente(){ coste = 0; }
    puente(size_t cA, size_t cB): a(cA), b(cB), coste(GrafoP<tCoste>::INFINITO){}
};

template <typename tCoste>
void Grecoland(const GrafoP<tCoste>& isla1, const GrafoP<tCoste>& isla2, const std::vector<bool>& c1, std::vector<bool>& c2) {
    GrafoP<tCoste> archipielago = new GrafoP<tCoste>(isla1.numVert()+isla2.numVert());
    for (size_t i = 0; i < archipielago.numVert(); i++) {
        for (size_t j = 0; j < archipielago.numVert(); j++) {
            archipielago[i][j] = GrafoP<tCoste>::INFINITO;
        }   
    }
    rellenarSuperGrafo(archipielago, isla1, isla2);

    puente p, res{archipielago.numVert(), archipielago.numVert()};
    matriz<typename GrafoP<tCoste>::vertice> P = new matriz<typename GrafoP<tCoste>::vertice>(archipielago.numVert());
    for (size_t i = 0; i < isla1; i++) {
        if (esCostera(i, isla1, isla2, c1, c2)) {
            for (size_t j = 0; j < isla2; j++) {
                if (esCostera(j, isla1, isla2, c1, c2)) {
                    p.a = i;
                    p.b = j;
                    agregarPuente(archipielago, p, isla1.numVert());

                    matriz<tCoste> costesIndividuales = Floyd(archipielago, P);
                    for (size_t i = 0; i < costesIndividuales.dimension(); i++) {
                        for (size_t j = 0; j < costesIndividuales.dimension(); j++) {
                            p.coste += costesIndividuales[i][j];
                        }
                    }
                    
                    eliminarPuente(archipielago, p, n);
                    if (p.coste < res.coste) {
                        res = p;
                    }
                }
            }
        }
    }
}


template <typename tCoste>
void rellenarSuperGrafo(GrafoP<tCoste>& archipielago, const GrafoP<tCoste>& isla1, const GrafoP<tCoste>& isla2, const GrafoP<tCoste>& isla3) {
    for (size_t i = 0; i < isla1.numVert(); i++) {
        for (size_t j = 0; j < isla1.numVert(); j++) {
            archipielago[i][j] = isla1[i][j];
        }
    }

    for (size_t i = 0; i < isla2.numVert(); i++) {
        for (size_t j = 0; j < isla2.numVert(); j++) {
            archipielago[i+isla1.numVert()][+isla1.numVert()] = isla2[i][j];
        }
    }
}

template <typename tCoste>
bool esCostera(size_t ciudad, const GrafoP<tCoste>& isla1, const GrafoP<tCoste>& isla2, const std::vector<bool>& c1, std::vector<bool>& c2) {
    return (ciudad < isla1.numVert() && c1[ciudad] || (ciudad - isla1.numVert()) < isla2.numVert() && c2[ciudad]);
}

template <typename tCoste>
void agregarPuente(GrafoP<tCoste>& archipielago, puente<tCoste> p, size_t n) {
    archipielago[p.a][p.b + n] = archipielago[p.b + n][p.a] = 0;
}

template <typename tCoste>
void eliminarPuente(GrafoP<tCoste>& archipielago, puente<tCoste> anterior, size_t n) {
    if (anterior.a < archipielago.numVert() && anterior.b < archipielago.numVert()) {
        // Quitamos el puente anterior
        archipielago[anterior.a][anterior.b + n] = archipielago[anterior.b + n][anterior.a] = GrafoP<tCoste>::INFINITO;
    }
}