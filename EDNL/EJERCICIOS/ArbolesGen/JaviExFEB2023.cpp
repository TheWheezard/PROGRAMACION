/**
 * Definimos como peso de un nodo la cantidad de hojas que cuelgan de este. Definimos como peso de un árbol la cantidad de hojas de ese árbol, el peso del nodo raíz.
 * Se define entonces como desequilibrio de un árbol la diferencia entre el mayor peso y el menor peso de los subárboles que cuelguen de la raíz. Implementar una    
 * función que dado un árbol general, devuelva el desequilibrio del mismo.
 * */

#include <limits>
#include "../../Implementaciones/Agen.hpp"

template <typename T>
int desequilibrioAgen(Agen<T>& A) {
    if (A.arbolVacio()) {
        return 0;
    } else {
        if (esHoja(A, A.raiz())) {
            return 0;
        } else {
            int maxPeso = 0;
            int minPeso = std::numeric_limits<int>::max();
            int aux;

            typename Agen<T>::nodo hijo = A.hijoIzqdo(A.raiz());
            while (hijo != Agen<T>::NODO_NULO) {
                aux = calcularPeso(A, hijo);
                if (aux > maxPeso) maxPeso = aux;
                if (aux < minPeso) minPeso = aux;
                
                hijo = A.hermDrcho(A, hijo);
            }

            return maxPeso - minPeso;
        }
    }
}

template <typename T>
int calcularPeso(Agen<T>& A, typename Agen<T>::nodo n) {
    if (esHoja(A, n)){
        return 1;
    } else {
        int contHojas = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO) {
            contHojas += calcularPeso(A, hijo);
            hijo = A.hermDrcho(hijo);
        }
        return contHojas;
    }
}

template <typename T>
bool esHoja(Agen<T>& A, typename Agen<T>::nodo n) {
    return A.hijoIzqdo(n) == Agen<T>::NODO_NULO;
}