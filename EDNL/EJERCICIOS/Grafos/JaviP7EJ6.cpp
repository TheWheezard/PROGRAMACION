/**
 * @file JaviP7EJ6.cpp
 * @author Javier López Sierra
 * @brief Problema EDNL, Grafos, Taxis en huelga
 * @version 0.1
 * @date 2023-06-14
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

/* Al dueño de una agencia de transportes se le plantea la siguiente situación. La
agencia de viajes ofrece distintas trayectorias combinadas entre N ciudades españolas
utilizando tren y autobús. Se dispone de dos grafos que representan los costes (matriz de
costes) de viajar entre diferentes ciudades, por un lado en tren, y por otro en autobús
(por supuesto entre las ciudades que tengan línea directa entre ellas). Además coincide
que los taxis de toda España se encuentran en estos momentos en huelga general, lo que
implica que sólo se podrá cambiar de transporte en una ciudad determinada en la que,
por casualidad, las estaciones de tren y autobús están unidas.
Implementa una función que calcule la tarifa mínima (matriz de costes mínimos) de
viajar entre cualesquiera de las N ciudades disponiendo del grafo de costes en autobús,
del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas. */

template <typename tCoste>
size_t calcularTarifaMinimaCiudades(const GrafoP<tCoste>& trenes, const GrafoP<tCoste>& buses, size_t origen, size_t destino, size_t transbordo) {
    matriz<tCoste> tarifasViajes = calcularCosteViajes(trenes, buses, transbordo);
    size_t aux = tarifasViajes.dimension()/2;
    // tren - tren
    tCoste tarifaBarata = tarifasViajes[origen][destino];
    // bus - tren
    if (tarifaBarata > tarifasViajes[origen+aux][destino])
        tarifaBarata = tarifasViajes[origen+aux][destino];
    // tren - bus
    if (tarifaBarata > tarifasViajes[origen][destino+aux])
        tarifaBarata = tarifasViajes[origen][destino+aux];
    // bus - bus
    if (tarifaBarata > tarifasViajes[origen+aux][destino+aux])
        tarifaBarata = tarifasViajes[origen+aux][destino+aux];
    
    return tarifaBarata;
}

template <typename tCoste>
matriz<tCoste> calcularCosteViajes(const GrafoP<tCoste>& trenes, const GrafoP<tCoste>& buses, size_t ciudadTransbordo) {
    GrafoP<tCoste> costeViajes = new GrafoP<tCoste>(trenes.numVert() + buses.numVert());
    rellenarSuperGrafo(costeViajes, trenes, buses);

    // ponemos a 0 la casilla que referencia la ciudad que admite transbordo
    costeViajes[ciudadTransbordo][ciudadTransbordo] = 0;

    // calculamos el coste mínimo de todas las posibles combinaciones
    GrafoP<tCoste> P = new GrafoP<tCoste>(costeViajes.numVert());
    
    return Floyd(costeViajes, P);
}

template <typename tCoste>
void rellenarSuperGrafo(GrafoP<tCoste>& costeViajes, const GrafoP<tCoste>& trenes, const GrafoP<tCoste>& buses) {
    // Datos trenes
    for (size_t i = 0; i < trenes.numVert(); i++) {
        for (size_t j = 0; j < trenes.numVert(); j++) {
            costeViajes[i][j] = trenes[i][j];
        }
    }
    // Datos buses
    for (size_t i = 0; i < buses.numVert(); i++) {
        for (size_t j = 0; j < buses.numVert(); j++) {
            costeViajes[i + trenes.numVert()][j + trenes.numVert()] = buses[i][j];
        }
    }
}