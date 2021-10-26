#include "usuario.hpp"

unordered_set<Cadena> Usuario::registrados;

/***CLASE CLAVE***/
/*CONSTRUCTOR*/
Clave::Clave(const char* p){
	setlocale(LC_ALL,"");
	if(strlen(p)<5) throw Clave::Incorrecta(Clave::CORTA);
	random_device r;
	uniform_int_distribution<size_t>dist(0,63);
	char const MD5chars[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	char salt[2] = {MD5chars[dist(r)], MD5chars[dist(r)]};
	if(crypt(p,salt)==nullptr) throw Clave::Incorrecta(Clave::ERROR_CRYPT);	//ciframos y comprobamos que es correcto
	pass_c = crypt(p,salt);
}
/*FUNCION*/
bool Clave::verifica(const char* c) const
{
	char *p = crypt (c, pass_c.c_str());		
	return p == pass_c;		
}

/**CLASE INCORRECTA**/
/*CONSTRUCTOR*/
Clave::Incorrecta::Incorrecta(const Clave::Razon r): r_(r){}
/*DESTRUCTOR*/
Clave::~Clave(){}


/***CLASE USUARIO***/
/*CONSTRUCTOR*/
Usuario::Usuario(const Cadena& _id, const Cadena& _nomb, const Cadena& _apell, const Cadena& _direcc, const Clave& _pass)
		:ID_(_id), nombre_(_nomb), apell_(_apell), direcc_(_direcc), pass_(_pass), n_articulos_(articulos_.size()){
	if(!registrados.insert(ID_).second) throw Id_duplicado(ID_);
}

/**CLASE ID_DUPLICADO**/
/*CONSTRUCTOR*/
Usuario::Id_duplicado::Id_duplicado(const Cadena&c):idd_(c){}

/*FUNCIONES USUARIO*/
void Usuario::es_titular_de(const Tarjeta& t){
	if(t.titular() == this) tarjetas_[t.numero()] = const_cast<Tarjeta*>(&t);
}
void Usuario::no_es_titular_de(Tarjeta &t){
	tarjetas_.erase(t.numero());
}
void Usuario::compra(const Articulo &a, size_t cant){
	Usuario::Articulos::const_iterator got = articulos_.find(const_cast<Articulo*>(&a));
	if(got == articulos_.end()){
		if(cant>0){
			articulos_[const_cast<Articulo*>(&a)]=cant;
			n_articulos_++;
		}
	}
	else{
		if(cant > 0){
			articulos_[const_cast<Articulo*>(&a)]=cant;
		}
		else{
			articulos_.erase(const_cast<Articulo*>(&a));
			n_articulos_--;
		}
	}
}
/*DESTRUCTOR*/
Usuario::~Usuario(){
	for(auto& i:tarjetas_){
		i.second->anula_titular();
	}
	registrados.erase(ID_);
}

/*OPERADORES*/
ostream& operator <<(ostream& os, const Usuario& u) noexcept{
	setlocale(LC_ALL,"");		//categoria --> LC_ALL && localidad --> entorno nativo
	os<<u.ID_<<"["<<u.pass_.clave()<<"]"<<u.nombre_<<" "<<u.apell_<<endl;
	os<<u.direcc_<<endl;
	os<<"Tarjetas:\n";
	for(auto& t:u.tarjetas_){
		os<<*t.second<<endl;
	}
	return os;
}
void mostrar_carro (ostream &os, const Usuario &u){
	os<<"Carrito de compra de "<<u.id()<<" [Artículos: "<<u.n_articulos()<<"]"<< endl<< " Cant.\tArtículo" <<endl;
	os<<"========================================================"<<endl;
	for(Usuario::Articulos::const_iterator i = u.compra().begin(); i!=u.compra().end();i++){
		os<<" "<<i->second<<"\t"<<"["<<i->first->referencia()<<"] \""<<i->first->titulo()<<"\", ";	//usamos iteradores para navegar y mostrar los elementos
		os<<i->first->f_publi().anno()<<". "<<setprecision(2)<<fixed<<i->first->precio()<<" €"<<endl;
	}
	
}
	
		
