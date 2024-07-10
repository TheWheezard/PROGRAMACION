/*
El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas,
Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2
ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2 ). Se dispone de las coordenadas
cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. El huracán
Isadore acaba de devastar el archipiélago, con lo que todas las carreteras y puentes
construidos en su día han desaparecido. En esta terrible situación se pide ayuda a la
ONU, que acepta reconstruir el archipiélago (es decir volver a comunicar todas las
ciudades del archipiélago) siempre que se haga al mínimo coste.
 De cara a poder comparar costes de posibles reconstrucciones se asume lo
siguiente:
1. El coste de construir cualquier carretera o cualquier puente es proporcional a su
longitud (distancia euclídea entre las poblaciones de inicio y fin de la carretera o
del puente).
2. Cualquier puente que se construya siempre será más caro que cualquier carretera
que se construya.
 De cara a poder calcular los costes de VIAJAR entre cualquier ciudad del
archipiélago se considerará lo siguiente:
1. El coste directo de viajar, es decir de utilización de una carretera o de un puente,
coincidirá con su longitud (distancia euclídea entre las poblaciones origen y
destino de la carretera o del puente).
 En estas condiciones, implementa un subprograma que calcule el coste mínimo
de viajar entre dos ciudades de Grecoland, origen y destino, después de haberse
reconstruido el archipiélago, dados los siguientes datos:
1. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
2. Lista de ciudades de Deimos representadas mediante sus coordenadas
cartesianas.
3. Lista de ciudades costeras de Fobos.
4. Lista de ciudades costeras de Deimos.
5. Ciudad origen del viaje.
6. Ciudad destino del viaje. 
*/
#include <vector>
#include <set>
#include <cmath>
#include "Kruskal.hpp"
#include "Dijkstra.hpp"
#include "particion.hpp"
#include "GrafoP.hpp"

struct coordenadas{
    double x,y;
    coordenadas(double x_=0.0, double y_=0.0):x(x_), y(y_){}
};

template <typename tCoste>
double distancia(coordenadas ciudad1, coordenadas ciudad2){
    return sqrt(pow(ciudad1.x-ciudad2.x,2) + pow(ciudad1.y-ciudad2.y,2));
}

template <typename tCoste>
tCoste caminoCorto(std::vector<coordenadas> Fobos, std::vector<coordenadas> Deimos, 
std::set<coordenadas> costeras_Fobos, std::set<coordenadas> costeras_Deimos, 
typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino){
    GrafoP<tCoste> islas(Fobos.size()+Deimos.size());
    //unimos las ciudades de cada isla entre sí por carretera
    for(size_t i=0; i < Fobos.size(); ++i){
        for(size_t j=0; j < Fobos.size(); ++j){
            islas[i][j] = distancia(Fobos[i], Fobos[j]);
        }
    }
    for(size_t i=Fobos.size(); i < islas.numVert(); ++i){
        for(size_t j=Fobos.size(); j < islas.numVert(); ++j){
            islas[i][j] = distancia(Deimos[i-Fobos.size()], Deimos[j-Fobos.size()]);
        }
    }
    //colocamos los puentes de las ciudades costeras
    for(size_t i=0; i < Fobos.size(); ++i){
        for(size_t j=Fobos.size(); j < islas.numVert(); ++j){
            if(costeras_Fobos.find(Fobos[i]) && costeras_Deimos.find(Deimos[j-Fobos.size()])){ // si ambas son costeras (en sus islas)
                islas[j][i] = islas[i][j] = distancia(Fobos[i], Deimos[j-Fobos.size()]); //trazamos la distancia del puente en ambos sentidos
            }
        }
    }
    islas = Kruskal(islas);
    std::vector<GrafoP<tCoste>::vertice> caminos;
    std::vector<tCoste> viaje = Dijkstra(islas, origen, caminos);
    return caminos[destino];
}