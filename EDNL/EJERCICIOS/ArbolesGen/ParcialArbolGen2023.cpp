#include "..\..\Implementaciones\Agen.hpp"
/**
 * @file ParcialArbolGen2023.cpp
 * @author Javi López
 * @brief Dos árboles generales son similares si todos los nodos están en la misma posición
 * (tienen la misma estructura) y las hojas tienen los mismos elementos entre sí. Dados dos
 * árboles generales, devolver si son similares.
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief Comprueba si dos árboles generales son similares (de acuerdo a la especificación 
 * descrita en el inicio del fichero). Para ello devuelve true si las raíces son nulas (se 
 * considerará que dos árboles generales son similares si ambos están vacíos), o se devuelve
 * la comparación de sus elementos si las raíces son hojas. En cualquier otro caso, delega
 * en la función comprobarSimilares().
 * 
 * 
 * @tparam T tipo genérico para plantilla 
 * @param a árbol general genérico
 * @param b árbol general genérico
 * @return true 
 * @return false 
 */
template <typename T>
bool sonSimilares(Agen<T>& a, Agen<T>& b) {
    if (a.raiz() == Agen<T>::NODO_NULO && b.raiz() == Agen<T>::NODO_NULO) {
        return true;
    }
    else if (esHoja(a.raiz(), a) && esHoja(b.raiz(),b)) {
        return a.elemento(a.raiz()) == b.elemento(b.raiz());
    }
    else {
        return comprobarSimilares(a.raiz(), b.raiz(), a, b);
    }
}

/**
 * @brief Comprueba si el nodo nA del árbol a y el nodo nb del árbol b están ubicados en la misma posición
 * dentro de sus respectivos árboles y tienen subárboles con la misma ramificación. Y si son hojas comprueba
 * que tengan el mismo valor en su interior.
 * 
 * @tparam T tipo genérico para plantilla
 * @param nA nodo del árbol general a
 * @param nB nodo del árbol general b
 * @param a árbol general genérico
 * @param b árbol general genérico
 * @return true 
 * @return false 
 */
template <typename T>
bool comprobarSimilares(typename Agen<T>::nodo nA, typename Agen<T>::nodo nB, Agen<T>& a, Agen<T>& b) {
    if (nA == Agen<T>::NODO_NULO && nB == Agen<T>::NODO_NULO) {
        return true;
    }
    else if (esHoja(nA, a) && esHoja(nB,b)) {
        return a.elemento(nA) == b.elemento(nB);
    }
    else if (nA != Agen<T>::NODO_NULO && nB != Agen<T>::NODO_NULO) {
        typename Agen<T>::nodo hermanoA = a.hijoIzqdo(nA);
        typename Agen<T>::nodo hermanoB = b.hijoIzqdo(nB);
        bool similar = true;
        while (hermanoA != Agen<T>::NODO_NULO && hermanoB != Agen<T>::NODO_NULO && similar) {
            if (!comprobarSimilares(hermanoA, hermanoB, a, b)) {
                similar = false;
            }
            hermanoA = a.hermDrcho(hermanoA);
            hermanoB = b.hermDrcho(hermanoB);
        }
        if (hermanoA == hermanoB) 
            return similar;
        else 
            return false;
    }
    else return false;
}

/**
 * @brief Comprueba si un nodo n de un árbol general es un nodo hoja.
 * Para ello ese nodo NO PUEDE tener hijo izquierdo.
 * 
 * @tparam T tipo genérico para plantilla
 * @param n nodo del árbol general que se va a evaluar
 * @param arbol árbol general genérico
 * @return true 
 * @return false 
 */
template <typename T>
bool esHoja(typename Agen<T>::nodo n, Agen<T>& arbol) {
    return arbol.hijoIzqdo(n) == Agen<T>::NODO_NULO;
}