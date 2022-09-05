#include "..\..\Implementaciones\Abin.hpp"

/*NODOS NOSTÁLGICOS*/
/*Contar cuántos nodos tienen más ancestros que sucesores*/

//Devuelve el número de ancestros del nodo n
template <typename T>
int contarAncestros(Abin<T>& a, typename Abin<T>::nodo n){
    if (n != Abin<T>::NODO_NULO)
        return 1 + contarAncestros(a, a.padre(n));
    else return 0;
}

//Devuelve el número de descendientes del nodo n
template <typename T>
int contarDescendientes(Abin<T>& a, typename Abin<T>::nodo n){
    if (n != Abin<T>::NODO_NULO)
        return 1 + contarDescendientes(a, a.hijoIzqdo(n)) + contarDescendientes(a, a.hijoDrcho(n));
    else return 0;
}

//Devuelve 1 si es nostálgico y 0 si no es nostálgico
template <typename T>
int esNostalgico(Abin<T>& a, typename Abin<T>::nodo n){
    int nAncestros = 1 + contarAncestros(a, a.padre(n));
    int nDescendientes = 1 + contarDescendientes(a, a.hijoIzqdo(n)) + contarDescendientes(a, a.hijoDrcho(n));
    if (nAncestros > nDescendientes)
        return 1;
    else
        return 0;
}

//Devuelve cuántos nodos nostálgicos hay desde el nodo n, en preorden
template <typename T>
int contarNostalgicos(Abin<T>& a, typename Abin<T>::nodo n){
    if (n != Abin<T>::NODO_NULO)
        return esNostalgico(n) + contarNostalgicos(a, a.hijoIzqdo(n)) + contarNostalgicos(a, a.hijoDrcho(n));
    else
        return 0;
}

//Devuelve cuántos nodos nostálgicos hay en el árbol a, desde la raíz
template <typename T>
int nodosNostalgicos(Abin<T>& a){
    if (a.arbolVacio())
        return 0;
    else
        return contarNostalgicos(a, a.raiz());
}