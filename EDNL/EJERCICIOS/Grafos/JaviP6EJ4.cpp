#include "..\ImplementacionesEDNL\GrafoP.hpp"
#include "..\ImplementacionesEDNL\matriz.hpp"
#include "..\ImplementacionesEDNL\Dijkstra.hpp"
#include "..\ImplementacionesEDNL\Floyd.hpp"


#include <iostream>
#include <vector>
#include <math.h>

/* Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre
dos ciudades cualesquiera de un país llamado Zuelandia. El problema es sencillo pero
hay que tener en cuenta unos pequeños detalles:
a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas
y por tanto solo permiten un sentido de la circulación.
b) Actualmente Zuelandia es un país en guerra. Y de hecho hay una serie de
ciudades del país que han sido tomadas por los rebeldes, por lo que no pueden
ser usadas para viajar.
c) Los rebeldes no sólo se han apoderado de ciertas ciudades del país, sino que
también han cortado ciertas carreteras, (por lo que estas carreteras no pueden ser
usadas).
d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido
que absolutamente todos los viajes que se hagan por el país pasen por la capital
del mismo, donde se harán los controles de seguridad pertinentes.
Dadas estas cuatro condiciones, se pide implementar un subprograma que dados
• el grafo (matriz de costes) de Zuelandia en situación normal,
• la relación de las ciudades tomadas por los rebeldes,
• la relación de las carreteras cortadas por los rebeldes
• y la capital de Zuelandia,
calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades
zuelandesas en esta situación. */


//GrafoP<tCoste>::vertice capital;
template<typename tCoste>
struct Carretera {
    GrafoP<tCoste>::vertice ciudad1, ciudad2;
    Carretera(GrafoP<tCoste>::vertice a, GrafoP<tCoste>::vertice b): ciudad1(a), ciudad2(b) {}
};

template<typename tCoste>
void costeZuelandia(GrafoP<tCoste>& zuelandia, std::vector<typename GrafoP<tCoste>::vertice> ciudades, std::vector<Carretera<tCoste>> carreteras, typename GrafoP<tCoste>::vertice capital) {
    //Empezamos poniendo a infinito las conexiones desde y hacia las ciudades rebeldes
    for (GrafoP<tCoste>::vertice ciudad : ciudades) {
        for (GrafoP<tCoste>::vertice i = 0; i < zuelandia.numVert(); i++) {
            zuelandia[ciudad][i] = GrafoP<tCoste>::INFINITO;
            zuelandia[i][ciudad] = GrafoP<tCoste>::INFINITO;
        }
    }

    //Ahora hacemos lo mismo, pero con las carreteras cortadas (aristas entre ciudades)
    for (Carretera carretera : carreteras) {
        zuelandia[carretera.ciudad1][carretera.ciudad2] = GrafoP<tCoste>::INFINITO;
    }

    //Crearemos una matriz que contenga los costes de viajar desde cualquier ciudad a la capital y viceversa
    matriz<tCoste> viajeActualizado = new matriz<>;
    matriz<typename GrafoP<tCoste>::vertice> camino2 = new matriz<>; // necesario solo para floyd
    viajeActualizado = Floyd(zuelandia, camino2);

    //Reescribimos el grafo de costes original: los costes serán igual a la suma de viajar de origen a capital y de capital a destino
    for (GrafoP<tCoste>::vertice i = 0; i < zuelandia.numVert(); i++) {
        for (GrafoP<tCoste>::vertice j = 0; j < zuelandia.numVert(); j++) {
            if (i != j) {//si ciudad origen == ciudad destino, no es viaje
                zuelandia[i][j] = viajeActualizado[i][capital] + viajeActualizado[capital][j];
            }
        }
    }
}
