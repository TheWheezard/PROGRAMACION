#ifndef PILA_2
#define PILA_2
#include <cassert>
template <typename T> class Pila
{
	struct nodo;
public:
	Pila(); //constructor
	Pila(const Pila& P); //constructor de copia
	Pila& operator =(const Pila& P); //asignacion entre pilas
	bool vacia() const;
	bool llena() const; //Requerida por implementacion
	const T& tope() const;
	void pop();
	void push(const T& x);
	~Pila(); //destructor
private:
	struct nodo{
		T elto;
		nodo* sig;
		nodo(const T& e, nodo* p = nullptr): elto(e), sig(p) {}
	};
	nodo *tope_; // Tope de la pila
	void copiar(const Pila<T>& P);
};
// Método privado
template <typename T>
void Pila<T>::copiar(const Pila<T>& P)
{
	if (P.tope_)
	{
		// P no está vacía
		// Copiar el primer elto.
		tope_ = new nodo(P.tope_->elto);
		// Copiar el resto de elementos hasta el final de la cola.
		for (nodo *p = P.tope_->sig; p; p = p->sig)
		{
			tope_->sig = new nodo(p->elto);
			tope_ = tope_->sig;
		}
	}
}

// Constructor
template <typename T>
inline Pila<T>::Pila() :tope_(nullptr){}
// Constructor de copia
template <typename T>
Pila<T>::Pila(const Pila& P) :
	tope_(nullptr)
	{
		copiar(P);
	}

// Asignación entre pilas
template <typename T>
Pila<T>& Pila<T>::operator =(const Pila<T>& P)
{
	if (this != &P)
	{ // evitar autoasignación
	  // Destruir la pila y crear una nueva
		this->~Pila();
		copiar(P);
	}
	return *this;
}
template <typename T>
bool Pila<T>::vacia() const
{
	return (tope_ == nullptr);
}

template <typename T>
const T& Pila<T>::tope() const //
{
	assert(!vacia());
	return tope_->elto;
}
template <typename T>
void Pila<T>::pop()
{
	assert(!vacia());
	nodo* p = tope_;
	tope_ = p->sig;
	delete p;
}
template <typename T>
void Pila<T>::push(const T& x)
{
	nodo* p = new nodo(x);
	p->sig = tope_;
	tope_ = p;
}
// Destructor
template <typename T>
Pila<T>::~Pila()
{
	nodo* p;
	while(tope_)
	{
		p = tope_->sig;
		delete tope_;
		tope_ = p;
	}
}

#endif // PILA_2


