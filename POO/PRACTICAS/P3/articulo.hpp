#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "fecha.hpp"
#include "cadena.hpp"
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <locale>

using namespace std;

/*---CLASE ARTÍCULO---*/
class Articulo
{
	private:
		/*--VARIABLES PRIVADAS--*/
		Cadena referencia_;
		Cadena titulo_;
		Fecha f_publi_;
		double precio_;
		unsigned stock_;
		
	public:
		/* --CONSTRUCTOR-- */
		Articulo (const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned s);
		
		/* --FUNCIONES OBSERVADORAS--*/
		Cadena referencia() const	{return referencia_;}
		Cadena titulo() const			{return titulo_;}
		Fecha f_publi() const			{return f_publi_;}
		double precio()const			{return precio_;}
		unsigned stock()const		{return stock_;}
		double& precio()				{return precio_;}
		unsigned& stock()				{return stock_;}
};

/*--FUNCIÓN DE SALIDA--*/
ostream& operator <<(ostream& os, const Articulo& ar) noexcept;

#endif
