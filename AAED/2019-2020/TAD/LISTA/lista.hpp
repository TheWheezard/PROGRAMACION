#ifndef LISTA_VEC_H
#define LISTA_VEC_H
#include <cassert>
template <typename T>
class Lista {
	struct nodo;
public:
	typedef nodo* posicion; // Posición de un elemento
	explicit Lista(); // Constructor, req. ctor. T()
	Lista(const Lista<T>& Lis); // Ctor. de copia, requiere ctor. T()
	Lista<T>& operator =(const Lista<T>& Lis);// Asig, req. ctor. T()
	void insertar(const T& x, posicion p);
	void eliminar(posicion p);
	const T& elemento(posicion p) const;// Lec. elto. en Lista const
	T& elemento(posicion p); // Lec/Esc elto. en Lista no−const
	posicion buscar(const T& x) const;// Req. operador == para T
	posicion siguiente(posicion p) const;
	posicion anterior(posicion p) const;
	posicion primera() const;
	posicion fin() const; // Posición después del último
	~Lista(); // Destructor
private:
	// private
	struct nodo{
		T elto;
		nodo* sig;
		nodo(const T& e, nodo* p = nullptr): elto(e), sig(p) {}
	};
	nodo* L; // Lista enlazada de nodos
	void copiar(const Lista<T>& L);
};
// clase Lista genérica: dinamica de celdas simplemente enlazadas.
// Implementación de operaciones
// Método privado
template <typename T>
void Lista<T>::copiar(const Lista<T> &Lis)
{
	L = new nodo(T()); // Crear el nodo cabecera
	nodo* q = L;
	for (nodo* r = Lis.L->sig; r; r = r->sig) {
		q->sig = new nodo(r->elto);
		q = q->sig;
	}
}
template <typename T>
inline Lista<T>::Lista() :L(new nodo( T() ))
{}

template <typename T>
Lista<T>::Lista(const Lista<T>& Lis)
{
	copiar(Lis);
}
template <typename T>
Lista<T>& Lista<T>::operator =(const Lista<T>& Lis)//CAMBIAR
{
	if (this != &Lis) { // Evitar autoasignación
	// Destruir el vector y crear uno nuevo si es necesario
		this->~Lista();
	// Copiar elementos
		copiar(Lis);
	}
	return *this;
}
template <typename T>
void Lista<T>::insertar(const T& x, Lista<T>::posicion p)
{
	p->sig = new nodo(x,p->sig); //nuevo nodo queda en posicion p	
}
template <typename T>
void Lista<T>::eliminar(Lista<T>::posicion p)
{
	assert(p->sig); // Posición válida
	nodo* q = p->sig;
	p->sig = q->sig;
	delete q;
}
template <typename T> inline
const T& Lista<T>::elemento(Lista<T>::posicion p) const
{
	assert(p->sig); // p no es fin
	return p->sig->elto;
}
template <typename T>
inline T& Lista<T>::elemento(Lista<T>::posicion p)
{
	assert(p->sig); // p no es fin
	return p->sig->elto;
}
template <typename T>
typename Lista<T>::posicion
Lista<T>::buscar(const T& x) const
{
	nodo* q = L;
	bool encontrado = false;
	while (q->sig && !encontrado)
		if (q->sig->elto == x)
			encontrado = true;
		else q = q->sig;
		return q;
	}
template <typename T> inline
	typename Lista<T>::posicion 
	Lista<T>::siguiente(Lista<T>::posicion p) const
	{
	assert(p->sig); // p no es fin
	return p->sig;
}
template <typename T> inline
typename Lista<T>::posicion
Lista<T>::anterior(Lista<T>::posicion p) const
{
	nodo* q;
	assert(p != L); // Posición válida
	for (q = L; q->sig != p; q = q->sig);
	return q;
}
template <typename T>
inline typename Lista<T>::posicion Lista<T>::primera() const
{ return L; }
template <typename T>
inline typename Lista<T>::posicion Lista<T>::fin() const
{
	nodo* p;
	for(p = L; p->sig; p = p->sig);
	return p;
}
template <typename T> inline Lista<T>::~Lista()
{
	nodo* q;
	while(L)
	{
		q = L->sig;
		delete L;
		L=q;
	}
}

#endif // LISTA_VEC_H