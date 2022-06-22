#ifndef _SIMBOLO_HPP_
#define _SIMBOLO_HPP_
#include"pila_enla.h"
#include<cassert>
#include<iostream>

/*Especificacion:*/
/*Simbolo():
	·Precondicion:-------.
	·Postcondicion:Crea un Simbolo vacio.
*/
/*void anadirTrazo(const Trazos& T):
	·Precondicion:-------.
	·Postcondicion:Anade el trazo al simbolo.
*/
/*void eliminarTrazos(size_t n):
	·Precondicion:EL numero de trazos es <=n.
	·Postcondicion:Elimina los ultimos n trazos del simbolo.
*/
/*void simetricoX():
	·Precondicion:-------.
	·Postcondicion:Devuelve el Simbolo simetrico por X.
*/
/*void simetricoY():
	·Precondicion:-------.
	·Postcondicion:Devuelve el Simbolo simetrico por Y.
*/
/*void simetricoXY():
	·Precondicion:-------.
	·Postcondicion:Devuelve el Simbolo simetrico por XY.
*/

class Simbolo{
public:
	enum Trazos{D,I,S,B};
	Simbolo();
	void anadirTrazo(const Trazos& T);
	void eliminarTrazos(size_t n);
	void simetricoX();
	void simetricoY();
	void simetricoXY();
	void mostrar()const;
private:
	Pila<Trazos> trazos;
	size_t n_;
};

//Constructor:
Simbolo::Simbolo():n_(0){}

//Funcion anadirTrazo:
void Simbolo::anadirTrazo(const Trazos& T)
{
	trazos.push(T);
	n_++;
}

//Funcion eliminarTrazos:
void Simbolo::eliminarTrazos(size_t n)
{
	assert(n<=n_);
	for(size_t i=0;i<n;i++)
	{
		trazos.pop();
		n_--;
	}
}

//Funcion simetricoX:
void Simbolo::simetricoX()
{
	//Creamos un auxiliar. 
	Pila<Trazos> aux;
	while(!trazos.vacia())
	{
		switch(trazos.tope())
		{
			case Trazos::D:aux.push(Trazos::I);break;
			case Trazos::I:aux.push(Trazos::D);break;
			default:aux.push(trazos.tope());break;
		}
		trazos.pop();
	}
	//Correcta pero inversa, luego desinvertimos.
	while(!aux.vacia())
	{
		trazos.push(aux.tope());
		aux.pop();
	}
}

//Funcion simetricoY:
void Simbolo::simetricoY()
{
	//Creamos un auxiliar. 
	Pila<Trazos> aux;
	while(!trazos.vacia())
	{
		switch(trazos.tope())
		{
			case Trazos::S:aux.push(Trazos::B);break;
			case Trazos::B:aux.push(Trazos::S);break;
			default:aux.push(trazos.tope());break;
		}
		trazos.pop();
	}
	//Correcta pero inversa, luego desinvertimos.
	while(!aux.vacia())
	{
		trazos.push(aux.tope());
		aux.pop();
	}
}

//Funcion simetricoXY:
void Simbolo::simetricoXY()
{
	simetricoX();
	simetricoY();
}

//Funcion mostrar:
void Simbolo::mostrar()const
{
	std::cout << "n= " << n_ << std::endl;
	Pila<Trazos> aux=trazos;
	while(!aux.vacia())
	{
		std::cout << aux.tope() << " ";
		aux.pop();
	}
}



#endif