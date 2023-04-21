#include "..\..\Implementaciones\Abb.hpp"
#include <math.h>
#include <vector>
#include <iterator>
/**
 * @file InfimoYSupremo.cpp
 * @author Javi López
 * @brief Realizar una función que, dado un número X y un ABB, localice el ínfimo y el supremo de X.
 * Se entiende por ínfimo de X el número más cercano a X del conjunto de números menores que X en el ABB.
 * Se entiende por supremo de X el número más cercano a X del conjunto de números mayores que X en el ABB.
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// AVISO: Se está asumiendo que a NO está vacío.
void infimoYSupremo(int& infimo, int& supremo, int numero, Abb<int>& a) {
    std::vector<int> arbol;
    extraerArbol(arbol, a);
    Abb<int> aux = a.buscar(numero);
    if (aux.vacio()) {
        auto iter = arbol.begin();
        while (*iter < numero || iter != arbol.end()) {
            iter++;
        }
        iter--;
        if (*iter > numero) { // si el número encontrado sigue sin ser ínfimo
            infimo = numero; // devolvemos número como respuesta
        }
        else {
            infimo = *iter;
        }

        iter = arbol.end();
        iter--;
        while (*iter > numero || iter != arbol.begin()) {
            iter--;
        }
        if (*iter < numero) {
            supremo = numero;
        }
        else {
            supremo = *iter;
        }
        
    }
    else {
        auto iter = arbol.begin();
        while (*iter != numero) {
            iter++;
        }

        infimo = *(--iter);
        supremo = *(++iter);
    }
}

/**
 * @brief Toma un std::vector y un árbol binario de búsqueda. Introduce los elementos ordenados
 * del ABB dentro del vector
 * 
 * @param arbol std::vector<int>
 * @param a Abb<int>
 */
void extraerArbol(std::vector<int>& arbol, Abb<int> a) {
    if (!a.izqdo().vacio()) {
        extraerArbol(arbol, a.izqdo());
    }
    arbol.push_back(a.elemento());
    if (!a.drcho().vacio()) {
        extraerArbol(arbol, a.drcho());
    }
}