#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>
#include <iomanip>
#include <locale>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

class Articulo{
public:
    Articulo(const Cadena&, const Cadena&, const Fecha&, double, size_t);
    const Cadena& referencia() const noexcept;
    const Cadena& titulo() const noexcept;
    const Fecha& f_publi() const noexcept;
    double precio() const noexcept;
    double& precio();
    size_t stock() const noexcept;
    size_t& stock();
private:
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha f_publicacion;
    double precio_;
    size_t ejemplares;
};

std::ostream& operator<<(std::ostream&,const Articulo&) noexcept;
inline const Cadena& Articulo::referencia() const noexcept{ return referencia_; }
inline const Cadena& Articulo::titulo() const noexcept{ return titulo_; }
inline const Fecha& Articulo::f_publi() const noexcept{ return f_publicacion; }
inline double Articulo::precio() const noexcept{ return precio_; }
inline double& Articulo::precio(){ return precio_; }
inline size_t Articulo::stock() const noexcept{ return ejemplares; }
inline size_t& Articulo::stock(){ return ejemplares; }

#endif // !ARTICULO_HPP
