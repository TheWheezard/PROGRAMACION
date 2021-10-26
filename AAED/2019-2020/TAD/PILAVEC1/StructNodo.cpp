// private
struct nodo{
	T elto;
	nodo* sig;
	nodo(const T& e, nodo* p = nullptr): elto(e), sig(p) {}
};
nodo *inicio, *fin; // Extremos de la cola 
void copiar(const Cola<T>& C);

//-----------------------------------

// Método privado
template <typename T>
void Cola<T>::copiar(const Cola<T>& C)
{
	if (C.inicio)
	{ 
		// C no está vacía
		// Copiar el primer elto.
		inicio = fin = new nodo(C.inicio->elto);
		// Copiar el resto de elementos hasta el final de la cola.
		for (nodo *p = C.inicio->sig; p; p = p->sig)
		{
			fin->sig = new nodo(p->elto);
			fin = fin->sig;
		}
	}
}