//pila_vec1.h
#ifndef PILA_VEC1_H
#define PILA_VEC1_H
#include <cassert>

template <typename T>
class Pila {
public:
	Pila(); // constructor
	Pila(const Pila<T>& P); // ctor. de copia
	Pila<T>& operator =(const Pila<T>& P); // asignacion
	bool vacia() const;
	const T& tope() const;
	void pop();
	void push(const T& x);
	~Pila(); // destructor
};
#endif // PILA_VEC1_H
