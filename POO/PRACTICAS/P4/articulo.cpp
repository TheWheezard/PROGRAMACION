#include "articulo.hpp"

/*Operador de flujo de Articulo*/
std::ostream& operator<<(std::ostream& os, const Articulo& a) noexcept{
    os << "[" << a.referencia() << "] \"" << a.titulo() << "\", de ";
    
    auto iter = a.autores().begin();
    //ponemos primer autor
    os << (*iter)->apellidos();
    ++iter;
    //y todos los que queden, junto a sus respectivas comas
    while (iter != a.autores().end()){
        os << ", " << (*iter)->apellidos();
        ++iter;
    }
    
    os << ". " << a.f_publi().anno() << ". " << std::setprecision(2) << std::fixed << a.precio() << " €"
    << std::endl << "\t";
    a.impresion_especifica(os);
    return os;
}