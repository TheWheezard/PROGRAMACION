/*
Implemente una función que modifique un árbol binario de forma que, si el árbol tiene nodos
con un solo hijo, se elimine toda la descendencia de dichos nodos.
*/

#include "..\..\Implementaciones\Abin.hpp"

//Recibe un Abin A y un nodo n de A
//Elimina los hijos de n y sus descendientes
template<typename T>
void poda(Abin<T>& A, typename Abin<T>::nodo n){
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO){
        poda(A, A.hijoIzqdo(n));
        A.eliminarHijoIzqdo(n);
    }
    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO){
        poda(A, A.hijoDrcho(n));
        A.eliminarHijoDrcho(n);
    }
}


//Recibe un Abin A y un nodo n de A
//Se poda el hijo de n si es único, o se avanza recursivamente, hasta las hojas
template<typename T>
void recorrido(Abin<T>& A, typename Abin<T>::nodo n){
    if (n != Abin<T>::NODO_NULO){
        if ((A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO) || (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)){
            // Si solo tiene hijo izquierdo o solo tiene hijo derecho
            poda(A, n);
        }
        
        recorrido(A, A.hijoIzqdo(n));
        recorrido(A, A.hijoDrcho(n));
    }
}

//Recibe un Abin y elimina la descendencia de nodos con hijo único
template<typename T>
void eliminarHijosUnicos(Abin<T>& A){
    if (!A.arbolVacio())
        recorrido(A, A.raiz());
}