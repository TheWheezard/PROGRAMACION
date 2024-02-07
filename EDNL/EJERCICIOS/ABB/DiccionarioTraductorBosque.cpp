#include "..\..\Implementaciones\Abb.hpp"
#include <string>
#include <iostream>
#include <exception>

/**
 * @brief Versión mejorada del ejercicio 1 del examen de septiembre de 2019. Se trata de un diccionario traductor que permite escoger entre dos idiomas,
 * español y zuelandés. Se puede insertar una palabra con su traducción, eliminar una palabra con su traducción, buscar la traducción de una palabra, como
 * principales operaciones. Además, se puede listar todo el diccionario. Para ello se ha implementado una estructura Termino que guarda en su interior una
 * palabra y un puntero a Termino que apunta a otro término establecido como traducción. Esto se guarda en dos árboles binarios de búsqueda distintos, uno 
 * por cada idioma. Se ha decidido esto como alternativa ya que el espacio ocupado es el mismo, y al almacenar un solo idioma cada árbol, podemos reducir
 * el tiempo de bísqueda de dicho término, y su traducción.
 *
 * @file DiccionarioTraductor.cpp
 * @version 0.1
 * @date 2024-01-13
 */

struct Termino {
    std::string palabra;
    Termino* traduccion;

    Termino (std::string pal, Termino* term = nullptr): palabra(pal), traduccion(term) {}
};

class Diccionario {
public:
    enum Idioma {es, zu};
    Diccionario () {}
    Diccionario (Abb<Termino> esp, Abb<Termino> zue) : espanol(esp), zuelandes(zue) {}

    void insertar(Termino esp, Termino zue) ;
    void eliminar(const Termino t, const Idioma i);
    const Termino& buscar(const Termino t, const Idioma i) const;
    bool existe(const Termino t, const Idioma i);
    bool existe(const Termino t, const Idioma i) const;

private:
    Abb<Termino> espanol;
    Abb<Termino> zuelandes;
};

//TODO: insertar, eliminar, buscar

void Diccionario::insertar(Termino esp, Termino zue) {
    esp.traduccion = &zue;
    zue.traduccion = &esp;

    if (existe(esp, es)) eliminar(esp, es);
    if (existe(zue, zu)) eliminar(zue, zu);

    espanol.insertar(esp);
    zuelandes.insertar(zue);
}

void Diccionario::eliminar(const Termino t, const Idioma i){
    if (existe(t, i)) {
        Abb<Termino>* arbol;
        Abb<Termino>* arbolT;

        if (i == es) {
            arbol = &espanol;
            arbolT = &zuelandes;
        }
        else { // i == zu
            arbol = &zuelandes;
            arbolT = &espanol;
        }

        Termino t = arbol->buscar(t).elemento();
        arbolT->eliminar(*t.traduccion);
        arbol->eliminar(t);
    }
}

const Termino& Diccionario::buscar(const Termino t, const Idioma i) const {
    if (!existe(t, i)) return Termino("");
    else {
        const Abb<Termino>* arbol;

        if (i == es) arbol = &espanol;
        else arbol = &zuelandes;

        return *arbol->buscar(t).elemento().traduccion;
    }
}

bool Diccionario::existe(const Termino t, const Idioma i) {
    const Abb<Termino>* arbol;

    if (i == es) arbol = &espanol;
    else arbol = &zuelandes;

    return !arbol->buscar(t).vacio();
}

bool Diccionario::existe(const Termino t, const Idioma i) const {
    const Abb<Termino>* arbol;

    if (i == es) arbol = &espanol;
    else arbol = &zuelandes;

    return !arbol->buscar(t).vacio();
}
