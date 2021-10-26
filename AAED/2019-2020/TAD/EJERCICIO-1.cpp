/** EJERCICIO 1 **/
#include <string>
#include "pilavec1.h"

bool testcad(string cad)
{
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