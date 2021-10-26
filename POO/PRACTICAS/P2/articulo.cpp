#include "articulo.hpp"

/**CLASE ARTICULO**/
/*CONSTRUCTOR*/
Articulo::Articulo(const Cadena& r, const Cadena& t, const Fecha& f, double p, unsigned s) : referencia_(r), titulo_(t), f_publi_(f), precio_(p), stock_(s){}

/*FUNCIÓN DE SALIDA*/
ostream& operator <<(ostream& os, const Articulo& ar) noexcept{
	locale::global(locale(""));
	os<<"["<<ar.referencia()<<"]\"";																
	os<<ar.titulo()<<"\","<<ar.f_publi().anno()<<"."<<fixed<<setprecision(2)<<ar.precio()<<"€.";	
	return os;
}

