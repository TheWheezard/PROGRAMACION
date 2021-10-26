#include <iostream>
#include "pila2.hpp"


using namespace std;
void intercambio(int,int,Pila<int>);
int main()
{
	int vectorIni[19] = {4,7,8,9,9,1,8,6,7,9,6,2,4,8,9,3,2,1,0};
	int vectorRes[19] = {4,7,8,9,9,2,6,9,7,6,8,1,4,8,9,3,2,1,0};
	int i = 0;
	bool test = true;
	Pila<int> pila;
	cout<<"INTRODUCIENDO EN LA PILA:"<<endl;
	while(i<19)
	{
		pila.push(vectorIni[i]);
		cout<<pila.tope()<<endl;
		i++;
	}
	intercambio(1, 2, pila);
	cout<< "PILA  VS  VECTOR"<<endl;
	for(i=0; i<19; i++)
	{
		if(pila.tope() != vectorRes[i])
			test = false;
		cout<<pila.tope()<<"      "<<vectorRes[i]<<endl;
		pila.pop();
	}
	if(test == false)
		cout<<"ALGO HA FALLADO"<<endl;
	else
		cout<<"TODO VA BIEN"<<endl;
	return 0;
}
/** EJERCICIO-3 **/

#include "pila2.hpp"

void intercambio(int a, int b, Pila<int> original)
{
	Pila<int> aux;
	Pila<int> aux2;
	int x;
	bool op = false;
	cout<<"bucle interno"<<endl;
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
				cout<<aux.tope()<<"    aux2"<<endl;
				aux2.pop();
			}
		}
		else // En caso de no ser la secuencia buscada, volcaremos la pila original en una auxiliar principal
		{
			aux.push(original.tope());
			cout<<aux.tope()<<"     original"<<endl;
			original.pop();
		}
	}

	while(!aux.vacia()) // Una vez terminado, volcamos todo en la pila original, quedando modificada como se requiere
	{
		original.push(aux.tope());
		cout<<"fin_bucle"<<endl;
		aux.pop();
	}
	//return original;
}
