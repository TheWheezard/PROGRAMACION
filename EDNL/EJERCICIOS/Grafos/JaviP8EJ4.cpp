/*
La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del valle del Jerte (Cáceres). Calcula qué canales 
y de qué longitud deben construirse partiendo del grafo con las distancias entre las ciudades y asumiendo las siguientes premisas:

- el coste de abrir cada nuevo canal es casi prohibitivo, luego la solución final debe tener un número mínimo de canales.

- el Ministerio de Fomento nos subvenciona por Kms de canal, luego los canales deben ser de la longitud máxima posible.
*/

#include "Kruskal.hpp"
#include "GrafoP.hpp"

template<typename distancia>
void invertir(GrafoP<distancia>& g){
    for (size_t i = 0; i < g.numVert(); ++i)
        for (size_t j = 0; j < g.numVert(); ++j)
            if (g[i][j] != GrafoP<distancia>::INFINITO)
                g[i][j] *= -1;
}

template<typename distancia>
GrafoP<distancia> canales(GrafoP<distancia> G){
    GrafoP<distancia> aux(G);
    invertir(aux);
    aux = Kruskal(aux);
    invertir(aux);
    return aux;
}

