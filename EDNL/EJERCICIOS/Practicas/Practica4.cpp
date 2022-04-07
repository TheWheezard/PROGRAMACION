#include "..\Implementaciones\Agen.hpp"
/*
2. Implementa un subprograma, que dado un árbol general, nos calcule su grado.
*/
//Funcion llamada
template <typename T>
int grado (Agen<T>& A){
	if(A.arbolVacio())
		return 0;
	else
		return gradoRec(A.raiz(), A);
}

//Funcion recursiva+iterativa
template <typename T>
int gradoRec (typename Agen<T>::nodo n, Agen<T>& A){
	int max = numHijos(A, n);
	typename Agen<T>::nodo hermano = A.hijoIzqdo(n);
	while(hermano != Agen<T>::NODO_NULO){
		max = maximo(max, gradoRec(hermano, A)); //Recorrido en profundidad
		hermano = A.hermDrcho(hermano); //iterar a traves de los hermanos (recorrido en anchura)
	}
	return max;	
}

/*
3. Implementa un subprograma que, dados un árbol y un nodo dentro de dicho árbol,
determine la profundidad de éste nodo en el árbol.
*/
//caso base: peor nodo que encontramos
template <typename T>
int profundidad(Agen<T>& A, typename Agen<T>::nodo n){
	if(n == Agen<T>::NODO_NULO) //if(n==A.raiz()) return 0;
		return -1;
	else
		return 1 + profundidad(A, A.padre(n));
}

/*
4. Se define el desequilibrio de un árbol general como la máxima diferencia entre las
alturas de los subárboles más bajo y más alto de cada nivel. Implementa un
subprograma que calcule el grado de desequilibrio de un árbol general.
*/

//Funcion llamada
template <typename T>
int desequilibrio(const Agen<T>& A){
    return (alturaMax(A.raiz(),A) - alturaMin(A.raiz(),A)); 
}

//-----------------------------------------------------------------------------------------------------
//Post: Devuelve la altura maxima de un arbol
template <typename T>
int alturaMax(typename Agen<T>::nodo n, const Agen<T>& A){
    if(n == Agen<T>::NODO_NULO)
        return -1;
    else{
        int max = -1;
        typename Agen<T>::nodo her = A.hijoIzqdo(n);
        while(her != Agen<T>::NODO_NULO){
                max = maximo(max,alturaMax(her,A)); //Profundidad
                her = A.hermDrcho(her); //anchura
        }
        return 1 + max;
    }
}
//-----------------------------------------------------------------------------------------------------
//Post : Devuelve la altura minima de un arbol
        
template <typename T>
int alturaMin(typename Agen<T>::nodo n, const Agen<T>& A){
    if(n == Agen<T>::NODO_NULO)
        return -1;
    else if(A.hermDrcho(A.hijoIzqdo(n)) == Agen<T>::NODO_NULO) //Si solo tiene un hijo la altura minima es 0
        return 0;
    else{
        typename Agen<T>::nodo her = A.hijoIzqdo(n);
        int min = alturaMax(her,A);
        while(her != Agen<T>::NODO_NULO){
            min = minimo(min,altura(her,A));
            her = A.hermDrcho(her);
        }
        return 1 + min;
    }
}

/*
5. Dado un árbol general de enteros A y un entero x, implementa un subprograma que
realice la poda de A a partir de x. Se asume que no hay elementos repetidos en A.
*/

//Funcion llamada
void poda(int x, Agen<int>& A){
    Agen<int>::nodo n = Agen<int>::NODO_NULO;
    buscar(x,A.raiz(),n,A);
    destruir(n,A);
}
//-----------------------------------------------------------------------------------------------
void buscar(int x, typename Agen<int>::nodo n, typename Agen<int>::nodo& encont, Agen<int>& A){
    if(n == Agen<int>::NODO_NULO)
        encont = Agen<int>::NODO_NULO;
    else if(A.elemento(n) == x) //elemento encontrado
        encont = n;
    else{ //elemento no encontrado
        Agen<int>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<int>::NODO_NULO and encont == Agen<int>::NODO_NULO){
                buscar(x,hijo,encont,A); //profundidad
                hijo = A.hermDrcho(hijo); //anchura
        }
    }
}
//----------------------------------------------------------------------------------------------
template<typename T> void destruir(typename Agen<T>::nodo n,Agen<T>& A)
{
    if(n!=Agen<T>::NODO_NULO)
    {
    	//Prioriza la eliminacion de toda la descendencia
        while(A.hijoIzqdo(n)!=Agen<T>::NODO_NULO)
        {
            destruir(A, A.hijoIzqdo(n)); 
        }
        //Elimina el propio nodo
        if(n==A.raiz() && A.hijoIzqdo(n)==Agen<T>::NODO_NULO) 
            A.eliminarRaiz();
        else
            A.eliminarHijoIzqdo(A.padre(n)); 
    }
}