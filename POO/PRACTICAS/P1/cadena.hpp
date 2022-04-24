#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <iterator>
#include <stdexcept>
#include <functional>

class Cadena{
private:
    size_t tam_;
    char* s_;
public:
    /*CONSTRUCTORES*/
    explicit Cadena(size_t tam=0, char c=' ');
    Cadena(const Cadena&);
    Cadena(const char*);
    Cadena(Cadena&&);

    /*OBSERVADORES*/
    //Cadena
    const char* puts() const noexcept;
    const char* puts() noexcept;
    const char* c_str() const noexcept;
    //Tamaño
    const size_t length() const noexcept;
    size_t length() noexcept;

    /*OPERADORES ASIGNACIÓN*/
    Cadena& operator+=(const Cadena&);
    Cadena& operator=(const Cadena&);
    Cadena& operator=(const char*);
    Cadena& operator=(Cadena&&);

    /*OPERACIONES ÍNDICES*/
    char& operator[](const size_t) noexcept;
    const char& operator[](const size_t) const noexcept;
    char& at(const size_t);
    const char& at(const size_t) const;
    Cadena substr(size_t, size_t) const;
    Cadena substr(int, int) const;

    /*ENTRADA-SALIDA*/
    friend std::ostream& operator<<(std::ostream&, const Cadena&) noexcept;
    friend std::istream& operator>>(std::istream&, Cadena&);

    /*ITERADORES (typedefs)*/
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    /*ITERADORES (funciones)*/
    //begin
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    //end
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    /*DESTRUCTOR*/
    ~Cadena();
};

/*OBSERVADORES*/
//Cadena
inline const char* Cadena::puts() const noexcept {return s_;}
inline const char* Cadena::puts() noexcept {return s_;}
inline const char* Cadena::c_str() const noexcept {return s_;}
//Tamaño
inline const size_t Cadena::length() const noexcept {return tam_;}
inline size_t Cadena::length() noexcept {return tam_;}

/*ITERADORES*/
//begin
inline Cadena::iterator Cadena::begin() noexcept {return s_;}
inline Cadena::const_iterator Cadena::begin() const noexcept {return const_iterator(s_);}
inline Cadena::const_iterator Cadena::cbegin() const noexcept {return const_iterator(s_);}
inline Cadena::reverse_iterator Cadena::rbegin() noexcept {return reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::rbegin() const noexcept {return const_reverse_iterator(end());}
inline Cadena::const_reverse_iterator Cadena::crbegin() const noexcept {return const_reverse_iterator(end());}
//end
inline Cadena::iterator Cadena::end() noexcept {return s_ + tam_;}
inline Cadena::const_iterator Cadena::end() const noexcept {return const_iterator(s_ + tam_);}
inline Cadena::const_iterator Cadena::cend() const noexcept {return const_iterator(s_ + tam_);}
inline Cadena::reverse_iterator Cadena::rend() noexcept {return reverse_iterator(begin());}
inline Cadena::const_reverse_iterator Cadena::rend() const noexcept {return const_reverse_iterator(begin());}
inline Cadena::const_reverse_iterator Cadena::crend() const noexcept {return const_reverse_iterator(begin());}

/*OPERADORES ARITMÉTICOS*/
Cadena operator+(const Cadena&, const Cadena&);

/*OPERADORES LÓGICOS*/
bool operator==(const Cadena&, const Cadena&);
bool operator!=(const Cadena&, const Cadena&);
bool operator<(const Cadena&, const Cadena&);
bool operator>(const Cadena&, const Cadena&);
bool operator<=(const Cadena&, const Cadena&);
bool operator>=(const Cadena&, const Cadena&);

// Para P2 y ss.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std
{               // Estaremos dentro del espacio de nombres std
    template <> // Es una especialización de una plantilla para Cadena
    struct hash<Cadena>{  // Es una clase con solo un operador publico
        size_t operator()(const Cadena &cad) const {// El operador función
            /*hash<string> hs;             // Creamos un objeto hash de string
            const char *p = cad.c_str(); // Obtenemos la cadena de la Cadena
            string s(p);                 // Creamos un string desde una cadena
            size_t res = hs(s);          // El hash del string. Como hs.operator()(s);
            return res;*/                  // Devolvemos el hash del string
            return hash <string> {}(cad.c_str());
        }
    };
}

#endif // !CADENA_HPP