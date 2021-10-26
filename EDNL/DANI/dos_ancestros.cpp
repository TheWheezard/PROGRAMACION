template<typename T>
int dos_ancestros_rec(Abin<T>& a, Abin<T>::nodo n)
{
    if(n!=Abin<T>::NODO_NULO)
    {
        if((a.padreB(n)!=Abin<T>::NODO_NULO) && (a.padreB(a.padreB(n))!=Abin<T>::NODO_NULO))
            return 1+dos_ancestros_rec(a, a.hijoIzqdoB(n))+dos_ancestros_rec(a, a.hijoDrchoB(n));
        else
            return dos_ancestros_rec(a, a.hijoIzqdoB(n))+dos_ancestros_rec(a, a.hijoDrchoB(n));
    }
    else
        return 0;
}

template<typename T>
int dos_ancestros(Abin<T>& a)
{
	return dos_ancestros_rec(a, a.raizB());
}