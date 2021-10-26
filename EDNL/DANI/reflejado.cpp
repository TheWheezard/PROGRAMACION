template<typename T>
void reflejado_rec(Abin<T>& a, Abin<T>& reflejo, typename Abin<T>::nodo n, typename Abin<T>::nodo r)
{
	if(n!=Abin<T>::NODO_NULO)
	{
		//if(reflejo.arbolVacio())
		//{
		//	reflejo.insertarRaizB(a.elemento(n));
		//	r=reflejo.raizB();
		//}
		//else
		//{
			if(a.padreB(n)!=Abin<T>::NODO_NULO)
			{
				if(a.hijoIzqdoB(a.padreB(n))==n)
				{
					reflejo.insertarHijoDchoB(r, a.elemento(n));
					r=reflejo.hijoDchoB(r);
				}
				else
				{
					if(a.hijoDchoB(a.padreB(n))==n)
					{
						reflejo.insertarHijoIzqdoB(r, a.elemento(n));
						r=reflejo.hijoIzqdoB(n);
					}
				}
			}
		//}
		reflejado_rec(a, reflejo, a.hijoIzqdoB(n), r);
		reflejado_rec(a, reflejo, a.hijoDchoB(n), r);
	}
} 

//funcion llamada
template<typename T>
void reflejado(Abin<T>& a, Abin<T>& reflejo)
{
	if(!a.arbolVacio())
	{
		reflejo.insertarRaizB(a.elemento(n));
		r=reflejo.raizB();
		reflejado_rec(a, reflejo, a.raizB(), Abin<T>::NODO_NULO);	
	}
}
/*
int main()
{
	Abin<int> a, r;
	a.insertarRaizB(1);
	a.insertarHijoIzqdoB(a.raizB(), 2);
	reflejado(a, r);
}
*/