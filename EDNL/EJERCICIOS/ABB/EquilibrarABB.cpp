#include "..\..\Implementaciones\Abb.hpp"
#include <vector>

/* Un árbol binario de búsqueda se puede equilibrar realizando el recorrido en inorden
del árbol para obtener el listado ordenado de sus elementos y a continuación, repartir
equitativamente los elementos a izquierda y derecha colocando la mediana en la raíz y
construyendo recursivamente los subárboles izquierdo y derecho de cada nodo.
Implementa este algoritmo para equilibrar un ABB.*/



/// @brief Función que recibe un árbol binario de búsqueda A (ref) y lo devuelve equilibrado.
/// @tparam T Tipo genérico
/// @param A (ref) Árbol binario de búsqueda
template<typename T>
void equilibrarABB(Abb<T>& A){
    std::vector<T> vec = new std::vector<T>;
    extraerEltos(A, vec);
    Abb<T>& B = new Abb<T>;
    int ini = 0; int fin = vec.size();
    rellenarABB(B, vec, ini, fin);
    A = B;
    B = nullptr;
}

//Recibe un ABB (ref) y un vector (ref), ambos de tipo genérico T
//Extrae en inorden los elementos de un ABB y los introduce en un vector
//Devuelve (ref) el vector con los elementos del ABB ordenados
template<typename T>
void extraerEltos(Abb<T>& A, std::vector<T>& vec){
    extraerEltos(A.izqdo(), vec);
    if (!A.vacio()){
        vec.push_back(A.elemento());
    }
    extraerEltos(A.drcho(), vec);
}

//Recibe un ABB (ref), un vector (ref) y dos enteros ini y fin
//Introduce en el ABB el valor de la posición del vector que se encuentra en el centro de las posiciones marcadas por ini y fin
//Devuelve (ref) el ABB relleno con los valores del vector
template<typename T>
void rellenarABB(Abb<T>& A, std::vector<T>& vec, int ini, int fin){
    if (ini != fin) {
        posicion = (ini + fin) / 2;
        A.insertar(vec[posicion]);
        rellenarABB(A, vec, ini, posicion);
        rellenarABB(A, vec, posicion + 1, fin);
    }
}

