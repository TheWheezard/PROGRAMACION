/*EJERCICIO FEB-2022*/
/*NODOS ABUELOS Y NIETOS A LA VEZ*/
/*Implementar un programa que, dado un árbol, devuelva cuántos nodos son abuelos y nietos al mismo tiempo.*/

#include "..\..\Implementaciones\Abin.hpp"
template <typename T>
bool esAbuNieto(Abin<T>& a, typename Abin<T>::nodo n){
    bool aux = false;
    if (n == Abin<T>::NODO_NULO)
        return aux; //return false
    else{
        if (a.padre(n) != Abin<T>::NODO_NULO && a.padre(a.padre(n)) != Abin<T>::NODO_NULO){ //si tiene padre y abuelo
            if (a.hijoIzqdo(n) != Abin<T>::NODO_NULO){ // si tiene hizd
                if (a.hijoIzqdo(a.hijoIzqdo(n)) != Abin<T>::NODO_NULO || a.hijoDrcho(a.hijoIzqdo(n)) != Abin<T>::NODO_NULO){ //si hizd(n) tiene al menos un hijo
                    aux = true;
                }
            }
            if (aux == false && a.hijoDrcho(n) != Abin<T>::NODO_NULO){ //si no tiene nietos de hizd(n) y sí tiene hder(n)
                if (a.hijoIzqdo(a.hijoDrcho(n)) != Abin<T>::NODO_NULO || a.hijoDrcho(a.hijoDrcho(n)) != Abin<T>::NODO_NULO){//si hder(n) tiene al menos un hijo
                    aux = true;
                }
            }

            return aux;
        }
        else return aux; // return false
    }
}

template <typename T>
int esAbuNietoRecorrer(Abin<T>& a, typename Abin<T>::nodo n){
    if (esAbuNieto(a, n))
        return 1 + esAbuNietoRecorrer(a, a.hijoIzqdo(n)) + esAbuNietoRecorrer(a, a.hijoDrcho(n));
    else return 0 + esAbuNietoRecorrer(a, a.hijoIzqdo(n)) + esAbuNietoRecorrer(a, a.hijoDrcho(n));
}

template <typename T>
int esAbuNietoMain(Abin<T>& a){
    if (!a.arbolVacio())
        return esAbuNietoRecorrer(a, a.raiz()); //me podría saltar la raíz para ahorrar cálculos
    else return 0;
}