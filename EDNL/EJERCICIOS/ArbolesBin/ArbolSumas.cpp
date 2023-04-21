#include "..\..\Implementaciones\Abin.hpp"

/**
 * @brief El árbol de sumas del árbol de enteros A, es otro árbol B con la misma estructura,
 * tal que cada nodo de B es la suma de todos los descendientes de su correspondiente en A. 
 * Implemente una función que dado un árbol A, devuelva su árbol de sumas.
 */
Abin<int> arbolSumas(Abin<int>& a) {
    Abin<int>* res = new Abin<int>{a};
    sumarDescendientes(res->raiz(), *res);

    return *res;
}

// Recibe un nodo n y su árbol a.
// Modifica el valor de n por la suma de su valor más el de sus descendientes.
// Devuelve el valor actualizado de n y modifica en el árbol el valor de n y sus descendientes.
int sumarDescendientes(Abin<int>::nodo n, Abin<int>& a) {
    if (n == Abin<int>::NODO_NULO) {
        return 0; // Si el nodo no existe, devuelvo el valor neutro para la suma de enteros
    }
    else { // Si el nodo existe, actualizamos su valor con la suma de sus descendientes.
        a.elemento(n) += sumarDescendientes(a.hijoIzqdo(n), a) + sumarDescendientes(a.hijoDrcho(n), a);
        return a.elemento(n);
    }
}