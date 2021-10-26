template<typename T>
bool pseudocompleto_rec(Abin<T>& a, typename Abin<T>::nodo n, bool es)
{

    if(n!=Abin<T>::NODO_NULO)
    {
        if(calcular_altura(a,n)==2 && numero_de_hijos(a,n)==1)
            return false;
        else
        {
            es=pseudocompleto_rec(a, a.hijoIzqdoB(n), es);
            es=pseudocompleto_rec(a, a.hijoDrchoB(n), es);
        }
    }
    return es;
}


//funcion llamada
template<typename T>
bool pseudocompleto(Abin<T>& a)
{
    return pseudocompleto_rec(a, a.raizB(), true);
}
