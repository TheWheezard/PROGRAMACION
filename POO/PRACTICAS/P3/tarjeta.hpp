#ifndef TARJETA_HPP
#define TARJETA_HPP
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "usuario.hpp"

using namespace std;

class Usuario;
class Clave;

/*---CLASE NUMERO---*/
class Numero
{
	private:
		/*--VARIABLES PRIVADAS--*/
		Cadena numero_;
		
	public:
		/*--CONSTANTES--*/
		enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
		
		/*--CONSTRUCTORES--*/
		Numero (const Cadena&);
		
		/*--OPERADOR--*/
		operator const char*()const;

		/*--OBSERVADOR--*/
		const Cadena& num() const{return numero_;}

		/*--DESTRUCTOR--*/
		~Numero(); 
		
		/*---CLASE INCORRECTO (dentro de numero para excepciones)---*/
		class Incorrecto
		{
			public:	
				/*--CONSTRUCTOR--*/
				Incorrecto(const Numero::Razon r);

				/*--OBSERVADORA--*/
				Numero::Razon razon() const;
			
			private:
				/*--VARIABLES PRIVADAS--*/
				Numero::Razon r_;
		};
};

/*--FUNCION FUERA DE CLASE--*/
void eliminarChar(Cadena& cad, size_t pos);


/*---CLASE TARJETA---*/
class Tarjeta
{
	public:
		/*--CONSTANTE--*/
		enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
		
		/*--CONSTRUCTORES--*/
		Tarjeta(const Numero& n, Usuario& usuario, const Fecha& caducidad);
		Tarjeta (const Tarjeta& that)=delete;
		Tarjeta& operator=(const Tarjeta &)=delete;
		
		/*--OBSERVADORES--*/
		const Tarjeta::Tipo& tipo() const		{return tipo_;}
		const Numero& numero() const		{return numero_;}
		Usuario* titular() const				{return usuario_;}
		const Fecha& caducidad() const		{return caducidad_;}
		const bool activa()const				{return activa_;}

		bool &activa(bool a=true);

		/*--DESTRUCTOR--*/
		~Tarjeta();		

		/*---CLASE CADUCADA (dentro de tarjeta para excepciones)---*/
		class Caducada
		{
			public:
				/*--CONSTRUCTOR--*/
				Caducada(const Fecha& f);

				/*--OBSERVADORA--*/
				const Fecha& cuando()const{return fecha_caducada;}
		
			private:
				/*--VARIABLES PRIVADAS--*/
				Fecha fecha_caducada;
		};
		
		/*--CLASE NUM_DUPLICADO (dentro de tarjeta)--*/
		class Num_duplicado
		{
			public:
				/*--CONSTRUCTOR--*/
				Num_duplicado(const Numero&);

				/*--OBSERVADORA--*/
				const Numero& que()const;

			private:
				/*--VARIABLES PRIVADAS--*/
				Numero numer_;
		};
	
		/*---CLASE DESACTIVADA (dentro de tarjeta)---*/
		class Desactivada
		{
			public:
				/*--CONSTRUCTOR--*/
				Desactivada();
			private:
		};
	
		/*--FUNCIONES DE LA CLASE TARJETA--*/
		void anula_titular();
		Tipo esTipo();
		
		/*--OPERADOR DE SALIDA--*/
		friend ostream& operator<<(ostream& os, const Tarjeta& t);

	private:
		/*--VARIABLES--*/
		Numero numero_; 			//numero troquelado
		Usuario* const usuario_;	//su titular
		Fecha caducidad_;			//caducidad
		bool activa_;				//1==activa; 0==no
		Tipo tipo_;					//tipo de la tarjeta
};

/*--OPERADORES DE SALIDA FUERA DE LA CLASE--*/
ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo);

/*--OPERADORES LOGICOS FUERA DE LA CLASE--*/
bool operator <(const Numero& a, const Numero& b);
bool operator <(const Tarjeta& a, const Tarjeta& b);
bool operator >(const Tarjeta& a, const Tarjeta& b);

#endif
