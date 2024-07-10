#include "../ImplementacionesEDNL/GrafoP.hpp"
#include "../ImplementacionesEDNL/Dijkstra.hpp"
#include "../ImplementacionesEDNL/Kruskal.hpp"
#include "../ImplementacionesEDNL/particion.hpp"
#include "../ImplementacionesEDNL/matriz.hpp"
#include <math.h>
#include <vector>
#include <set>

/* El archipiélago de Tombuctú2 está formado por un número desconocido de islas,
cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales
tienen en común que todas y cada una de ellas dispone de un aeropuerto. Sí que se
conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo).
Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la
opción de comunicación más económica de implantar será el avión.
Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las
ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se
indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. El
objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para
poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:
1) Se implantará una y sólo una línea aérea entre cada par de islas.
2) La línea aérea escogida entre cada par de islas será la más corta entre todas
las posibles.
Así pues, dados los siguientes datos:
• Lista de ciudades de Tombuctú2 representada cada una de ellas por sus
coordenadas cartesianas.
• Matriz de adyacencia de Tombuctú que indica las carreteras existentes en
dicho archipiélago,
Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para
comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente
expuestos. */

struct ciudad {
    int x, y;
    ciudad(int a, int b): x(a), y(b) {}
};
bool operator==(ciudad a, ciudad b) {
    return a.x == b.x && a.y == b.y;
}

struct linea_aerea {
    ciudad a, b;
    int dist;
    linea_aerea(ciudad c1, ciudad c2): a(c1), b(c2) {
        dist = distancia(a, b);
    }
};
bool operator==(linea_aerea c1, linea_aerea c2) {
    return c1.a == c2.a && c1.b == c2.b;
}
bool operator<(linea_aerea c1, linea_aerea c2) {
    return c1.dist < c2.dist;
}

// Recibe un vector de ciudades (con sus coordenadas) y una matriz que marca qué carreteras existen y entre qué ciudades
// Devuelve un vector con las líneas aéreas mínimas necesarias para conectar todas las islas, con la distancia más corta posible
template<typename T>
std::vector<linea_aerea> lineasAereasTombuctu(std::vector<ciudad>& ciudades, matriz<bool>& carreteras) {
    //Creamos una partición con todas las ciudades, y las agrupamos por islas
    Particion islas = new Particion(carreteras.dimension());
    for (size_t i = 0; i < carreteras.dimension(); i++) {
        for (size_t j = 0; j < carreteras.dimension(); j++) {
            if (carreteras[i][j] && islas.encontrar(i) != islas.encontrar(j)) { //si hay carretera y aún no están unidas
                islas.unir(encontrar(i), encontrar(j));
            }
        }
    }

    //Creamos un set (contenedor ordenado) y lo rellenamos con todas las posibles líneas aéreas
    std::set<linea_aerea> lineasAux = new std::set<linea_aerea>();
    for (size_t i = 0; i < carreteras.dimension(); i++) {
        for (size_t j = 0; j < carreteras.dimension(); j++) {
            if (!carreteras[i][j]) //si no hay carretera entre las ciudades, lo añadimos como posible línea aérea
                lineasAux.insert(new linea_aerea(ciudades[i], ciudades[j]));
        }
    }

    //Creamos el vector que contendrá el resultado: las líneas aéreas de menor distancia que unan las diferentes islas
    std::vector<linea_aerea> lineasRes = new std::vector<linea_aerea>();
    std::set<linea_aerea>::iterator iter = lineasAux.begin();
    while (es_bosque(islas, carreteras.dimension) && iter != lineasAux.end()) {//mientras haya islas sin unir, y no lleguemos al final
        if (islas.encontrar(iter->a) != islas.encontrar(iter->b)) { //si las ciudades de la línea aérea aún están en distintos conjuntos
            lineasRes.push_back(*iter); //añadimos la línea aérea como parte de la solución
            islas.unir(iter->a, iter->b); // y unimos los conjuntos de las ciudades
        }
        iter++;
    }

    return lineasRes;
}

// Recibe una partición, y un entero que determina su tamaño
// Devuelve true si existe más de un conjunto en la partición, false si solo hay un único conjunto
bool es_bosque(Particion p, int tam) {
    bool check = false;
    int i = 0;
    while (i < tam && !check) {
        int j = 0;
        while (j < tam && !check) {
            if (p.encontrar(i) != p.encontrar(j))
                check = true;
            j++;
        }
        i++;
    }
    return check;
}

// Recibe dos ciudades
// Devuelve la distancia entre ambas de acuerdo a sus coordenadas cartesianas
int distancia(ciudad c1, ciudad c2) {
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}