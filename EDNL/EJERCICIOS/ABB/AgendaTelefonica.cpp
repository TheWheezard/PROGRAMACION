#include "..\..\Implementaciones\Abb.hpp"
#include <string>
#include <iostream>

// La estructura contacto contiene un campo string que almacena un nombre
// y un campo size_t que almacena un número de teléfono. No se va a comprobar
// que un número de teléfono sea válido.
struct contacto {
    contacto(std::string nom, size_t num):nombre(nom), numero(num){}
    std::string nombre;
    size_t numero;
};

//OPERADORES DE COMPARACIÓN
bool operator < (contacto c1, contacto c2){
    return c1.nombre < c2.nombre;
}
bool operator == (contacto c1, contacto c2){
    return c1.nombre == c2.nombre;
}
bool operator == (std::string c1, contacto c2){
    return c1 == c2.nombre;
}

// La clase AgendaTelefónica crea un ABB, donde almacena estructuras de tipo contacto
// ordenadas por el campo nombre. Permite añadir, eliminar, buscar y listar contactos.
class AgendaTelefonica{
public:
    AgendaTelefonica () { agenda = new Abb<contacto>; }
    ~AgendaTelefonica () { delete agenda; }
    bool insertarContacto (std::string, size_t);
    void eliminarContacto (std::string);
    size_t buscarContacto (std::string);
    void listarContactos ();
private:
    Abb<contacto>* agenda;
    bool existe (contacto);
};

// Recibe un string nombre y un size_t numero.
// Crea un nuevo contacto e intenta insertarlo en la agenda.
// Devuelve True si lo inserta, False si no lo inserta.
bool AgendaTelefonica::insertarContacto(std::string nombre, size_t numero) {
    contacto c {nombre, numero};
    if (!existe(c)) {
        agenda->insertar(c);
        return true;
    }
    else return false;
}

// Recibe un string con el nombre.
// Comprueba si existe el contacto en la agenda.
// En caso de existir el contacto, lo elimina. En caso contrario no hace nada.
void AgendaTelefonica::eliminarContacto(std::string nombre) {
    contacto c {nombre, 0};
    if (existe(c))
        agenda->eliminar(c);
}

// Recibe un string con el nombre.
// Comprueba si existe el contacto en la agenda.
// En caso afirmativo, devuelve el número de teléfono. En caso negativo, devuelve 0.
size_t AgendaTelefonica::buscarContacto(std::string nombre) {
    contacto c {nombre, 0};
    Abb<contacto> res = agenda->buscar(c);
    if (!res.vacio())
        return res.elemento().numero;
    else return c.numero;
}

//TODO: LISTAR CONTACTOS Y EXISTE