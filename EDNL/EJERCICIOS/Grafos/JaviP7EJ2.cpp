/**
 * @file JaviP7EJ2.cpp
 * @author your name (you@domain.com)
 * @brief Práctica 7, ejercicio2. Problema de grafos, laberinto simplificado.
 * @version 0.1
 * @date 2023-09-10
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

/* Se dispone de un laberinto de NxN casillas del que se conocen las casillas de entrada
y salida del mismo. Si te encuentras en una casilla sólo puedes moverte en las siguientes
cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las
casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared
(en caso contrario no sería un verdadero laberinto).
Implementa un subprograma que dados
 N (dimensión del laberinto),
 la lista de paredes del laberinto,
 la casilla de entrada, y
 la casilla de salida,
calcule el camino más corto para ir de la entrada a la salida y su longitud. */

typedef int vertice;

struct tCasilla {
    size_t x, y;
    tCasilla (size_t a, size_t b) : x(a), y(b) {}
};

struct Pared {
    tCasilla a, b;
    Pared (tCasilla c1, tCasilla c2) : a(c1), b(c2) {}
};

template <typename tCoste>
tCoste laberinto_2D_facil(matriz<tCasilla>& laberinto, std::vector<Pared>& paredes, tCasilla origen, tCasilla destino, std::vector<typename GrafoP<tCoste>::vertice>& P) {
    GrafoP<tCoste>& grafoLab = *new GrafoP<tCoste>(laberinto.dimension()*laberinto.dimension());
    rellenar_paredes(grafoLab, paredes, laberinto);
    vertice casillaOrigen = encuentra_casilla(laberinto, origen);
    vertice casillaDestino = encuentra_casilla(laberinto, destino);
    std::vector<tCoste> res = Dijkstra(grafoLab, casillaOrigen, P);
    return res[casillaDestino];
}

template <typename tCoste>
void rellenar_paredes(GrafoP<tCoste>& g, std::vector<Pared>& paredes, matriz<tCasilla>& laberinto) {
    vertice aux = 0;
    for (size_t i = 0; i < laberinto.dimension(); i++) {
        for (size_t j = 1; j < laberinto.dimension(); j++) {
            if (!hay_pared(laberinto[i][j-1], laberinto[i][j], paredes)) {
                g[i+j-1][i+j] = 1;
            }
        }
    }
}

template <typename tCoste>
bool hay_pared(tCasilla c1, tCasilla c2, std::vector<Pared>& paredes) {
    bool found = false;
    size_t i = 0;
    while (!found && i < paredes.size()) {
        if ((paredes[i].a == c1 && paredes[i].b == c2) || (paredes[i].a == c2 && paredes[i].b == c1)) {
            found == true;
        }
        i++;
    }
    return found;
}

template<typename tCoste>
vertice encuentra_casilla(matriz<tCasilla>& m, tCasilla casilla) {
    size_t i = 0;
    size_t j = 0;
    while (casilla != m[i][j] && i < m.dimension()) {
        while (casilla != m[i][j] && j < m.dimension()) {
            j++;
        }
        i++;
    }
    return i+j;
}