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

//funcion llamada
template<typename T>
bool similares(Abin<T>& a, Abin<T>& b)
{
    return similares_rec(a,b,a.raizB(), b.raizB());
}