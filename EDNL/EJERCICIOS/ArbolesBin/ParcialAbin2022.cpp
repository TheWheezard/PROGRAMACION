#include "..\..\Implementaciones\Abin.hpp"

/* Implementa una función que, dado un árbol binario de tipo genérico T, devuelva el nº de nodos */
/* que, siendo hermanos entre sí, sean raíces de subárboles reflejados. */

template <typename T>
bool compara(Abin<T>& a, typename Abin<T>::nodo n1, typename Abin<T>::nodo n2){
    if (n1 == Abin<T>::NODO_NULO && n2 == Abin<T>::NODO_NULO)
        return true;
    else if (a.elemento(n1) == a.elemento(n2)) // aquí hice n1 == n2 y está mal
        return compara(a, a.hijoIzqdo(n1), a.hijoDrcho(n2)) && compara(a, a.hijoDrcho(n1), a.hijoIzqdo(n2));
    else
        return false;
}

template <typename T>
int esReflejo(Abin<T>& a, typename Abin<T>::nodo n){
    if (n != Abin<T>::NODO_NULO){
        if (a.hijoIzqdo(n) != Abin<T>::NODO_NULO && a.hijoDrcho(n) != Abin<T>::NODO_NULO && compara(a, a.hijoIzqdo(n), a.hijoDrcho(n)))
            return 2 + esReflejo(a, a.hijoIzqdo(n)) + esReflejo(a, a.hijoDrcho(n));
        else
            return 0 + esReflejo(a, a.hijoIzqdo(n)) + esReflejo(a, a.hijoDrcho(n));
    }
    else 
        return 0;
}

template <typename T>
int contarReflejos(Abin<T>& a){
    if (!a.arbolVacio())
        return esReflejo(a, a.raiz());
    else
        return 0;
}