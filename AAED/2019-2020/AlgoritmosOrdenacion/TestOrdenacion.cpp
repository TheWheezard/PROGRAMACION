#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "AlgoritmosOrdenacion.hpp"
#include "cronometro.hpp"


bool ordenado(int*,int);
int aleatorio(int*,int);

int main() 
{
	using namespace std;
	cronometro c;
	for(int n=1;n<10;n++) // Por cada iteracion de n, el vector V[n] crece en un elemento (empezando con V[1] hasta V[9])
	{
		int i;
		int V[n]; // Creamos un vector que tendra la secuencia (alterada) y no es modificado
		int A[n]; // Este vector sera reordenado por los algoritmos, y reinicializado con V
		int m=n;  // Como pasaremos A[m] con m por referencia, necesitamos evitar que el tamano luego sea alterado, m sera igualado a n cada vez que A sea reordenado
		double t; // tiempo
		for(int i=0;i<n;i++)
		{
			V[i] = i+1;	//Rellenamos V 
		}
		aleatorio(V,n); // Y lo desordenamos
		
		// Ordenacion por Intercambio Directo
		for(i=0;i<n;i++)
		{
			A[i] = V[i]; // Metemos el vector desordenado en A 
		}
		c.activar();
		ordenacion_intercambio(A,&m); // Se ordena por intercambio
		c.parar();
		t = c.tiempo();
		if(ordenado(A,n) == true)
			cout << "Intercambio Directo correcto en: " << t << endl; //Comprobamos si esta ordenado y el tiempo que tarda
		
		cout << " VECTOR[ ";
		for(i=0;i<n;i++)
		{
			cout << A[i] << " "; // Imprime vector ordenado para comprobacion visual
		}
		cout << "]" << endl;
		
		// Ordenacion por Seleccion Directa
		m=n;
		for(i=0;i<n;i++)
		{
			A[i] = V[i]; // Metemos el vector desordenado en A
		}
		c.activar();
		ordenacion_seleccion(A,&m); // Se ordena por seleccion
		c.parar();
		t = c.tiempo();
		if(ordenado(A,n) == true)
			cout << "Seleccion Directa correcto en: " << t << endl; //Comprobamos si esta ordenado y el tiempo que tarda
		
		cout << " VECTOR[ ";
		for(i=0;i<n;i++)
		{
			cout << A[i] << " "; // Imprime vector ordenado para comprobacion visual
		}
		cout << "]" << endl;

		// Ordenacion por insercion directa
		m=n;
		for(i=0;i<n;i++)
		{
			A[i] = V[i]; // Metemos el vector desordenado en A
		}
		c.activar();
		ordenacion_insercion(A,&m);
		c.parar();
		t = c.tiempo();
		if(ordenado(A,n) == true)
			cout << "Insercion Directa correcto en: " << t << endl; //Comprobamos si esta ordenado y el tiempo que tarda
		
		cout << " VECTOR[ ";
		for(i=0;i<n;i++)
		{
			cout << A[i] << " "; // Imprime vector ordenado para comprobacion visual
		}
		cout << "]" << endl;
	}
	return 0;
}


int aleatorio (int *A, int n) //reordena de forma aleatoria el vector que se le entrega (por referencia)
{
	using namespace std;
	
	int i;
	const size_t x = sizeof A / sizeof *A;
	random_shuffle(A, A + x);
	cout << endl;
	cout << " VECTOR[ ";
	for(i=0;i<n;i++)
	{
		cout << A[i] << " "; // Imprime el vector desordenado
	}
	cout << "]" << endl;

}

bool ordenado(int *A, int n) //Comprueba si el vector está ordenado
{
	int i=1;
	bool x=true;
	while(i < n && x != false)
	{
		if(A[i]<A[i-1])
			x = false;
		i += 1;
	}
	return x;
}

