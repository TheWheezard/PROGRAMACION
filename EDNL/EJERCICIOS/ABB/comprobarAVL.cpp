#include "..\..\Implementaciones\Abin.hpp"
#include <vector>

/* Dado un árbol binario, comprobar si este es un AVL, árbol binario de búsqueda equilibrado*/

// Recibe un árbol binario genérico (ref)
// Devuelve true si cumple la especificación de un AVL, false en caso contrario
template<typename T>
bool esAVL(Abin<T>& A){
    std::vector<T> vec = new std::vector<T>;
    rellenarVector(A, A.raiz(), vec);
    return elementosOrdenados(vec) && estaEquilibrado(A, A.raiz());
}

// Recibe un árbol binario (ref), un nodo que pertenece al árbol y un vector (ref)
// Devuelve (ref) el vector relleno con los elementos del árbol, en inorden
template<typename T>
void rellenarVector(Abin<T>& A, typename Abin<T>::nodo n, std::vector<T>& vec){
    if (n != Abin<T>::NODO_NULO) {
        rellenarVector(A, A.hijoIzqdo(n), vec);
        vec.push_back(A.elemento(n));
        rellenarVector(A, A.hijoDrcho(n), vec);
    }
}

// Recibe un vector (ref)
// Devuelve true si todos los elementos están ordenados de menor a mayor, false en caso contrario
template<typename T>
bool elementosOrdenados(std::vector<T>& vec){
    int i = 1;
    bool condicion = true;
    while (i < vec.size() && condicion){
        if (vec[i-1] > vec[i]){
            condicion = false;
        }
        ++i;
    }
    return condicion;
}

// Recibe un árbol binario (ref) y un nodo perteneciente al árbol
// Devuelve si ese nodo está equilibrado o no (factor de equilibrio eq: -1 <= eq <= 1)
template<typename T>
bool estaEquilibrado(Abin<T>& A, typename Abin<T>::nodo n){
    if (n != Abin<T>::NODO_NULO) {
        int alturaIzdo = medirAltura(A, A.hijoIzqdo(n));
        int alturaDcho = medirAltura(A, A.hijoDrcho(n));
        if (-1 <= (alturaIzdo - alturaDcho) && (alturaIzdo - alturaDcho) <= 1) {
            return true && estaEquilibrado(A, A.hijoIzqdo(n)) && estaEquilibrado(A, A.hijoDrcho(n));
        }
        else {
            return false;
        }
    }
    else return true;
}

// Recibe un árbol binario (ref) y un nodo perteneciente al árbol
// Devuelve la altura máxima del nodo en el árbol
template<typename T>
int medirAltura(Abin<T>& A, typename Abin<T>::nodo n){
    if (n == Abin<T>::NODO_NULO){
        return 0;
    }
    else {
        return 1 + maximo(medirAltura(A, A.hijoIzqdo(n)), medirAltura(A, A.hijoDrcho(n)));
    }
}

// Recibe dos enteros
// Devuelve el máximo entre esos dos valores
int maximo(int a, int b){
    if (a >= b){
        return a;
    }
    else return b;
}