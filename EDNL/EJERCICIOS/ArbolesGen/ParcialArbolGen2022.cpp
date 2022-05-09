#include "..\..\Implementaciones\Agen.hpp"

struct tNodo{
    bool vivo; // true = vivo; false = muerto
    double riqueza;
};

void repartir_herencia(Agen<tNodo>&, Agen<tNodo>::nodo);

void muerto(Agen<tNodo>& a, Agen<tNodo>::nodo n){
    if (n != Agen<tNodo>::NODO_NULO && a.elemento(n).vivo){
        a.elemento(n).vivo = false;
        repartir_herencia(a, n);
    }
}

void repartir_herencia(Agen<tNodo>& a, Agen<tNodo>::nodo n){
    int herederos = 0;
    if (a.hijoIzqdo(n) != Agen<tNodo>::NODO_NULO){ //si tiene al menos un hijo (heredero), repartimos
        ++herederos; //herederos+1
        Agen<tNodo>::nodo aux = a.hijoIzqdo(n);
        while (a.hermDrcho(aux) != Agen<tNodo>::NODO_NULO){ //sumamos el resto de herederos que tenga
            ++herederos;
            aux = a.hermDrcho(aux);
        }
        aux = a.hijoIzqdo(n);
        while (aux != Agen<tNodo>::NODO_NULO){
            a.elemento(aux).riqueza += a.elemento(n).riqueza/herederos; //actualizamos la riqueza del hijo
            if (!a.elemento(aux).vivo){ // si el hijo está muerto
                repartir_herencia(a, aux); // repartimos la herencia entre los descendientes del hijo
            }
            aux = a.hermDrcho(aux);
        }
    }
    else{ // si no tiene descendencia
        a.elemento(n).riqueza = 0; // le retiramos la riqueza
    }
}