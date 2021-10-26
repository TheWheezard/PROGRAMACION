#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <cstring>		
#include <iterator>		//iteradores
#include <stdexcept>	//std::out_of_range
#include <functional>

class Cadena{
private:
	size_t tam_;
	char *s_;
	void copiar(const Cadena& c);
	void copiar(const char* c);

public: 
	/*CONSTRUCTORES*/
	explicit Cadena(size_t l=0, char c=' ');
	Cadena(const char* s);
	Cadena(const Cadena& c);
	Cadena(Cadena&& c);
	
	/*GETERS*/		
	const char* puts(){return s_;}			//Devuelve cad
	const char* puts() const{return s_;}

	size_t length() noexcept {return tam_; }     			//devuelve tamanio de cadena
	const size_t length() const noexcept {return tam_; }

	size_t length(const char*c)noexcept;				//devuelve tamanio de cadena
	const size_t length(const char*s) const noexcept;

	const char* c_str() const noexcept;
	
	/*ARITMETICA*/
   	Cadena& operator+= (const Cadena& c); // cadA <-- cadA + cadB
   	
	/*ASIGNACION*/
	Cadena& operator= (const Cadena& c);	//cad = cad
	Cadena& operator= (const char* c);		//cad = const char*
	Cadena& operator=(Cadena&&c);			//movimiento
   	
	/*INDICE*/
	
	char& operator[] (size_t i)	noexcept;				//no comprueba indice
	const char& operator[] (size_t i) const	noexcept;	//const
	char& at(size_t i);									//comprueba indice valido
	const char& at(size_t i) const;						//const  
	Cadena substr(size_t i, size_t fin)const;			//devuelve cad desde i hasta fin
	
	/*ITERADORES*/
	typedef char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator <iterator> reverse_iterator;
	typedef std::reverse_iterator <const_iterator> const_reverse_iterator;
	
	/*FUNCIONES ITERATOR*/
	//begin
	iterator  begin() noexcept{return s_;}
	const_iterator  begin() const noexcept{return const_iterator(s_);}
	//cbegin
	const_iterator cbegin() const noexcept{return const_iterator(s_);}
	//rbegin
	reverse_iterator  rbegin() noexcept{return reverse_iterator(end());}
	const_reverse_iterator  rbegin() const noexcept{return const_reverse_iterator(end());}
	//crbegin
	const_reverse_iterator crbegin() const noexcept{return const_reverse_iterator(end());}

	//end
	iterator end() noexcept{return s_ + tam_;}
	const_iterator end() const noexcept{return const_iterator(s_ + tam_);}
	//cend
	const_iterator cend() const noexcept{return const_iterator(s_ + tam_);}
	//rend
	reverse_iterator rend() noexcept{return reverse_iterator(begin());}
	const_reverse_iterator rend() const noexcept{return const_reverse_iterator(begin());}
	//crend
	const_reverse_iterator crend() const noexcept{return const_reverse_iterator(begin());}
	
	/*ENTRADA - SALIDA*/
	friend std::ostream& operator<<(std::ostream& os, const Cadena& c) noexcept;//salida
	friend std::istream& operator>>(std::istream& is, Cadena& c)noexcept;//entrada
	
	/*DESTRUCTOR*/
	~Cadena();
};

/*OPERADOR ARITMETICO '+'*/
Cadena operator+(const Cadena& c1, const Cadena& c2);

/*OPERADORES LOGICOS --- COMPARACIONES ASCII*/
bool operator==(const Cadena& c1, const Cadena& c2);
bool operator!=(const Cadena& c1, const Cadena& c2);
bool operator >(const Cadena& c1, const Cadena& c2);
bool operator <(const Cadena& c1, const Cadena& c2);
bool operator>=(const Cadena& c1, const Cadena& c2);
bool operator<=(const Cadena& c1, const Cadena& c2);

#endif //FIN_CADENA_HPP
