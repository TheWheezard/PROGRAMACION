#ifndef PRACTICA6_HPP_
#define PRACTICA6_HPP_

#include <string>
#include <fstream>
#include <algorithm>
#include "Dijkstra.hpp"
#include "Floyd.hpp"
#include "Warshall.hpp"

using namespace std;

//Ejercicios 1 y 2-------------------------------------------------------------
/*
 Sobrecargar el operador de extracción >> para leer de un flujo de entrada de tipo
istream la matriz de costes de un grafo ponderado. El grafo estará definido
previamente y el operador se limitará a sustituir las aristas que pueda tener por los pesos
extraídos de la entrada.
Para facilitar la introducción de grafos en los programas de prueba utilizaremos la
función leerFicheroGrafo(), cuyo parámetro es el nombre de un fichero de texto
del cual lee la matriz de costes de un grafo. En el fichero debe aparecer el número de
nodos del grafo seguido de los pesos de las aristas en orden creciente de filas y
columnas de la matriz de costes, por conveniencia podemos escribir una fila de la matriz
en cada línea del fichero. 
*/
//Entrada
template <typename tCoste>
istream& operator >>(istream& is, GrafoP<tCoste>& g){
    tCoste e;
    for(size_t i=0; i<g.numVert(); ++i){
        for(size_t j=0; j<g.numVert(); ++j){
            is >> e;
            if(e == -1)
                g[i][j] = GrafoP<tCoste>::INFINITO;
            else
                g[i][j] = e;
        }
    }
    return is;
}

//Salida
template <typename tCoste>
ostream& operator <<(ostream& os, const GrafoP<tCoste> g){
    os << "\t";
    for(size_t i=0; i<g.numVert(); ++i)
        os << i << "\t";
    os << "\n\n";
    for(size_t i=0; i<g.numVert(); ++i){
        os << i << "\t";
        for(size_t j=0; j<g.numVert(); ++j)
            if(g[i][j] == GrafoP<tCoste>::INFINITO)
                os << char(126) << "\t";
            else
                os << g[i][j] << "\t";
        os << "\n\n";
    }
    return os;
}

//Principal
template <typename tCoste>
GrafoP<tCoste> leerFicheroGrafo(const string& nf, GrafoP<tCoste> w)
{
    ifstream fg(nf.c_str()); // apertura del fichero
    unsigned n; // núm. vértices
    fg >> n; //lee la primera linea del fichero que contiene el numero de vertices del grafo
    GrafoP<tCoste> g(n); // Se instancia un grafo ponderado de n vértices
    fg >> g; // lectura de aristas usando la sobrecarga del operador >>
    fg.close(); // cierre del fichero
    return g;
}
/*
3. Escribir una función genérica que implemente el algoritmo de Dijkstra usando un
grafo ponderado representado mediante listas de adyacencia
*/
template <typename tCoste>
GrafoPL<tCoste> generarGrafoPL()
{
    GrafoPL<tCoste> g(5);
    typename Lista<typename GrafoPL<tCoste>::vertice_coste>::posicion pos=g.adyacentes(0).primera();
    g.adyacentes(0).insertar(GrafoPL<tCoste>::INFINITO, pos);

    return g;
}
/*
template<typename tCoste>
std::vector<tCoste> DijkstraL(GrafoPL<tCoste>& g) //Dijkstra aplicado a un grafo con listas de hijos
{
    GrafoPL<tCoste>::vertice origen, destino;
    Lista<GrafoPL<tCoste>::vertice_coste>::posicion p;
    tCoste menorCoste;
    for(origen=0;origen<g.numVert();++origen)
    {

    }
}
*/
//----------------------------------------Dijkstra inverso------------------------------------
//Dijkstra -> Costes minimos desde un nodo origen al resto 
//Dijkstra inverso -> Costes minimos desde todos los nodos hasta un nodo destino
template <typename tCoste>
std::vector<tCoste> DijkstraInv(const GrafoP<tCoste>& G, typename GrafoP<tCoste>::vertice destino,
std::vector<typename GrafoP<tCoste>::vertice>& P)
{
    typename GrafoP<tCoste>::vertice v;
    const size_t n = G.numVert();
    std::vector<tCoste> D(n,0); // Costes mínimos desde todos los nodos hasta el destino
    matriz<typename GrafoP<tCoste>::vertice> Q;
    matriz<tCoste> f=Floyd(G, Q);
    for(v=0;v<n;++v)
    {
        D[v]=f[v][destino]; //Almacenamos en el vector que devolvemos la columna correspondiente de la matriz de Floyd
        //que coincide con el destino
    }
    return D;
}
//Funcion que calcula el minimo coste entre origen y destino usando Floyd
template<typename tCoste>
tCoste menor_coste_Floyd(GrafoP<tCoste>& g, typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino)
{
    matriz<typename GrafoP<tCoste>::vertice> P;
    matriz<tCoste> f=Floyd(g, P);
    return f[origen][destino];
}
//Funcion que calcula el minimo coste entre origen y destino usando Dijkstra
template<typename tCoste>
tCoste menor_coste_Dijkstra(GrafoP<tCoste>& g, typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino)
{
    std::vector<typename GrafoP<tCoste>::vertice> P;
    std::vector<tCoste> f=Dijkstra(g, origen, P);
    return f[destino];
}

/*
4. Se define el pseudocentro de un grafo conexo como el nodo del mismo que minimiza
la suma de las distancias mínimas a sus dos nodos más alejados.
Se define el diámetro del grafo como la suma de las distancias mínimas a los dos
nodos más alejados del centro del grafo.
Dado un grafo conexo representado mediante matriz de costes, implementa un
subprograma que devuelva la longitud de su diámetro
*/
template<typename tCoste>
tCoste sumaMayores(std::vector<tCoste> v) //devuelve la suma de los dos nodos mas alejados 
{
    typename GrafoP<tCoste>::vertice i;
    for(i=0;i<v.size();++i) //Sustituye todos los INFINITOS del vector por 0 para poder ordenarlos de menor a mayor
    {
        if (v[i]==GrafoP<tCoste>::INFINITO)
        {
            v[i]=0;
        }
    }
    std::sort(v.begin(), v.end());
    if(v[v.size()-1]!=0 && v[v.size()-2]!=0)
        return v[v.size()-1] + v[v.size()-2]; //Devuelve la suma de los 2 mayores costes
    else
        return GrafoP<tCoste>::INFINITO;
}

template<typename tCoste>
typename GrafoP<tCoste>::vertice pseudocentro(GrafoP<tCoste>& g, tCoste& diametro)
{
    typename GrafoP<tCoste>::vertice v, pcentro;
    tCoste sumaMin=GrafoP<tCoste>::INFINITO;
    matriz<typename GrafoP<tCoste>::vertice> P;
    matriz<tCoste> m=Floyd(g, P); //costes minimos entre todos los nodos del grafo
    //cout << m <<endl;
    for(v=0;v<m.dimension();++v) //Recorremos todos los costes minimos para cada nodo
    {
        if(sumaMayores(m[v])<sumaMin) //Seleccionamos aquel nodo cuya suma de costes a sus nodos mas alejados sea minima
        {
            sumaMin=sumaMayores(m[v]);
            pcentro=v;
        }
    }
    diametro=sumaMin; //Devolvemos el diametro
    return pcentro; //devolvemos el pseudocentro
}

//-----------------------
template<typename tCoste>
tCoste diametro(GrafoP<tCoste>& g)
{
   typename GrafoP<tCoste>::vertice pcentro=pseudocentro(g);
   std::vector<typename GrafoP<tCoste>::vertice> P;
   std::vector<tCoste> v=Dijkstra(g, pcentro, P);
   for(size_t i=0;i<v.size()-1;++i)
   {
        if(v[i]==GrafoP<tCoste>::INFINITO)
            v[i]=0;
   }
   std::sort(v.begin(), v.end());
   std::cout << v << std::endl;
   return v[v.size()-1]+v[v.size()-2];
}
/*
5. Tu empresa de transportes “PEROTRAVEZUNGRAFO S.A.” acaba de recibir la
lista de posibles subvenciones del Ministerio de Fomento, en la que una de las más
jugosas se concede a las empresas cuyo grafo asociado a su matriz de costes sea
acíclico. ¿Puedes pedir esta subvención?.
Implementa un subprograma que a partir de la matriz de costes, nos indique si tu
empresa tiene derecho a dicha subvención. 
*/
template<typename tCoste>
bool aciclico(GrafoP<tCoste>& g)
{
    typename GrafoP<tCoste>::vertice v, w;
    bool a=true;
    for(v=0;v<g.numVert();++v)
    {
        if(g[v][v]!=GrafoP<tCoste>::INFINITO)
            a=false;
    }
    return a;
}
/*
6. Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre
dos ciudades cualesquiera de un país llamado Zuelandia. El problema es sencillo pero
hay que tener en cuenta unos pequeños detalles:
a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas
y por tanto solo permiten un sentido de la circulación.
b) Actualmente Zuelandia es un país en guerra. Y de hecho hay una serie de
ciudades del país que han sido tomadas por los rebeldes, por lo que no pueden
ser usadas para viajar.
c) Los rebeldes no sólo se han apoderado de ciertas ciudades del país, sino que
también han cortado ciertas carreteras, (por lo que estas carreteras no pueden ser
usadas). 
d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido
que absolutamente todos los viajes que se hagan por el país pasen por la capital
del mismo, donde se harán los controles de seguridad pertinentes.
Dadas estas cuatro condiciones, se pide implementar un subprograma que dados
• el grafo (matriz de costes) de Zuelandia en situación normal,
• la relación de ciudades tomadas por los rebeldes,
• la relación de carreteras cortadas por los rebeldes
• y la capital de Zuelandia,
calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades
zuelandesas en esta situación
*/
template<typename tCoste>
matriz<tCoste>& zuelandia(GrafoP<tCoste> g, std::vector<typename GrafoP<tCoste>::vertice> ciudades,
 matriz<bool>& carreteras, typename GrafoP<tCoste>::vertice capital)
{
    matriz<typename GrafoP<tCoste>::vertice> P; //Para Floyd
    matriz<tCoste> m; //Para Floyd
    typename GrafoP<tCoste>::vertice origen,destino;
    //Recorremos las ciudades prohibidas para eliminarlas
    for(origen=0;origen<ciudades.size();++origen)
    {
        //Se eliminan todos los caminos que salen y entran en cada ciudad prohibida
        for(destino=0;destino<g.numVert();++destino)
        {
            g[origen][destino]=GrafoP<tCoste>::INFINITO;
            g[destino][origen]=GrafoP<tCoste>::INFINITO;
        }
    }
    //Recorremos las carreteras prohibidas para eliminarlas
    for(int i=0;i<carreteras.dimension();++i)
    {
        for(int j=0;j<carreteras.dimension();++j)
        {
            if(carreteras[i][j]==false)
                g[i][j]=GrafoP<tCoste>::INFINITO;
        }
    }
    //Controlamos que todos los caminos pasen por capital
    m=Floyd(g,P); //nos proporciona la matriz de costes con todos los caminos minimos entre todas las ciudades
    for(origen=0;origen<m.dimension();++origen)
    {
        for(destino=0;destino<m.dimension();++destino)
        {
            //Hay que tener en cuenta que en la matriz m los costes son tanto de caminos directos como indirectos
            //por lo que si no hay camino entre cualquier nodo y la capital significa que la capital no forma
            //parte del camino, por lo que hay que eliminar ese camino
            if(m[origen][capital]==GrafoP<tCoste>::INFINITO || m[capital][destino]==GrafoP<tCoste>::INFINITO)
                m[origen][destino]=GrafoP<tCoste>::INFINITO;
            else
            {
                //Sumar coste de origen a capital + capital a destino (Si el origen != destino)
                if(origen != destino)
                   	m[origen][destino] = m[origen][capital] + m[capital][destino];
            }
        }
    }
    //calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades
    //zuelandesas en esta situación.
    return m;
}
#endif
