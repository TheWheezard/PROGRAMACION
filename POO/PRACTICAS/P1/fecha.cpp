#include "fecha.hpp"
#include <new>

using namespace std;

/*PRIVATE*/
bool Fecha::comprueba()const{
	return !(dia_ > dia_max() || dia_ < 1 || mes_ > 12 || mes_ < 1 || anno_ > Fecha::AnnoMaximo || anno_ < Fecha::AnnoMinimo );
}

int Fecha::dia_max() const{
	if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12 ) return 31; //31 dias
	else if(mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11 ) return 30; //30 dias
	else if(mes_ == 2 ){
        //CONTROL BISIESTO//
		if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) return 29; //anio bisiesto
		else return 28;  //anio no bisiesto
	}
	else {throw Fecha::Invalida ("Mes invalido");}
	
	return 0;
}

/*CLASE INVALIDA*/
Fecha::Invalida::Invalida(const char *in): info_(in){}
const char* Fecha::Invalida::por_que()const{
	return info_;
}

/*CONSTRUCTORES*/
Fecha::Fecha(int dd, int mm, int aaaa): dia_(dd), mes_(mm), anno_(aaaa){
	std::time_t tiempo_calendario = std::time(0);
	std::tm* tiempo_descompuesto  = std::localtime(&tiempo_calendario);
	
	if(anno_==0) anno_ = tiempo_descompuesto->tm_year + 1900;
	else while(anno_>9999) anno_/=10;  //se toman solo los primeros 4 digitos, descartando el resto
	if(mes_==0) mes_ = tiempo_descompuesto->tm_mon + 1;
	if(dia_==0) dia_ = tiempo_descompuesto->tm_mday;
	
	if(!comprueba()) throw Fecha::Invalida ("Fecha invalida");
}

Fecha::Fecha(const char* c){
	dia_=-2; mes_=-2;anno_=-2;	
	sscanf(c, "%d/%d/%d", &dia_, &mes_, &anno_);
	
	std::time_t tiempo_calendario = std::time(0);
	std::tm* tiempo_descompuesto  = std::localtime(&tiempo_calendario);
	if(anno_==0) anno_ = tiempo_descompuesto->tm_year + 1900;
	else while(anno_>9999) anno_/=10;  //se toman solo los primeros 4 digitos, descartando el resto
	if(mes_==0) mes_ = tiempo_descompuesto->tm_mon + 1;
	if(dia_==0) dia_ = tiempo_descompuesto->tm_mday;
	if(!comprueba()) throw Fecha::Invalida ("Fecha invalida");
}

/*conversion a const char* */
const char* Fecha::cadena() const{
	static char* buffer = new char[40];
	tm f= {};
	f.tm_mday=dia_;
	f.tm_mon =mes_ -1;
	f.tm_year=anno_ -1900;
   
	mktime(&f);
	strftime(buffer, 40, "%A %d de %B de %Y", &f);

	return buffer;  
}

/*OPERADORES*/
Fecha& Fecha::operator++(){  //pre-incremento (++f);			
	*this +=(1);
	return *this;
}
Fecha Fecha::operator++(int){  //post-incremento (f++);			
	Fecha t(*this);
	*this +=(1);
	return t;
}
Fecha&  Fecha::operator--(){  //pre-decremento (--f)		
	*this +=(-1);
	return *this;
}
Fecha Fecha::operator--(int){  //post-decremento (f--)
	Fecha t(*this);
	*this +=(-1);
	return t;
}

/*ARITMETICOS*/
Fecha& Fecha :: operator += (int i){ //fecha+=i
	this->dia_+=i;
	while(mes_>12){
		mes_-=12;
		anno_++;
	}
	while(dia_>dia_max()){
		dia_-=dia_max();
		if(++mes_>12){
			mes_=1;
			anno_++;
		}
	}
	while(dia_<=0){
		if(--mes_<=0){
			mes_=12;
			anno_--;
		}
		dia_+=dia_max();
	}
	if(!comprueba()){ throw Fecha::Invalida("Fecha invalida");}

	return *this;
}
Fecha&  Fecha::operator-=(int i){  //fecha-=i	
	*this +=(-i);
	return *this;
}
Fecha Fecha::operator+( int d) const{	
	Fecha t(*this);
	t +=(d);
	return t;
}
Fecha Fecha::operator-(int d)const{	
	Fecha t(*this);
	t +=(-d);
	return t;
}

/*ENTRADA - SALIDA*/
ostream& operator<<(std::ostream& os, const Fecha& f) noexcept{ //salida
	os<<f.cadena();
	return os;
}
istream& operator>>(std::istream& is, Fecha& f){ //entrada
	char *cadAux = new char[11];
	is.width(11);      			//maximo de caracteres en "dd/mm/aaaa\0"
	is >> cadAux;
	try {
		f = cadAux;
	}catch ( Fecha::Invalida e ){
		is.setstate(std::ios::failbit); //activar failbit
		delete[] cadAux;
     	   throw Fecha::Invalida("Error: operador >>: error de formato o al constuir el objeto. Formato: dd/mm/aaaa");
	}
	delete[] cadAux;
	return is;
}	

/*OPERADORES LOGICOS*/
bool operator==(const Fecha& f1, const Fecha& f2)noexcept{	
	return (f1.dia()==f2.dia() && f1.mes()==f2.mes() && f1.anno()==f2.anno());
}
bool operator!=(const Fecha& f1, const Fecha& f2)noexcept{	
	return !( f1 == f2 );
}
bool operator <(const Fecha& f1, const Fecha& f2)noexcept{
	if (f1.anno() < f2.anno())	return true;
	else if (f1.anno() > f2.anno())	return false;
	else if (f1.mes() < f2.mes())	return true;
	else if (f1.mes() > f2.mes())	return false;
	else if (f1.dia() < f2.dia())	return true;
	else if (f1.dia() > f2.dia())	return false;
	else return false;
}
bool operator >(const Fecha& f1, const Fecha& f2)noexcept{	
	return (f2 < f1);
}
bool operator>=(const Fecha& f1, const Fecha& f2)noexcept{	
	return !(f1 < f2);
}
bool operator<=(const Fecha& f1, const Fecha& f2)noexcept{	
	return !(f2 < f1);
}
