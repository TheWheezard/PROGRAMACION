#include "..\..\Implementaciones\Agen.hpp"

/* Dado un árbol general de enteros A y un entero x, implementa un subprograma que realice
la poda de A a partir de x. Se asume que no hay elementos repetidos en A. */

typedef Agen<int>::nodo nodo;


/// @brief Recibe por referencia un árbol general A de tipo int, y un entero int x y Devuelve por referencia el árbol A podado desde el nodo que contiene x, si existe
/// @param A Árbol general (referencia)
/// @param x (int) entero que buscar
void podaGeneral(Agen<int>& A, int x){
    nodo n = buscarNodo(A, A.raiz(), x);
    if (n != Agen<int>::NODO_NULO)
        podar(A, n);
}

//Recibe un árbol general A (ref), un nodo n perteneciente a A, y un int x
//Devuelve el nodo n perteneciente a A donde se encuentra x o NODO_NULO si x no se encuentra
nodo buscarNodo(Agen<int>& A, nodo n, int x){
    if (A.elemento(n) == x){
        return n;
    }
    else{
        n = A.hijoIzqdo(n);
        while(n != Agen<int>::NODO_NULO){
            return buscarNodo(A, n, x);
            n = A.hermDrcho(n);
        }
    }
}

//Recibe un árbol general A (ref), y un nodo n perteneciente a A
//Devuelve A después de eliminar los descendientes del nodo n
void podar(Agen<int>& A, nodo n){
    while(A.hijoIzqdo(n) != Agen<int>::NODO_NULO){
        if(A.hijoIzqdo(A.hijoIzqdo(n)) != Agen<int>::NODO_NULO){
            podar(A, A.hijoIzqdo(n));
        }
        A.eliminarHijoIzqdo(n);
    }
}
