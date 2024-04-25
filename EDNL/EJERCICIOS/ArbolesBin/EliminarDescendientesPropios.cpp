/*
Implementa una función genérica que transforme un árbol binario de un tipo genérico T,
eliminando los descendientes propios de todos aquellos nodos cuyo contenido sea, al mismo tiempo,
mayor o igual que el de sus ascendientes propios y menor o igual que el de sus descendientes propios.
*/
#include "..\..\Implementaciones\Abin.hpp"

/*INICIO*/
//Transforma el Abin A que recibe de acuerdo al enunciado
// T debe ser un tipo que permita ser ordenado (usando <,>,<=,>=)
template<typename T>
void transformarArbolBin(Abin<T>& A){
    if (!A.arbolVacio()){
        if (A.hijoIzqdo(A.raiz()) != Abin<T>::NODO_NULO)
            recorrerAbin(A, A.hijoIzqdo(A.raiz()));
        if (A.hijoDrcho(A.raiz()) != Abin<T>::NODO_NULO)
            recorrerAbin(A, A.hijoDrcho(A.raiz()));
    }
}

//Comprueba si el nodo cumple la condición del problema
//y elimina los descendientes en caso afirmativo.
//Se detiene cuando no hay más descendientes que recorrer
template<typename T>
void recorrerAbin(Abin<T>& A, typename Abin<T>::nodo n){
    bool condicion = comparaAncestros(A, A.padre(n), A.elemento(n));
    
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO) // si tiene hIzdo
        condicion = condicion && comparaDescendientes(A, A.hijoIzqdo(n), A.elemento(n));
    
    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO) // si tiene hDcho
        condicion = condicion && comparaDescendientes(A, A.hijoDrcho(n), A.elemento(n));

    // Si cumple la condición de los Ancestros y la condición de todos los Descendientes, hacemos poda:
    if (condicion) podaAbin(A, n); 

    // descendemos en el árbol
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
        recorrerAbin(A, A.hijoIzqdo(n));
    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO)
        recorrerAbin(A, A.hijoDrcho(n));
}

//Compara el valor de un nodo con todos sus ancestros propios recursivamente
//Recibe el árbol, el ancestro del nodo que comparamos, y el elemento del nodo
//Devuelve TRUE si TODOS los ascendientes propios son MENORES O IGUALES que el elemento del nodo
template<typename T>
bool comparaAncestros(Abin<T>& A, typename Abin<T>::nodo n, T elemento){
    if (A.elemento(n) > elemento) // si n NO es menor o igual, devuelve false
        return false;
    else if (A.padre(n) != Abin<T>::NODO_NULO) // si cumple, comprueba ascendientes
        return comparaAncestros(A, A.padre(n), elemento);
    else // si llegamos a la raíz y cumple, devuelve true
        return true;
}

//Compara el valor de un nodo con todos sus descendientes propios recursivamente
//Recibe el árbol, los descendientes del nodo que comparamos, y el elemento del nodo
//Devuelve TRUE si TODOS los descendientes propios son MAYORES O IGUALES que el elemento del nodo
template<typename T>
bool comparaDescendientes(Abin<T>& A, typename Abin<T>::nodo n, T elemento){
    if (A.elemento(n) < elemento) // si n NO es mayor o igual
        return false;
    else if (A.hijoIzqdo(n) == A.hijoDrcho(n) == Abin<T>::NODO_NULO) // si n es hoja
        return true;
    else{ // Si no es hoja, comprueba
        if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO) // si existen ambos hijos
            return comparaDescendientes(A, A.hijoIzqdo(n), elemento) && comparaDescendientes(A, A.hijoDrcho(n), elemento);
        else if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO) // si solo existe hIzdo
            return comparaDescendientes(A, A.hijoIzqdo(n), elemento);
        else // si solo existe hDcho
            return comparaDescendientes(A, A.hijoDrcho(n), elemento);
    }
}

//Elimina todos los descendientes de un nodo
//Recibe un árbol y el nodo desde el que hacemos la poda
template<typename T>
void podaAbin(Abin<T>& A, typename Abin<T>::nodo n){
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO){
        podaAbin(A, A.hijoIzqdo(n));
        A.eliminarHijoIzqdo(n);
    }
    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO){
        podaAbin(A, A.hijoDrcho(n));
        A.eliminarHijoDrcho(n);
    }
}