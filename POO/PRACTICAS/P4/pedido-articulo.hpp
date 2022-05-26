#ifndef Pedido_Articulo_HPP
#define Pedido_Articulo_HPP
#include <iostream>
#include <iomanip>
#include <map>
#include "articulo.hpp"
#include "pedido.hpp"

/*DECLARACIONES DE CLASES*/
class Pedido;
class Articulo;

/*BINARY FUNCTIONS*/
class OrdenaPedidos: public std::binary_function<Pedido*, Pedido*, bool>{
public:
    bool operator()(const Pedido*, const Pedido*) const;
};

class OrdenaArticulos: public std::binary_function<Articulo*, Articulo*, bool>{
public:
	bool operator()(const Articulo* a1, const Articulo* a2) const {return a1->referencia() < a2->referencia();}
};

/*LINEA PEDIDO*/
class LineaPedido{
public:
    explicit LineaPedido(const double, const size_t =1);
    const double precio_venta() const noexcept;
    const size_t cantidad() const noexcept;
private:
    double precio;
    size_t cant;
};
std::ostream& operator<<(std::ostream&, const LineaPedido&);
inline LineaPedido::LineaPedido(const double pv, const size_t c):precio(pv), cant(c){}
inline const double LineaPedido::precio_venta() const noexcept {return precio;}
inline const size_t LineaPedido::cantidad() const noexcept {return cant;}

/*PEDIDO-ARTICULO*/
class Pedido_Articulo{
public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

    void pedir(Pedido&, Articulo&, const double, const size_t =1);
    void pedir(Articulo&, Pedido&, const double, const size_t =1);
    const ItemsPedido& detalle(Pedido&);
    const Pedidos ventas(Articulo&);
    std::ostream& mostrarDetallePedidos(std::ostream&) const noexcept;
    std::ostream& mostrarVentasArticulos(std::ostream&) const noexcept;
private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> ped_art;
    std::map<Articulo*, Pedidos, OrdenaArticulos> art_ped;
};
std::ostream& operator<<(std::ostream&, const Pedido_Articulo::ItemsPedido&);
std::ostream& operator<<(std::ostream&, const Pedido_Articulo::Pedidos&);


#endif // !Pedido_Articulo_HPP