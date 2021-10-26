/**almacen.hpp**/
/*Una empresa ha robotizado su almacén. Para ello lo ha dividido en 60 estantes de tres tamaños diferentes (pequeño, mediano y grande) 
a partes iguales. A cada estante se le asigna un elemento según su tamaño (en cada estante solo hay elementos de un tipo, pero puede 
haber hasta 50 elementos del mismo tipo).
Se pide diseñar un TAD para el funcionamiento del robot que incluya las siguientes operaciones:
    1. Crear un almacén vacío.
    2. Insertar un elemento en un estante. Si ya hay un estante asignado, y el elemento cabe, se coloca en ese. Si no es así, 
    se busca otro estante del mismo tamaño. Si no hay, se devuelve False. Si se puede colocar se devuelve True.
    3. Comprobar si hay elementos de un tipo determinado.
    4. Sacar un elemento de un tipo dado.
    5. Vaciar el almacén (destructor del TAD).
*/
#ifndef _ALMACEN_HPP_
#define _ALMACEN_HPP_
//#include "listaDoble.hpp"
//#include "cola.h"
#include <cassert>

enum tamanio{S,M,L};
typedef T;
typedef Cola<T>;
typedef Lista<T>;


struct Objeto
{
    int tipo_o;
    tamanio tam_o;
};

struct Estante{
    Cola<Objeto> objetos;
    int cant = 0; int topeE = 50;
}


class Almacen
{
private:
    Lista<Estante> estante_s; //20 estantes pequeños
    Lista<Estante> estante_m; //20 estantes medianos
    Lista<Estante> estante_l; //20 estantes grandes
    int tope=20;
public:
    Almacen();
    bool InsertarElemento(Objeto);
    bool ComprobarElemento(int, tamanio);
    Objeto SacarElemento(int);
    ~Almacen();
};

Almacen::Almacen()
{
    //En principio nada.
}

bool Almacen::InsertarElemento(Objeto o)
{
    bool res = false;
    Cola<Objeto>* c;
    Lista<Estante>.Posicion p;
    switch (o.tam_o)
    {
    case S:
        p = estante_s.buscar(o.tipo_o);
        break;
    case M:
        p = estante_m.buscar(o.tipo_o);
        break;
    case L:
        p = estante_l.buscar(o.tipo_o);
        break;
    default:
        break;
    }

    if(p != estante_s.fin() && p != estante_m.fin() && p != estante_l.fin())
    {
        c = 
    }
    else
    {
        /* code */
    }
    
}

Almacen::~Almacen()
{
}


#endif