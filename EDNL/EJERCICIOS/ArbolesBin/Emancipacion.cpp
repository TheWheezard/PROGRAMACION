#include "..\..\Implementaciones\Abin.hpp"
#include "CopiarAbin.cpp"

template <typename T>
void poda(Abin<T>& a, typename Abin<T>::nodo n){
    if (a.hijoIzqdo(n) != Abin<T>::NODO_NULO){ // podar subárbol izquierdo
        poda(a, a.hijoIzqdo(n));
        a.eliminarHijoIzqdo(n);
    }
    if (a.hijoDrcho(n) != Abin<T>::NODO_NULO){ // podar subárbol derecho
        poda(a, a.hijoDrcho(n));
        a.eliminarHijoDrcho(n);
    }
}

template <typename T>
Abin<T> emancipar(Abin<T>& a, typename Abin<T>::nodo n){
    Abin<T> arbolEmancipado = copiar(a, n);
    poda(a, n);

    if (a.padre(n) == Abin<T>::NODO_NULO){ //si n == raíz
        a.eliminarRaiz();
    }
    else { // si no es la raíz, lo buscamos y eliminamos desde el padre
        if (a.hijoIzqdo(a.padre(n)) == n)
            a.eliminarHijoIzqdo(a.padre(n));
        else
            a.eliminarHijoDrcho(a.padre(n));
    }
    return arbolEmancipado;
}