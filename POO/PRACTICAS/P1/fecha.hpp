#ifndef FECHA_HPP
#define FECHA_HPP

#include <exception>
#include <iomanip>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <locale>

class Fecha{
private:
    int dia_, mes_, anio_;
    bool dia_correcto();
    int dia_max();

public:
    /*CONSTANTES*/
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    /*CLASE DE ERROR*/
    class Invalida{
    private:
        const char *info;

    public:
        Invalida(const char *);
        const char *por_que() const;
    };

    /*CONSTRUCTORES*/
    explicit Fecha(int dia = 0, int mes = 0, int anio = 0);
    Fecha(const char*); // conversion

    /*OBSERVADORES*/
    const int dia() const noexcept;
    const int mes() const noexcept;
    const int anno() const noexcept;

    const char* cadena() const;

    /*OPERADORES INCREMENTO*/
    Fecha& operator++();   // operador ++f
    Fecha operator++(int); // operador f++
    Fecha& operator--();   // operador --f
    Fecha operator--(int); // operador f--

    /*OPERADORES ARITMETICOS*/
    Fecha& operator+=(int);
    Fecha& operator-=(int);
    

    /*ENTRADA-SALIDA*/
    friend std::ostream& operator<<(std::ostream&, const Fecha&) noexcept;
    friend std::istream& operator>>(std::istream&, Fecha&);
};

/*OBSERVADORES*/
const inline int Fecha::dia() const noexcept{ return dia_; }
const inline int Fecha::mes() const noexcept{ return mes_; }
const inline int Fecha::anno() const noexcept{ return anio_; }

/*OPERADORES ARITMÉTICOS EXTERNOS*/
Fecha& operator+(const Fecha&, int);
Fecha& operator-(const Fecha&, int);

/*OPERADORES LÓGICOS*/
bool operator==(const Fecha&, const Fecha&) noexcept;
bool operator!=(const Fecha&, const Fecha&) noexcept;
bool operator>(const Fecha&, const Fecha&) noexcept;
bool operator<(const Fecha&, const Fecha&) noexcept;
bool operator>=(const Fecha&, const Fecha&) noexcept;
bool operator<=(const Fecha&, const Fecha&) noexcept;

#endif // !FECHA_HPP
