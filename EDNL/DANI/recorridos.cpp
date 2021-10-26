/*
Árbol binario

    Preorden: (raíz, izquierdo, derecho). Para recorrer un árbol binario no vacío en preorden, hay que realizar las siguientes operaciones recursivamente en cada nodo, comenzando con el nodo de raíz:

        Visite la raíz
        Atraviese el sub-árbol izquierdo
        Atraviese el sub-árbol derecho

    Inorden: (izquierdo, raíz, derecho). Para recorrer un árbol binario no vacío en inorden (simétrico), hay que realizar las siguientes operaciones recursivamente en cada nodo:

        Atraviese el sub-árbol izquierdo
        Visite la raíz
        Atraviese el sub-árbol derecho

    Postorden: (izquierdo, derecho, raíz). Para recorrer un árbol binario no vacío en postorden, hay que realizar las siguientes operaciones recursivamente en cada nodo:

        Atraviese el sub-árbol izquierdo
        Atraviese el sub-árbol derecho
        Visite la raíz
*/
template<typename T> void preorden(const Abin<T>& a, typename Abin<T>::nodo n, )
{
    if(n!=Abin<T>::NODO_NULO)
    {
        cout << a.elemento(n) << endl;
        preorden(a, a.hijoIzqdoB(n));
        preorden(a,a.hijoDrchoB(n));
    }
}
template<typename T> void inorden(const Abin<T>& a, typename Abin<T>::nodo n)
{
if(n!=Abin<T>::NODO_NULO)
    {
        inorden(a, a.hijoIzqdoB(n));
        cout << a.elemento(n) << endl;
        inorden(a,a.hijoDrchoB(n));
    }
}
template<typename T> void postorden(const Abin<T>& a, typename Abin<T>::nodo n)
{
if(n!=Abin<T>::NODO_NULO)
    {
        postorden(a, a.hijoIzqdoB(n));
        postorden(a,a.hijoDrchoB(n));
        cout << a.elemento(n) << endl;
    }
}