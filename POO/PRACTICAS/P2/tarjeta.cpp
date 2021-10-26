#include "tarjeta.hpp"
#include <iomanip>
#include <cstring>
#include <string.h>
#include <cctype>

/*ALGORITMO DE LUHN*/
bool luhn(const Cadena&);

/***CLASE NUMERO***/
/*CONSTRUCTORES*/
Numero::Numero(const Cadena& num){
	char keys[]="./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	size_t ii=strcspn(num.c_str(), keys);			//caracteres del primer elemento que no esten en el segundo
	if(ii<num.length()) throw Incorrecto(Razon::DIGITOS);
	char *pch;
	char *aux=new char[30];
	pch=strpbrk(const_cast<char*>(num.c_str()),"1234567890");  //buscar una cadena por cualquier caracter del conjunto
	int i=0;
	while(pch !=NULL){
		aux[i++]=*pch;
		pch=strpbrk(pch+1,"1234567890");
	}
	aux[i]='\0';
	Cadena n(aux);
	delete[] aux;
	if(n.length()>19 || n.length()<13)			//Verificamos que tamanio no este entre 13 y 19 caracteres
		throw Incorrecto(Razon::LONGITUD);
	if(!luhn(n))								//Verificamos si el numero es invalido segun el algoritmo de lunh
		throw Incorrecto(Razon::NO_VALIDO);
	numero_=n;
}
/*DESTRUCTOR*/
Numero::~Numero(){}	

/**NUMERO INCORRECTO**/
Numero::Incorrecto::Incorrecto(const Numero::Razon r):r_(r){}

/*FUNCION eliminar*/
void eliminarChar(Cadena& cad, size_t pos){
	Cadena nuevo = cad.substr(0,pos);			//Obtener lo que necesitamos de cad y lo guardamos
	if((pos+1)<cad.length())
		nuevo+=Cadena(cad.substr(pos+1, cad.length()));
	cad=move(nuevo);
} 

/***CLASE TARJETA***/
/*CONSTRUCTOR*/
Tarjeta::Tarjeta(const Numero& n, Usuario& u, const Fecha& f):numero_(n), usuario_(&u), caducidad_(f), activa_(1), tipo_(esTipo()){
	if(f<Fecha()) throw Caducada(f);
	usuario_->es_titular_de(*this);
}
/*GETER*/
bool& Tarjeta::activa(bool a){
	activa_=a;
	return activa_;
}
/*DESTRUCTOR*/
Tarjeta::~Tarjeta(){
	if(usuario_) usuario_->no_es_titular_de(*this);
}

/**CLASE CADUCADA**/
/*CONSTRUCTOR*/
Tarjeta::Caducada::Caducada(const Fecha& f):fecha_caducada(f){}

/**CLASE NUM_DUPLICADO**/
/*CONSTRUCTOR*/
Tarjeta::Num_duplicado::Num_duplicado(const Numero& n):numer_(n){}

/**CLASE DESACTIVADA**/
/*CONSTRUCTOR*/
Tarjeta::Desactivada::Desactivada(){}

/*FUNCIONES DE TARJETA*/
void Tarjeta::anula_titular(){
	activa_=false;
	const_cast<Usuario*&>(usuario_)=nullptr;
}

Tarjeta::Tipo Tarjeta::esTipo(){
	int a=atoi(numero_.num().substr(0,2).c_str());
	switch(a/10){
		case 3:
			if(a==34 || a==37) return Tarjeta::AmericanExpress;
			else return Tarjeta::JCB;
			break;
		case 4:
			return Tarjeta::VISA;
			break;
		case 5:
			return Tarjeta::Mastercard;
			break;
		case 6:
			return Tarjeta::Maestro;
			break;
		default:
			return Tarjeta::Otro;
	}
}

/*FLUJO DE SALIDA*/
ostream& operator <<(ostream& os, const Tarjeta& t){
	os<<t.tipo()<<endl<<t.numero()<<endl;
	//Transformar nombre y apellidos en mayusculas
	Cadena aux=t.titular()->nombre();					 //Asignamos un nombre a la cadena aux modificable
	int i=0;
	while(aux[i]!='\0'){
		if(islower(aux[i])) aux[i]=toupper(aux[i]);			//Pasamos a mayusculas si no lo esta
		i++;
	}
	os<<aux<<" ";
	i=0;
	aux=t.titular()->apellidos();
	while(aux[i]!='\0'){
		if(islower(aux[i])) aux[i]=toupper(aux[i]);			//Pasamos a mayusculas si no lo esta
		i++;
	}
	os<<aux<<endl;
	os<<"Caduca: "<<setfill('0')<<setw(2)<<t.caducidad().mes()<<"/"<<setw(2)<<(t.caducidad().anno()%100)<<endl;
	return os;
}

ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo){
	switch(tipo){//segun tipo de tarjeta
		case Tarjeta::VISA: 
			os<<"VISA";
			break;
		case Tarjeta::Mastercard:
			os << "Mastercard";
			break;
		case Tarjeta::Maestro:
			os<<"Maestro";
			break;
		case Tarjeta::JCB: 
			os<<"JCB";
			break;
		case Tarjeta::AmericanExpress:
			os<<"AmericanExpress";
			break;
		case Tarjeta::Otro:
			os<<"Otro";
			break;
		default:
			os<<"Error";
	}
	return os;
}

/*OPERADORES LOGICOS*/
bool operator <(const Numero& a, const Numero& b){
	return strcmp(a,b)<0;
}
bool operator <(const Tarjeta& a, const Tarjeta& b){
	return a.numero()<b.numero();
}
bool operator >(const Tarjeta& a, const Tarjeta& b){
	return b.numero()<a.numero();
}



