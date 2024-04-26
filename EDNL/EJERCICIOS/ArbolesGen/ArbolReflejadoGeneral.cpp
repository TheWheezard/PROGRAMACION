/* Dado un árbol general genérico A, devolver su reflejado */

#include "..\..\Implementaciones\Agen.hpp"

template <typename T>
Agen<T> arbolReflejadoGeneral(const Agen<T>& A){
    if (A.arbolVacio()) {
        return A;
    }
    else {
        Agen<T> B;
        B.insertarRaiz(A.elemento(A.raiz()));
        reflejar(A, A.hijoIzqdo(A.raiz()), B, B.raiz());
        return B;
    }
}

template <typename T>
void reflejar(const Agen<T>& A, typename Agen<T>::nodo nA, Agen<T>& B, typename Agen<T>::nodo nB) {
    if (nB != Agen<T>::NODO_NULO) {
        while (nA != Agen<T>::NODO_NULO) {
            B.insertarHijoIzqdo(nB, A.elemento(nA));
            reflejar(A, A.hijoIzqdo(nA), B, B.hijoIzqdo(nB));
            nA = A.hermDrcho(nA);
        }
    }
}
