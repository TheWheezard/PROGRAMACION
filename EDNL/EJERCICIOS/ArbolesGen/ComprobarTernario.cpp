// 4. Un árbol es estrictamente ternario si todos sus nodos son hojas o tienen tres hijos.
// Escribe una función que, dado un árbol de grado arbitrario, nos indique si es o no
// estrictamente ternario. [Este ejercicio pertenece a la P5 de APOs en realidad.]

#include "..\..\Implementaciones\Agen.hpp"


template<typename T>
bool esEstrictamenteTernario(Agen<T>& A) {
    return esEstrictamenteTernarioRec(A, A.raiz());
}

template<typename T>
bool esEstrictamenteTernarioRec(Agen<T>& A, typename Agen<T>::nodo n) {
    if (n == Agen<T>::NODO_NULO || esHoja(A, n)) return true;
    else return contarHermanos(A, A.hijoIzqdo(n)) == 3;
}

template<typename T>
bool esHoja(Agen<T>& A, typename Agen<T>::nodo n) {
    return A.hijoIzqdo(n) == Agen<T>::NODO_NULO;
}

template<typename T>
int contarHermanos(Agen<T>& A, typename Agen<T>::nodo n) {
    int cont = 1;
    while (cont < 4 || A.hermDrcho(n) != Agen<T>::NODO_NULO) {
        cont++;
        n = A.hermDrcho(n);
    }
    return cont;
}