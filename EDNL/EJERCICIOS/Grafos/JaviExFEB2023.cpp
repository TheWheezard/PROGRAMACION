/**
 * El archipiélago de Grecoland (Zuelandia) está formado únicamente por tres islas,
 * Fobos, Deimos y Europa, que tienen N1, N2 y N3 ciudades, respectivamente, de las cuales 
 * C1, C2 y C3 ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2 ). Se dispone de las
 * coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago.
 * El huracán Isadore acaba de devastar el archipiélago, con lo que todas las carreteras y 
 * puentes construidos en su día han desaparecido. En esta terrible situación se pide ayuda
 * a la ONU, que acepta reconstruir el archipiélago (es decir volver a comunicar todas las
 * ciudades del archipiélago) siempre que se haga al mínimo coste.
 *  De cara a poder comparar costes de posibles reconstrucciones se asume lo
 * siguiente:
 *   1. El coste de construir cualquier carretera o cualquier puente es proporcional a su
 * longitud (distancia euclídea entre las poblaciones de inicio y fin de la carretera o
 * del puente).
 *   2. Cualquier puente que se construya siempre será más barato que cualquier carretera
 * que se construya.
 *  En estas condiciones, implementa un subprograma que calcule el coste mínimo
 * de viajar entre dos ciudades de Grecoland, origen y destino, después de haberse
 * reconstruido el archipiélago, dados los siguientes datos:
 *   • Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
 *   • Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas.
 *   • Lista de ciudades de Europa representadas mediante sus coordenadas cartesianas.
 *   • Lista de ciudades costeras de Fobos.
 *   • Lista de ciudades costeras de Deimos.
 *   • Lista de ciudades costeras de Europa.
 *   • Ciudad origen del viaje.
 *   • Ciudad destino del viaje. 
 * */

#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include "../ImplementacionesEDNL/GrafoP.hpp"
#include "../ImplementacionesEDNL/Floyd.hpp"
#include "../ImplementacionesEDNL/Dijkstra.hpp"
#include "../ImplementacionesEDNL/Kruskal.hpp"
#include "../ImplementacionesEDNL/particion.hpp"
#include "../ImplementacionesEDNL/matriz.hpp"

struct ciudad {
    double x, y;
    ciudad(double x_, double y_) : x(x_), y(y_){}
};

bool operator==(ciudad c1, ciudad c2) {
    return c1.x == c2.x && c1.y == c2.y;
}

double distancia(ciudad c1, ciudad c2) {
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

template <typename tCoste>
tCoste reconstruirGrecoland(const std::vector<ciudad>& fobos, const std::vector<ciudad>& deimos, const std::vector<ciudad>& europa, std::vector<bool> cfobos, std::vector<bool> cdeimos, std::vector<bool> ceuropa, size_t origen, size_t destino) {
    // CREAMOS GRAFOS DE CADA ISLA Y LOS CONECTAMOS ENTEROS
    GrafoP<tCoste> gfobos = new GrafoP<tCoste>(fobos.size()*2);
    GrafoP<tCoste> gdeimos = new GrafoP<tCoste>(deimos.size()*2);
    GrafoP<tCoste> geuropa = new GrafoP<tCoste>(europa.size()*2);
    // Grafo de Fobos
    for (size_t i = 0; i < gfobos.numVert(); i++) {
        for (size_t j = 0; j < gfobos.numVert(); j++) {
            gfobos[i][j] = distancia(fobos[i], fobos[j]);
        }
    }
    // Grafo de Deimos
    for (size_t i = 0; i < gdeimos.numVert(); i++) {
        for (size_t j = 0; j < gdeimos.numVert(); j++) {
            gdeimos[i][j] = distancia(deimos[i], deimos[j]);
        }
    }
    // Grafo de Europa
    for (size_t i = 0; i < geuropa.numVert(); i++) {
        for (size_t j = 0; j < geuropa.numVert(); j++) {
            geuropa[i][j] = distancia(europa[i], europa[j]);
        }
    }

    // CREAMOS UN GRAFO DE COSTE MÍNIMO A PARTIR DE LOS GRAFOS HIPERCONEXOS ANTERIORES
    gfobos = Kruskal(gfobos);
    gdeimos = Kruskal(gdeimos);
    geuropa = Kruskal(geuropa);

    // CREAMOS UN SUPERGRAFO CON LOS GRAFOS ANTERIORES, Y AÑADIMOS LOS PUENTES A LAS CIUDADES COSTERAS
    GrafoP<tCoste> islas = new GrafoP<tCoste>(gfobos.numVert()+gdeimos.numVert()+geuropa.numVert());
    for (size_t i = 0; i < islas.numVert(); i++) {
        if (esCostera(i, cfobos, cdeimos, ceuropa)){
            for (size_t j = 0; j < islas.numVert(); j++) {
                if (esCostera(j, cfobos, cdeimos, ceuropa)) {
                    c1 = buscarCiudad(i, fobos, deimos, europa);
                    c2 = buscarCiudad(j, fobos, deimos, europa);
                    islas[i][j] = distancia(c1, c2);
                }
            }
        }
    }
    
    // FINALMENTE APLICAMOS KRUSKAL Y DIJSTRA AL SUPERGRAFO RESULTANTE 
    islas = Kruskal(islas);
    vector<typename GrafoP<tCoste>::vertice> P = new vector<typename GrafoP<tCoste>::vertice>(islas.numVert());
    std::vector<tCoste> viajes = Dijkstra(islas, origen, P);
    return viajes[destino];
}

template <typename tCoste>
void crearSuperGrafo(GrafoP<tCoste>& supergrafo, const GrafoP<tCoste>& gfobos, const GrafoP<tCoste>& gdeimos, const GrafoP<tCoste>& geuropa) {
    //Ponemos todo a infinito
    for (size_t i = 0; i < supergrafo.numVert(); i++) {
        for (size_t j = 0; j < supergrafo.numVert(); j++) {
            supergrafo[i][j] = GrafoP<tCoste>::INFINITO;
        }
    }

    //Añadimos Fobos
    for (size_t i = 0; i < gfobos.numVert(); i++) {
        for (size_t j = 0; j < gfobos.numVert(); j++) {
            supergrafo[i][j] = gfobos[i][j];
        }
    }
    
    //Añadimos Deimos
    for (size_t i = 0; i < gdeimos.numVert(); i++) {
        for (size_t j = 0; j < gdeimos.numVert(); j++) {
            supergrafo[i+gfobos.numVert()][j+gfobos.numVert()] = gdeimos[i][j];
        }
    }

    //Añadimos Europa
    for (size_t i = 0; i < geuropa.numVert(); i++) {
        for (size_t j = 0; j < geuropa.numVert(); j++) {
            supergrafo[i+gfobos.numVert()+gdeimos.numVert()][j+gfobos.numVert()+gdeimos.numVert()] = geuropa[i][j];
        }
    }
    
}

ciudad buscarCiudad(size_t i, std::vector<ciudad> fobos, std::vector<ciudad> deimos, std::vector<ciudad> europa) {
    if (i < fobos.size()) {
        return fobos[i];
    }

    else if ((i - fobos.size()) < deimos.size()) {
        return deimos[i-fobos.size()];
    }

    else {
        return europa[i - (fobos.size() + deimos.size())];
    }
}

bool esCostera(size_t c, std::vector<bool> cfobos, std::vector<bool> cdeimos, std::vector<bool> ceuropa) {
    if (c < cfobos.size()) {
        return cfobos[c];
    }

    else if ((c - cfobos.size()) < cdeimos.size()) {
        return cdeimos[c-cfobos.size()];
    }

    else {
        return ceuropa[c - (cfobos.size() + cdeimos.size())];
    }
}