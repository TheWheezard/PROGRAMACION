
template<typename T>
int desequilibrio_rec(Abin<T>& a, typename Abin<T>::nodo n)
{
    if(n!=Abin<T>::NODO_NULO)
        return 0;
    else
        return max(abs(calcular_altura(a, a.hijoIzqdoB(n))-calcular_altura(a,a.hijoDrchoB(n))), 
        max(desequilibrio_rec(a, a.hijoIzqdoB(n)), desequilibrio_rec(a, a.hijoDrchoB(n)));
}

//Funcion llamada
template<typename T>
int desequilibrio(Abin<T>& a)
{
	return desequilibrio_rec(a, a.raizB());
}
--------------------------------------------------
Ejemplo

		1
	2		3
				4

desequilibrio(1)
	|
	|
max( abs(altura(2)-altura(3)), max(desequilibrio(2), desequilibrio(3)) )
			|							|					|
			|							|  max(abs(altura(null) - altura(4)), max(desequilibrio(null), desequilibrio(4))  ) 
			|							|						|					|						|
			|							|						1					0						max(abs(altura(null) - altura(null)), max(desequilibrio(null), desequilibrio(null))  ) 
			|							|																						|									|					|
			|							|																						0									0					0 = 0
			|							|
			1						max(abs(altura(null) - altura(null)), max(desequilibrio(null), desequilibrio(null))  ) 
													|								|						|
													0								0						0 = 0

Al final queda: max(1, 1)= 1 que es el maximo desequilibrio del arbol