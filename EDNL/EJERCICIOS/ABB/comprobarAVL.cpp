#include "..\..\Implementaciones\Abin.hpp"
#include <vector>

/* Dado un árbol binario, comprobar si este es un AVL, árbol binario de búsqueda equilibrado */

// Recibe un árbol binario genérico (ref)
// Devuelve true si cumple la especificación de un AVL, false en caso contrario
template<typename T>
bool esAVL(Abin<T>& A) {
    // std::vector<T> vec = new std::vector<T>;
    // rellenarVector(A, A.raiz(), vec);
    // return elementosOrdenados(vec) && estaEquilibrado(A, A.raiz());
    return comparaElementos(A, A.raiz()) && estaEquilibrado(A, A.raiz());
}

// @param A un árbol binario (referencia) 
// @param n un nodo que pertenece al árbol
// @param vec un vector (referencia)
// @return (ref) el vector relleno con los elementos del árbol, en inorden
// @deprecated ya no se rellena el vector y se compara directamente sobre los elementos del árbol
template<typename T>
void rellenarVector(Abin<T>& A, typename Abin<T>::nodo n, std::vector<T>& vec) {
    if (n != Abin<T>::NODO_NULO) { 
        rellenarVector(A, A.hijoIzqdo(n), vec);
        vec.push_back(A.elemento(n));
        rellenarVector(A, A.hijoDrcho(n), vec);
    }
}

// @param vec Un vector por referencia
// @returns Devuelve true si todos los elementos están ordenados de menor a mayor, false en caso contrario
// @deprecated Ya no se compara el vector y se compara directamente sobre los elementos del árbol
template<typename T>
bool elementosOrdenados(std::vector<T>& vec) {
    int i = 1;
    bool condicion = true;
    while (i < vec.size() && condicion) {
        condicion = vec[i-1] < vec[i];
        ++i;
    }
    return condicion;
}

// @param A un árbol binario (referencia) 
// @param n un nodo que pertenece al árbol
// @return true si el árbol desde el nodo n cumple con la condición de orden
template<typename T>
bool comparaElementos(Abin<T>& A, typename Abin<T>::nodo n) {
    if (n != Abin<T>::NODO_NULO) { 
        bool checkIzdo = true;
        bool checkDcho = true;
        if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
            checkIzdo = A.elemento(A.hijoIzqdo(n)) < A.elemento(n) && comparaElementos(A, A.hijoIzqdo(n));
        if (A.hijoDrcho(n) != Abin<T>::NODO_NULO)
            checkDcho = A.elemento(A.hijoDrcho(n)) > A.elemento(n) && comparaElementos(A, A.hijoDrcho(n));
        
        return checkIzdo && checkDcho;
    }
}

// @param A un árbol binario (ref)
// @param n un nodo perteneciente al árbol
// @return true si ese nodo está equilibrado (factor de equilibrio eq: -1 <= eq <= 1)
template<typename T>
bool estaEquilibrado(Abin<T>& A, typename Abin<T>::nodo n) {
    if (n != Abin<T>::NODO_NULO) {
        int alturaIzdo = medirAltura(A, A.hijoIzqdo(n));
        int alturaDcho = medirAltura(A, A.hijoDrcho(n));
        if (-1 <= (alturaIzdo - alturaDcho) && (alturaIzdo - alturaDcho) <= 1) {
            return true && estaEquilibrado(A, A.hijoIzqdo(n)) && estaEquilibrado(A, A.hijoDrcho(n));
        } else {
            return false;
        }
    }
    else return true;
}

// @param A un árbol binario (ref)
// @param n un nodo perteneciente al árbol
// @return la altura máxima del nodo en el árbol
template<typename T>
int medirAltura(Abin<T>& A, typename Abin<T>::nodo n) {
    if (n == Abin<T>::NODO_NULO) {
        return 0;
    } else {
        return 1 + maximo(medirAltura(A, A.hijoIzqdo(n)), medirAltura(A, A.hijoDrcho(n)));
    }
}

// @param a un entero
// @param b un entero
// @return el máximo entre esos dos valores
int maximo(int a, int b) {
    if (a >= b) return a;
    else return b;
}