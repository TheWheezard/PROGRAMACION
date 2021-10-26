#ifndef TARJETA_HPP
#define TARJETA_HPP
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "usuario.hpp"

using namespace std;

class Usuario;
class Clave;

/***CLASE NUMERO***/
class Numero{
private:
	Cadena numero_;
public:
	enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
	/*CONSTRUCTOR*/
	Numero (const Cadena&);
		
	/*OPERADOR*/
	operator const char*()const{return numero_.c_str();}
	
	/*GETER*/
	const Cadena& num() const{return numero_;}

	/*DESTRUCTOR*/
	~Numero(); 
		
	/**CLASE INCORRECTO**/
	class Incorrecto{
	public:	
		/*CONSTRUCTOR*/
		Incorrecto(const Numero::Razon r);
		/*GETER*/
		Numero::Razon razon()const{return r_;}
	private:
		Numero::Razon r_;
	};
};

/*FUNCION eliminar*/
void eliminarChar(Cadena& cad, size_t pos);


/***CLASE TARJETA***/
class Tarjeta{
public:
	enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

	/*CONSTRUCTORES*/
	Tarjeta(const Numero& n, Usuario& usuario, const Fecha& caducidad);
	Tarjeta (const Tarjeta& that)=delete;
	Tarjeta& operator=(const Tarjeta &)=delete;
		
	/*GETERS*/
	const Tarjeta::Tipo& tipo() const {return tipo_;}
	const Numero& numero() const {return numero_;}
	Usuario* titular() const {return usuario_;}
	const Fecha& caducidad() const {return caducidad_;}
	const bool activa()const {return activa_;}

	bool &activa(bool a=true);

	/*DESTRUCTOR*/
	~Tarjeta();		

	/**CLASE CADUCADA**/
	class Caducada{
	public:
		/*CONSTRUCTOR*/
		Caducada(const Fecha& f);
		/*GETER*/
		const Fecha& cuando()const{return fecha_caducada;}
	private:
		Fecha fecha_caducada;
	};
		
	/**CLASE NUM_DUPLICADO**/
	class Num_duplicado{
	public:
		/*CONSTRUCTOR*/
		Num_duplicado(const Numero&);
		/*GETER*/
		const Numero& que()const{return numer_;}
	private:
		Numero numer_;
	};
	
	/**CLASE DESACTIVADA**/
	class Desactivada{
	public:
		/*CONSTRUCTOR*/
		Desactivada();
	private:
	};
	
	/*FUNCIONES DE TARJETA*/
	void anula_titular();
	Tipo esTipo();
	
	/*OPERADOR DE SALIDA*/
	friend ostream& operator<<(ostream& os, const Tarjeta& t);

private:
	Numero numero_; 		//numero troquelado
	Usuario* const usuario_;	//su titular
	Fecha caducidad_;		//caducidad
	bool activa_;	//1==activa; 0==no
	Tipo tipo_;		//tipo de tarjeta
};

/*OPERADORES DE SALIDA*/
ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo);

/*OPERADORES LOGICOS*/
bool operator <(const Numero& a, const Numero& b);
bool operator <(const Tarjeta& a, const Tarjeta& b);
bool operator >(const Tarjeta& a, const Tarjeta& b);

#endif //FIN_TARJETA_HPP
