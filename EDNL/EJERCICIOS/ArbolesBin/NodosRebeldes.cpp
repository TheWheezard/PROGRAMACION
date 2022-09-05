#include "..\..\Implementaciones\Abin.hpp"

/*NODOS REBELDES*/
/*Contar cuántos nodos tienen valores diferentes a la mayoría de sus ancestros*/

void contarValores(Abin<bool>& a, Abin<bool>::nodo n, bool valor, int& contN, int& contOp){
    //contN: contador nodos iguales a n; contOp: contador nodos opuestos
    if (n != Abin<bool>::NODO_NULO){
        if(a.elemento(n) == valor)
            contarValores(a, a.padre(n), valor, ++contN, contOp);
        else
            contarValores(a, a.padre(n), valor, contN, ++contOp);
    }
}

int esRebelde(Abin<bool>& a, Abin<bool>::nodo n){
    if (n != Abin<bool>::NODO_NULO){
        int contN = 1;
        int contOp = 0;
        contarValores(a, a.padre(n), a.elemento(n), contN, contOp);
        return (contN < contOp) + esRebelde(a, a.hijoIzqdo(n)) + esRebelde(a, a.hijoDrcho(n));
    } // en lugar de if/else pongo la condición, aprovechando conversión bool->int
    else return 0;
}

int contarRebeldes(Abin<bool>& a){
    return esRebelde(a, a.raiz());
}