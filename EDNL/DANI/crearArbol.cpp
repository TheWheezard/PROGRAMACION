template<typename T>
Abin<T>& crearArbol()
{
    Abin<T> *res=new Abin<T>();
    Abin<T>::nodo n=Abin<T>::NODO_NULO;
    res->insertarRaizB(1);
    n=res->raizB();
    res->insertarHijoIzqdoB(n, 2);
    res->insertarHijoDrchoB(n,3);
    n=res->hijoIzqdoB(n);
    res->insertarHijoIzqdoB(n,4);
    res->insertarHijoDrchoB(n,5);

    return *res;
}