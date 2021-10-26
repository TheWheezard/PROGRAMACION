#ifndef Pedido_Articulo_HPP_
#define Pedido_Articulo_HPP_

#include<iostream>
#include<iomanip>
#include "articulo.hpp"
#include "pedido.hpp"

/*---CLASE LINEAPEDIDO---*/
class LineaPedido
{
	public:
		/*--CONSTRUCTOR--*/
		explicit LineaPedido(double pr, unsigned c=1);
		
		/*--OBSERVADORAS--*/
		const double precio_venta() const noexcept	{return precio_;}
		const unsigned cantidad() const noexcept	{return cantidad_;}
		
	private:
		/*--VARIABLES--*/
		double precio_;
		unsigned cantidad_;
};

std::ostream& operator<<(std::ostream& os, const LineaPedido& p);

class Pedido;
class Articulo;

/*--FUNCIONES DE LA CLASE--*/
class OrdenaPedidos: public std::binary_function<Pedido*, Pedido*, bool>
{
	public:
		bool operator()(const Pedido* p1, const Pedido* p2) const;
};

class OrdenaArticulos: public std::binary_function<Articulo*, Articulo*, bool>
{
	public:
		bool operator()(const Articulo* a1, const Articulo* a2) const	{return (a1->referencia()<a2->referencia());}
};

/*---CLASE PEDIDO_ARTICULO---*/
class Pedido_Articulo
{
	public:
		/*--LIBRERIA--*/
		typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
		typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
		typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
		typedef std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;
		
		/*--OBSERVADORES--*/
		/*-PEDIR-*/
		void pedir(Pedido& ped, Articulo& art, double precio, unsigned cantidad=1);	//enlace pedido-articulo
		void pedir(Articulo& art, Pedido& ped, double precio, unsigned cantidad=1);	//enlace articulo-pedido
		
		/*-DETALLE-*/
		const ItemsPedido& detalle(Pedido& p);
		
		/*-VENTAS-*/
		Pedidos ventas(Articulo& a);
		
		/*-mostrarDetallePedidos-*/
		std::ostream& mostrarDetallePedidos(std::ostream& os) const;
		
		/*-mostrarVentasarticulos-*/
		std::ostream& mostrarVentasArticulos(std::ostream& os) const;
	
	private:
		/*--VARIABLES--*/
		PedArt ped_art_;
		ArtPed art_ped_;
};

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& p);

#endif
