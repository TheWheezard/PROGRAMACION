#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>
#include <iomanip>
#include <locale>
#include <set>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

/*CLASE ARTICULO*/
class Articulo{
public:
    typedef std::set<Autor*> Autores;    

    Articulo(const Autores, const Cadena&, const Cadena&, const Fecha&, double);
    const Cadena& referencia() const noexcept;
    const Cadena& titulo() const noexcept;
    const Fecha& f_publi() const noexcept;
    double precio() const noexcept;
    double& precio();
    virtual void impresion_especifica(std::ostream&) = 0;
    virtual ~Articulo();
private:
    Autores autores;
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha f_publicacion;
    double precio_;
    
};
//Operador de flujo
inline std::ostream& operator<<(std::ostream& os, const Articulo& a) noexcept{ //necesario metodo con ostream en subcl
    //locale::global(locale(""));
    os << "[" << a.referencia() << "] \"" << a.titulo() << "\", " << a.f_publi().anno() <<". " << std::setprecision(2) << std::fixed << a.precio() << " €";
    //usar dynamic_cast para aplicar polimorfismo
    return os;
}
//Constructor
inline Articulo::Articulo(const Autores a, const Cadena& ref, const Cadena& titu, const Fecha& fecha, double pr): 
    autores(a), referencia_(ref), titulo_(titu), f_publicacion(fecha), precio_(pr){}
//Métodos
inline const Cadena& Articulo::referencia() const noexcept{ return referencia_; }
inline const Cadena& Articulo::titulo() const noexcept{ return titulo_; }
inline const Fecha& Articulo::f_publi() const noexcept{ return f_publicacion; }
inline double Articulo::precio() const noexcept{ return precio_; }
inline double& Articulo::precio(){ return precio_; }


/*CLASE ARTICULOALMACENABLE*/
class ArticuloAlmacenable: virtual public Articulo{
public:
    ArticuloAlmacenable(const Autores, const Cadena&, const Cadena&, const Fecha&, double, size_t);
    size_t stock() const noexcept; //mover stock a ArticuloAlmacenable
    size_t& stock();
    virtual ~ArticuloAlmacenable();
private:
    size_t ejemplares;
};
//Constructor
inline ArticuloAlmacenable::ArticuloAlmacenable(const Autores a, const Cadena& ref, const Cadena& titu, const Fecha& fecha, double pr, size_t existencias = 0):
    Articulo(a, ref, titu, fecha, pr), ejemplares(existencias){}
//Métodos
inline size_t ArticuloAlmacenable::stock() const noexcept{ return ejemplares; }
inline size_t& ArticuloAlmacenable::stock(){ return ejemplares; }

class Libro: virtual public ArticuloAlmacenable{};
class Cederron: virtual public ArticuloAlmacenable{};
class LibroDigital: virtual public Articulo{};
class Autor;

#endif // !ARTICULO_HPP
