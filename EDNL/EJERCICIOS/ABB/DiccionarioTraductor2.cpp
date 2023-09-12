#include "..\..\Implementaciones\Abb.hpp"
#include <string>
#include <iostream>

/**
 * @brief Versión mejorada del ejercicio 1 del examen de septiembre de 2019. Se trata de un diccionario traductor que permite escoger entre dos idiomas,
 * español y zuelandés. Se puede insertar una palabra con su traducción, eliminar una palabra con su traducción, buscar la traducción de una palabra, como
 * principales operaciones. Además, se puede listar todo el diccionario. Para ello se ha implementado un ABB que guarda en su interior una estructura Termino
 * que guarda en su interior una palabra, un enum que indica el idioma en que está y un puntero a Termino que apunta a otro término establecido como traducción.
 * 
 * @file DiccionarioTraductor.cpp
 * @version 0.1
 * @date 2023-09-09
 */


enum opIdioma {es, zu}; // especifica el idioma de un término con es(pañol) o zu(elandés)

// La estructura Termino guarda en su interior una cadena con una palabra,
// un enum que indica el idioma en que está y un puntero a Termino que apunta a otro término
// establecido como traducción.
struct Termino {
    Termino (std::string pal, opIdioma v) : palabra(pal), idioma(v), traduccion(nullptr){}
    std::string palabra; //término que guardamos
    opIdioma idioma;
    Termino* traduccion; //puntero a la traducción
};

//Sobrecarga del operador de salida OSTREAM para imprimir por pantalla el tipo Termino
std::ostream* operator<<(std::ostream* os, Termino term){
    *(os) << term.palabra;
    return os;
}

//Sobrecarga de operadores de orden y comparación
bool operator < (std::string s, Termino t){
    return s < t.palabra;
}
bool operator == (std::string s, Termino t){
    return s == t.palabra;
}
bool operator == (Termino t, std::string s){
    return t.palabra == s;
}
bool operator == (Termino t1, Termino t2){
    return t1.palabra == t2.palabra && t1.idioma == t2.idioma;
}
bool operator != (Termino t1, Termino t2){
    return !(t1 == t2);
}
bool operator < (Termino t1, Termino t2){
    if (t1.palabra == t2.palabra){
        return t1.idioma < t2.idioma;
    }
    else return t1.palabra < t2.palabra;
}

// Clase que emula el comportamiento de un diccionario español-zuelandés, en el que se permite ingresar palabras con su traducción,
// eliminar palabras con su traducción, buscar la traducción de una palabra y listar todo el diccionario.
class DiccionarioTraductor {
public:
    DiccionarioTraductor() : diccionario(*new Abb<Termino>()) {}

    void insertar_traduccion (std::string palabra1, opIdioma idioma1, std::string palabra2, opIdioma idioma2);
    
    void eliminar_traduccion (std::string palabra, opIdioma idioma);

    std::string devolver_traduccion (std::string palabra, opIdioma idiomaOrigen);

private:
    bool existe (std::string palabra, opIdioma idioma);
    bool existe (Termino palabra);

    Abb<Termino> diccionario;
};

void DiccionarioTraductor::insertar_traduccion (std::string palabra1, opIdioma idioma1, std::string palabra2, opIdioma idioma2) {
    Termino* termino1 = new Termino (palabra1, idioma1);
    Termino* termino2 = new Termino (palabra2, idioma2);

    if (idioma1 != idioma2 && palabra1 != palabra2) {
        if (!existe(*termino1) && !existe(*termino2)) {
            termino1->traduccion = termino2;
            termino2->traduccion = termino1;
            diccionario.insertar(*termino1);
            diccionario.insertar(*termino2);
        }
        else if (!existe(*termino1) && existe(*termino2)) {
            diccionario.eliminar(*termino2->traduccion);
            delete termino2->traduccion;
            termino1->traduccion = termino2;
            termino2->traduccion = termino1;
            diccionario.insertar(*termino1);
        }
        else if (existe(*termino1) && !existe(*termino2)) {
            diccionario.eliminar(*termino1->traduccion);
            delete termino1->traduccion;
            termino2->traduccion = termino1;
            termino1->traduccion = termino2;
            diccionario.insertar(*termino2);
        }
    }
}

void DiccionarioTraductor::eliminar_traduccion (std::string palabra, opIdioma idioma) {
    if (existe(palabra, idioma)) {
        Termino t = diccionario.buscar(*new Termino(palabra, idioma)).elemento();
        diccionario.eliminar(*t.traduccion);
        delete t.traduccion;
        diccionario.eliminar(t);
    }
}

std::string DiccionarioTraductor::devolver_traduccion (std::string palabra, opIdioma idioma) {
    Termino t (palabra, idioma);
    if (existe(t)) {
        return diccionario.buscar(t).elemento().traduccion->palabra;
    }
    else return "Término no encontrado";
}

bool DiccionarioTraductor::existe(std::string palabra, opIdioma idioma) {
    return existe (*new Termino(palabra, idioma));
}

bool DiccionarioTraductor::existe(Termino palabra) {
    if (!diccionario.buscar(palabra).vacio())
        return true;
    else return false;
}