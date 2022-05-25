#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario& u, Pedido& p){
    user_peds[&u].insert(&p);
    ped_user.insert(std::make_pair(&p, &u));
}

void Usuario_Pedido::asocia(Pedido& p, Usuario& u){
    asocia(u, p);
}

const std::set<Pedido*>& Usuario_Pedido::pedidos(Usuario& u) const noexcept {return user_peds.find(&u)->second;}
const Usuario* Usuario_Pedido::cliente(Pedido& p) const noexcept {return ped_user.find(&p)->second;}