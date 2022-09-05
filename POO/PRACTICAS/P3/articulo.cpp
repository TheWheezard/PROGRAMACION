#include "articulo.hpp"


Articulo::Articulo(const Cadena& ref, const Cadena& titu, const Fecha& fecha, double pr, size_t existencias = 0):
    referencia_(ref), titulo_(titu), f_publicacion(fecha), precio_(pr), ejemplares(existencias){}

std::ostream& operator<<(std::ostream& os, const Articulo& a) noexcept{
    //locale::global(locale(""));
    os << "[" << a.referencia() << "] \"" << a.titulo() << "\", " << a.f_publi().anno() <<". " << std::setprecision(2) << std::fixed << a.precio() << " €";
    return os;
}