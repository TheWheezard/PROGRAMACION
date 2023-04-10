#include "..\..\Implementaciones\Abb.hpp"
#include <string>
#include <iostream>

enum opIdioma {es, zu}; // especifica el idioma de un término con es(pañol) o zu(elandés)
// La estructura termino guarda en su interior una cadena con una palabra,
// un enum que indica el idioma en que está y un puntero a termino que apunta a otro término
// establecido como traducción.
struct termino {

    termino (std::string pal, opIdioma v) : palabra(pal), idioma(v), traduccion(nullptr){}
    std::string palabra; //término que guardamos
    opIdioma idioma;
    termino* traduccion; //puntero a la traducción
};
//Sobrecarga del operador de salida OSTREAM para imprimir por pantalla el tipo termino
std::ostream* operator<<(std::ostream* os, termino term){
    *(os) << term.palabra;
    return os;
}
//Sobrecarga de operadores de orden y comparación
bool operator < (std::string s, termino t){
    return s < t.palabra;
}
bool operator == (std::string s, termino t){
    return s == t.palabra;
}
bool operator == (termino t, std::string s){
    return t.palabra == s;
}
bool operator == (termino t1, termino t2){
    return t1.palabra == t2.palabra && t1.idioma == t2.idioma;
}
bool operator < (termino t1, termino t2){
    if (t1.palabra == t2.palabra){
        return t1.idioma < t2.idioma;
    }
    else return t1.palabra < t2.palabra;
}

// Clase que emula el comportamiento de un diccionario español-zuelandés, en el que se permite ingresar palabras con su traducción,
// eliminar palabras con su traducción, buscar la traducción de una palabra y listar todo el diccionario.
class DiccionarioTraductor {
public:
    DiccionarioTraductor () { diccionario = new Abb<termino>; }
    ~DiccionarioTraductor () { delete diccionario; }
    bool insertarPalabra(std::string, std::string);
    void eliminarPalabra(std::string, opIdioma);
    std::string traducirPalabra(std::string, opIdioma);
    void listarPalabras();
//private:
    bool existe (termino&);
    void procesarTermino(const Abb<termino>&);
    Abb<termino>* diccionario;
};

// Comprueba si un término existe en el diccionario.
// Recibe un término.
// Intenta localizar el término en el árbol. Devuelve True si existe, False si no se encuentra.
bool DiccionarioTraductor::existe (termino& term){
    Abb<termino> res = diccionario->buscar(term);
    if (res.vacio()){ // si res está vacío, el término no existe
        return false;
    }
    else return true;
}

// Realiza el recorrido en inorden del diccionario
// Imprime por pantalla la dupla español-zuelandés de cada término
void DiccionarioTraductor::procesarTermino(const Abb<termino>& a) {
    procesarTermino(a.izqdo());
    //procesar
    if (!a.vacio() && a.elemento().idioma == es) // si nodo existe y es una palabra en español, imprime con traducción
        std::cout << a.elemento().palabra << " - " << a.elemento().traduccion->palabra << std::endl;
    //fin_procesar
    procesarTermino(a.drcho());
}

// Recibe un término español y un término zuelandés, en ese orden.
// Une ambos términos como traducción uno del otro y trata de insertarlos en el diccionario.
// Si ya existe al menos uno de ellos, no los introduce.
// Devuelve True si introduce los términos, False en caso contrario.
bool DiccionarioTraductor::insertarPalabra(std::string espanol, std::string zuelandes) {
    termino esp = termino{espanol, es};
    termino zue = termino{zuelandes, zu};
    esp.traduccion = &zue;
    zue.traduccion = &esp;
    if (diccionario->vacio() || (!existe(esp) && !existe(zue))) {
        diccionario->insertar(esp);
        diccionario->insertar(zue);
        return true;
    }
    else {
        return false;
    }
}

// Recibe un término y el idioma en el que está, es(pañol) o zu(elandés).
// Comprueba si el término se encuentra en el diccionario.
// En caso de existir el término, se eliminan el término y su traducción.
// En caso contrario, no se hace nada.
void DiccionarioTraductor::eliminarPalabra(std::string cad, opIdioma op) {
    termino term = termino{cad, op};
    if (existe(term)){ // si existe el término, debe estar también su traducción
        term = (diccionario->buscar(term)).elemento();
        diccionario->eliminar(*term.traduccion); // eliminamos primero la traducción
        diccionario->eliminar(term); // eliminamos el término después
    }
}

// Recibe un término y el idioma en el que está, es(pañol) o zu(elandés).
// Comprueba si existe el término en el diccionario.
// Si el término existe, devolverá su traducción.
// Si el término no existe, devolverá una cadena vacía.
std::string DiccionarioTraductor::traducirPalabra(std::string cad, opIdioma op) {
    termino term = termino{cad, op};
    if (existe(term)) {
        term = (diccionario->buscar(term)).elemento();
        return term.traduccion->palabra;
    }
    else {
        std::string c;
        return c;
    }
}

// Crea una lista ordenada en "orden alfabético" de palabras españolas y su traducción al zuelandés
// Utiliza la función privada procesarTermino para imprimir las traducciones
void DiccionarioTraductor::listarPalabras() {
    std::cout << "Diccionario Español -Zuelandés" << std::endl << "Término Español - Término Zuelandés" << std::endl;
    procesarTermino(*diccionario);
    std::cout << "------------------------------" << std::endl;
}