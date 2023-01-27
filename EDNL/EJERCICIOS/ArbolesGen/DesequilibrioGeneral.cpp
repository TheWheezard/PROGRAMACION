#include "..\..\Implementaciones\Agen.hpp"

/*Se define el desequilibrio de un árbol general como la máxima diferencia entre las alturas
de los subárboles más bajo y más alto de cada nivel. Implementa un subprograma que calcule
el grado de desequilibrio de un árbol general.*/


//Recibe un árbol general de tipo genérico A (ref)
//Devuelve un int con el grado de desequilibrio
template<typename T>
int desequilibrioGeneral(Agen<T>& A){
    int max = 0, min = 0;
    if (!A.arbolVacio()){
        recorrerArbol(A, A.raiz(), min, max);
    }
    return max - min;
}

//Recibe un árbol general A (ref), un nodo n perteneciente al árbol, y referencias a dos enteros min y max
//Devuelve (ref) la altura mínima y la altura máxima del árbol general
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

//Recibe un árbol general A (ref) y un nodo n perteneciente al árbol
//Devuelve la altura del nodo n en el árbol A
template<typename T>
int calcularAltura(Agen<T>& A, typename Agen<T>::nodo n){
    if (n == A.raiz()) {
        return 0;
    }
    else {
        return 1 + calcularAltura(A, A.padre(n));
    }
}

//Recibe un int con una altura, y los valores min y max (refs)
//Devuelve min y max modificados en función de si altura < min || altura > max
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

//Recibe un árbol general A (ref) y un nodo n perteneciente a A
//Devuelve si n es un nodo hoja (true) o no (false)
template<typename T>
bool esHoja(Agen<T>& A, typename Agen<T>::nodo n){
    if (A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return true;
    else return false;
}