#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "cadena.hpp"
#include "usuario.hpp"
#include <unordered_set>

class Clave;
class Usuario;


/* CLASE NUMERO */
class Numero{
public:
    enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
    class Incorrecto{
        Razon r;
    public:
        Incorrecto(Razon raz): r(raz){}
        const Razon razon() const {return r;}
    };
    Numero(const Cadena&);
    operator const char*() const;
    const Cadena& num() const;
private:
    Cadena num_;
    Cadena elimEsp(const Cadena&); //elimina espacios en blanco
};
inline Numero::operator const char*() const {return this->num_.c_str();}
inline const Cadena& Numero::num() const {return this->num_;}

inline bool operator<(const Numero& n1, const Numero& n2){
    return n1.num() < n2.num();
}

/* CLASE TARJETA */
class Tarjeta{
public:
    friend Usuario;

    enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
    class Caducada{
        Fecha f;
    public:
        Caducada(const Fecha& fec):f(fec){}
        const Fecha& cuando() const {return f;}
    };
    class Num_duplicado{
        Numero n;
    public:
        Num_duplicado(const Numero& num):n(num){}
        const Numero que() const {return n;}
    };
    class Desactivada{
    public:
        Desactivada(){}
    };

    Tarjeta(const Numero&, Usuario&, const Fecha&);//aparte activa y tipo
    Tarjeta(const Tarjeta&) = delete;
    Tarjeta& operator=(const Tarjeta&) = delete;

    const Numero& numero() const noexcept;
    Usuario* const titular() const noexcept;
    const Fecha& caducidad() const noexcept;
    const bool activa() const noexcept;
    bool &activa(bool);
    const Tipo& tipo() const noexcept;

    ~Tarjeta();
private:
    static std::unordered_set<Cadena> numeros;
    Numero num_;
    Usuario* titular_;
    const Fecha caducidad_;
    bool activa_;
    Tipo tipo_;
    void anula_titular();

};

inline const Numero& Tarjeta::numero() const noexcept {return this->num_;}
inline Usuario* const Tarjeta::titular() const noexcept {return this->titular_;}
inline const Fecha& Tarjeta::caducidad() const noexcept {return this->caducidad_;}
inline const bool Tarjeta::activa() const noexcept {return this->activa_;}
inline bool& Tarjeta::activa(bool b=true) {return this->activa_ = b;}
inline const Tarjeta::Tipo& Tarjeta::tipo() const noexcept {return this->tipo_;}

inline bool operator<(const Tarjeta& t1, const Tarjeta& t2){
    return t1.numero() < t2.numero();
}
std::ostream& operator<<(std::ostream&, const Tarjeta::Tipo&);
std::ostream& operator<<(std::ostream&, const Tarjeta&);



#endif // !TARJETA_HPP
