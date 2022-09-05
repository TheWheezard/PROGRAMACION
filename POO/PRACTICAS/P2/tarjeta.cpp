#include "tarjeta.hpp"
//#include "../luhn.cpp"

#include <iomanip>
#include <cstring>
#include <cctype>

/* CLASE NUMERO */
bool luhn(const Cadena& numero);
Numero::Numero(const Cadena& cad):num_(elimEsp(cad)){
    for(size_t i = 0; num_[i] != '\0'; ++i)
        if (!isdigit(num_[i])) throw Incorrecto(DIGITOS);
    if (num_.length() < 13 || num_.length() > 19) throw Incorrecto(LONGITUD);
    if (!luhn(num_)) throw Incorrecto(NO_VALIDO);
}

Cadena Numero::elimEsp(const Cadena& cad){
    char* aux = new char[cad.length()+1];
    size_t i = 0;
    size_t j = 0;
    while (cad[i] != '\0'){
        if (!isspace(cad[i])){
            aux[j] = cad[i];
            ++j;
        }
        ++i;
    }
    aux[j] = cad[i];
    return Cadena {aux};
}

/* CLASE TARJETA */
std::unordered_set<Cadena> Tarjeta::numeros;
Tarjeta::Tarjeta(const Numero& num, Usuario& us, const Fecha& f):num_(num), titular_(&us), caducidad_(f), activa_(true){
    //if (!numeros.insert(num.num()).second) throw Num_duplicado(num);
    Fecha hoy{};
    if (f < hoy) throw Caducada(f);
    switch (num_.num()[0])
    {
    case '3': // dig 3
        {
        if (num_.num()[1] == '4' || num_.num()[1] == '7') //dig 3 && (4|7)
            tipo_ = AmericanExpress;
        else //dig 3 && !(4|7)
            tipo_ = JCB;
        break;
        }
    case '4': {
        tipo_ = VISA;
        break;
        }
    case '5': {
        tipo_ = Mastercard;
        break;
        }
    case '6': {
        tipo_ = Maestro;
        break;
        }
    default: {
        tipo_ = Otro;
        break;
        }
    }
    titular_->es_titular_de(*this);
}
void Tarjeta::anula_titular(){
    this->activa_ = false;
    this->titular_ = nullptr;
}
Tarjeta::~Tarjeta(){
    //numeros.erase(this->numero().num());
    if (this->titular_ != nullptr){
        this->titular_->no_es_titular_de(*this);
    }
}


//Salida Tipo
std::ostream& operator<<(std::ostream& os, const Tarjeta::Tipo& t){
    switch (t){
    case Tarjeta::Otro:
        os << "Otro";
        break;
    case Tarjeta::VISA:
        os << "VISA";
        break;
    case Tarjeta::Mastercard:
        os << "Mastercard";
        break;
    case Tarjeta::Maestro:
        os << "Maestro";
        break;
    case Tarjeta::JCB:
        os << "JCB";
        break;
    case Tarjeta::AmericanExpress:
        os << "American Express";
        break;
    
    default:
        os << "Error";
        break;
    }
    return os;
}
//Salida Tarjeta
std::ostream& operator<<(std::ostream& os, const Tarjeta& t){
// Inicio de la tarjeta
    os  << " ____________________" << std::endl
        << "/                    \\" <<std::endl;
// Tipo de la tarjeta
    switch (t.tipo())
    {
    case Tarjeta::Otro:
        os << "| " << t.tipo() << "               |" << std::endl;
        break;
    case Tarjeta::VISA:
        os << "| " << t.tipo() << "               |" << std::endl;
        break;
    case Tarjeta::Mastercard:
        os << "| " << t.tipo() << "         |" << std::endl;
        break;
    case Tarjeta::Maestro:
        os << "| " << t.tipo() << "            |" << std::endl;
        break;
    case Tarjeta::JCB:
        os << "| " << t.tipo() << "                |" << std::endl;
        break;
    case Tarjeta::AmericanExpress:
        os << "| " << t.tipo() << "   |" << std::endl;
        break;
    
    default:
        os << "Error" << std::endl;
        break;
    }
// Numero de la tarjeta
    os << "| " << t.numero();
    int cont = 19 - t.numero().num().length(); // conteo de los espacios restantes hasta '|'
    while (cont > 0){
        os << " "; // tantos espacios como haga falta para llegar a '|'
        --cont;
    }
    os << "|" << std::endl;
// Usuario de la tarjeta
    //Nombre
    Cadena aux {t.titular()->nombre()};
    for(size_t i = 0; aux[i] != '\0'; ++i){
        if (islower(aux[i]))
            aux[i] = toupper(aux[i]);
    }
    cont = 19 - aux.length(); // conteo de los espacios restantes hasta '|'
    os << "| " << aux << " ";
    --cont; // espacio
    //Apellidos
    aux = t.titular()->apellidos();
    for(size_t i = 0; aux[i] != '\0'; ++i){
        if (islower(aux[i]))
            aux[i] = toupper(aux[i]);
    }
    cont -= aux.length();
    os << aux;
    while (cont > 0){
        os << " "; // tantos espacios como haga falta para llegar a '|'
        --cont;
    }
    os << "|" << std::endl;
// Caducidad y fin
    os << "| Caduca: " << std::setfill('0') << std::setw(2) << t.caducidad().mes() << "/" << std::setw(2) << t.caducidad().anno()%100 << "      |" << std::endl
       << "\\____________________/";
    
    return os;
}
