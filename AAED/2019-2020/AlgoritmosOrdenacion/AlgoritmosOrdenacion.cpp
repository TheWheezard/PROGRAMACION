/** Algoritmos Ordenacion **/

#include <algorithm>
#include <iterator>

static void burbujea(int* i, int* j);
static void inserta(int* i, int* j);

// Ordenacion por Intercambio Directo

void ordenacion_intercambio(int* p, int* f)
{
	for(int* i = p; i != f-1; ++i)
		burbujea(i,f);
}

// Desciende el minimo del rango (i,j)
// hasta la posicion i
static void burbujea(int* i, int* j)
{
	for(int* k = j-1, *p = k; k != i; --k)
	{
		--p;
		if(*k < *p)
			std::swap(*k, *p);
	}
}

// Ordenacion por Seleccion Directa

void ordenacion_seleccion(int* p, int* f)
{
	for(int* i = p; i != f-1; ++i)
	{
		int* p = std::min_element(i,f);
		std::swap(*i,*p);
	}
}

// Ordenacion por insercion directa

void ordenacion_insercion(int* p, int* f)
{
	for(int* i = p+1; i != f; ++i)
		inserta(p,i);
}

// Insercion ordenada de *j en el rango (i,j)
static void inserta(int* i, int* j)
{
	int x = *j;
	int* p = j - 1;
	while(j != i && x < *p)
		*j-- = *p--;
	*j = x;
}
