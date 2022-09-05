/*
Dado un conjunto ordenado no vacio A, se define el ínfimo de x como el mayor elemento de A menor o igual que x,
si existe. Análogamente, el supremo de x en A, si existe, es el menor elemento de A mayor o igual que x.

Implementa dos funciones de O(log n) en promedio que dados un valor x cualquiera y un ABB A no vacío devuelvan,
respectivamente, el ínfimo y el supremo de x en A. Si no existe el ínfimo de x en A, la función correspondiente 
devolverá el mínimo de A. Así mismo, la otra función devolverá el máximo de A, en el caso de que no exista el supremo.
*/

#include "..\..\Implementaciones\Abb.hpp"

template<typename T>
void buscarInfimo(Abb<T>& A, T x, T& infimo){
    if (!A.vacio()){
        if (x < A.elemento() && infimo <= A.elemento()){ // si x < elemento_actual && infimo <= elemento_actual
            buscarInfimo(A.izqdo(), x, infimo); // descartamos elemento_actual
        }
        else if (x < A.elemento() && infimo > A.elemento()){ // si x < elemento_actual < infimo
            buscarInfimo(A.izqdo(), x, A.elemento()); // infimo <- elemento_actual
        }
        else if (x > A.elemento() && infimo <= A.elemento()){ // si x > elemento_actual >= infimo
            buscarInfimo(A.drcho(), x, A.elemento()); // infimo <- elemento_actual
        }
        else if (x > A.elemento() && infimo > A.elemento()){ // si x > infimo > elemento_actual 
            buscarInfimo(A.drcho(), x, infimo); // descartamos elemento_actual
        }
    }
}

template<typename T>
void buscarSupremo(Abb<T>& A, T x, T& supremo){
    if (!A.vacio()){
        if (x > A.elemento() && supremo >= A.elemento()){ // si x > elemento_actual && supremo >= elemento_actual
            buscarSupremo(A.drcho(), x, supremo);
        }
        else if(x > A.elemento() && supremo < A.elemento()){ // si x > elemento_actual > supremo
            buscarSupremo(A.drcho(), x, A.elemento()); // supremo <- elemento_actual
        }
        else if(x < A.elemento() && supremo >= A.elemento()){ // si x < elemento_actual <= supremo
            buscarSupremo(A.izqdo(), x, A.elemento()); // supremo <- elemento_actual
        }
        else if(x < A.elemento() && supremo < A.elemento()){ // si x < supremo < elemento_actual || supremo < x < elemento_actual
            buscarInfimo(A.izqdo(), x, supremo);
        }
    }
}


//Recibe árbol ABB debidamente equilibrado, el valor X y dos referencias a objetos T vacíos
//Devuelve en ambas referencias el ínfimo (o valor mínimo) y el supremo (o máximo) respectivamente
template<typename T>
void infimoYsupremo(Abb<T>& A, T x, T& infimo, T& supremo){
    Abb<T> Aux = A.buscar(x);
    if (!Aux.vacio()){ // Si x existe en el árbol
        infimo = supremo = x; // Devolvemos x (es ínfimo y supremo de sí mismo)
    }
    else{
        Aux = A;
        if (x < A.elemento()){ // x < raíz, buscar en subárbol izdo
            buscarInfimo(Aux.izqdo(), x, infimo = Aux.izqdo().elemento());
            buscarSupremo(Aux.izqdo(), x, supremo = Aux.elemento());
        }
        else{ // Si x > raíz, buscar en subárbol dcho
            buscarInfimo(Aux.drcho(), x, infimo = Aux.elemento());
            buscarSupremo(Aux.drcho(), x, supremo = Aux.drcho().elemento());
        }
    }
}