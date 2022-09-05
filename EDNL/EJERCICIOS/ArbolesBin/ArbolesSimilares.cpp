/*ÁRBOLES SIMILARES*/
/* Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación,
es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y derecho
similares. Implementa un subprograma que determine si dos árboles binarios son similares.
*/

#include "..\..\Implementaciones\Abin.hpp"

// Devuelve si las ramas de dos árboles presentan estructura similar o no
template <typename T>
bool comprobarEstructura(Abin<T>& A, typename Abin<T>::nodo a, Abin<T>& B, typename Abin<T>::nodo b){
    if (a == A.NODO_NULO && b == B.NODO_NULO)
        return true;
    else if (a != A.NODO_NULO && b != B.NODO_NULO)
        return comprobarEstructura(A, A.hijoIzqdo(a), B, B.hijoIzqdo(b)) && comprobarEstructura(A, A.hijoDrcho(a), B, B.hijoDrcho(b)); //ambas ramas deberán ser true para devolver true
    else
        return false;
}

// Devuelve true si dos árboles son similares, false si la estructura no coincide
template <typename T>
bool arbolesSimilares(Abin<T>& A, Abin<T>& B){
    if (A.arbolVacio() && B.arbolVacio())
        return true;
    else
        return comprobarEstructura(A, A.raiz(), B, B.raiz());
}