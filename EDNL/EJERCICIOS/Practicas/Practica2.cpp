#include "..\..\Implementaciones\Abin.hpp"
#include<math.h>
//Ejercicio 1
template<typename T> int contarNodos(typename Abin<T>::nodo n, const Abin<T>& a)
{
    if(n==Abin<T>::NODO_NULO)
        return 0;
    else
        return 1+contarNodos(a.hijoIzqdoB(n), a)+contarNodos(a.hijoIzqdoB(n), a);
}
//Ejercicio 2
template<typename T>
int calcular_altura(typename Abin<T>::nodo n, Abin<T>& a)
{
    if(n!=Abin<T>::NODO_NULO)
        return 1+max(calcular_altura(a.hijoDrchoB(n),a), calcular_altura(a.hijoIzqdoB(n),a));
    else
        return 0;
}
template<typename T>
int altura(Abin<T>& a) //Funcion llamada
{
	return calcular_altura(a.raizB(), a);
}
//Ejercicio 3
template<typename T>
int profundidad(typename Abin<T>::nodo n, const Abin<T>& a)
{
	if(n==a.raizB())
		return 0;
	else
		return 1+profundidad(a.padre(n),a);		
}
//Ejercicio 6
template<typename T>
int desequilibrio_rec(Abin<T>& a, typename Abin<T>::nodo n)
{
    if(n==Abin<T>::NODO_NULO)
        return 0;
    else
        return max(abs(calcular_altura(a, a.hijoIzqdoB(n))-calcular_altura(a,a.hijoDrchoB(n))), 
        max(desequilibrio_rec(a, a.hijoIzqdoB(n)), desequilibrio_rec(a, a.hijoDrchoB(n))));
}
template<typename T>
int desequilibrio(Abin<T>& a) //Funcion llamada
{
	return desequilibrio_rec(a, a.raizB());
}
//Ejercicio 7
template<typename T>
bool pseudocompleto_rec(Abin<T>& a, typename Abin<T>::nodo n)
{
    if(n!=Abin<T>::NODO_NULO)
    {
        if(calcular_altura(a,n)==1 && numero_de_hijos(a,n)==1) //sin usar altura
            return false;
        return pseudocompleto_rec(a, a.hijoIzqdoB(n)) && pseudocompleto_rec(a, a.hijoDrchoB(n));
    }
    else
        return true;
    
}
template<typename T>
bool pseudocompleto(Abin<T>& a) //funcion llamada
{
    if(a.arbolVacio())
        return true;
    else
        return pseudocompleto_rec(a, a.raizB(), true);
}
