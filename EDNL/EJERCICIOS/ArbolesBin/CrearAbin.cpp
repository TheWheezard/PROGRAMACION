#include "..\..\Implementaciones\Abin.hpp"

template <typename T>
Abin<T> &crearArbol()
{
  Abin<T> *res = new Abin<T>();
  typename Abin<T>::nodo n = Abin<T>::NODO_NULO;
  res->insertarRaiz(1);
  n = res->raiz();
  res->insertarHijoIzqdo(n, 2);
  res->insertarHijoDrcho(n, 3);
  n = res->hijoIzqdo(n);
  res->insertarHijoIzqdo(n, 4);
  res->insertarHijoDrcho(n, 5);
  n = res->hijoDrcho(n);
  res->insertarHijoIzqdo(n, 6);
  res->insertarHijoDrcho(n, 7);
  n = res->hijoDrcho(res->raiz());
  res->insertarHijoIzqdo(n, 8);
  res->insertarHijoDrcho(n, 9);

  return *res;
}
/*
            1
    2               3
  4   5           8   9
     6 7
*/