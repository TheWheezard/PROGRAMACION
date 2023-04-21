#include "..\..\Implementaciones\Abin.hpp"

/**
 * @brief Dados dos árboles binarios, realizar un método que devuelva VERDADERO 
 * si ambos árboles son simétricos y la suma de los nodos hijos (descendientes 
 * directos) es mayor que la de su nodo padre.
 */
bool simetricosYSuma(Abin<int>& a, Abin<int>& b) {
    if (!a.arbolVacio() && !b.arbolVacio()) { // si no están vacíos
        if (simetricos(a.raiz(), b.raiz(), a, b)) { // comprobamos simetría
            return sumaHijosMayor(a.raiz(), a) && sumaHijosMayor(b.raiz(), b);
        }
        else return false;
    }
    else return false; // si están vacíos no sabemos si cumplen
}

// Recibe dos nodos y dos árboles, perteneciendo el primer nodo al primer árbol
// y el segundo nodo al segundo árbol.
// Comprueba si los árboles son simétricos (si el nodo nA del árbol A tiene un nodo
// equivalente nB en el árbol B en las ramas opuestas a modo de reflejo).
// Devuelve True si los árboles son simétricos, False en caso contrario.
bool simetricos(Abin<int>::nodo nA, Abin<int>::nodo nB, Abin<int>& a, Abin<int>& b) {
    if (nA == nB) { // si nA == nB es porque nA == nB == NODO_NULO
        return true;
    }
    else if (nA != Abin<int>::NODO_NULO && nB != Abin<int>::NODO_NULO) {
        return simetricos(a.hijoIzqdo(nA), b.hijoDrcho(nB), a, b) && simetricos(a.hijoDrcho(nA), b.hijoIzqdo(nB), a, b);
    }
    else return false;
}

// Recibe un nodo n y su árbol.
// Comprueba que la suma de los hijos de n de un valor mayor que n.
// Si se cumple la condición, devuelve True & condición en los hijos; si no se cumple, devuelve False.
bool sumaHijosMayor(Abin<int>::nodo n, Abin<int>& arbol) {
    if (n != Abin<int>::NODO_NULO) {
        int sum = sumaHijos(arbol.hijoIzqdo(n), arbol.hijoDrcho(n), arbol);
        if ((arbol.hijoIzqdo(n) != Abin<int>::NODO_NULO || arbol.hijoDrcho(n) != Abin<int>::NODO_NULO) && sum > arbol.elemento(n))
            return true && sumaHijosMayor(arbol.hijoIzqdo(n), arbol) && sumaHijosMayor(arbol.hijoDrcho(n), arbol);
        else // Si ambos hijos son nulos, o n > sum
            return false;
    }
    else return true;
}

// Recibe dos nodos de un árbol, y el árbol.
// Suma los valores de los nodos. Se convierte NODO_NULO a 0 para realizar la operación correctamente.
// Devuelve el resultado de la suma.
int sumaHijos(Abin<int>::nodo hIzdo, Abin<int>::nodo hDcho, Abin<int>& arbol) {
    int sum1, sum2;

    if(hIzdo == Abin<int>::NODO_NULO)
        sum1 = 0;
    else
        sum1 = arbol.elemento(hIzdo);

    if(hDcho == Abin<int>::NODO_NULO)
        sum2 = 0;
    else
        sum2 = arbol.elemento(hDcho);
    
    return sum1 + sum2;
}