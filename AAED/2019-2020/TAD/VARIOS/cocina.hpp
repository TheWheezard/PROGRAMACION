#include "Lista.hpp"
#include<iostream>
class cocina
{
public:
    struct mueble
    {
        double posicion;
        double anchura;
        mueble(double p=0, double a=0):posicion(p), anchura(a){}
        bool operator==(const mueble&);
    };
    cocina(double l):longitud(l){}
    bool cabe(const mueble&, Lista<mueble>::posicion&);
    void anadir(const mueble&);
    const mueble& iesimo(double) const;
    void eliminar(mueble&);
    void mover(mueble&);
    void destruir();
	void mostrar() const;
private:
    double longitud;
    Lista<mueble> l;
};

//0-------------------------------------------------------------longitud

bool cocina::cabe(const mueble& m, typename Lista<mueble>::posicion& pos)
{
	typename Lista<mueble>::posicion p, aux;
	if(l.primera()==l.fin()) //Si la cocina esta vacia
	{
		if(longitud>=m.anchura) //si la longitud de la pared es mayor o igual que la anchura del mueble
		{
			pos=l.primera(); //devuelve la primera posicion de la lista
			return true;
		}	
		else
			return false;	//devuelve el fin porque no cabe
	}
	else
	{
		for(p=l.primera();p!=l.fin() && l.elemento(p).posicion<m.posicion;p=l.siguiente(p)); //Este bucle posiciona p en el lugar
			//de la lista de muebles que le corresponderia a m

		//Ahora habria que comprobar la posicion y anchura del elemento donde se ha parado el bucle for
		//para ver si el mueble que intentamos colocar cabe o no
		if(p!=l.primera())
		{
			aux=l.anterior(p);
			if(m.posicion>l.elemento(aux).posicion+l.elemento(aux).anchura)
			{
				pos=p;
				return true;
			}
			else
				return false;
		}
		else
		{
			if(m.posicion+m.anchura<l.elemento(p).posicion)
			{
				pos=l.primera();
				return true;
			}
			else
				return false;
		}
	}
}
void cocina::anadir(const mueble& m)
{
	typename Lista<mueble>::posicion p;
	if(cabe(m,p))
		l.insertar(m,p);
}
void cocina::mostrar() const
{
	Lista<mueble>::posicion p=l.primera();
	while(p!=l.fin())
	{
		std::cout << "(" << l.elemento(p).posicion << "," << l.elemento(p).anchura << ")";
		p=l.siguiente(p);
	}
}