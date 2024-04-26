#include "..\..\Implementaciones\Agen.hpp"

/*Se define el desequilibrio de un árbol general como la máxima diferencia entre las alturas
de los subárboles más bajo y más alto de cada nivel. Implementa un subprograma que calcule
el grado de desequilibrio de un árbol general.*/


//@param A un árbol general de tipo genérico (ref)
//@return un int con el grado de desequilibrio
template<typename T>
int desequilibrioGeneral(Agen<T>& A){
    int max = 0, min = 0;
    if (!A.arbolVacio()){
        recorrerArbol(A, A.raiz(), min, max);
    }
    return max - min;
}

//@param A un árbol general (ref)
//@param n un nodo perteneciente al árbol
//@param min referencia a entero 
//@param max referencia a entero 
//@returns (ref) la altura mínima y la altura máxima del árbol general
template<typename T>
void recorrerArbol(Agen<T>& A, typename Agen<T>::nodo n, int& min, int& max){
    int altura = 0;
    if (n != Agen<T>::NODO_NULO) {
        if (esHoja(A, n)) {
            altura = calcularAltura(A, n);
            compararAltura(altura, max, min);
        }
        n = A.hijoIzqdo(n);
        while (n != Agen<T>::NODO_NULO) {
            recorrerArbol(A, n, min, max);
            n = A.hermDrcho(n);
        }
    }
}

//@param A un árbol general (ref)
//@param n un nodo perteneciente al árbol
//@return la altura del nodo n en el árbol A
template<typename T>
int calcularAltura(Agen<T>& A, typename Agen<T>::nodo n){
    if (n == A.raiz()) {
        return 0;
    }
    else {
        return 1 + calcularAltura(A, A.padre(n));
    }
}

//@param altura un int con una altura
//@param max referencia a altura máxima
//@param min referencia a altura mínima
//@returns min y max modificados en función de si altura < min || altura > max
template<typename T>
void compararAltura(int altura, int& max, int& min){
    if (max == min == 0 && altura != 0){
        max = min = altura;
    }
    if (max < altura){
        max = altura;
    }
    if (min > altura){
        min = altura;
    }
}

//@param A (ref) árbol general
//@param n un nodo perteneciente a A
//@return si n es un nodo hoja (true) o no (false)
template<typename T>
bool esHoja(Agen<T>& A, typename Agen<T>::nodo n){
    if (A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return true;
    else return false;
}