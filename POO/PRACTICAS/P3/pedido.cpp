#include "pedido.hpp"

size_t Pedido::N_pedidos{0};

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& f):numped_(N_pedidos+1), tarjeta_(&tarjeta), fPedido_(f), importe_(0.){
    if (tarjeta.titular() != &usuario) throw Pedido::Impostor(&usuario);  
    if (tarjeta.caducidad() < f) throw Tarjeta::Caducada(tarjeta.caducidad());
    if (!tarjeta.activa()) throw Tarjeta::Desactivada();
    auto carro = usuario.compra();
    if (carro.empty()) throw Pedido::Vacio(&usuario);

    for (auto& iter : carro){
        if(iter.first->stock() < iter.second){
            for (auto& iter2 : carro){
                usuario.compra(*iter2.first, 0);
            }
            throw Pedido::SinStock(iter.first);
        }
    }
    up.asocia(*this, usuario);
    for (auto& iter : carro){
        importe_ += iter.first->precio() * iter.second;
        pa.pedir(*iter.first, *this, iter.first->precio(), iter.second);
        iter.first->stock() -= iter.second;
    }

    const_cast<Usuario::Articulos&>(usuario.compra()).clear();
    numped_ = ++N_pedidos;
    
}

std::ostream& operator<<(std::ostream& os, const Pedido& ped){
    os << "Núm. pedido: " << ped.numero() << std::endl
    << "Fecha:       " << ped.fecha() << std::endl
    << "Pagado con:  " << ped.tarjeta()->tipo() << " nº: " << ped.tarjeta()->numero() << std::endl
    << "Importe:     " << ped.total() << " €" << std::endl;
    return os;
}