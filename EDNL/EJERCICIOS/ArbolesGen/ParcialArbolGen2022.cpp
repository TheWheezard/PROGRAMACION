#include "..\..\Implementaciones\Agen.hpp"
#include <set>

struct tNodo{
    bool vivo; // true = vivo; false = muerto
    double riqueza;
};

void repartir_herencia(Agen<tNodo>&, Agen<tNodo>::nodo);
bool comprueba_descendientes(Agen<tNodo>&, Agen<tNodo>::nodo);

// Recibe el nodo que queremos actualizar a muerto y su árbol
// Actualiza el valor del nodo a "muerto" y procede a repartir la herencia
void muerto(Agen<tNodo>& a, Agen<tNodo>::nodo n){
    if (n != Agen<tNodo>::NODO_NULO && a.elemento(n).vivo){
        a.elemento(n).vivo = false;
        repartir_herencia(a, n);
    }
}

// Recibe un nodo muerto y el árbol al que pertenece
// Realiza el reparto de la riqueza entre sus descendientes (si tiene)
// Un descendiente se considera heredero si: (está vivo OR (está muerto PERO tiene al menos un descendiente vivo))
void repartir_herencia(Agen<tNodo>& a, Agen<tNodo>::nodo n){
    std::set<Agen<tNodo>::nodo> listaHerederos; //quería usar vector<> pero genera fallos

    if (a.hijoIzqdo(n) != Agen<tNodo>::NODO_NULO){ //si tiene al menos un hijo, contamos herederos
        if (a.elemento(a.hijoIzqdo(n)).vivo || comprueba_descendientes(a, a.hijoIzqdo(n))){
            listaHerederos.insert(a.hijoIzqdo(n));
        }

        Agen<tNodo>::nodo aux = a.hijoIzqdo(n);
        while (a.hermDrcho(aux) != Agen<tNodo>::NODO_NULO){ //sumamos el resto de herederos que tenga
            if (a.elemento(a.hermDrcho(n)).vivo || comprueba_descendientes(a, a.hermDrcho(n))){
                listaHerederos.insert(a.hermDrcho(n));
            }
            aux = a.hermDrcho(aux);
        }

        for (auto iter : listaHerederos){
            a.elemento(iter).riqueza += a.elemento(n).riqueza/listaHerederos.size(); //actualizamos la riqueza del hijo
            if (!a.elemento(iter).vivo){ // si el hijo está muerto
                repartir_herencia(a, iter); // repartimos la herencia entre los descendientes del hijo
            }
        }
    }

    a.elemento(n).riqueza = 0; // le retiramos la riqueza
}

// Recibe un nodo y el árbol al que pertenece
// Comprueba si el nodo recibido tiene al menos un descendiente vivo o no
// Devuelve un booleano: true si existe descendiente, false en caso contrario
bool comprueba_descendientes(Agen<tNodo>& a, Agen<tNodo>::nodo n){
    Agen<tNodo>::nodo aux = a.hijoIzqdo(n);
    while (aux != Agen<tNodo>::NODO_NULO){
        if (a.elemento(aux).vivo)
            return true;
        else 
            return comprueba_descendientes(a, aux);
        aux = a.hermDrcho(aux);
    }
    return false;
}