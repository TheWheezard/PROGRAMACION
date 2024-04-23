/*
Implementa una funcion generica que transforme un arbol general de un tipo genérico T,
eliminando los descendientes propios de todos aquellos nodos cuyo contenido sea, al mismo tiempo,
mayor o igual que el de sus ascendientes propios y menor o igual que el de sus descendientes propios.
*/

#include "..\..\Implementaciones\Agen.hpp"

template <typename T>
void transformarAgen(Agen<T>& A) {
    if (!A.arbolVacio()) {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(A.raiz());
        while (hijo != Agen<T>::NODO_NULO) { // Nos saltamos la raíz, porque no tiene ancestros propios
            transformarAgenRec(A, hijo);
            A.hermDrcho(hijo);
        }
    }
}

template <typename T>
void transformarAgenRec(Agen<T>& A, typename Agen<T>::nodo n) {
    if (n != Agen<T>::NODO_NULO) {
        bool checkDescendientes = true;
        typename Agen<T>::nodo iter = A.hijoIzqdo(n);

        while (iter != Agen<T>::NODO_NULO || checkDescendientes) {
            checkDescendientes = verificarDescendientes(A, iter, A.elemento(n));
            iter = A.hermDrcho(iter);
        }
        
        if (verificarAncestros(A, A.padre(n), A.elemento(n)) && checkDescendientes) {
            poda(A, n);
        }

        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO) {
            transformarAgenRec(A, hijo);
            A.hermDrcho(hijo);
        }
    }
}

// Comprueba que se cumple elemento >= A.elemento(ancestros(n))
template <typename T>
bool verificarAncestros(Agen<T>& A, typename Agen<T>::nodo n, T elemento) {
    if (n == Agen<T>::NODO_NULO) {
        return true;
    } else if (elemento >= A.elemento(n)) {
        return verificarAncestros(A, A.padre(n), elemento);
    } else return false;
}

template <typename T>
bool verificarDescendientes(Agen<T>& A, typename Agen<T>::nodo n, T elemento) {
    if (n == Agen<T>::NODO_NULO) {
        return true;
    } else if (elemento <= A.elemento(n)) {
        bool checkDesc = true;
        typename Agen<T>::nodo iter = A.hijoIzqdo(n);

        while (iter != Agen<T>::NODO_NULO || checkDesc) {
            checkDesc = verificarDescendientes(A, iter, A.elemento(n));
            iter = A.hermDrcho(iter);
        }
        
        return checkDesc;
    } else return false;
}

template <typename T>
void poda(Agen<T>& A, typename Agen<T>::nodo n) {
    while (A.hijoIzqdo(n) != Agen<T>:NODO_NULO) {
        poda(A, A.hijoIzqdo(n));
        A.eliminarHijoIzqdo(n);
    }
}