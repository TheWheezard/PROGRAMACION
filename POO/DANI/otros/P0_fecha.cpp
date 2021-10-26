#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <iostream>
#include <ctime>

//CLASE FECHA
class Fecha{
private:
    int dia_,mes_,anno_;
    void valida();
public:
  explicit Fecha(int d=0,int m=0,int a=0);
  Fecha(const char*);
  Fecha& operator++();//prefijo
  Fecha& operator++(int);//postfijo
  Fecha& operator--();//prefijo
  Fecha& operator--(int);//postfijo
  Fecha& operator+(int);
  Fecha& operator-(int );
  Fecha& operator-= (int);
  Fecha& operator+= (int);
  /*
    Si  se  usa  una  función  miembro  y  un  argumento  de  un  tipo  diferente,
    la  función  miembro  solo  nos  permite  que  el  nuevo  tipo  se  encuentre  en  el  lado  derecho  del  operador.
    Esto es, A + 2, puede ser válido, pero 2 + A, no lo es. Una función friend, nos permite ambas combinaciones
  */
  friend bool operator==(const Fecha&,const Fecha&);
  friend bool operator<(const Fecha&,const Fecha&);
  friend bool operator>(const Fecha&,const Fecha&);
  friend bool operator<=(const Fecha&,const Fecha&);
  friend bool operator>=(const Fecha&,const Fecha&);
  friend bool operator!=(const Fecha&,const Fecha&);
  static const int AnnoMinimo=1902,AnnoMaximo=2037;
  //observadores
  int dia()const;
  int mes()const;
  int anno()const;
  const char* cadena() const;//convertir fecha a const char*

  friend std::ostream& operator <<(std::ostream& os, const Fecha& f);
  friend std::istream& operator >>(std::ostream& is, Fecha& f);

  class Invalida{
  public:
    Invalida(const char* e):error(e){}
    const char* por_que()const{return error;}
  private:
    const char* error;
  };


};//FIN CLASE FECHA

//Definir comparacion de fechas fuera de la clase como amigo

bool operator==(const Fecha&,const Fecha&);
bool operator<(const Fecha&,const Fecha&);
bool operator>(const Fecha&,const Fecha&);
bool operator<=(const Fecha&,const Fecha&);
bool operator>=(const Fecha&,const Fecha&);
bool operator!=(const Fecha&,const Fecha&);

//Operadores de flujo
std::ostream& operator <<(std::ostream& os, const Fecha& f);//Operador de extraccion
std::istream& operator >>(std::ostream& is, Fecha& f); //operador de insercion

#endif

----------------------------------------------------------------------------------------------------------------------

#include "fecha.hpp"
#include <iomanip>

using namespace std;
/*
Time structure
Structure containing a calendar date and time broken down into its components.
tm_sec  int seconds after the minute  0-61*
tm_min  int minutes after the hour  0-59
tm_hour int hours since midnight  0-23
tm_mday int day of the month  1-31
tm_mon  int months since January  0-11
tm_year int years since 1900  
tm_wday int days since Sunday 0-6
tm_yday int days since January 1  0-365
tm_isdst  int Daylight Saving Time flag 
*/
std::time_t tiempo_calendario = std::time(nullptr);
std::tm* tiempo_descompuesto= std::localtime(&tiempo_calendario);
//Excepciones
Fecha::Fecha(int d,int m,int a):dia_(d),mes_(m),anno_(a){
  if(a==0)
    anno_=tiempo_descompuesto->tm_year+1900;
  if(m==0)
      mes_=tiempo_descompuesto->tm_mon+1;
  if(d==0)
    dia_=tiempo_descompuesto->tm_mday;
  valida();
}
Fecha::Fecha(const char* c){
  int f;
  f=sscanf(c,"%2d/%2d/%4d",&dia_,&mes_,&anno_);
  /*
    The sscanf() function returns the number of fields that were successfully converted and assigned.
    The return value does not include fields that were read but not assigned. 
    The return value is EOF when the end of the string is encountered before anything is converted.
  */  
  if(f!=3)
    throw(Invalida("Formato de fecha incorrecta"));
  *this=Fecha(dia_,mes_,anno_);
}
void Fecha::valida(){
  tm f={};
  f.tm_mday=dia_;
  f.tm_mon=mes_-1;
  f.tm_year=anno_-1900;
  mktime(&f);
  if(dia_!=f.tm_mday)
    throw Invalida("Dia erroneo");
  if(mes_!=f.tm_mon+1)
    throw Invalida("Mes erroneo");
  if(anno_!=f.tm_year+1900)
    throw Invalida("Anno erroneo");
  if(anno_<AnnoMinimo || anno_>AnnoMaximo)
    throw Invalida("El anno no se encuentra en los limites establecido");
  if(dia_==29&&mes_==2&& (anno_ % 4 == 0 && !(anno_ % 400 == 0 || anno_ % 100 != 0)))
    throw Invalida("El anno no es bisiesto por lo que no puede ser 29 de Febrero");
}

const char* Fecha::cadena()const{
  tm f{};
  f.tm_mday=dia_;
  f.tm_mon=mes_-1;
  f.tm_year=anno_-1900;
  f.tm_isdst=-1;
  mktime(&f);
  const char* dia_semana[]={"domingo","lunes","martes","miércoles","jueves","viernes","sábado"};
  const char* mes_actual[]={"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};
  static char cadena[100];
  sprintf(cadena, "%s %d de %s de %d",dia_semana[f.tm_wday],f.tm_mday, mes_actual[f.tm_mon],anno_);
  return cadena;
}

//observadores
int Fecha::dia()const{return dia_;}
int Fecha::mes()const{return mes_;}
int Fecha::anno()const{return anno_;}
//Operadores sobrecargados
Fecha& Fecha::operator++(){
  return *this+=1;
}
Fecha& Fecha::operator++(int){
  Fecha *f=new Fecha(*this);
  *this+=1;
  return *f;
}
Fecha& Fecha::operator--(){
  return *this-=1;
}
Fecha& Fecha::operator--(int){
  Fecha *f=new Fecha(*this);
  *this+=-1;
  return *f;
}
Fecha& Fecha::operator+(int d){
  Fecha *f=new Fecha(*this);
  f->dia_+=d;
  return *f;
}
Fecha& Fecha::operator-(int d){
  Fecha *f=new Fecha(*this);
  f->dia_+=-d;
  return *f;

}
Fecha& Fecha::operator-= (int d){
  return *this +=-d;
}
Fecha& Fecha::operator+= (int d){
  tm f={};
  f.tm_mday=dia_+d;
  f.tm_mon=mes_-1;
  f.tm_year=anno_-1900;
  mktime(&f);
  dia_=f.tm_mday;
  mes_=f.tm_mon+1;
  anno_=f.tm_year+1900;
  //mktime(&f);//Dos veces mktime???
  valida();
  return *this;
}

//Operadores de comparacion
bool operator==(const Fecha& f1,const Fecha& f2){
  return (f1-f2==0);
}
bool operator<(const Fecha& f1,const Fecha& f2){
  return (f1-f2<0);
}
bool operator>(const Fecha& f1,const Fecha& f2){
  return f2<f1;
}
bool operator<=(const Fecha& f1,const Fecha& f2){
return !(f2<f1);
}
bool operator>=(const Fecha& f1,const Fecha& f2){
  return !(f1<f2);
}
bool operator!=(const Fecha& f1,const Fecha& f2){
  return !(f1==f2);
}


//operador de extraccion
ostream& Fecha::operator<< (ostream& os, const Fecha& f){
  os<<f.cadena();
  return os;
}

//operador inserccion
istream& Fecha::operator>>(ostream& is, Fecha& f){
  char* cad = new char[11];
  is >> setw(11) >> cad;

  int dia = -1, mes = -1, anno = -1;
  sscanf(cad, "%2d/%2d/%4d", &dia, &mes, &anno);

  delete[] cad;

  try {
    f = Fecha(dia, mes, anno);
  } catch (...) {
    is.setstate(ios_base::failbit);
    throw;
}
return is;
}