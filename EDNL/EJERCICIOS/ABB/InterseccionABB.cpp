#include "..\..\Implementaciones\Abb.hpp"
#include <vector>


// Recibe dos árboles binarios de búsqueda (ABB) (ref) del mismo tipo
// Devuelve un ABB con solo los valores que se encuentran en ambos ABB de entrada a la vez
template<typename T>
Abb<T> interseccionABB(Abb<T>& A, Abb<T>& B){
    Abb<T> I = new Abb<T>;
    I = A;
    filtrarElementos(I, B);
    equilibrarABB(I);
    return I;
}

// Recibe dos ABB (ref) del mismo tipo
// Modifica el primero, eliminando los elementos que no se encuentran en el segundo ABB
template<typename T>
void filtrarElementos(Abb<T>& A, Abb<T>& B){
    if(!A.vacio()){
        if(B.buscar(A.elemento()) == nullptr){
            A.eliminar(A.elemento());
        }
        filtrarElementos(A.izqdo(), B);
        filtrarElementos(A.drcho(), B);
    }
}

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
