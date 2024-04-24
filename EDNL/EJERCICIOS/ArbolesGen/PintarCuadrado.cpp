// [De la práctica 5]
// 5. Una forma de representar una figura plana en blanco y negro consiste en utilizar un
// árbol cuaternario en el que cada nodo o tiene exactamente cuatro hijos, o bien es una
// hoja. Un nodo hoja puede ser blanco o negro y un nodo interno no tiene color.
// Una figura dibujada dentro de un cuadrado de lado 2^k se representa de la forma siguiente: 
// Se divide el cuadrado en cuatro cuadrantes y cada uno se representa como un
// hijo del nodo raíz. Si un cuadrante está completamente negro corresponde a una hoja
// negra; si, por el contrario, el cuadrante está completamente blanco, éste corresponde a
// una hoja blanca; y si un cuadrante está parcialmente ocupado por negro y blanco,
// entonces corresponde a un nodo interno del árbol y este cuadrante se representa
// siguiendo el mismo método subdividiéndolo en otros cuatro cuadrantes. Como ejemplo
// se muestra una figura en blanco y negro y su árbol asociado, tomando los cuadrantes en
// el sentido de las agujas del reloj a partir del cuadrante superior izquierdo.

// Implementa una función que dado un árbol de esta clase, con k+1 niveles,
// devuelva la figura asociada, representada como una matriz cuadrada de tamaño 2^k en la que 
// cada celda representa un punto blanco o negro.

// Nota: Por simplificar el problema, se asume que en cada nodo del árbol se
// incluyen las coordenadas de la esquina superior izquierda y de la esquina inferior
// derecha del cuadrante que representa.


#include "..\..\Implementaciones\Agen.hpp"
#include <cmath>

enum color { blanco, negro, vacio };

void pintarCuadrado(Agen<color>& A) {
    // 1- Comprobar si es cuaternario.
    if (!A.arbolVacio() && esEstrictamenteCuaternarioRec(A, A.raiz())) {
        // 2- Determinar valor de k.
        int k = alturaArbol(A, A.raiz()) - 1;

        // 3- Crear matriz 2^k.
        color** matriz = new color * [static_cast<int>(pow(2, k))];
        for (int i = 0; i < static_cast<int>(pow(2, k)); i++) {
            matriz[i] = new color[static_cast<int>(pow(2, k))];
        }

        // 4- Pintar determinando el algoritmo para "bajar" y recorrer.
        divideLoad(A, A.raiz(), matriz, 0, static_cast<int>(pow(2, k)), 0, static_cast<int>(pow(2, k)));
    }
}

void divideLoad(Agen<color>& A, Agen<color>::nodo n, color** matriz, int iniF, int finF, int iniC, int finC) {
    if (n != Agen<color>::NODO_NULO) {
        if (A.elemento(n) != vacio) {
            pintar(matriz, iniF, finF, iniC, finC, A.elemento(n));
        }
        else {
            Agen<color>::nodo hijo = A.hijoIzqdo(n);
            divideLoad(A, hijo, matriz, iniF, finF / 2, iniC, finC / 2);
            hijo = A.hermDrcho(hijo);
            divideLoad(A, hijo, matriz, finF / 2, finF, iniC, finC / 2);
            hijo = A.hermDrcho(hijo);
            divideLoad(A, hijo, matriz, finF / 2, finF, finC / 2, finC);
            hijo = A.hermDrcho(hijo);
            divideLoad(A, hijo, matriz, iniF, finF / 2, finC / 2, finC);
        }
    }
}

void pintar(color** matriz, int iniF, int finF, int iniC, int finC, color c) {
    for (int i = iniF; i < finF; i++) {
        for (int j = iniC; j < finC; j++) {
            matriz[i][j] = c;
        }
    }
}

bool esEstrictamenteCuaternarioRec(Agen<color>& A, typename Agen<color>::nodo n) {
    if (n == Agen<color>::NODO_NULO || esHoja(A, n)) return true;
    else return contarHermanos(A, A.hijoIzqdo(n)) == 4;
}

bool esHoja(Agen<color>& A, typename Agen<color>::nodo n) {
    return n != Agen<color>::NODO_NULO && A.hijoIzqdo(n) == Agen<color>::NODO_NULO;
}

int contarHermanos(Agen<color>& A, typename Agen<color>::nodo n) {
    int cont = 1;
    while (cont <= 4 || A.hermDrcho(n) != Agen<color>::NODO_NULO) {
        n = A.hermDrcho(n);
        cont++;
    }
    return cont;
}

int alturaArbol(Agen<color>& A, typename Agen<color>::nodo n) {
    if (n == Agen<color>::NODO_NULO) {
        return 0;
    }
    else {
        int maxAltura = 0;
        typename Agen<color>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<color>::NODO_NULO) {
            int alturaHijo = alturaArbol(A, hijo);
            if (alturaHijo > maxAltura) {
                maxAltura = alturaHijo;
            }
            hijo = A.hermDrcho(hijo);
        }
        return maxAltura + 1;
    }
}