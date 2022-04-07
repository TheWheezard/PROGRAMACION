#include "..\Implementaciones\Abin.hpp"
#include "..\Implementaciones\Abb.hpp"
/*
Ejercicio 1
Añade al TAD Abb un operador de conversión para obtener un árbol binario a partir
de un ABB, template <typename T> Abb<T>::operator Abin<T>() const;. Es
necesario declararlo como amigo de la clase Abin. Este operador nos permitirá obtener
una copia de un ABB y tratarlo como un árbol binario, por ejemplo para realizar un
recorrido del mismo.
*/
template <typename T>
Abb<T>::operator Abin<T>() const 
{
    Abin<T> arb;
    if(r)
    {
        arb.insertarRaizB(r->elto);
        copiarnodos(r, arb.raizB(), arb);
    }
    return arb;
}

template <typename T>
void Abb<T>::copiarnodos(arbol_* n, typename Abin<T>::nodo m, Abin<T>& arb) const
{
    if(n->izq.r)
    {
        arb.insertarHijoIzqdoB(m, n->izq.r->elto);
        copiarnodos(n->izq.r,arb.hijoIzqdoB(m), arb);
    }
    if(n->der.r)
    {
        arb.insertarHijoDrchoB(m, n->der.r->elto);
        copiarnodos(n->der.r, arb.hijoDrchoB(m), arb);
    }
}
/*
Ejercicio 2
Implementa una nueva operación para el TAD ABB que tomando el contenido del
campo informativo de un nodo, elimine al completo el subárbol que cuelga de él.
*/
template <typename T>
void Abb<T>::eliminarNodo (const T& e){
	buscar(e).~Abb<T>();
}
/*
Implementa una funcion externa que tomando el contenido del
campo informativo de un nodo, elimine al completo el subárbol que cuelga de él.
*/
template<typename T>
void podaABB(T elto, Abb<T>& A)
{
    Abb<T> subA = A.buscar(elto);
    if(!A.vacio())
    {
        podaABB_rec(A, subA);
    }
}

template<typename T>
void podaABB_rec(Abb<T>& A, Abb<T>& subA)
{
    if(subA.izqdo().vacio() && subA.drcho().vacio())
        A.eliminar(subA.elemento());
    else
    {
        podaABB_rec(A, A.izqdo());
        podaABB_rec(A, A.drcho());
    }
}
//EQUILIBRAR*************************************************************
template<typename T> void Abb2vector(const Abb<T>& a, std::vector<T>& v)
{
    if(!a.vacio())
    {
        Abb2vector(a.izqdo(),v);
        v.push_back(a.elemento());
        Abb2vector(a.drcho(),v);
    }
}
template<typename T> void equilibrar_rec(Abb<T>& a, const std::vector<T>& v, int inicio, int fin)
{
    if(fin>=inicio)
    {
        int centro=inicio+(fin-inicio)/2;
        a.insertar(v[centro]);
        equilibrar_rec(a,v,inicio, centro-1);
        equilibrar_rec(a,v,centro+1,fin);
    }
}
template<typename T> Abb<T>& equilibrar(Abb<T>& origen) //Funcion llamada
{
    Abb<T> *destino=new Abb<T>();
    std::vector<T> v;
    Abb2vector(origen, v); //Ordena todos los elementos del arbol en v
    equilibrar_rec(*destino, v, 0, v.size()-1);
    return *destino;
}
//UNION**********************************************************************
/*
Ejercicio 3
Dados dos conjuntos representados mediante árboles binarios de búsqueda,
implementa la operación UNIÓN de conjuntos, que devuelva como resultado otro
conjunto que sea la unión de ambos.
¿Es importante el orden en qué se inserten los nodos en el conjunto UNIÓN?
SI
¿Por qué?
Dependiendo del orden de insercion el Abb resultante estará más o menos equilibrado

            10

    7               18
2       8       13      40

v=2 7 8 10 13 18 40

        10
    7

*/
typedef Abb<int> Conjunto;
Conjunto& Union(const Conjunto& A,const Conjunto& B) //Funcion llamada
{
    Conjunto *Solucion=new Conjunto(A);
    Union_rec(B, *Solucion);
    return *Solucion;
}
void Union_rec(const Conjunto& B, Conjunto& Solucion)
{
    if(!B.vacio())
    {
        Solucion.insertar(B.elemento());
        Union_rec(B.izqdo(),Solucion);
        Union_rec(B.drcho(), Solucion);
    }
}
/*
Ejercicio 4
Dados dos conjuntos representados mediante árboles binarios de búsqueda,
implementa la operación INTERSECCIÓN de conjuntos, que devuelva como resultado
otro conjunto que sea la intersección de ambos. El conjunto INTERSECCIÓN debe
quedar equilibrado.
*/
template<typename T> void Interseccion_rec(const Abb<T>& A, const Abb<T>& B, Abb<T>& C)
{
    if(!A.vacio() && !B.vacio())
    {
        Abb<T> aux=A.buscar(B.elemento());
        if(!aux.vacio())        // if(A.buscar(5).vacio())
            C.insertar(B.elemento());

        Interseccion_rec(A, B.izqdo(), C);
        Interseccion_rec(A, B.drcho(), C);
    }
}
template<typename T> Abb<T>& Interseccion(const Abb<T>& A, const Abb<T>& B) //Funcion llamada
{
    Abb<T> *C=new Abb<T>();
    Interseccion_rec(A,B,*C);
    return equilibrar(*C);
}
/*
Ejercicio 5
Implementa el operador ♦ para conjuntos de números de tipo entero. Se define este
operador como sigue A ♦ B = (A ∪ B) - (A ∩ B). La implementación del operador ♦
debe realizarse utilizando obligatoriamente la operación ∈, que nos indica si un
elemento pertenece o no a un conjunto. La representación del tipo conjunto de enteros
debe ser tal que la operación de pertenencia sea en el caso medio O(log n).
*/
template<typename T>
bool pertenece(int e, const Abb<T>& C)
{
    //Primero hay que equilibrar el conjunto para que la operacion pertenece sea O(lon(n))
    Abb<int> CE;
    CE=equilibrar(C);
    if(!CE.buscar(e).vacio())
        return true;
    else
        return false;
}
void diferencia(const Conjunto& A, const Conjunto& B, Conjunto& Solucion)
{
    if(!A.vacio())
    {
        if(B.buscar(A.elemento()).vacio())
            Solucion.insertar(A.elemento());
        diferencia(A.izqdo(),B,Solucion);
        diferencia(A.drcho(),B,Solucion);
    }
}
Conjunto& rombo(const Conjunto& A, const Conjunto& B)
{
    Conjunto Un, In;
    Conjunto *Solucion=new Conjunto();
    Un=Union(A,B);
    In=Interseccion(A,B);
    //Tiene que devolver los elementos de la union que no estan en la interseccion
    diferencia(Un,In,*Solucion);
    return *Solucion;
}
