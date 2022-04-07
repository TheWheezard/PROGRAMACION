#include "..\..\Implementaciones\Abin.hpp"
//Ejercicio 1
template<typename T>
bool similares_rec(Abin<T>& a, Abin<T>& b, typename Abin<T>::nodo n_a, typename Abin<T>::nodo n_b)
{
    if(n_a!=Abin<T>::NODO_NULO && n_b!=Abin<T>::NODO_NULO)
    {
        if(a.arbolVacioB() && b.arbolVacioB())
            return true;
        else
        {
            if((a.hijoIzqdoB(n_a)!=Abin<T>::NODO_NULO) && (b.hijoIzqdoB(n_b)==Abin<T>::NODO_NULO))
                return false;
            if((b.hijoIzqdoB(n_b)!=Abin<T>::NODO_NULO) && (a.hijoIzqdoB(n_a)==Abin<T>::NODO_NULO))
                return false;
            if((a.hijoDrchoB(n_a)!=Abin<T>::NODO_NULO) && (b.hijoDrchoB(n_b)==Abin<T>::NODO_NULO))
                return false;
            if((a.hijoDrchoB(n_a)==Abin<T>::NODO_NULO) && (b.hijoDrchoB(n_b)!=Abin<T>::NODO_NULO))
                return false;
        }
        return similares_rec(a,b,a.hijoIzqdoB(n_a), b.hijoIzqdoB(n_b)) && similares_rec(a,b,a.hijoDrchoB(n_a), b.hijoDrchoB(n_b));
    }
    else
        return true;
}
template<typename T>
bool similares(Abin<T>& a, Abin<T>& b) //funcion llamada
{
    return similares_rec(a,b,a.raizB(), b.raizB());
}

//Ejercicio 2
template<typename T>
void reflejado_rec(const Abin<T>& a, Abin<T>& reflejo, typename Abin<T>::nodo n, typename Abin<T>::nodo r)
{
	if(n!=Abin<T>::NODO_NULO)
	{
		if(a.padreB(n)!=Abin<T>::NODO_NULO)
		{
			if(a.hijoIzqdoB(a.padreB(n))==n)
			{
				reflejo.insertarHijoDchoB(r, a.elemento(n));
				r=reflejo.hijoDchoB(r);
			}
			else
			{
				if(a.hijoDchoB(a.padreB(n))==n)
				{
					reflejo.insertarHijoIzqdoB(r, a.elemento(n));
					r=reflejo.hijoIzqdoB(n);
				}
			}
		}
		reflejado_rec(a, reflejo, a.hijoIzqdoB(n), r);
		reflejado_rec(a, reflejo, a.hijoDchoB(n), r);
	}
} 
template<typename T>
void reflejado(Abin<T>& a, Abin<T>& reflejo) //funcion llamada
{
	if(!a.arbolVacio())
	{
		reflejo.insertarRaizB(a.elemento(n));
		r=reflejo.raizB();
		reflejado_rec(a, reflejo, a.raizB(), Abin<T>::NODO_NULO);	
	}
}

//Ejercicio 3
struct elem
{
    char op;
    double valor;
    elem(char o=' ', double v=0.0):op(o), valor(v){} //Constructor
};
double evaluar(const Abin<elem>& a, typename Abin<elem>::nodo n)
{
    if(n!=Abin<elem>::NODO_NULO)
    {
        if(a.elemento(n).op=='+' || a.elemento(n).op=='-' || a.elemento(n).op=='*' || a.elemento(n).op=='/' )
        {
            if(a.elemento(n).op=='+')
                return evaluar(a, a.hijoIzqdoB(n))+evaluar(a, a.hijoDrchoB(n));
            if(a.elemento(n).op=='-')
                return evaluar(a, a.hijoIzqdoB(n))-evaluar(a, a.hijoDrchoB(n));
            if(a.elemento(n).op=='*')
                return evaluar(a, a.hijoIzqdoB(n))*evaluar(a, a.hijoDrchoB(n));
            if(a.elemento(n).op=='/')
                return evaluar(a, a.hijoIzqdoB(n))/evaluar(a, a.hijoDrchoB(n));
        }
        else
        {
            return a.elemento(n).valor;
        }
    }
    else
        return 0;
}
double evaluar_llamada(const Abin<elem>& a)
{
    return evaluar(a, a.raizB());
}