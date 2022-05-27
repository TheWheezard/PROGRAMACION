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
inline std::ostream& operator<<(std::ostream& os, Articulo& a) noexcept{ //necesario metodo con ostream en subcl
    //locale::global(locale(""));
    os << "[" << a.referencia() << "] \"" << a.titulo() << "\", " << a.f_publi().anno() <<". " << std::setprecision(2) << std::fixed << a.precio() << " €";
    os << std::endl << "\t";
    a.impresion_especifica(os);
    
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
class ArticuloAlmacenable: public Articulo{
public:
    ArticuloAlmacenable(const Autores, const Cadena&, const Cadena&, const Fecha&, double, size_t);
    size_t stock() const noexcept; //mover stock a ArticuloAlmacenable
    size_t& stock();
    virtual ~ArticuloAlmacenable();
protected:
    size_t ejemplares;
};
//Constructor
inline ArticuloAlmacenable::ArticuloAlmacenable(const Autores a, const Cadena& ref, const Cadena& titu, const Fecha& fecha, double pr, size_t existencias = 0):
    Articulo(a, ref, titu, fecha, pr), ejemplares(existencias){}
//Métodos
inline size_t ArticuloAlmacenable::stock() const noexcept{ return ejemplares; }
inline size_t& ArticuloAlmacenable::stock(){ return ejemplares; }

/*CLASE LIBRO*/
class Libro: public ArticuloAlmacenable{
public:
    Libro(const Autores, const Cadena&, const Cadena&, const Fecha&, double, size_t, size_t);
    size_t n_pag() const noexcept;
    void impresion_especifica(std::ostream&);
private:
    size_t npags;
};
//Constructor
inline Libro::Libro(const Autores a, const Cadena& ref, const Cadena& titu, const Fecha& fecha, double pr, size_t pags, size_t existencias = 0):
    ArticuloAlmacenable(a, ref, titu, fecha, pr, existencias), npags(pags){}
//Métodos
inline size_t Libro::n_pag() const noexcept{ return npags; }
inline void Libro::impresion_especifica(std::ostream& os){
    os << npags << " págs., " << ejemplares << " unidades.";
}

/*CLASE CEDERRON*/
class Cederron: public ArticuloAlmacenable{
public:
    Cederron(const Autores, const Cadena&, const Cadena&, const Fecha&, double, double, size_t);
    double tam() const noexcept;
    void impresion_especifica(std::ostream&);
private:
    double tam_;
};
//Constructor
inline Cederron::Cederron(const Autores a, const Cadena& ref, const Cadena& titu, const Fecha& fecha, double pr, double t, size_t existencias = 0):
    ArticuloAlmacenable(a, ref, titu, fecha, pr, existencias), tam_(t){}
//Métodos
inline double Cederron::tam() const noexcept{ return tam_; }
inline void Cederron::impresion_especifica(std::ostream& os){
    os << tam_ << " MB, " << ejemplares << " unidades.";
}

/*CLASE LIBRODIGITAL*/
class LibroDigital: public Articulo{
public:
    LibroDigital(const Autores, const Cadena&, const Cadena&, const Fecha&, double, const Fecha&);
    const Fecha& f_expir() const noexcept;
    void impresion_especifica(std::ostream&);
private:
    Fecha expira;
};
//Constructor
inline LibroDigital::LibroDigital(const Autores a, const Cadena& ref, const Cadena& titu, const Fecha& fecha, double pr, const Fecha& exp):
    Articulo(a, ref, titu, fecha, pr), expira(exp){}
//Métodos
inline const Fecha& LibroDigital::f_expir() const noexcept{ return expira; }
inline void LibroDigital::impresion_especifica(std::ostream& os){
    os << "A la venta hasta el " << expira << ".";
}

/*CLASE AUTOR*/
class Autor;

#endif // !ARTICULO_HPP
