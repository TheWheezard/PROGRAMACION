#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include <map>
#include <set>

class Pedido;
class Usuario;

class Usuario_Pedido
{
	public:
		/*--DEFINICIONES--*/
		typedef std::set<Pedido*> Pedidos;
		typedef std::map<Usuario*, Pedidos> UsuarioP;
		typedef std::map<Pedido*, Usuario*> PedidoU;
		
		/*--OBSERVADORES--*/
		/*-ASOCIA-*/
		void asocia(Usuario& us, Pedido& ped){usu_ped_[&us].insert(&ped); ped_usu_[&ped]=&us;}		//enlace usuario-pedido
		void asocia(Pedido& ped, Usuario& us){asocia(us, ped);}											//enlace pedido-usuario
		
		/*-PEDIDOS-*/
		Pedidos& pedidos(Usuario& us){return usu_ped_.find(&us)->second;}
		
		/*-CLIENTE-*/
		Usuario* cliente(Pedido& ped){return ped_usu_.find(&ped)->second;}
		
	
	private:
		/*--VARIABLES--*/
		UsuarioP usu_ped_;
		PedidoU ped_usu_;
};

#endif

