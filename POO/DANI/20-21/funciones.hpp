#include<iostream>
#include<math.h>
#include<vector>
#include<fstream>
/*
Se trata de implementar en C++ una funcion generica, ordenado(), que decida si los elementos 
de un rango de iteradores aparecen en un cierto orden. Para lograr la maxima generalidad,
los unicos requisitos que la funcion impondra es que los iteradores sean de entrada y que la
relacion de orden tenga las propiedades de un orden estricto debil (es reflexiva,
antisimétrica y transitiva). Tambien hay que tratar adecuadamente los rangos vacios, 
que se suponen ordenados, ya que no contienen elementos.
*/
//Escriba una version que compruebe el orden respecto del operator < del tipo en cuestion
template <class T>
bool ordenado(const T* first, const T* last)
{
    for (; first != last; first++)
    {
        if (*first > *(++first)) return false;
         
    }
    return true;
}
//Escriba una version que compruebe el orden respecto de una funcion de comparacion arbitraria
template<class T>
bool f(const T* first, const  T* last)
{
    if (*first > *(first+1)) return false;
    else return true;
}

template <class T>
bool ordenadoFuncion(const T* first,const  T* last, bool (*f)(const T* f,const  T* l))
{
    for (; first != last; first++)
    {
        if (!f(first, last)) return false;
    }
    return true;
}
/*
Escriba un fragmento de codigo que compruebe si un vector de bajo nivel de enteros 
esta en orden ascendente de valores absolutos. Emplee un objeto funcion.
*/
template <class T>
bool ordenadoFuncionObj(const T* first, const T* last)
{
    auto funcion=[](T* valor)->bool
    {
        if (abs(*valor) > abs(*(valor+1))) return false;
        else return true;
    };
    for (; first != last; first++)
    {
        if (!funcion(first)) return false;
    }
    return true;
}
/*
Escriba un fragmento de codigo que compruebe si un fichero de texto que contiene enteros
separados por espacio blanco esta en orden ascendente
*/
bool ordenadoFichero()
{
    std::ifstream fichero("numeros.txt"); //Abrir el fichero
    std::string linea,token;
    int pos=0;
    std::vector<int> v;

    while (std::getline(fichero,linea)) //Bucle para procesar las lineas del fichero
    {
        while(linea.find(' ')<linea.length())
        {
            //std::cout << linea << std::endl;
            token = linea.substr(0, linea.find(' '));
            //std::cout << "substring desde 0"  << " hasta " << linea.find(' ') << " = " <<  token << std::endl;
            v.push_back(atoi(token.c_str()));

            size_t p=linea.find(' ');
            ++p;
            linea=linea.substr(p, linea.length());
        }
        v.push_back(atoi(linea.c_str()));
    }
    fichero.close();
    return(ordenado(&v[0],&v[v.size()-1]));
}

/*
Codigo del main

int main()
{
    bool (*pf)(const int*,const int*); //Declaramos el puntero a funcion f
    pf=f;

    int v[5]={2,5,7,9,11};
    if(ordenadoFuncionObj(&v[0], &v[4]))
        cout << "OK";
    else
        cout << "NO ord";

    if(ordenadoFuncion(&v[0], &v[4], pf))
        cout << "OK ordenadofuncion";
    else
        cout << "NO ordenadofuncion";
    cout << endl;
    
    if(ordenadoFichero())
        cout << "OK Fichero";
    else
        cout << "NO Fichero";

}


*/