/**
 * @file JaviP7EJ3.cpp
 * @author Javier López Sierra
 * @brief Ejercicio 3 de grafos, práctica 7. Guardar producto en almacenes con diferentes beneficios.
 * @version 0.1
 * @date 2023-09-11
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


/* Eres el orgulloso dueño de una empresa de distribución. Tu misión radica en
distribuir todo tu stock entre las diferentes ciudades en las que tu empresa dispone de
almacén.
Tienes un grafo representado mediante la matriz de costes, en el que aparece el coste
(por unidad de producto) de transportar los productos entre las diferentes ciudades del
grafo.
Pero además resulta que los Ayuntamientos de las diferentes ciudades en las que
tienes almacén están muy interesados en que almacenes tus productos en ellas, por lo
que están dispuestos a subvencionarte con un porcentaje de los gastos mínimos de
transporte hasta la ciudad. Para facilitar el problema, consideraremos despreciables los
costes de volver el camión a su base (centro de producción).
He aquí tu problema. Dispones de
 el centro de producción, nodo origen en el que tienes tu producto (no tiene
almacén),
 una cantidad de unidades de producto (cantidad),
 la matriz de costes del grafo de distribución con N ciudades,
 la capacidad de almacenamiento de cada una de ellas,
 el porcentaje de subvención (sobre los gastos mínimos) que te ofrece cada
Ayuntamiento.
Las diferentes ciudades (almacenes) pueden tener distinta capacidad, y además la
capacidad total puede ser superior a la cantidad disponible de producto, por lo que
debes decidir cuántas unidades de producto almacenas en cada una de las ciudades.
Debes tener en cuenta además las subvenciones que recibirás de los diferentes
Ayuntamientos, las cuales pueden ser distintas en cada uno y estarán entre el 0% y el
100% de los costes mínimos.
La solución del problema debe incluir las cantidades a almacenar en cada ciudad bajo
estas condiciones y el coste mínimo total de la operación de distribución para tu
empresa.*/

typedef int tCoste;

template <typename tCoste>
tCoste almacenes_subvenciones(typename GrafoP<tCoste>::nodo origen, size_t cantidadTotal, matriz<tCoste>& ciudades, const std::vector<size_t>& capacidadCiudades, const std::vector<double>& subvencionCiudades, std::vector<size_t>& cantidadCiudades) {
    GrafoP<tCoste> gCiudades = GrafoP<tCoste>(ciudades.dimension());
    // Creo que esto me falta primero: calcular las subvenciones antes de crear el grafo
    for (size_t i = 0; i < ciudades.dimension(); i++) {
        for (size_t j = 0; j < ciudades.dimension(); j++) { // he añadido '- ciudades[i][j] * subvencionCiudades[j]' para calcular el valor con subvención
            gCiudades[i][j] = ciudades[i][j] - ciudades[i][j] * subvencionCiudades[j];
        }
    }
    tCoste coste = 0;
    std::vector<GrafoP<tCoste>::vertice>& P;
    std::vector<tCoste> viaje = Dijkstra(gCiudades, origen, P);
    //calcular_subvencion(viaje, subvencionCiudades);
    size_t cont = viaje.size(); //contador de ciudades sin visitar
    while (cantidadTotal > 0 && cont > 0) {
        size_t destino = devolver_minimo(viaje);
        coste += viaje[destino];
        almacenar_producto(cantidadTotal, destino, capacidadCiudades[destino], cantidadCiudades);
        if (capacidadCiudades[destino] == cantidadCiudades[destino]) //si el almacén está lleno, no podemos utilizar más la ciudad
            viaje[destino] = GrafoP<tCoste>::INFINITO; // equivale a marcar como utilizado el almacén
        cont--;
    }
    return coste;
}

template <typename tCoste>
void calcular_subvencion(std::vector<tCoste>& costes, const std::vector<double>& subvencionCiudades) {
    for (size_t i = 0; i < costes.size(); i++) {
        costes[i] -= costes[i] * (subvencionCiudades[i]); //asumimos que subvencionCiudades[i] es x/100
    }
}

template <typename tCoste>
size_t devolver_minimo(std::vector<tCoste>& costes) {
    size_t min = 0;
    size_t cont = 0;
    while (cont < costes.size()) {
        if (costes[cont] < costes[min])
            min = cont;
        cont++;
    }
    return min;    
}

void almacenar_producto(size_t& cantidadTotal, size_t ciudad, size_t capacidad, std::vector<size_t>& cantidadCiudades) {
    if (cantidadTotal >= capacidad) {
        cantidadCiudades[ciudad] = capacidad;
        cantidadTotal -= capacidad;
    }
    else { // if(cantidadTotal < capacidad)
        cantidadCiudades[ciudad] = capacidad - cantidadTotal;
        cantidadTotal = 0;
    }
}