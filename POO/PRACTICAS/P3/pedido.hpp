#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "usuario.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

#include <iomanip>
#include <iostream>

class Pedido_Articulo;
class Tarjeta;
class Usuario_Pedido;

/*---CLASE PEDIDO---*/
class Pedido
{
	public:
		/*--CONSTRUCTOR--*/
		Pedido(Usuario_Pedido& UP, Pedido_Articulo& PA, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& f=Fecha());
		
		/*--OBSERVADORES--*/
		const int numero() const noexcept			{return n_p_;}
		const Tarjeta* tarjeta() const noexcept		{return tarjeta_;}
		const Fecha fecha() const noexcept			{return fPedido_;}
		const double total() const noexcept			{return importe_;}
		static unsigned n_total_pedidos() noexcept	{return N_pedidos;}
		
		/*---CLASE VACIO (PARA EXCEPCIONES)--*/
		class Vacio
		{
			public:
				/*--CONSTRUCTOR--*/
				Vacio(Usuario* us): us_(us){}
				
				/*--OBSERVADORA--*/
				Usuario& usuario() const{return *us_;}		
			private:
				/*--VARIABLES PRIVADAS--*/
				Usuario* us_;
		};
		
		/*---CLASE IMPOSTOR (PARA EXCEPCIONES)---*/
		class Impostor
		{
			public:
				/*--CONSTRUCTOR--*/
				Impostor(Usuario *us): us_(us){}
				
				/*--OBSERVADORA--*/
				Usuario& usuario() const {return *us_;}
			
			private:
				/*--VARIABLES PRIVADAS--*/
				Usuario *us_;
		};
		
		/*---CLASE SINSTOCK (PARA EXCEPCIONES)---*/
		class SinStock
		{
			public:
				/*--CONSTRUCTOR--*/
				SinStock(Articulo *art): art_(art){}
				Articulo& articulo()const {return *art_;}
				
			private:
				/*--VARIABLE PRIVADA--*/
				Articulo* art_;
		};
	
	private:
		/*--VARIABLES PRIVADAS--*/
		int n_p_;
		const Tarjeta* tarjeta_;			//numero de pedido, desde 1 se va incrementando en 1
		Fecha fPedido_;					//fecha del pedido
		double importe_;					//importe total
		static unsigned N_pedidos;		//cantidad de pedidos hechos
};

std::ostream& operator<<(std::ostream& os, const Pedido& p);

#endif
