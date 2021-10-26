#include "cadena.hpp"

using namespace std;

/*PRIVATE*/
void Cadena::copiar(const Cadena& c){    
	tam_ = c.tam_;
	delete[] s_;
	s_ = new char[tam_ + 1];
	strcpy(s_, c.s_);
}

void Cadena::copiar(const char* c){  //copiar char*
    tam_ = strlen(c);
    delete[] s_;
    s_ = new char[tam_ + 1];
    strcpy(s_, c);
}

/*CONSTRUCTORES*/
Cadena::Cadena(size_t l, char c):tam_(l), s_(new char[l+1]) {
	while(l-->0) s_[l]=c;
	s_[tam_] = '\0';
}
Cadena::Cadena(const char* c): tam_{length(c)}, s_{new char[length(c)+1]} {
	copiar(c);
}
Cadena::Cadena(const Cadena& c):tam_{c.tam_},  s_{new char [c.tam_+1]} {
	copiar(c);
}
Cadena::Cadena(Cadena&& c): tam_(c.tam_), s_(c.s_){//movimiento
    c.tam_ = 0;
    c.s_=nullptr;
}

/*FUNCIONES*/
size_t Cadena::length(const char*s)noexcept{
	int i=0;
	while(s[i]) i++;
	return i;
}
const size_t Cadena::length(const char*s) const noexcept{
	int i=0;
	while(s[i]) i++;
	return i;
}	
const char* Cadena::c_str() const noexcept{
	return s_;
}

/*ARITMETICA*/
Cadena& Cadena::operator += (const Cadena& c){
	Cadena aux(tam_+c.tam_);//crea una cadena aux con el tamanio de ambas cadenas
	aux.s_ = new char[tam_+c.tam_+1];
	for(unsigned i=0;i<tam_;i++){
		aux.s_[i]=(*this).s_[i]; //copia la primera cadena en aux
	}
	for(unsigned i=tam_; i<tam_+c.tam_;i++){
		aux.s_[i]=c.s_[i-tam_];		//concatena la segunda cadena al final de aux
	}
	aux.s_[tam_+c.tam_]='\0'; //ponemos el caracter terminador al final
	*this=aux;
	return *this;
}

/*ASIGNACION*/
Cadena& Cadena::operator= (const Cadena& c){//cad = cad
	if ( *this != c ){
		copiar(c);
	}
	return *this;
}
Cadena& Cadena::operator= (const char* c){//cad = const char*
	Cadena aux(c);
	if ( *this != aux ){
		copiar(c);
	}
	return *this;
}
Cadena& Cadena::operator=(Cadena&&c){//movimiento
	tam_=c.tam_;
 	delete[] s_;
	s_=c.s_;
	c.tam_ = 0;
	c.s_ = nullptr;
	return *this;
}

/*INDICE*/
char& Cadena::operator[] (size_t i) noexcept{//no comprueba indice
	return s_[i];
}									
const char& Cadena::operator[] (size_t i) const noexcept{
	return s_[i];
}						

char& Cadena::at(size_t i){//comprueba indice valido
	if (i < tam_) return s_[i];  //i es unsigned int, no puede ser negativo
	else throw std::out_of_range ("Funcion at(): indice fuera de rango de la Cadena");
}
const char& Cadena::at(size_t i) const{
    if (i < tam_) return s_[i]; 																		//No se comprueba i >= 0 porque i es unsigned int, nunca puede ser menos que 0
    else throw std::out_of_range ("Funcion at(): indice fuera de rango de la Cadena");
}

Cadena Cadena::substr(size_t i, size_t tam)const{//devuelve cad desde i hasta fin   											
	if ( i > tam_ || tam > tam_ || (i + tam) > tam_)//detectamos si sale del rango
		throw std::out_of_range ("Funcion substr(): Indices fuera de rango");
	char *caux = new char[tam + 1];   //tam + \0
	int j = 0;
	unsigned int fin = i + tam;
	while ( i < fin ){
		caux[j++] = s_[i++];
	}
	caux[j] = '\0';
	Cadena cc(caux);
	delete[] caux;
	return cc;
}

/*ENTRADA - SALIDA*/
ostream& operator<<(std::ostream& os, const Cadena& c) noexcept{//salida
	os<<c.c_str();
	return os;
}
istream& operator>>(std::istream& is, Cadena& c)noexcept{//entrada
	char s[33] = "";
	is.width(33);
	is>>s;
	c = s;
	return is;
}

/*DESTRUCTOR*/
Cadena::~Cadena(){
    tam_ = 0;
    delete[] s_;
}

/*OPERADOR ARITMETICO '+'*/
Cadena operator+(const Cadena& c1, const Cadena& c2){
	Cadena caux(c1);
	return caux += c2;
}

/*OPERADORES LOGICOS --- COMPARACIONES ASCII*/
bool operator==(const Cadena& c1, const Cadena& c2){
	if(c1.length()!=c2.length()) return false;
	int tm = min(c1.length(), c2.length());
	for(int i = 0; i < tm; i++){
       	if (c1.at(i) != c2.at(i)){
			return false;
		}
	}
	return true;
}

bool operator!=(const Cadena& c1, const Cadena& c2){
	return !(c1==c2);
}

bool operator <(const Cadena& c1, const Cadena& c2){
	if(c1.length()>c2.length() ) return false;
	if(c1.length()<c2.length()) return true;
	for(int i = 0; i < (int)c1.length(); i++)
		if (c1.at(i) < c2.at(i)) 
		{
			return true;
		}
        return false; 
}

bool operator >(const Cadena& c1, const Cadena& c2){
	return  (c2<c1);
}

bool operator>=(const Cadena& c1, const Cadena& c2){
	if(c1==c2) return true;
	return  (c2<c1);
}

bool operator<=(const Cadena& c1, const Cadena& c2){
	if(c1==c2) return true;
	else return  (c1<c2);
}
