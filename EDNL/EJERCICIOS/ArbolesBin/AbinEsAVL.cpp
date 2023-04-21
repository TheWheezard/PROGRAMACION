#include "..\..\Implementaciones\Abin.hpp"
#include <vector>
#include <iterator>
#include <math.h>
/**
 * @file AbinEsAVL.cpp
 * @author Javier López
 * @brief Determinar si un Abin cumple las especificaciones de un AVL. Los dos requisitos
 * que determinan si un árbol es AVL son que los elementos deben estar ordenados de tal
 * manera que subárbol_izquierdo < nodo < subárbol_derecho Y el árbol debe estar equilibrado,
 * esto es que la diferencia de alturas entre la rama más corta y más larga sea 1, 0 ó -1.
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
template <typename T>
bool esAVL(Abin<T>& a) {
    if (!a.arbolVacio()) {
        std::vector<T> vec;
        rellenarVector(vec, a.raiz(), a);
        bool ordenado = true;
        auto iter = vec.begin(); // iterator al inicio
        iter++; // lo pongo en la segunda posición
        while (ordenado && iter != vec.end()) {
            ordenado = *(--iter) < *iter; // intento comparar *(iter-1) < *iter
            iter++;
        }

        if (ordenado) {
            int min = 100000000;
            int max = 0;
            return factorEquilibrio(a.raiz(), a);
        }
        else return false;
    }
    else return false;
}

/**
 * @brief Función que toma los elementos de un árbol binario a y los introduce en un vector
 * vec en inorden.
 * 
 * @tparam T tipo genérico
 * @param vec std::vector destino
 * @param n nodo del árbol binario a
 * @param a árbol binario genérico
 */
template <typename T>
void rellenarVector(std::vector<T>& vec, typename Abin<T>::nodo n, Abin<T>& a) {
    if (a.hijoIzqdo(n) != Abin<T>::NODO_NULO) {
        rellenarVector(vec, a.hijoIzqdo(n), a);
    }
    vec.push_back(a.elemento(n));
    if (a.hijoDrcho(n) != Abin<T>::NODO_NULO) {
        rellenarVector(vec, a.hijoDrcho(n), a);
    }
}

/**
 * @brief Función que comprueba el factor de equilibrio de un nodo n y sus descendientes,
 * pertenecientes a un árbol binario a.
 * 
 * @tparam T 
 * @param n nodo del árbol a
 * @param a árbol binario genérico
 * @return true 
 * @return false 
 */
template <typename T>
bool factorEquilibrio(typename Abin<T>::nodo n, Abin<T>& a) {
    if (n == Abin<T>::NODO_NULO) {
        return true;
    }
    else {
        int alturaIzqdo = medirAltura(a.hijoIzqdo(n), a);
        int alturaDrcho = medirAltura(a.hijoDrcho(n), a);
        if (estaEquilibrado(alturaIzqdo, alturaDrcho))
            return true && factorEquilibrio(a.hijoIzqdo(n), a) && factorEquilibrio(a.hijoDrcho(n), a);
        else
            return false;
    }
}

/**
 * @brief Función que calcula la altura de la rama más larga que parte del nodo n de un
 * árbol binario genérico a.
 * 
 * @tparam T 
 * @param n nodo del árbol a
 * @param a árbol binario genérico
 * @return int 
 */
template <typename T>
int medirAltura(typename Abin<T>::nodo n, Abin<T>& a) {
    if (n == Abin<T>::NODO_NULO) {
        return 0;
    }
    else {
        int alturaIzqdo = medirAltura(a.hijoIzqdo(n), a);
        int alturaDrcho = medirAltura(a.hijoDrcho(n), a);
        return 1 + std::max(alturaIzqdo, alturaDrcho);
    }
}

/**
 * @brief Función que recibe dos enteros con las alturas de dos ramas de un árbol y determina
 * si está equilibrado (True) o no (False). Para que esté equilibrado debe cumplirse que
 * -1 <= (alturaIzqdo - alturaDrcho) <= +1 .
 * 
 * @param alturaIzqdo entero, altura de un subárbol izquierdo de un nodo n
 * @param alturaDrcho entero, altura de un subárbol derecho de un nodo n
 * @return true 
 * @return false 
 */
bool estaEquilibrado(int alturaIzqdo, int alturaDrcho) {
    return (-1 <= alturaIzqdo - alturaDrcho) && (alturaIzqdo - alturaDrcho <= 1) ;
}