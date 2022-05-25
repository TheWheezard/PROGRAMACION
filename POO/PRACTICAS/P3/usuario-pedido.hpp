#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <set>
#include <map>

class Pedido;
class Usuario;

class Usuario_Pedido{
public:
    void asocia(Usuario&, Pedido&);
    void asocia(Pedido&, Usuario&);
    const std::set<Pedido*>& pedidos(Usuario&) const noexcept;
    const Usuario* cliente(Pedido&) const noexcept;
private:
    std::map<Usuario*,std::set<Pedido*>> user_peds;
    std::map<Pedido*, Usuario*> ped_user;
};

#endif // !USUARIO_PEDIDO_HPP