#include <iostream>
#include <algorithm>
#include "..\..\Implementaciones\Agen.hpp"

using namespace std;

/*
¿Qué necesita?: Arbol
¿Que devuelve?: Un entero
*/

template <typename T>
int altura_maxima_nodo(typename Agen<T>::nodo n, Agen<T>& A){
	int maxima_altura;
	typename Agen<T>::nodo hermano;
	
	if(n == A.NODO_NULO){
		return -1;
	} else{
		hermano = A.hijoIzqdo(n);
        maxima_altura = altura_maxima_nodo(hermano, A);
		while(hermano !=A.NODO_NULO){
			
			hermano = A.hermDrcho(hermano);
            maxima_altura = max(maxima_altura,altura_maxima_nodo(hermano, A));
			
		}
	}
	return maxima_altura+1;
}

template <typename T>
int altura_minimo_nodo(typename Agen<T>::nodo n, Agen<T>& A){
	int minima_altura;
	typename Agen<T>::nodo hermano;
	
	if(n == A.NODO_NULO){
		return 0;
	} else{
		hermano = A.hijoIzqdo(n);
        minima_altura = altura_minimo_nodo(hermano, A);
		while(hermano !=A.NODO_NULO){
			
			hermano = A.hermDrcho(hermano);
            minima_altura = min(minima_altura, altura_minimo_nodo(hermano, A));	
		}
	}
	return minima_altura+1;
}

template <typename T>
int desequilibrio_general(Agen<T>& A){
	return desequilibrio_general_rec(A.raiz(),A);
}

template <typename T>
int desequilibrio_general_rec(typename Agen<T>::nodo n, Agen<T>& A){
	int max_altura;
	int min_altura;
	
	typename Agen<T>::nodo hermano;
	
	int sol = 0;
	
	if(n == A.NODO_NULO){
		return 0;
	}else{
		hermano = A.hijoIzqdo(n);
        max_altura = altura_maxima_nodo(hermano,A);
        min_altura = altura_minimo_nodo(hermano,A);
		while(hermano != A.NODO_NULO){
            hermano = A.hermDrcho(hermano);
			max_altura = max(max_altura,altura_maxima_nodo(hermano,A));
			min_altura = min(min_altura,altura_minimo_nodo(hermano,A));
            
			sol = max(abs(max_altura-min_altura), desequilibrio_general_rec(hermano,A));
        }
	}
	return sol;
}

int main() {
	Agen<int> Arbol{};
	Arbol.insertarRaiz(1);
	Arbol.insertarHijoIzqdo(Arbol.raiz(),2);
	Arbol.insertarHermDrcho(Arbol.hijoIzqdo(Arbol.raiz()),3);
	Arbol.insertarHermDrcho(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.raiz())),4);
	Arbol.insertarHijoIzqdo(Arbol.hijoIzqdo(Arbol.raiz()),5);
	Arbol.insertarHijoIzqdo(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.raiz())),6);
	Arbol.insertarHermDrcho(Arbol.hijoIzqdo(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.raiz()))),7);
	Arbol.insertarHermDrcho(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.raiz())))),8);
	Arbol.insertarHermDrcho(Arbol.hermDrcho(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.raiz()))))),9);
	Arbol.insertarHermDrcho(Arbol.hermDrcho(Arbol.hermDrcho(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.raiz())))))),10);
	Arbol.insertarHijoIzqdo(Arbol.hermDrcho(Arbol.hermDrcho(Arbol.hermDrcho(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.hermDrcho(Arbol.hijoIzqdo(Arbol.raiz()))))))),11);
	
	int num_max = altura_maxima_nodo(Arbol.raiz(),Arbol);
    int num_menos = altura_minimo_nodo(Arbol.raiz(),Arbol);
	
    cout<<"Altura max: "<<num_max<<endl;
    cout<<"Altura min: "<<num_menos<<endl;

	int n = desequilibrio_general(Arbol);
	cout<<"El mayor desequilibrio es de: "<<n<<endl;
	
	//cout<<num;
	return 0;
}