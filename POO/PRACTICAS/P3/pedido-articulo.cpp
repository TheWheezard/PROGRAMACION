#include "pedido-articulo.hpp"

//función auxiliar para contar los digitos de un número (conteo de espacios en blanco)
int contdig(size_t n){
    if (n/10 == 0)
        return 1;
    return 1 + contdig(n / 10);
}

/*ORDENA-PEDIDOS BINARY*/
bool OrdenaPedidos::operator()(const Pedido* p1, const Pedido* p2) const {return p1->numero() < p2->numero();}

/*LINEA PEDIDO*/
std::ostream& operator<<(std::ostream& os, const LineaPedido& lp){
    os << std::setprecision(2) << std::fixed << lp.precio_venta() << " €   " << lp.cantidad();
    return os;
}

/*PEDIDO-ARTICULO*/
void Pedido_Articulo::pedir(Pedido& p, Articulo& a, const double precio, const size_t cantidad){
    ped_art[&p].insert(std::make_pair(&a, LineaPedido(precio, cantidad)));
    art_ped[&a].insert(std::make_pair(&p, LineaPedido(precio, cantidad)));
}
void Pedido_Articulo::pedir(Articulo& a, Pedido& p, const double precio, const size_t cantidad){
    Pedido_Articulo::pedir(p, a, precio, cantidad);
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p){
    return ped_art.find(&p)->second;
}

const Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a){
    if (art_ped.find(&a) != art_ped.end())
        return art_ped.find(&a)->second;
    else{
        Pedido_Articulo::Pedidos vacio;
        return vacio;
    }
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os) const noexcept{
    double cont = 0.0;
    for (auto& iter : ped_art){
        os << "Pedido núm. " << iter.first->numero() << std::endl
        << "Cliente: " << iter.first->tarjeta()->titular()->nombre()
        << "\tFecha: " << iter.first->fecha() << std::endl << iter.second << std::endl;
        cont += iter.first->total();
    }
    os << "TOTAL VENTAS: " << std::setprecision(2) << std::fixed << cont << " €" << std::endl;
    return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os) const noexcept{
    for (auto& iter : art_ped){
        os << "Ventas de [" << iter.first->referencia() << "] \"" << iter.first->titulo() << "\""
        << std::endl << iter.second << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip){
	double precio = 0.0;

	os << std::endl << "=========================================================" << std::endl
	<< " PVP \t Cant. \t\t Articulo" << std::endl
	<< "=========================================================" << std::endl;
	for (auto& iter : ip){
		os << iter.second;
        for(size_t i = 0; i < 7 - contdig(iter.second.cantidad()); ++i){
            os << " "; // introducimos los espacios exactos para que todas las líneas queden igual
        }
		os << "["<<iter.first->referencia() << "] "
		<< "\"" << iter.first->titulo() << "\" " << std::endl;

		precio += iter.second.precio_venta() * iter.second.cantidad();
	}
	
	os << "=========================================================" << std::endl
	<< std::setprecision(2) << std::fixed << precio << " €" << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& pedidos){
	double precio = 0.0;
	size_t total = 0;

	os << "=====================================================" << std::endl
	<< " PVP \t Cant. \t\t Fecha venta" << std::endl
    << "=====================================================" << std::endl;
	for (auto iter : pedidos){
		os << iter.second;
        for(size_t i = 0; i < 11 - contdig(iter.second.cantidad()); ++i){
            os << " "; // introducimos los espacios exactos para que todas las líneas queden igual
        }
        os << iter.first->fecha() << std::endl;
		precio += iter.second.precio_venta() * iter.second.cantidad();
		total += iter.second.cantidad();
	}
	
	os <<"=====================================================" << std::endl
	<< std::setprecision(2) << std::fixed << precio << " € \t" << total << std::endl;	
	return os;
}