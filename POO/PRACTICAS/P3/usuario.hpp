#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "articulo.hpp"
#include "tarjeta.hpp"

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <random>
#include <unistd.h>
#include <iterator>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>


class Numero;
class Tarjeta;


/* CLASE CLAVE */
class Clave{
public:
    enum motivo{CORTA, ERROR_CRYPT};
    class Incorrecta{
        motivo r;
    public:
        Incorrecta(motivo m):r(m){}
        const motivo razon() const {return r;}
    };

    Clave(const char*);
    const Cadena& clave() const noexcept;
    bool verifica(const char*) const noexcept;
private:
    Cadena cad;
    Cadena cifrar(const char*) const;
    Cadena cifrar(const Cadena&) const;
};

inline Clave::Clave(const char* c): cad(cifrar(c)){
    if (strlen(c) < 5)
        throw Clave::Incorrecta(Clave::CORTA);
}

inline const Cadena& Clave::clave() const noexcept{
    return this->cad;
}

/* CLASE USUARIO */
class Usuario{
public:
    typedef std::map<Cadena, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    class Id_duplicado{
        Cadena iddup;
    public:
        Id_duplicado(const Cadena& c):iddup(c){}
        Id_duplicado(const char* c):iddup(c){}
        const Cadena idd() const {return iddup;}
    };

    Usuario(const Cadena&, const Cadena&, const Cadena&, const Cadena&, const Clave&);
    Usuario(const Usuario&) = delete;
    Usuario& operator=(const Usuario&) = delete;
    
    const Cadena& id() const noexcept;
    const Cadena& nombre() const noexcept;
    const Cadena& apellidos() const noexcept;
    const Cadena& direccion() const noexcept;
    const Tarjetas& tarjetas() const noexcept;
    const Articulos& compra() const noexcept;
    const size_t n_articulos() const;

    void es_titular_de(const Tarjeta &);
    void no_es_titular_de(const Tarjeta&);
    void compra(const Articulo& art, int cantidad = 1);
    friend std::ostream& operator<<(std::ostream&, const Usuario&);
    
    ~Usuario();
private:
    static std::unordered_set<Cadena> identificadores;
    Cadena id_, nombre_, apellidos_, direccion_;
    Clave contrasenia;
    Tarjetas tarjetas_;
    Articulos compra_;
    size_t n_articulos_;
};

inline Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& clave): id_(id), nombre_(nom), apellidos_(apell), direccion_(dir), contrasenia(clave), n_articulos_(0){
    if (!(identificadores.insert(id_)).second) throw Id_duplicado(id);
}

inline const Cadena& Usuario::id() const noexcept {return this->id_;}
inline const Cadena& Usuario::nombre() const noexcept {return this->nombre_;}
inline const Cadena& Usuario::apellidos() const noexcept {return this->apellidos_;}
inline const Cadena& Usuario::direccion() const noexcept {return this->direccion_;}
inline const Usuario::Tarjetas& Usuario::tarjetas() const noexcept {return this->tarjetas_;}
inline const Usuario::Articulos& Usuario::compra() const noexcept {return this->compra_;}
inline const size_t Usuario::n_articulos() const{return this->n_articulos_;}

void mostrar_carro(std::ostream&, const Usuario&);

#endif // !USUARIO_HPP