/*
La nueva compañía de telefonía RETEUNI3 tiene que conectar entre sí, con fibra
óptica, todas y cada una de las ciudades del país. Partiendo del grafo que representa las
distancias entre todas las ciudades del mismo, implementad un subprograma que
calcule la longitud mínima de fibra óptica necesaria para realizar dicha conexión
*/
/*Necesitamos conocer el mínimo de aristas necesario para conectar todas las ciudades entre sí, el resultado final será la suma de todas ellas*/

#include "GrafoP.hpp"
#include "Kruskal.hpp"

double longitudMinima(GrafoP<double>& ciudades){
    GrafoP<double> aux = Kruskal(ciudades);
    double res = 0;
    for (size_t i = 0; i < ciudades.numVert(); ++i){
        for (size_t j = 0; j < ciudades.numVert(); ++j){
            if(aux[i][j] != GrafoP<double>::INFINITO){
                res += aux[i][j];
                aux[j][i] = GrafoP<double>::INFINITO; // si lo pongo a infinito, cuando llegue a ese valor (que ya he contado de ida), lo descarto
            }
        }
    }
    return res;
}