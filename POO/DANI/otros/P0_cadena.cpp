#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <string.h>
#include <stdexcept>
#include <iterator>

class Cadena{
private:
  char * s_;
  unsigned tam_;
public:
  explicit Cadena(unsigned n=0,const char c=' ');//CTOR
  Cadena(const Cadena& c);//Constructor de copia
  Cadena(const char* c);//constructor al que se le pasa un char
  Cadena& operator= (const Cadena&);//Iguala Cadenas
  Cadena& operator= (const char*);//Iguala  char a Cadena
  const char* c_str()const;//Convierte Cadena a char
  unsigned length()const;//Devuelve el tamaño
  Cadena& operator +=(const Cadena&);//Concatena cadenas
  friend Cadena operator+(const Cadena& c1, const Cadena& c2);
  friend  bool operator ==(const Cadena& c1, const Cadena& c2);
  friend bool operator !=(const Cadena& c1, const Cadena& c2);
  friend bool operator > (const Cadena& c1, const Cadena& c2);
  friend bool operator < (const Cadena& c1, const Cadena& c2);
  friend bool operator ==(const Cadena& c1, const Cadena& c2);
  friend bool operator >=(const Cadena& c1, const Cadena& c2);
  friend bool operator <=(const Cadena& c1, const Cadena& c2);
  friend std::ostream& operator <<(std::ostream& os, const Cadena& c);//Operador de extraccion
  friend std::istream& operator >>(std::ostream& is,/* Cadena&*/);

  char& operator[](unsigned n);
  char& operator[](unsigned n)const;
  char& at(unsigned n);
  char& at(unsigned n)const;

  ~Cadena();//Destructor
  Cadena& substr(unsigned i, unsigned n)const;
  //Operadores con semantica de movimiento
  Cadena(Cadena&& c);
  Cadena& operator=(Cadena&& c);

  //iteradores
	typedef char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator <const_iterator> const_reverse_iterator;
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator crend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator rbegin() const;
};//FIN clase

//operadores amigos
Cadena operator+(const Cadena& c1, const Cadena& c2);
bool operator ==(const Cadena& c1, const Cadena& c2);
bool operator !=(const Cadena& c1, const Cadena& c2);
bool operator > (const Cadena& c1, const Cadena& c2);
bool operator < (const Cadena& c1, const Cadena& c2);
bool operator ==(const Cadena& c1, const Cadena& c2);
bool operator >=(const Cadena& c1, const Cadena& c2);
bool operator <=(const Cadena& c1, const Cadena& c2);
std::ostream& operator <<(std::ostream& os, const Cadena& c);//Operador de extraccion
std::istream& operator >>(std::ostream& is, Cadena&);

#endif

---------------------------------------------------------------------------------------------------------------------

#include "cadena.hpp"
using namespace std;
#include <iomanip>
//constructor
Cadena::Cadena(unsigned n,const char c):tam_(n){
  s_=new char[tam_+1];//+1 por el \0
  for(unsigned i=0;i<tam_;++i){
    s_[i]=c;
  }
  s_[tam_]='\0';
}

Cadena::Cadena(const Cadena& c){
  this->s_=new char[c.tam_+1];
  this->tam_=c.tam_;
  for(unsigned i=0;i<c.tam_;++i)
    this->s_[i]=c.s_[i];
}

Cadena::Cadena(const char* c){
  tam_=strlen(c);
  s_=new char [tam_+1];
  strcpy(s_,c);
  s_[tam_]='\0';

}
Cadena& Cadena::operator= (const Cadena& c){
  if(this!=&c){
    tam_=c.tam_;
    delete[] s_;
    s_=new char[tam_+1];
    strcpy(s_,c.s_);
  }
  return *this;
}
Cadena& Cadena::operator= (const char * c){
  tam_=strlen(c);
  delete[] s_;
  s_=new char[tam_+1];
  strcpy(s_,c);
  return *this;

}
const char* Cadena::c_str()const{
  return s_;
}

unsigned Cadena::length()const{
  return tam_;
}

Cadena& Cadena::operator +=(const Cadena& c){
  tam_+=c.tam_;
  char* aux= new char[tam_+1];
  strcpy(aux,s_);
  strcat(aux,c.s_);
  delete[] s_;
  s_ = new char[tam_+1];
  s_=aux;
  return *this;

}
Cadena operator+(const Cadena& c1, const Cadena& c2){
  return Cadena(c1)+=c2;
}
bool operator ==(const Cadena& c1, const Cadena& c2){
  return strcmp(c1,c2)==0;
}
bool operator !=(const Cadena& c1, const Cadena& c2){
  return strcmp(c1,c2)!=0;
}
bool operator >(const Cadena& c1, const Cadena& c2)
{
  return strcmp(c1,c2)>0;

}
bool operator <(const Cadena& c1, const Cadena& c2){
  return strcmp(c1,c2)<0;
}
bool operator >=(const Cadena& c1, const Cadena& c2){
  return strcmp(c1,c2)>=0;
}
bool operator <=(const Cadena& c1, const Cadena& c2){
  return strcmp(c1,c2)<=0;
}

char& Cadena::operator [](unsigned n){
  return s_[n];
}
char& Cadena::operator [](unsigned n)const{
  return s_[n];
}

char& Cadena::at(unsigned n){
  if(tam_<n)
    throw (out_of_range("La posicion esta fuera del vector"));
  return s_[n];
}
char& Cadena::at(unsigned n)const{
  if(tam_<n)
    throw (out_of_range("La posicion esta fuera del vector"));
  return s_[n];
}

Cadena::~Cadena(){
  delete[] s_;
}
Cadena& Cadena::substr(unsigned i, unsigned n)const{
  if(tam_<i || n> tam_-1)
    throw out_of_range("Posiciones inaccesibles");
  Cadena *aux= new Cadena(n);
  aux->s_= new char[tam_+1];
  strncpy(aux->s_,this->s_+i,tam_);
  aux->s_[tam_]='\0';
  return *aux;
}
//movimiento
Cadena::Cadena(Cadena&& c){
  tam_=c.tam_;
  s_=new char[tam_+1];
  strcpy(s_,c.s_);
  c.s_=nullptr;
  c.tam_=0;
}

Cadena& Cadena::operator =(Cadena&& c){
  s_=c.s_;
  tam_=c.tam_;
  c.tam_=0;
  c.s_=nullptr;
  return *this;
}

//Operadores de flujo
ostream& Cadena::operator <<(ostream& os, const Cadena& cad){
  os<<cad.c_str();
  return os;
}
istream& Cadena::operator >>(ostream& is/*, Cadena& c*/){
  char *aux = new char [32]{'\0'};
  //setw:Set field width: Sets the field width to be used on output operations.
  is >> setw(32) >> aux;
  cad = Cadena(aux);
  delete[] aux;
  return is;
}

//iteradores
Cadena::iterator Cadena::begin()
{
  return s_;
}

Cadena::const_iterator Cadena::begin() const
{
  return s_;
}
Cadena::iterator Cadena::end()
{
  return s_ + tam_;
}
Cadena::const_iterator Cadena::end() const
{
  return s_ + tam_;
}
Cadena::const_iterator Cadena::cbegin() const
{
  return s_;
}

Cadena::const_iterator Cadena::cend() const
{
  return s_ + tam_;
}
Cadena::reverse_iterator Cadena::rbegin()
{
  return reverse_iterator(end());
}
Cadena::reverse_iterator Cadena::rend()
{
  return reverse_iterator(begin());
}

Cadena::const_reverse_iterator Cadena::crend() const
{
  return const_reverse_iterator(cbegin());
}

Cadena::const_reverse_iterator Cadena::crbegin() const
{
  return const_reverse_iterator(cend());
}

Cadena::const_reverse_iterator Cadena::rend() const
{
  return const_reverse_iterator(cbegin());
}

Cadena::const_reverse_iterator Cadena::rbegin() const
{
  return const_reverse_iterator(cend());
}