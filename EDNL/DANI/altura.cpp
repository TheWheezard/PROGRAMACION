template<typename T>
int calcular_altura(typename Abin<T>::nodo n, Abin<T>& a)
{
    if(n!=Abin<T>::NODO_NULO)
        return 1+max(calcular_altura(a, a.hijoDrchoB(n)), calcular_altura(a, a.hijoIzqdoB(n)));
    else
        return 0;
}

template<typename T>
int altura(Abin<T>& a)
{
	return calcular_altura(a.raizB(), a);
}