#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "abin.h"
#include "abin_E-S.h"

using namespace std;


// Para hacer el ejercicio 6, es necesario haber hecho el ejercicio 2 (altura) y diseñar una función que cuente el número de hijos de un nodo
// Ejercicio 2 (altura)
template <typename T>
int altura(const Abin<T> &A)
{
    return altura_rec(A.raizB(), A);
}

template <typename T>
int altura_rec(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
        return -1;
    else
        return 1 + max(altura_rec(A.hijoIzqdoB(n), A), altura_rec(A.hijoDrchoB(n), A));
}

//Función que cuenta hijos:
template <typename T>
int contarHijos(typename Abin<T>::nodo n, const Abin<T> &A)
{ //esta función devuelve el número de hijos de un nodo
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
        return (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO) + (A.hijoDrchoB(n) != Abin<T>::NODO_NULO);
}

/*
* 7. Implementa un subprograma que determine si un árbol binario es o no pseudocompleto.
* En este problema entenderemos que un árbol es pseudocompleto, si en el penúltimo nivel
* del mismo cada uno de los nodos tiene dos hijos o ninguno.
*/
template <typename T>
bool esPseudocompleto(const Abin<T> &A)
{
    return esPseudocompleto_rec(A.raizB(), A, altura(A)-1);
}

template <typename T>
bool esPseudocompleto_rec(typename Abin<T>::nodo n, const Abin<T> &A, int prof) //si prof=0, estamos en la altura adecuada para estudiar los nodos
{
    if (n == Abin<T>::NODO_NULO)
        return true;
    else
    {
        if (prof == 0)
            return (contarHijos(n,A) != 1);
        else
            return (esPseudocompleto_rec(A.hijoIzqdoB(n), A, prof-1) && esPseudocompleto_rec(A.hijoDrchoB(n), A, prof-1));
    }
}



/*PARA USAR ÁRBOLES DE CARACTERES:*/
    typedef char tElto;
    tElto fin = '#';
/*PARA USAR ÁRBOLES DE ENTEROS:*/
//  typedef int tElto;
//  tElto fin = -99;
int main()
{
    Abin<tElto> A;
    //PARA RELLENAR DESDE FICHERO:
        ifstream fA("abin2-char.txt"); // Abrir fichero de entrada.
        rellenarAbin(fA,A); // Rellenar desde fichero.
    //PARA RELLENAR MANUALMENTE:
    //    rellenarAbin(A, fin);

    imprimirAbin(A);
    if (esPseudocompleto(A))
        cout << "El árbol es pseudocompleto" << endl;
    else
        cout << "El árbol NO es pseudocompleto" << endl;


    return 0;
}
