/** EJERCICIO-3 **/

#include "pila2.hpp"

void intercambio(int a, int b, Pila<int> original)
{
	Pila<int> aux;
	Pila<int> aux2;
	int x;
	bool op = false;
	while(!original.vacia())
	{
		if(original.tope() == a && op==false) // Si nos encontramos con la primera coincidencia de a
		{
			do{		// Metemos la secuencia en una pila distinta
				x=original.tope();
				original.pop();
				aux2.push(x);
			}while(x!=b); // Hasta encontrar la primera coincidencia con b
			op=true;
			while(!aux2.vacia()) // Volcamos la secuencia en la pila auxiliar
			{
				aux.push(aux2.tope());
				aux2.pop();
			}
		}
		else // En caso de no ser la secuencia buscada, volcaremos la pila original en una auxiliar principal
		{
			aux.push(original.tope());
			original.pop();
		}
	}

	while(!aux.vacia()) // Una vez terminado, volcamos todo en la pila original, quedando modificada como se requiere
	{
		original.push(aux.tope());
		aux.pop();
	}
}

