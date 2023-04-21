#include "..\..\Implementaciones\Agen.hpp"
#include <math.h>
/**
 * @file DesequilibrioPesosGeneral.cpp
 * @author Javi López
 * @brief Entenderemos como desequilibrio de pesos de un nodo la máxima diferencia
 * de pesos de los subárboles de ese nodo. El peso de un nodo será el número de nodos hoja
 * que cuelgan de dicho subárbol. El desequilibrio de pesos de un árbol general será calculado
 * desde la raíz de dicho árbol general.
 * Crear un programa que dado un árbol general devuelva su desequilibrio de pesos.
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief Función que recibe un árbol general a, y devuelve su grado de desequilibrio de pesos.
 * En caso de que a esté vacío o solo tenga raíz, devolverá 0.
 * 
 * @tparam T 
 * @param a árbol Agen<T>&
 * @return int
 */
template <typename T>
int desequilibrioPesosGeneral(Agen<T>& a) {
    int pesoMin = 10000000;
    int pesoMax = 0;
    if (a.arbolVacio() || esHoja(a.raiz(), a)) {
        return 0;
    }
    else {
        Agen<T>::nodo hijo = a.hijoIzqdo(a.raiz());
        int suma = 0;
        while (hijo != Agen<T>::NODO_NULO) {
            suma += calcularPesos(hijo, a);

            if (pesoMin > suma) { // si suma < pesoMin
                pesoMin = suma; // usamos suma
            }
            if (pesoMax < suma) { // si suma > pesoMax
                pesoMax = suma; // usamos suma
            }

            hijo = a.hermDrcho(hijo);
        }

        return abs(max - min);
    }
}

/**
 * @brief Función que calcula los pesos de un nodo n de un árbol general a. Descenderá hasta los
 * nodos hoja, y subirá sumando los resultados para devolverlos.
 * 
 * @tparam T 
 * @param n nodo del árbol general a
 * @param a árbol general Agen<T>&
 * @return int 
 */
template <typename T>
int calcularPesos(typename Agen<T>::nodo n, Agen<T>& a) {
    if (n == Agen<T>::NODO_NULO) { // En teoría no es necesario
        return 0;
    }
    else if (esHoja(n, a)) {
        return 1;
    }
    else {
        Agen<T>::nodo hijo = a.hijoIzqdo(n);
        int suma = 0;
        while (hijo != Agen<T>::NODO_NULO) {
            suma += calcularPesos(hijo, a);
            hijo = a.hermDrcho(hijo);
        }
        return suma;
    }
}

/**
 * @brief Comprueba si un nodo n del árbol general a es hoja o no.
 * Devuelve True si el nodo es hoja, devuelve False en caso contrario.
 * (Si n no tiene hijo izqdo, entonces n no tiene descendientes).
 * @tparam T 
 * @param n nodo de a
 * @param a árbol general Agen<T>&
 * @return true
 * @return false
 */
template <typename T>
bool esHoja(typename Agen<T>::nodo n, Agen<T>& a) {
    return a.hijoIzqdo(n) == Agen<T>::NODO_NULO;
}