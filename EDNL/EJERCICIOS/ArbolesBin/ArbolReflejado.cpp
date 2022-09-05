/*ÁRBOL REFLEJADO*/
/* Para un árbol binario B, podemos construir el árbol binario reflejado BR
cambiando los subárboles izquierdo y derecho en cada nodo. Implementa un subprograma
que devuelva el árbol binario reflejado de uno dado.
*/

#include "..\..\Implementaciones\Abin.hpp"

//Construye el arbol reflejado de A haciendo un recorrido en profundidad
template<typename T>
void construirReflejo(Abin<T>& A, typename Abin<T>::nodo a, Abin<T>& B, typename Abin<T>::nodo b){
    if (A.hijoIzqdo(a) != A.NODO_NULO){ //si existe hizdo de A
        B.insertarHijoDrcho(b, A.hijoIzqdo(a)->elto);
        construirReflejo(A, A.hijoIzqdo(a), B, B.hijoDrcho(b)); //avanzo en profundidad por la rama dcha de A y la rama izda de B
    }
    if (A.hijoDrcho(a) != A.NODO_NULO){ //si existe hdcho de A
        B.insertarHijoIzqdo(b, A.hijoDrcho(a)->elto);
        construirReflejo(A, A.hijoDrcho(a), B, B.hijoIzqdo(b)); //avanzo en profundidad por la rama izda de A y la rama dcha de B
    }
}

//Devuelve el arbol reflejado de A
template <typename T>
Abin<T>& arbolReflejo(Abin<T>& A){
    Abin<T>& B = new Abin<T>;
    if (!A.arbolVacio()){
        B.insertarRaiz(A.raiz()->elto);
        construirReflejo(A, A.raiz(), B, B.raiz());
    }
    return B;
}