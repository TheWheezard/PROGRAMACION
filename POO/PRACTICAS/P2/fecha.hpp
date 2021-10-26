#ifndef FECHA_HPP
#define FECHA_HPP

#include<iostream> //Para el 'operator<<'
#include <iomanip>
#include <cstdio>
#include <ctime>


class Fecha{
	private:
		/*--VARIABLES--*/
		int dia_, mes_, anno_;
		
		/*--FUNCIONES PRIVATE--*/
		bool comprueba() const;
		int  dia_max() const;

	public:
		/*--CONSTANTES--*/
    		static const int AnnoMaximo = 2037;
		static const int AnnoMinimo = 1902;
    
		/*--INVALIDA--*/
		class Invalida{
			private:
				const char *info_;
			public:
				Invalida(const char *in);
				const char* por_que() const;
		};
		
		/*--CONSTRUCTORES--*/
		explicit Fecha(int dd=0, int mm=0, int aaaa=0);
		Fecha(const char* c);
		/*Constructor asignaci�n default*/
		const char* cadena() const; 							//conversor a const char*
		
		/*--OBSERVADOR--*/
		const int dia()  const noexcept{return dia_;}
		const int mes()  const noexcept{return mes_;}
		const int anno() const noexcept{return anno_;}
				
		/*--OPERADORES--*/
		Fecha&  operator++();					//Operador pre-incremento   	  	++f;
		Fecha operator++(int);				//Operador post-incremento		f++;
		Fecha&  operator--();					//Operador pre-decremento			--f;
		Fecha operator--(int);					//Operador post-decremento		f--;

		/*--OPERADORES ARITMETICOS--*/
		Fecha& operator+=(int i);				//operador suma-igual				f+=i;
		Fecha& operator-=(int i);				//operador resta-igual				f-=i;
		Fecha operator+( int d)const ;
		Fecha operator-( int d)const ;
		
		/*--ENTRADA - SALIDA--*/
		friend std::ostream& operator<<(std::ostream& os, const Fecha& f)noexcept;
		friend std::istream& operator>>(std::istream& is, Fecha& f);

};
	
/*--OPERADORES L�GICOS--*/
bool operator==(const Fecha& f1, const Fecha& f2)noexcept;		//Operador igual que	 				==
bool operator!=(const Fecha& f1, const Fecha& f2)noexcept;			//Operador no-igual que	 			!=
bool operator> (const Fecha& f1, const Fecha& f2)noexcept;			//Operador mayor que		 			>
bool operator< (const Fecha& f1, const Fecha& f2)noexcept;			//Operador menor que		 			<
bool operator>=(const Fecha& f1, const Fecha& f2)noexcept;		//Operador mayor o igual que		 	>=
bool operator<=(const Fecha& f1, const Fecha& f2)noexcept; 		//Operador menor o igual que		 	<=


#endif
