#include "pedido.hpp"

size_t Pedido::N_pedidos{0};

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& f):numped_(N_pedidos+1), tarjeta_(&tarjeta), fPedido_(f), importe_(0.){
    if (tarjeta.titular() != &usuario) throw Pedido::Impostor(&usuario);  
    if (tarjeta.caducidad() < f) throw Tarjeta::Caducada(tarjeta.caducidad());
    if (!tarjeta.activa()) throw Tarjeta::Desactivada();
    
    auto carro = usuario.compra();
    //Comprobamos Libros Digitales caducados
    for (auto& iter:usuario.compra()){
        LibroDigital* pLib = dynamic_cast<LibroDigital*>(iter.first);
        if (pLib != nullptr && pLib->f_expir() < f){// Si LibroDigital ha caducado
            carro.erase(iter.first); // lo eliminamos del carro
        }
    }
    if (carro.empty()) throw Pedido::Vacio(&usuario); //Si carro está vacío, usuario.compra() está vacío o solo tiene LibrosDig caducados
    
    ArticuloAlmacenable* pArt;
    //Comprobamos stock ArticuloAlmacenable
    for (auto& iter : carro){ 
        if ((pArt = dynamic_cast<ArticuloAlmacenable*>(iter.first))){ //Si es ArticuloAlmacenable
            if (pArt->stock() < iter.second){ //Si no tiene stock
                for (auto &iter2 : carro){
                    usuario.compra(*iter2.first, 0);
                }
                throw Pedido::SinStock(iter.first);
            }
        }
    }
    
    //Restamos stock ArticuloAlmacenable
    up.asocia(*this, usuario);
    for (auto& iter : carro){
        importe_ += iter.first->precio() * iter.second;
        pa.pedir(*iter.first, *this, iter.first->precio(), iter.second);
        if((pArt = dynamic_cast<ArticuloAlmacenable*>(iter.first))){
            pArt->stock() -= iter.second;
        }
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