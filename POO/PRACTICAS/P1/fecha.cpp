#include "fecha.hpp"
#include <new>

/*CLASE INVALIDA*/
Fecha::Invalida::Invalida(const char *in):info(in){}
const char* Fecha::Invalida::por_que() const{
    return info;
}
/*FUNCIÓN PRIVADA*/
bool Fecha::dia_correcto(){
    //Meses que acaban en 31
    if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12 ){//31 dias
        return dia_ >= 1 && dia_ <= 31;
    }
    //Meses que acaban en 30
	else if(mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11 ){//30 dias
        return dia_ >= 1 && dia_ <= 30;
    }
    //Febrero
	else if(mes_ == 2 ){
        //CONTROL BISIESTO//
		if (anio_ % 4 == 0 && (anio_ % 400 == 0 || anio_ % 100 != 0)){//anio bisiesto
            return dia_ >= 1 && dia_ <= 29;
        }
		else{//anio no bisiesto
            return dia_ >= 1 && dia_ <= 28;
        }
	}
    
    return false;
}

int Fecha::dia_max(){
    //Meses que acaban en 31
    if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12 ){//31 dias
        return 31;
    }
    //Meses que acaban en 30
	else if(mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11 ){//30 dias
        return 30;
    }
    //Febrero
	else{ //if(mes_ == 2 )
        //CONTROL BISIESTO//
		if (anio_ % 4 == 0 && (anio_ % 400 == 0 || anio_ % 100 != 0)){//anio bisiesto
            return 29;
        }
		else{//anio no bisiesto
            return 28;
        }
	}
}

/*CONSTRUCTORES*/
Fecha::Fecha(int dia, int mes, int anio):dia_(dia), mes_(mes), anio_(anio){
    std::time_t t;
    if (anio_ == 0)
    {
        t = std::time(0);
        std::tm* now = std::localtime(&t);
        anio_ = now->tm_year + 1900; //tm_year: años desde 1900
    }
    if (anio_ < AnnoMinimo || anio_ > AnnoMaximo)
    {
        throw Fecha::Invalida("Año fuera de rango");
    }
    
    if (mes_ == 0)
    {
        t = std::time(0);
        std::tm* now = std::localtime(&t);
        mes_ = now->tm_mon + 1; //tm_mon: nº meses desde enero
    }
    else
    {
        if(mes_ < 1 || mes_ > 12)
            throw Fecha::Invalida("Mes fuera de rango");
    }

    if (dia_ == 0)
    {
        t = std::time(0);
        std::tm* now = std::localtime(&t);
        dia_ = now->tm_mday;
    }
    if (!dia_correcto())
    {
        throw Fecha::Invalida("Día no es válido");
    }
}

Fecha::Fecha(const char* cad){
    dia_ = 0; mes_ = 0; anio_ = 0;
    if (sscanf(cad, "%d/%d/%d", &dia_, &mes_, &anio_) == 3)
    {
        std::time_t t;
        if (anio_ == 0)
        {
            t = std::time(0);
            std::tm *now = std::localtime(&t);
            anio_ = now->tm_year + 1900; // tm_year: años desde 1900
        }
        if (anio_ < AnnoMinimo || anio_ > AnnoMaximo)
        {
            throw Fecha::Invalida("Año fuera de rango");
        }

        if (mes_ == 0)
        {
            t = std::time(0);
            std::tm *now = std::localtime(&t);
            mes_ = now->tm_mon + 1; // tm_mon: nº meses desde enero
        }
        else
        {
            if (mes_ < 1 || mes_ > 12)
                throw Fecha::Invalida("Mes fuera de rango");
        }

        if (dia_ == 0)
        {
            t = std::time(0);
            std::tm *now = std::localtime(&t);
            dia_ = now->tm_mday;
        }
        if (!dia_correcto())
        {
            throw Fecha::Invalida("Día no es válido");
        }
    }
    else
    {
        throw Fecha::Invalida("Formato introducido inválido");
    }
}

const char* Fecha::cadena() const{
    setlocale(LC_ALL, "es_ES.UTF-8");
    char* buffer = new char[40];
    tm fec={};
    fec.tm_mday = this->dia_;
    fec.tm_mon = this->mes_ - 1;
    fec.tm_year = this->anio_ - 1900;
    
    mktime(&fec);
    strftime(buffer, 40, "%A %d de %B de %Y", &fec);
    
    return buffer;
}

/*OPERADORES INCREMENTO*/
Fecha& Fecha::operator++(){
    *this += 1;
    return *this;
}
Fecha Fecha::operator++(int){
    Fecha f(*this);
    *this += 1;
    return f;    
}
Fecha& Fecha::operator--(){
    *this -= 1;
    return *this;
}
Fecha Fecha::operator--(int){
    Fecha f(*this);
    *this -= 1;
    return f;
}

/*OPERADORES ARITMETICOS*/
Fecha& Fecha::operator+=(int i){
    while (i > 0)
    {
        if (dia_max()>= dia_ + i) // si no supera el mes
        {
            dia_ += i; // sumamos el valor
            i = 0;
        }
        else // si supera el mes
        {
            i -= (dia_max() - dia_); // restamos a i el resto de días del mes
            dia_ = 0; // primer día
            mes_ += 1;// nuevo mes
            if (mes_ > 12) //si el mes supera el tope
            {
                mes_ = 1; //primer mes
                anio_ += 1; // nuevo año
                if (anio_ > Fecha::AnnoMaximo)
                { // Comprobamos que el año es válido
                    throw Fecha::Invalida("Fecha fuera de rango");
                }
            }
        }
    }
    return *this;
}

Fecha& Fecha::operator-=(int i){
    
    while (i > 0)
    {
        if (1 <= dia_ - i) // si no supera el mes
        {
            dia_ -= i; // sumamos el valor
            i = 0;
        }
        else // si supera el mes
        {
            i -= dia_; // restamos i el día (estamos en 1 del mes)
            mes_ -= 1;// mes anterior
            if (mes_ < 1) //si el mes está bajo umbral
            {
                mes_ = 12; //último mes
                anio_ -= 1; // año anterior
                if (anio_ < Fecha::AnnoMinimo)
                { // Comprobamos que el año es válido
                    throw Fecha::Invalida("Fecha fuera de rango");
                }
                dia_ = Fecha::dia_max(); // último día
            }
            else{ // si el mes está entre 1 y 12
                dia_ = Fecha::dia_max(); // último día
            }
        }
    }
    return *this;
}
/*OPERADORES ARITMÉTICOS FUERA DE CLASE*/
Fecha& operator+(const Fecha& fecha, int i){
    Fecha* f = new Fecha(fecha);
    try
    {
        *f += i;
    }
    catch(Fecha::Invalida e)
    {
        throw e;
    }
    return *f;
}
Fecha& operator-(const Fecha& fecha, int i){
    Fecha* f = new Fecha(fecha);
    try
    {
        *f -= i;
    }
    catch(Fecha::Invalida e)
    {
        throw e;
    }
    return *f;
}

/*ENTRADA-SALIDA*/
std::ostream& operator<<(std::ostream& os, const Fecha& f) noexcept{
    setlocale(LC_ALL, "es_ES.UTF-8");
    char* buffer = new char[40];
    tm fec={};
    fec.tm_mday = f.dia_;
    fec.tm_mon = f.mes_ - 1;
    fec.tm_year = f.anio_ - 1900;
    
    mktime(&fec); 
    strftime(buffer, 40, "%A %d de %B de %Y", &fec);
    
    os << buffer;
    return os;
}

std::istream& operator>>(std::istream& is, Fecha& f){
    char* cadAux = new char[11];
    try
    {
        is.width(11);
        is >> cadAux;
        f = cadAux;
    }
    catch(Fecha::Invalida e)
    {
        is.setstate(std::ios::failbit);
        delete[] cadAux;
        throw Fecha::Invalida("Error de entrada. El formato válido es \'dd/mm/aaaa\'.");
    }
    delete[] cadAux;
    return is;
}

/*OPERADORES LÓGICOS*/
bool operator==(const Fecha& f1, const Fecha& f2) noexcept{
    return (f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno());
}

bool operator !=(const Fecha& f1, const Fecha& f2) noexcept{
    return !(f1==f2);
}

bool operator>(const Fecha& f1, const Fecha& f2) noexcept{ // f1 > f2
    if (f1.anno() > f2.anno())
    {
        return true;
    }
    else if (f1.anno() == f2.anno())
    {
        if (f1.mes() > f2.mes())
        {
            return true;
        }
        else if (f1.mes() == f2.mes())
        {
            return f1.dia() > f2.dia();
        }
        else return false;
    }
    else return false;
}

bool operator<(const Fecha& f1, const Fecha& f2) noexcept{ // f1 < f2
    return f2 > f1;
}

bool operator>=(const Fecha& f1, const Fecha& f2) noexcept{ // f1 >= f2
    return !(f1 < f2);
}

bool operator<=(const Fecha& f1, const Fecha& f2) noexcept{ // f1 <= f2
    return !(f1 > f2);
}