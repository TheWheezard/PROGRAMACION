/*
Implementa una función genérica que transforme un árbol binario de un tipo genérico T,
eliminando los descendientes propios de todos aquellos nodos cuyo contenido sea, al mismo tiempo,
mayor o igual que el de sus ascendientes propios y menor o igual que el de sus descendientes propios
*/

#include "..\..\Implementaciones\Abin.hpp"

// Recibe un árbol binario A, un nodo ancestro de n y un nodo n, pertenecientes a A
// Devuelve True si n.elemento >= padre.elemento y False en caso contrario
template<typename T>
bool comprobarAncestros(const Abin<T>& A, typename Abin<T>::nodo padre, T elemento){
    if (padre == Abin<T>::NODO_NULO){
        return true;
    }
    else if (A.elemento(padre) > elemento){
        return false;
    }
    else{
        return comprobarAncestros(A, A.padre(padre), elemento);
    }
}

// Recibe un árbol binario A, un nodo descendiente de n y un nodo n, pertenecientes a A
// Devuelve True si n.elemento <= padre.elemento y False en caso contrario
template<typename T>
bool comprobarDescendientes(const Abin<T>& A, typename Abin<T>::nodo hijo, T elemento){
    if (hijo == Abin<T>::NODO_NULO){
        return true;
    }
    else if (A.elemento(hijo) < elemento){
        return false;
    }
    else{
        return comprobarDescendientes(A, A.hijoIzqdo(hijo), elemento) && comprobarDescendientes(A.hijoDrcho(n), elemento);
    }
}

// Recibe un árbol binario A y un nodo n que pertenece a A
// Elimina los subárboles izquierdo y derecho que cuelguen de n
template<typename T>
void poda(Abin<T>& A, typename Abin<T>::nodo n){
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO){
        poda(A, A.hijoIzqdo(n));
        A.eliminarHijoIzqdo(n);
    }
    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO){
        poda(A, A.hijoDrcho(n));
        A.eliminarHijoDrcho(n);
    }
}

// Recibe un árbol binario de tipo genérico T y
// Elimina los descendientes propios que cumplan la especificación del enunciado
template<typename T>
void modificarArbol(Abin<T>& A, typename Abin<T>::nodo n){
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO){ // Si hIzqdo existe
        // Compruebo si cumple las condiciones
        if (comprobarAncestros(A, n, A.elemento(A.hijoIzqdo(n))) && comprobarDescendientes(A, A.hijoIzqdo(A.hijoIzqdo(n)), A.elemento(A.hijoIzqdo(n))) && comprobarDescendientes(A, A.hijoDrcho(A.hijoIzqdo(n)), A.elemento(A.hijoIzqdo(n))))
            poda(A, A.hijoIzqdo(n));
        else{ //Si no las cumple, paso al nodo hIzdo y compruebo sus hijos
            modificarArbol(A, A.hijoIzqdo(n));
        }
    }
    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO){ // Si hDcho existe
        // Compruebo si cumple las condiciones
        if (comprobarAncestros(A, n, A.elemento(A.hijoDrcho(n))) && comprobarDescendientes(A, A.hijoIzqdo(A.hijoDrcho(n)), A.elemento(A.hijoDrcho(n))) && comprobarDescendientes(A, A.hijoDrcho(A.hijoDrcho(n)), A.elemento(A.hijoDrcho(n))))
            poda(A, A.hijoDrcho(n));
        else{ //Si no las cumple, paso al nodo hDcho y compruebo sus hijos
            modificarArbol(A, A.hijoDrcho(n));
        }
    }
}

/*No requiere entrar en el hijo si hemos hecho la poda de dicho hijo, ya que entonces se habrá convertido en nodo hoja*/