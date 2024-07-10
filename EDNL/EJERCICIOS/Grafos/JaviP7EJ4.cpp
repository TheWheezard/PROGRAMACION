/**
 * @file JaviP7EJ4.cpp
 * @author Javier López Sierra
 * @brief Grafos, Práctica 7, Ejercicio 4, Cementos de Zuelandia.
 * @version 0.1
 * @date 2023-09-12
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

/* Eres el orgulloso dueño de la empresa “Cementos de Zuelandia S.A”. Empresa
dedicada a la fabricación y distribución de cemento, sita en la capital de Zuelandia. Para
la distribución del cemento entre tus diferentes clientes (ciudades de Zuelandia)
dispones de una flota de camiones y de una plantilla de conductores zuelandeses.
El problema a resolver tiene que ver con el carácter del zuelandés. El zuelandés es
una persona que se toma demasiadas “libertades” en su trabajo, de hecho, tienes
fundadas sospechas de que tus conductores utilizan los camiones de la empresa para
usos particulares (es decir indebidos, y a tu costa) por lo que quieres controlar los
kilómetros que recorren tus camiones.
Todos los días se genera el parte de trabajo, en el que se incluyen el número de
cargas de cemento (1 carga = 1 camión lleno de cemento) que debes enviar a cada
cliente (cliente = ciudad de Zuelandia). Es innecesario indicar que no todos los días hay
que enviar cargas a todos los clientes, y además, puedes suponer razonablemente que tu
flota de camiones es capaz de hacer el trabajo diario.
Para la resolución del problema quizá sea interesante recordar que Zuelandia es un
país cuya especial orografía sólo permite que las carreteras tengan un sentido de
circulación.
Implementa una función que dado el grafo con las distancias directas entre las
diferentes ciudades zuelandesas, el parte de trabajo diario, y la capital de Zuelandia,
devuelva la distancia total en kilómetros que deben recorrer tus camiones en el día, para
que puedas descubrir si es cierto o no que usan tus camiones en actividades ajenas a la
empresa.*/

typedef double tCoste; // serán las distancias en km
typedef typename GrafoP<tCoste>::vertice vertice;

template <typename tCoste>
tCoste distancia_total_trabajo(GrafoP<tCoste>& distancias, vertice capital, std::vector<vertice> parteTrabajo) {
    std::vector<vertice>& P;
    std::vector<tCoste> distTrabajos = Dijkstra(distancias, capital, P);
    tCoste res = 0;
    for (vertice i = 0; i < distTrabajos.size(); i++) {
        res += distTrabajos[i] * parteTrabajo[i]; // Distancia por nº de cargas que llevar (si no hay cargas es d·0)
    }

    return res;
}