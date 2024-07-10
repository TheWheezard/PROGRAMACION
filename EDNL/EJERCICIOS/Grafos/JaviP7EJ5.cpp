/**
 * @file JaviP7EJ5
 * @author Javier López Sierra
 * @brief Problema EDNL, GRAFOS, Viajero alérgico.
 * @version 0.1
 * @date 2023-06-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
#include <map>
#include "../ImplementacionesEDNL/GrafoP.hpp"
#include "../ImplementacionesEDNL/Dijkstra.hpp"
#include "../ImplementacionesEDNL/Kruskal.hpp"
#include "../ImplementacionesEDNL/particion.hpp"
#include "../ImplementacionesEDNL/matriz.hpp"

 /* Se dispone de tres grafos que representan la matriz de costes para viajes en un
 determinado país pero por diferentes medios de transporte, por supuesto todos los grafos
 tendrán el mismo número de nodos. El primer grafo representa los costes de ir por
 carretera, el segundo en tren y el tercero en avión. Dado un viajero que dispone de una
 determinada cantidad de dinero, que es alérgico a uno de los tres medios de transporte, y
 que sale de una ciudad determinada, implementar un subprograma que determine las
 ciudades a las que podría llegar nuestro infatigable viajero. */

// El siguiente enum marca qué medio de transporte se pretende evitar
enum alergia {carretera, tren, avion};

template <typename tCoste>
void viajeroAlergico(const GrafoP<tCoste>& carretera, const GrafoP<tCoste>& tren, const GrafoP<tCoste>& avion, tCoste dinero, size_t origen, alergia) {
    std::vector<tCoste> viajes = viajesMasCortos(carretera, tren, avion, 0, origen, alergia);
    std::map<tCoste, size_t> destinos;
    for (size_t i = 0; i < viajes.size(); i++) {
        if (viajes[i] <= dinero)
            destinos.insert(std::make_pair(viajes[i], i));
    }
    //
}

template <typename tCoste>
std::vector<tCoste> viajesMasCortos(const GrafoP<tCoste>& carretera, const GrafoP<tCoste>& tren, const GrafoP<tCoste>& avion, int transbordo, size_t origen, alergia) {
    GrafoP<tCoste> transportes = new GrafoP<tCoste>(tren.numVert()*2); //todos tienen que tener el mismo numvert, transportes es un supergrafo para dos de ellos
    rellenarSuperGrafo(transportes, carretera, tren, avion, transbordo, alergia);
    std::vector<typename GrafoP<tCoste>::vertice> P;
    return Dijkstra(transportes, origen, P);
}

template <typename tCoste>
void rellenarSuperGrafo(GrafoP<tCoste>& transportes, const GrafoP<tCoste>& carretera, const GrafoP<tCoste>& tren, const GrafoP<tCoste>& avion, int transbordo, alergia) {
    size_t tamGrafo = tren.numVert();
    size_t tamSuperGrafo = transportes.numVert();

    // Rellenamos el supergrafo de tamaño N*2 (siendo N el tamaño de uno de los grafos)
    // con los dos medios escogidos (rechazando el incluido en alergia)
    switch (alergia) {
    case carretera: //case IGNORAR CARRETERA
        for (size_t i = 0; i < tamGrafo; i++) {
            for (size_t j = 0; j < tamGrafo; j++) {
                transportes[i][j] = tren[i][j];
            }
        }
        for (size_t i = 0; i < tamGrafo; i++){
            for (size_t j = 0; j < tamGrafo; j++) {
                transportes[i + tamGrafo][j + tamGrafo] = avion[i][j];
            }
        }
        break;

    case tren: //case IGNORAR TREN
        for (size_t i = 0; i < tamGrafo; i++) {
            for (size_t j = 0; j < tamGrafo; j++) {
                transportes[i][j] = carretera[i][j];
            }
        }
        for (size_t i = 0; i < tamGrafo; i++){
            for (size_t j = 0; j < tamGrafo; j++) {
                transportes[i + tamGrafo][j + tamGrafo] = avion[i][j];
            }
        }
        break;

    case avion: //case IGNORAR AVION
        for (size_t i = 0; i < tamGrafo; i++) {
            for (size_t j = 0; j < tamGrafo; j++) {
                transportes[i][j] = carretera[i][j];
            }
        }
        for (size_t i = 0; i < tamGrafo; i++){
            for (size_t j = 0; j < tamGrafo; j++) {
                transportes[i + tamGrafo][j + tamGrafo] = tren[i][j];
            }
        }
        break;

    default:
        break;
    }

    // Añadimos el valor de los transbordos
    for (size_t i = 0; i < tamGrafo; i++) {
        transportes[i][i + tamGrafo] = transportes[i + tamGrafo][i] = transbordo;
    }
}