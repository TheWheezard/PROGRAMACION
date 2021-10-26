#ifndef __TREN__
#define __TREN__

#include "../PILA2/pila2.hpp"
#include <assert.h>

struct Vagon
{
    int n_vagon;
};

class Tren
{
private:
    Pila<Vagon>* izda; //aux     c===== O
    Pila<Vagon>* dcha; //main           O =========D  /// O es dcha.tope()

public:
    Tren();
    void desplazarIzquierda();
    void desplazarDerecha();
    void eliminarVagon();
    void insertarVagon(Vagon);
    Vagon* mostrarVagon();
    bool trenVacio(); // T si vacio, F si al menos 1 vagon en cualquier pila
    ~Tren();
};

Tren::Tren()
{
    izda = new Pila<Vagon>();
    dcha = new Pila<Vagon>();
}

void Tren::desplazarDerecha()
{
    if (!dcha->vacia())
    {
        izda->push(dcha->tope());
        dcha->pop();
    }
}

void Tren::desplazarIzquierda()
{
    if (!izda->vacia())
    {
        dcha->push(izda->tope());
        izda->pop();
    }
}

void Tren::eliminarVagon()
{
    if (!dcha->vacia())
        dcha->pop();
    if (dcha->vacia() && !izda->vacia())
    {
        dcha->push(izda->tope());
        izda->pop();
    }    
}

void Tren::insertarVagon(Vagon v)
{
    dcha->push(v);
}

Vagon* Tren::mostrarVagon()
{
    if(!dcha->vacia())
        return dcha->tope();
}

bool Tren::trenVacio()
{
    if (dcha->vacia()&& izda->vacia())
        return true;
    else return false;    
}

Tren::~Tren()
{
    delete dcha;
    delete izda;
}


#endif