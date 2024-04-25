#include "..\..\Implementaciones\Abin.hpp"

template <typename T>
bool esPseudocompleto(Abin<T>& A) {
    if (!A.arbolVacio()) {
        size_t alturaMax = calcularAlturaMax(A, A.raiz());
        size_t alturaMin = calcularAlturaMin(A, A.raiz());

        if (alturaMax - alturaMin > 1) return false;
        else if (alturaMax - alturaMin == 0) return true;
        else {
           return comprobarPosicionHojas(A, A.raiz());
        }
    }
    else return true;
}

template<typename T>
bool comprobarPosicionHojas(Abin<T>& A, typename Abin<T>::nodo n) {
    if (n == Abin<T>::NODO_NULO) { // dudo que funcione perfectamente, no identificará si una hoja está un nivel por encima de las demás
        return true;
    } else if (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO) {
        return true;
    } else if (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO) {
        return false;
    } else if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO) {
        return comprobarPosicionHojas(A, A.hijoIzqdo(n));
    } else {
        return comprobarPosicionHojas(A, A.hijoIzqdo(n)) && comprobarPosicionHojas(A, A.hijoDrcho(n));
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