#include<iostream>
#include "..\..\EDNL\Arboles\Implementaciones\Abin.hpp"
#include<vector>

using namespace std;


bool masPobreDescendientes_rec(int nodoPobre, typename Abin<int>::nodo_ n, const Abin<int>& A)
{
    if(n == Abin<int>::NODO_NULO)
        return true;
    else if(nodoPobre > A.elemento(n))
        return false;

    else
        return masPobreDescendientes_rec(nodoPobre, A.hijoIzqdoB(n), A) &&
               masPobreDescendientes_rec(nodoPobre, A.hijoDchoB(n), A);
}

bool masPobreDescendientes(Abin<int>::nodo_ n, const Abin<int>& A)
{
    return masPobreDescendientes_rec(A.elemento(n), A.hijoIzqdoB(n), A) &&
           masPobreDescendientes_rec(A.elemento(n), A.hijoDchoB(n), A);
}

bool masRicoAscendiente(Abin<int>::nodo_ nodoRico, const Abin<int>& A)
{
    bool esProspero;
    Abin<int>::nodo_ asc;

    esProspero = true;
    asc = A.padreB(nodoRico);
    while(asc != Abin<int>::NODO_NULO && esProspero)
    {
        if(A.elemento(nodoRico) < A.elemento(asc))
            esProspero = false;
        asc = A.padreB(asc);
    }
    return esProspero;
}
bool prospero(Abin<int>::nodo_ n, const Abin<int>& A)
{
    return (masRicoAscendiente(n, A)) && (masPobreDescendientes(n, A));
}
int nodosProsperos_rec(typename Abin<int>::nodo_ n, const Abin<int>& A)
{
    if(n==Abin<int>::NODO_NULO)
        return 0;
    else
    {
        if(prospero(n, A))
            return 1 + nodosProsperos_rec(A.hijoIzqdoB(n), A) + nodosProsperos_rec(A.hijoDchoB(n), A);
        else
            return nodosProsperos_rec(A.hijoIzqdoB(n), A) + nodosProsperos_rec(A.hijoDchoB(n), A);
    }
}

int nodosProsperos(const Abin<int>& A)
{
    return nodosProsperos_rec(A.raizB(), A);
}