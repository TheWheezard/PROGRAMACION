#include "tarjeta.hpp"

/*--ALGORITMO DE LUHN--*/
bool luhn(const Cadena&);

/*---PARA LA CLASE NUMERO---*/
/*--CONSTRUCTORES--*/
class EsDigito: public unary_function<char,bool>
{
	public:
		bool operator()(char c) const {return isdigit(c);}
};
Numero::Numero(const Cadena& num)
{
	Cadena n(num);
	Cadena::iterator i = std::remove_if (n.begin(), n.end(), [](char x) {return std::isspace(x);});		//isspace para comprobar que pertenece al grup de caracteres

	if(i != n.end())	
	{
		*i='\0';
		n = Cadena(n.c_str());
	}

	unary_negate<EsDigito>not_EsDigito((EsDigito()));
	Cadena::const_iterator it = find_if(n.begin(), n.end(), not_EsDigito);
	if(it!=n.end()) throw Incorrecto(Razon::DIGITOS);
	
	if(n.length()>19 || n.length()<13)
		throw Incorrecto(Razon::LONGITUD);
	if(!luhn(n)) //si numero invalido segun el algoritmo de lunh
		throw Incorrecto(Razon::NO_VALIDO);
	numero_=n;
}

/*--DESTRUCTOR--*/
Numero::~Numero(){}	

/*-- OPERADOR --*/
Numero::operator const char*()const {return numero_.c_str();}

/*---CLASE NUMERO INCORRECTO (DENTRO DE NUMERO)---*/
Numero::Incorrecto::Incorrecto(const Numero::Razon r):r_(r){}
Numero::Razon Numero::Incorrecto::razon()const{return r_;}

/*--FUNCION FUERA DE CLASE--*/
void eliminarChar(Cadena& cad, size_t pos)
{
	Cadena nuevo = cad.substr(0,pos);
	
	if((pos+1)<cad.length())
		nuevo+=Cadena(cad.substr(pos+1, cad.length()));
	
	cad=move(nuevo);
} 


/*---PARA LA CLASE TARJETA---*/
/*--CONSTRUCTOR--*/
Tarjeta::Tarjeta(const Numero& n, Usuario& u, const Fecha& f):numero_(n), usuario_(&u), caducidad_(f), activa_(1), tipo_(esTipo())
{
	if(f<Fecha()) throw Caducada(f);
	usuario_->es_titular_de(*this);
}

/*--OBSERVADORA--*/
/*-- FUNCION ACTIVA --*/
bool& Tarjeta::activa(bool a)
{
	activa_=a;
	return activa_;
}

/*--DESTRUCTOR--*/
Tarjeta::~Tarjeta()
{
	if(usuario_) usuario_->no_es_titular_de(*this);
}

/*---CLASE CADUCADA (DENTRO DE TARJETA)---*/
/*--CONSTRUCTOR--*/
Tarjeta::Caducada::Caducada(const Fecha& f):fecha_caducada(f){}

/*---CLASE NUM_DUPLICADO (DENTRO DE TARJETA)---*/
/*--CONSTRUCTOR--*/
Tarjeta::Num_duplicado::Num_duplicado(const Numero& n):numer_(n){}

/*--OBSERVADORA--*/
const Numero& Tarjeta::Num_duplicado::que()const
{
	return numer_;
}

/*---CLASE DESACTIVADA (DENTRO DE TARJETA)---*/
/*--CONSTRUCTOR--*/
Tarjeta::Desactivada::Desactivada(){}

/*--FUNCIONES DE LA CLASE TARJETA--*/
void Tarjeta::anula_titular()
{
	activa_=false;
	const_cast<Usuario*&>(usuario_)=nullptr;
}

Tarjeta::Tipo Tarjeta::esTipo()
{
	int a=atoi(numero_.num().substr(0,2).c_str());
	switch(a/10)
	{
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

/*--FLUJO DE SALIDA--*/
ostream& operator <<(ostream& os, const Tarjeta& t)
{
	os<<t.tipo()<<std::endl<<t.numero()<<std::endl;
	//Transformar nombre y apellidos en mayusculas
	Cadena aux=t.titular()->nombre(); 				//Para asignarle un nombre a la cadena aux modificable
	int i=0;
	while(aux[i]!='\0')
	{
		if(islower(aux[i])) aux[i]=toupper(aux[i]);		//Para pasar a mayúsculas si no lo está
		i++;
	}
	os<<aux<<" ";
	i=0;
	aux=t.titular()->apellidos();
	while(aux[i]!='\0')
	{
		if(islower(aux[i])) aux[i]=toupper(aux[i]);		//Para pasar a mayúsculas si no lo está
		i++;
	}
	os<<aux<<endl;
	os<<"Caduca: "<<std::setfill('0')<<std::setw(2)<<t.caducidad().mes()<<"/"<<std::setw(2)<<(t.caducidad().anno()%100)<<std::endl;
	return os;
}

ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo)
{
	switch(tipo)
	{
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

/*--OPERADORES LOGICOS FUERA DE LA CLASE--*/
bool operator <(const Numero& a, const Numero& b)
{
	return strcmp(a,b)<0;
}

bool operator <(const Tarjeta& a, const Tarjeta& b)
{
	return a.numero()<b.numero();
}

bool operator >(const Tarjeta& a, const Tarjeta& b)
{
	return b.numero()<a.numero();
}




