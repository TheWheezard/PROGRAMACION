#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "usuario.hpp"
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "articulo.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"


class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

class Pedido{
public:
    Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha& = Fecha());
    class Vacio{
    public:
        Vacio(Usuario* us):us_(us){}
        Usuario& usuario() const {return *us_;}
    private:
        Usuario* us_;
    };
    class Impostor{
    public:
        Impostor(Usuario* us): us_(us){}
        Usuario& usuario() const {return *us_;}
    private:
        Usuario* us_;
    };
    class SinStock{
    public:
        SinStock(Articulo* art): art_(art){}
        Articulo& articulo() const {return *art_;}
    private:
        Articulo* art_;
    };
    //Observadores
    const int numero() const noexcept;
    const Tarjeta* tarjeta() const noexcept;
    const Fecha fecha() const noexcept;
    const double total() const noexcept;
    static size_t n_total_pedidos() noexcept;
private:
    int numped_;
    const Tarjeta* tarjeta_;
    Fecha fPedido_;
    double importe_;
    static size_t N_pedidos;
};

std::ostream& operator<<(std::ostream& os, const Pedido& p);

inline const int Pedido::numero() const noexcept {return Pedido::numped_;}
inline const Tarjeta* Pedido::tarjeta() const noexcept {return Pedido::tarjeta_;}
inline const Fecha Pedido::fecha() const noexcept {return Pedido::fPedido_;}
inline const double Pedido::total() const noexcept {return Pedido::importe_;}
inline size_t Pedido::n_total_pedidos() noexcept {return Pedido::N_pedidos;}

#endif // !PEDIDO_HPP