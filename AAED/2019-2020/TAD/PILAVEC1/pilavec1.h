#ifndef PILA_VEC1_H
#define PILA_VEC1_H

class Pila
{
public:
	typedef int tElemento;
	explicit Pila(unsigned TamMax); //constructor
	Pila(const Pila& P); //constructor de copia
	Pila& operator =(const Pila& P); //asignacion entre pilas
	bool vacia() const;
	bool llena() const; //Requerida por implementacion
	const tElemento& tope() const;
	void pop();
	void push(const tElemento& x);
	~Pila(); //destructor
private:
	tElemento *elementos; //vector de elementos
	int Lmax; //tamano vector
	int tope_; //posicion del tope
};
#endif // PILA_VEC1_H