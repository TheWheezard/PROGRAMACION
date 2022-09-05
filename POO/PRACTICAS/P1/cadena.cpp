#include "cadena.hpp"

/*CONSTRUCTORES*/
Cadena::Cadena(size_t tam, char c): tam_(tam), s_(new char[tam+1]){
    size_t i = 0;
    while (i < tam_)
    {
        s_[i] = c;
        ++i;
    }
    s_[tam_] = '\0';    
}

Cadena::Cadena(const Cadena& cad): tam_(cad.tam_),s_(new char[cad.tam_+1]){
    strcpy(this->s_, cad.s_);
}

Cadena::Cadena(const char* cad): tam_(strlen(cad)), s_(new char[strlen(cad)+1]){
    strcpy(this->s_, cad);
    this->s_[this->tam_] = '\0';
}

Cadena::Cadena(Cadena&& cad): tam_(cad.tam_), s_(cad.s_){
    cad.tam_ = 0;
    cad.s_ = nullptr;
}

/*OPERADORES ASIGNACIÓN*/
Cadena& Cadena::operator+=(const Cadena& cad){
    // creamos Cadena auxiliar
    Cadena *aux = new Cadena(this->tam_ + cad.tam_);
    // volcamos s_
    for(size_t i=0; i<this->tam_; ++i){
		aux->s_[i] = this->s_[i];
	}
    // volcamos cad.s_
    for(size_t i=this->tam_; i<aux->tam_; ++i){
		aux->s_[i] = cad.s_[i-this->tam_];
	}
    aux->s_[aux->tam_] = '\0';//caracter final
    
    *this = *aux;
    aux = nullptr;
    return *this;
}

Cadena& Cadena::operator=(const Cadena& cad){
    if (*this != cad) // si son iguales, no se hace nada
    {
        this->tam_ = cad.tam_; //actualizamos tam
        char* aux = new char[tam_ + 1];
        for(size_t i=0; i<=cad.tam_; ++i){
		    aux[i] = cad.s_[i];
	    }
        delete[] this->s_; //eliminamos char[] original
        this->s_ = aux; //nuevo char[tam]
        aux = nullptr;
    }
    return *this;
}

Cadena& Cadena::operator=(const char* cad){
    if (strcmp(this->s_,cad) != 0)
    {
        this->tam_ = strlen(cad);
        char* aux = new char[tam_ + 1];
        strcpy(aux, cad);
        delete[] this->s_;
        this->s_ = aux;
        aux = nullptr;
    }
    return *this;
}

Cadena& Cadena::operator=(Cadena&& cad){
    this->tam_ = cad.tam_;
    delete[] this->s_;
    this->s_ = cad.s_;
    cad.tam_ = 0;
    cad.s_ = nullptr;
    return *this;
}

/*OPERADORES ARITMÉTICOS*/
Cadena operator+(const Cadena& c1, const Cadena& c2){
    Cadena res(c1);
    return res += c2;
}

/*OPERADORES COMPARACIÓN*/
bool operator==(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1.puts(), c2.puts()) == 0);
}

bool operator!=(const Cadena& c1, const Cadena& c2){
    return !(c1==c2);
}

bool operator<(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1.puts(), c2.puts()) < 0);
}

bool operator>(const Cadena& c1, const Cadena& c2){
    return c2 < c1;
}

bool operator<=(const Cadena& c1, const Cadena& c2){
    return !(c1 > c2);
}

bool operator>=(const Cadena& c1, const Cadena& c2){
    return !(c1 < c2);
}

/*OPERACIONES INDICES*/
char& Cadena::operator[](const size_t i) noexcept{
    return s_[i];
}
const char& Cadena::operator[](const size_t i) const noexcept{
    return s_[i];
}
char& Cadena::at(const size_t i){
    if (i >= 0 && i < this->tam_) // está en el rango 0 < i < tam
    {
        return this->s_[i];
    }
    else
    {
        throw std::out_of_range("Índice fuera de rango");
    }
}
const char& Cadena::at(const size_t i) const{
    if (i >= 0 && i < this->tam_) // está en el rango 0 < i < tam
    {
        return this->s_[i];
    }
    else
    {
        throw std::out_of_range("Índice fuera de rango");
    }
}

Cadena Cadena::substr(size_t i, size_t tam) const{
    if (i + tam < this->tam_) 
    {
        char* auxcad = new char[tam + 1];
        size_t cont = 0;
        while (i < this->tam_ && cont <= tam)
        {
            auxcad[cont] = this->at(i);
            ++i; ++cont;
        }
        auxcad[tam] = '\0';
        Cadena cad(auxcad);
        delete[] auxcad;
        return cad;
    }
    else
    {
        throw std::out_of_range("Parámetros fuera de rango");
    }
}

Cadena Cadena::substr(int i, int tam) const{
    if (i < 0 || tam < 0)
        throw std::out_of_range("Parámetros fuera de rango");
    else
    {
        size_t indice = i;
        size_t tammanio = tam;
        return substr(indice, tammanio);
    }
}

/*ENTRADA-SALIDA*/
std::ostream& operator<<(std::ostream& os, const Cadena& cad) noexcept{
    os << cad.c_str();
    return os;
}
std::istream& operator>>(std::istream& is, Cadena& cad){
    char s[33] = "";
    is.width(33);
    is >> s;
    cad = s;
    return is;
}

/*DESTRUCTOR*/
Cadena::~Cadena(){
    delete[] this->s_;
}