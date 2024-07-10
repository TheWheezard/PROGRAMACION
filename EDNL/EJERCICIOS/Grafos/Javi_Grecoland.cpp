#include "..\ImplementacionesEDNL\Grafo.hpp"
#include "..\ImplementacionesEDNL\GrafoP.hpp"

#include <iostream>
#include <vector>
#include <math.h>

/*
El archipiélago de Grecoland (Nozuelandia) está formado únicamente por tres islas, Fobos, Deimos 
y Europa que tienen N1, N2 y N3 ciudades, respectivamente, todas ellas costeras.

Se dispone de la relación de ciudades de cada una de las tres islas, representadas por sus coordenadas cartesianas.

Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland. 

Las condiciones del programa COMUNICA indican que se sufragarán todos los costes de construcción 
de las comunicaciones (carreteras y puentes) al menor coste posible.

Se sabe que la construcción de cualquier puente es más cara que la de cualquier carretera. 

También es conocido que el coste de construcción de una carretera o de un puente es proporcional a su longitud.
En estas condiciones se debe calcular (mediante una función) qué carreteras y puentes deben 
construirse para comunicar entre sí todas las ciudades de Grecoland, dados los siguientes datos:

1.	Relación de ciudades de Fobos, representadas mediante sus coordenadas cartesianas.
2.	Relación de ciudades de Deimos, representadas mediante sus coordenadas cartesianas.
3.	Relación de ciudades de Europa, representadas mediante sus coordenadas cartesianas.



PLANTEAMIENTO

Colocar carreteras entre todas las ciudades de cada isla (ditancia*precio_carretera)

Colocar puentes entre todas las ciudades que pertenecen a islas diferentes (distancia*precio_puente)

Una vez que todas las ciudades estan conectadas aplicar Kruskal para obtener un solo camino minimo que una 
todas las ciudades.

*/

typedef double tCoste;
struct tipo_coordenada {
public:
	double latitud;
	double longitud;
	bool operator==(tipo_coordenada aux) { return (this->latitud == aux.latitud && this->longitud == aux.longitud); }
};
std::vector<tipo_coordenada> vFobos, vDeimos, vEuropa;

double distancia(tipo_coordenada a, tipo_coordenada b) {
	double dLatitud = abs(a.latitud - b.latitud);
	double dLongitud = abs(a.longitud - b.longitud);
	return sqrt(pow(dLatitud, 2) + pow(dLongitud, 2));
}

bool pertenece(std::vector<tipo_coordenada> isla, tipo_coordenada ubicacion) {
	bool res = false;
	for (size_t i = 0; i < isla.size(); ++i) {
		if (isla[i] == ubicacion) {
			res = true;
		}
	}
	return res;
}

bool misma_isla(std::vector<tipo_coordenada> Fobos, std::vector<tipo_coordenada> Deimos, std::vector<tipo_coordenada> Europa, tipo_coordenada isla1, tipo_coordenada isla2) {
	if (pertenece(Fobos, isla1) && pertenece(Fobos, isla2)) {
		return true;
	}
	else if (pertenece(Deimos, isla1) && pertenece(Deimos, isla2)) {
		return true;
	}
	else if (pertenece(Europa, isla1) && pertenece(Europa, isla2)) {
		return true;
	}
	else return false;
}

template <typename tCoste>
GrafoP<tCoste> comunica(std::vector<tipo_coordenada> vFobos, std::vector<tipo_coordenada> vDeimos, std::vector<tipo_coordenada> vEuropa, double costeFijoPuente, double costeFijoCarretera, double costeVarPuente, double costeVarCarretera) {
	std::vector<tipo_coordenada> vGrecoland;
	vGrecoland.insert(vGrecoland.end(), vFobos.begin(), vFobos.end());
	vGrecoland.insert(vGrecoland.end(), vDeimos.begin(), vDeimos.end());
	vGrecoland.insert(vGrecoland.end(), vEuropa.begin(), vEuropa.end());

	GrafoP<tCoste> gGrecoland(vGrecoland.size());
	GrafoP<tCoste> arbolRec(vGrecoland.size());

	for (size_t i = 0; i < gGrecoland.numVert(); ++i) {
		for (size_t j = 0; j < gGrecoland.numVert(); ++j) {
			if (misma_isla(vFobos, vDeimos, vEuropa, gGrecoland[i], gGrecoland[j])) {
				gGrecoland[i][j] = costeFijoCarretera + costeVarCarretera * distancia(gGrecoland[i], gGrecoland[j]);
			}
			else {
				gGrecoland[i][j] = costeFijoPuente + costeVarPuente * distancia(gGrecoland[i], gGrecoland[j]);
			}
		}
	}

	arbolRec = Kruskal(gGrecoland);
	return arbolRec;
}
