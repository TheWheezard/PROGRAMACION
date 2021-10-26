/** EJERCICIO 2 **/
#include <string>
#include "pilavec1.h"

bool SolucionEjercicio(string);
bool testcad(string cad, int n);

bool testcad(string cad, int n)
{
	int x=0;int z=0;
	while(cad[n]!='#'||n!=cad.length())
	{
		n++;x++;
	}
	string cadA[x];// = nuevacadena()
	while(z<x)
	{
		cadA[z]=cad[z];
		z+=1;
	}
	string cadB[(cadA.length()/2)];
	string cadC[cadB.length()];
	Pila<char> pila(cadA.length()/2);
	int i=0; int j=0;
	while(cadA[i]!='&')		// Introducimos en Pila la primera mitad de la cadena cadA
	{
		pila.push(cadA[i]);
		i++;
	}
	i+=1;
	while(j!=cadC.length()||i!=cadA.length()) // Introducimos el resto de cadA en cadC
	{
		cadC[j]=cadA[i];
		i++;
		j++;
	}
	i=1;
	while(i<cadB.length() || !pila.vacia()) // Volcamos la pila en cadB
	{
		cadB[i]=pila.tope();
		pila.pop();
		i++;
	}

	if (cadA.compare(cadB) == 0) // Comparamos cadB (primera mitad de cadA) con cadC (segunda mitad de cadA)
		return true;
	else return false;
}

bool SolucionEjercicio(string cad)
{
	int n=0;
	bool test=testcad(cad,&n);
	if(test==false||n==cad.length())
		return test;
	else
	{
		n=n+1;
		test=testcad(cad,&n);
	}
}