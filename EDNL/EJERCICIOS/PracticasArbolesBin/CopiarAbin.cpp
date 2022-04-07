#include"..\..\Implementaciones\Abin.hpp"

/*ALGORITMO COPIAR ABIN*/
/*Algoritmo que permite crear un árbol a partir de un nodo de otro árbol (y los nodos que cuelguen del mismo)*/

template <typename T>
void copiarHijos(Abin<T>& aDestino, typename Abin<T>::nodo nDest, Abin<T>& aOrigen, typename Abin<T>::nodo nOrigen){
    if (nOrigen != Abin<T>::NODO_NULO){
        if (aOrigen.hijoIzqdo(nOrigen) != Abin<T>::NODO_NULO){ //insertar subárbol izquierdo
            aDestino.insertarHijoIzqdo(nDest, aOrigen.elemento(aOrigen.hijoIzqdo(nOrigen)));
            copiarHijos(aDestino, aDestino.hijoIzqdo(nDest), aOrigen, aOrigen.hijoIzqdo(nOrigen));
        }
        if (aOrigen.hijoDrcho(nOrigen) != Abin<T>::NODO_NULO){ //insertar subárbol derecho
            aDestino.insertarHijoDrcho(nDest, aOrigen.elemento(aOrigen.hijoDrcho(nOrigen)));
            copiarHijos(aDestino, aDestino.hijoDrcho(nDest), aOrigen, aOrigen.hijoDrcho(nOrigen));
        }
    }
}

template <typename T>
Abin<T> copiar(Abin<T>& aOrigen, typename Abin<T>::nodo nOrigen){
    Abin<T> aDestino; // árbol resultado
    aDestino.insertarRaiz(aOrigen.elemento(nOrigen));
    copiarHijos(aDestino, aDestino.raiz(), aOrigen, aOrigen.hijoDrcho(nOrigen)); //insertar hijos
    return aDestino;
}