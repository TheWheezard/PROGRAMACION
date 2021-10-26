#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <iostream>
#include <string.h>
#include <random>
#include <stdlib.h>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>

using namespace std;

//Declaramos clases que usaremos en la clase clave
class Numero;
class Tarjeta;

/***CLASE CLAVE***/
class Clave{
private:
	Cadena pass_c;
public:
	/*CONSTRUCTOR*/
	Clave(const char*);

	/*CONSTANTE*/
	enum Razon{CORTA, ERROR_CRYPT};

	/*GETER*/
	Cadena clave() const{return pass_c;}
		
	/*FUNCION*/
	bool verifica (const char*) const;
		
	/**CLASE INCORRECTA**/
	class Incorrecta{
	public:
		/*CONSTRUCTOR*/
		Incorrecta(const Clave::Razon r);
		/*GETER*/
		Clave::Razon razon() const{return r_;}
	private:
		Clave::Razon r_;
	};
		
	/*DESTRUCTOR*/
	~Clave();
};

/***CLASE USUARIO***/
class Usuario{
private:
	Cadena ID_, nombre_, apell_, direcc_;
	Clave pass_;
	Tarjeta tarjetas_;
	Articulo articulos_;
	size_t n_articulos_;
	static unordered_set<Cadena> registrados;
public:
	/*CONSTRUCTORES*/
	Usuario(const Cadena& _id, const Cadena& _nomb, const Cadena& _apell, const Cadena& _direcc, const Clave& _pass);
	Usuario(const Usuario& that) = delete;
	Usuario& operator=(const Usuario &)=delete;
		
	/*CONSTANTES*/
	typedef map<Numero,Tarjeta*> Tarjetas;
	typedef unordered_map<Articulo*,unsigned> Articulos;
		
	/**CLASE ID_DUPLICADO**/
	class Id_duplicado
	{
	public:
		/*CONSTRUCTOR*/
		Id_duplicado(const Cadena&);
		/*GETER*/
		const Cadena& idd() const{return idd_;}
	private:
		Cadena idd_;
	};
		
	/*GETERS*/
	const Cadena& id() const noexcept {return ID_;}
	const Cadena& nombre() const noexcept {return nombre_;}
	const Cadena& apellidos() const noexcept {return apell_;}
	const Cadena& direccion() const noexcept {return direcc_;}
	const Tarjetas& tarjetas() const noexcept {return tarjetas_;}
	const size_t n_articulos() const noexcept {return n_articulos_;}
	const Articulos& compra() const noexcept {return articulos_;}
			
	/*FUNCIONES USUARIO*/
	void es_titular_de (const Tarjeta&);			//Para asociar una tarjeta
	void no_es_titular_de(Tarjeta&);				//Para desasociar una tarjeta
	void compra(const Articulo&a, size_t cant=1);
		
	/*FLUJO DE SALIDA*/
	friend ostream& operator << (ostream& os, const Usuario &u) noexcept;
		
	/*DESTRUCTOR*/
	~Usuario();
};

/*OPERADORES*/
void mostrar_carro(ostream&os, const Usuario& u);


#endif
