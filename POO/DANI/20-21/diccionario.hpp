/*
Se desea implementar en C++ una clase que almacene un diccionario. Esta clase se denominara
 Diccionario y su representacion interna estara basada en un atributo: una aplicacion o
map. Cada elemento de esta aplicacion sera un par de palabras (string); el primer componente
del par sera una palabra en un idioma y el segundo sera su correspondiente traduccion en otro
idioma.

Defina un constructor que reciba un nombre de fichero en un string.
Ese fichero contendra una serie de lineas compuestas de dos palabras separadas por espacios.
El constructor debera leer cada una de esas lineas e introducir, por cada una de ellas, un par
en la aplicacion cuyo primer elemento sera la primera palabra de la linea y el segundo la
segunda palabra de la linea.
Si se le pasa la cadena vacia como nombre de fichero no añaadira nada a la aplicacion (map)

¿Que hay que hacer para que dicho constructor sirva ademas de constructor predeterminado
(para la cadena vacia) y para que no se realicen conversiones implicitas con el?

Defina un metodo entradas que devuelva el numero de entradas del diccionario.

Defina un metodo introduce que reciba dos string, una palabra y su traduccion, e
introduzca una nueva entrada en el diccionario.

Defina un metodo traduccion que reciba una palabra y devuelve su traduccion asociada.
Si no se encuentra, devuelve la cadena vacia

Sobrecargue el operador de indice para poder acceder al par i-esimo del diccionario.
Si no se encuentra, devuelve un par de cadenas vacias.
Para realizar este operador le sera util la funcion generica de la STL advance que recibe un
iterador y un entero, y hace avanzar el iterador tantas posiciones como indique el entero.
*/
#include<iostream>
#include<string>
#include<map>
#include<fstream>
class Diccionario
{
public:
    explicit Diccionario(std::string nombre="")
    {
        std::ifstream fichero(nombre);
        std::string linea;

        while (std::getline(fichero,linea))
        {
            size_t pos = linea.rfind(' ');
            d.insert(std::make_pair(linea.substr(0, pos),linea.substr(pos+1, linea.size())));
        }
        fichero.close();
    }
    size_t entradas() const
    {
          return d.size();
    }
    void introduce(std::string palabra1, std::string palabra2)
    {
        d.insert(std::make_pair(palabra1, palabra2));
    }
    std::string traduccion(std::string palabra)
    {
        //Controlar si no se encuentra
        return d[palabra];
    }
    std::pair<std::string, std::string> operator[](size_t n) const
    {
        std::map<std::string, std::string>::const_iterator i=d.begin();
        std::advance(i,n);
        return *i;
    }
    void mostrar()
    {
        std::map<std::string, std::string>::iterator i;
        for(i=d.begin();i!=d.end();++i)
        {
            std::cout << i->first << "-" << i->second << std::endl;

        }
    }
private:
    std::map<std::string, std::string> d;
};
