//Funciones para imprimir todos los elementos de un arbol binario desde la raiz al resto de los nodos
// en preorden (raiz-izquiero-derecho)
template <typename T>
void imprimirAbin (const Abin<T>& A)
{
    if (!A.arbolVacioB()) {
        std::cout << "Raíz del árbol: " << A.elemento(A.raizB()) << std::endl;
        imprimirDescendientes(A.raizB(), A);
    }
    else
        std::cout << "Árbol vacío\n";
}
template <typename T>
void imprimirDescendientes (typename Abin<T>::nodo r, const Abin<T>& A)
{
    if (A.hijoIzqdoB(r) != Abin<T>::NODO_NULO) {
        std::cout << "Hijo izqdo de " << A.elemento(r) << ": " << A.elemento(A.hijoIzqdoB(r)) << std::endl;
        imprimirDescendientes(A.hijoIzqdoB(r), A);
    }
    if (A.hijoDrchoB(r) != Abin<T>::NODO_NULO) {
        std::cout << "Hijo derecho de " << A.elemento(r) << ": " << A.elemento(A.hijoDrchoB(r)) << std::endl;
        imprimirDescendientes(A.hijoDrchoB(r), A);
    }
}