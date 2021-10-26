#ifndef FECHA_HPP
#define FECHA_HPP

#include<iostream> //operator <<
#include <iomanip>
#include <cstdio>
#include <ctime>


class Fecha{
private:
	int dia_, mes_, anno_;
	bool comprueba() const;
	int  dia_max() const;
public:
	/*CLASE INVALIDA*/
	class Invalida{
	private:
		const char *info_;
	public:
		Invalida(const char *in);
		const char* por_que() const;
	};

	/*CONSTANTES*/
	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;
	
	/*CONSTRUCTORES*/
	explicit Fecha(int dd=0, int mm=0, int aaaa=0);
	Fecha(const char* c);
	
	const char* cadena() const; //conversion a const char*
	
	/*GETERS*/
	const int dia()  const noexcept{return dia_;}
	const int mes()  const noexcept{return mes_;}
	const int anno() const noexcept{return anno_;}
			
	/*OPERADORES*/
	Fecha&  operator++();  //pre-incremento (++f)
	Fecha operator++(int); //post-incremento (f++)
	Fecha&  operator--();  //pre-decremento (--f)
	Fecha operator--(int); //post-decremento (f--)
	/*ARITMETICOS*/
	Fecha& operator+=(int i); //fecha+=i;
	Fecha& operator-=(int i); //fecha-=i;
	Fecha operator+( int d)const;
	Fecha operator-( int d)const;
		
	/*ENTRADA - SALIDA*/
	friend std::ostream& operator<<(std::ostream& os, const Fecha& f)noexcept; //salida
	friend std::istream& operator>>(std::istream& is, Fecha& f); //entrada
};
	
/*OPERADORES LOGICOS*/
bool operator==(const Fecha& f1, const Fecha& f2)noexcept;
bool operator!=(const Fecha& f1, const Fecha& f2)noexcept;
bool operator> (const Fecha& f1, const Fecha& f2)noexcept;
bool operator< (const Fecha& f1, const Fecha& f2)noexcept;
bool operator>=(const Fecha& f1, const Fecha& f2)noexcept;
bool operator<=(const Fecha& f1, const Fecha& f2)noexcept;


#endif
