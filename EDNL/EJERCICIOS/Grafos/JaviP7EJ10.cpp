/*GRAFOS - P7 - EJ10*/
#include <vector>
#include <climits>
#include "..\ImplementacionesEDNL\GrafoP.hpp"
#include "..\ImplementacionesEDNL\Dijkstra.hpp"

template<typename tCoste>
tCoste costesViajes(GrafoP<tCoste>& gTren, GrafoP<tCoste>& gBus, GrafoP<tCoste>& gAvion, int ciudadOrigen, int ciudadDestino, double costeEstacion, double costeAeropuerto, std::vector<typename GrafoP<tCoste>::vertice>& P){
    size_t n = gTren.numVert();
    size_t nT = gTren.numVert() + gBus.numVert() + gAvion.numVert();
    GrafoP<tCoste> supergrafo(nT), arbolRec(nT);

    //Rellenamos coste de tren
    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j){
            supergrafo[i][j] = gTren[i][j];
        }
    }
    //Rellenamos coste de bus
    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j){
            supergrafo[i+n][j+n] = gBus[i][j];
        }
    }
    //Rellenamos coste de avion
    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j){
            supergrafo[i+2*n][j+2*n] = gAvion[i][j];
        }
    }
    /*por cada i hasta numVert, introducimos el coste de taxi de ambos transbordos*/
    for (size_t i = 0; i < n; ++i){
        supergrafo[i][i+n] = supergrafo[i+n][i] = costeEstacion;
        supergrafo[i][i+2*n] = supergrafo[i+n][i+2*n] =
        supergrafo[i+2*n][i] = supergrafo[i+2*n][i+n] = costeAeropuerto;
    }
    
    //Conseguimos los costes y devolvemos el resultado
    tCoste costeFinal;
    std::vector<tCoste> costes1;
    std::vector<tCoste> costes2;
    std::vector<tCoste> costes3;
    costes1 = Dijkstra(supergrafo, ciudadOrigen, P);       //Origen Tren
    costes2 = Dijkstra(supergrafo, ciudadOrigen + n, P);   //Origen Bus
    costes3 = Dijkstra(supergrafo, ciudadOrigen + 2*n, P); //Origen Avión
    //comparamos las diferentes posibles soluciones
    // desde Origen en Tren:
    std::vector<std::vector<int>> costes = {costes1, costes2, costes3};
    costeFinal = INT_MAX;
    for (auto& coste : costes) {
        for (int i = 0; i < 3; i++) {
            if (costeFinal > coste[ciudadDestino + i*n]) {
                costeFinal = coste[ciudadDestino + i*n];
            }
        }
    }

    return costeFinal; 
}