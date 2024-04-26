#include "..\..\Implementaciones\Abin.hpp"

template <typename T>
bool esPseudocompleto(Abin<T>& A) {
    if (!A.arbolVacio()) {
        size_t alturaMax = calcularAlturaMax(A, A.raiz());
        size_t alturaMin = calcularAlturaMin(A, A.raiz());


        if (alturaMax - alturaMin > 1) return false; //doubt, check question
        else if (alturaMax - alturaMin == 0) return true;
        else {
            return pseudocompleto_rec(A.raiz(), A, alturaMax - 1);
        }
    }
    else return true;
}

template <typename T>
bool pseudocompleto_rec(typename Abin<T> ::nodo n, const Abin<T>& A, unsigned altura_max, unsigned actual) {
    if (n == Abin<T> ::NODO_NULO)
        return true;
    else {
        if (altura_max == 1) // Voy restando 1 a altura_max y acabo cuando valga 1
            return (A.hijoDrcho(n) != Abin<T> ::NODO_NULO and A.hijoIzqdo(n) != Abin<T> ::NODO_NULO) or (A.hijoDrcho(n) == Abin<T> ::NODO_NULO and A.hijoIzqdo(n) == Abin<T> ::NODO_NULO);
        else
            return pseudocompleto_rec(A.hijoDrcho(n), A, altura_max - 1) and pseudocompleto_rec(A.hijoIzqdo(n), A, altura_max - 1);
    }
}

template <typename T>
size_t calcularAlturaMax(Abin<T>& A, typename Abin<T>::nodo n) {
    if (n == Abin<T>::NODO_NULO) {
        return 0;
    } else {
        return 1 + maximo(calcularAlturaMax(A, A.hijoIzqdo(n)), calcularAlturaMax(A, A.hijoDrcho(n)));
    }
}

template <typename T>
size_t calcularAlturaMin(Abin<T>& A, typename Abin<T>::nodo n) {
    if (n == Abin<T>::NODO_NULO) {
        return 0;
    } else {
        return 1 + minimo(calcularAlturaMin(A, A.hijoIzqdo(n)), calcularAlturaMin(A, A.hijoDrcho(n)));
    }
}

// @param a un entero
// @param b un entero
// @return el máximo entre esos dos valores
int maximo(int a, int b) {
    if (a >= b) return a;
    else return b;
}

// @param a un entero
// @param b un entero
// @return el mínimo entre esos dos valores
int minimo(int a, int b) {
    if (a <= b) return a;
    else return b;
}