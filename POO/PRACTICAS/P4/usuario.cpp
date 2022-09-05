#include "usuario.hpp"

std::unordered_set<Cadena> Usuario::identificadores;

/* CLASE CLAVE */
bool Clave::verifica(const char* c) const noexcept{
    char* pass = crypt(c, this->cad.c_str());
    return pass == this->cad;
}

Cadena Clave::cifrar(const char* ch) const{
    std::random_device r;
	std::uniform_int_distribution<size_t>dist(0,63);
	char const MD5chars[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	char salt[2] = {MD5chars[dist(r)], MD5chars[dist(r)]};
    char* aux = crypt(ch, salt);
    if (aux == nullptr)
        throw Clave::Incorrecta(Clave::ERROR_CRYPT);
    return Cadena(aux);
}
Cadena Clave::cifrar(const Cadena& c) const{
    const char* ch(c.c_str());
    return cifrar(ch);
}


/* CLASE USUARIO */


void Usuario::es_titular_de(const Tarjeta& t){
    if(t.titular() == this) tarjetas_[t.numero().num()] = const_cast<Tarjeta*>(&t);
}
void Usuario::no_es_titular_de(const Tarjeta& t){
    auto aux = this->tarjetas_.find(t.numero().num());
    aux->second->anula_titular();
    this->tarjetas_.erase(t.numero().num());
}
void Usuario::compra(const Articulo& art, int cantidad){
    if (cantidad > 0){
        if (this->compra_.find(const_cast<Articulo*>(&art)) == this->compra_.end())
            this->compra_.insert(std::make_pair(const_cast<Articulo*>(&art),cantidad));
        else
            this->compra_[const_cast<Articulo*>(&art)] = cantidad;
    }
    else if (cantidad == 0 && this->compra_.find(const_cast<Articulo*>(&art)) != this->compra_.end()){
        this->compra_.erase(const_cast<Articulo*>(&art));
    }
    this->n_articulos_ = this->compra_.size();
}

Usuario::~Usuario(){
    for (auto& iter:this->tarjetas_){
        iter.second->anula_titular();
    }
    identificadores.erase(this->id_);
}

void mostrar_carro(std::ostream& os, const Usuario& us){
    os << "Carrito de compra de " << us.id() << " [Artículos: " << us.n_articulos() << "]" << std::endl
    << "  Cant. Artículo" << std::endl << "===========================================================" << std::endl;
    for (auto iter : us.compra()){
        os << "   " << iter.second << "   " 
        << "[" << iter.first->referencia() << "] \"" << iter.first->titulo() << "\", " << iter.first->f_publi().anno() <<". " << std::setprecision(2) << std::fixed << iter.first->precio() << " €"
        << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Usuario& us){
    os << us.id() << " [" << us.contrasenia.clave() << "] " << us.nombre() << " " << us.apellidos() << std::endl
    << us.direccion() << std::endl << "Tarjetas:" << std::endl;
    for (auto iter = us.tarjetas().begin(); iter!=us.tarjetas().end(); ++iter){
        os << *iter->second << std::endl;
    }

    return os;
}