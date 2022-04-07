#include "Particion.hpp"
#include "Kruskal.hpp"
#include "GrafoP.hpp"
#include "matriz.hpp"
#include "Floyd.hpp"
#include <math.h>

//Funciones de ayuda
struct tipo_coordenada
{
    double x,y;
    tipo_coordenada(double x_=0.0, double y_=0.0):x(x_), y(y_){}
};
double distancia(tipo_coordenada& c1, tipo_coordenada& c2) //Distancia euclidea entre 2 puntos
{
    return sqrt(pow(c2.x-c1.x,2)+pow(c2.y-c1.y,2));
}
bool esBosque(Particion& p, size_t tam) //Si una particion es bosque es que tiene mas de un arbol
{
    bool es=false;
    for(size_t i=0;i<tam-1 && !es;++i)
    {
        for(size_t j=i+1;j<tam && !es;++j)
        {
            if(p.encontrar(i)!=p.encontrar(j))
                es=true;
        }
    }
    return es;
}
template <typename tCoste> //Invertir todos los costes de un grafo cambiando su signo
void invertir (GrafoP<tCoste>& grafo){
	for(typename GrafoP<tCoste>::vertice i = 0 ; i < grafo.numVert() ; i++)
		for(typename GrafoP<tCoste>::vertice j = 0 ; j < grafo.numVert() ; j++)
			if(grafo[i][j] != GrafoP<tCoste>::INFINITO)
				grafo[i][j] *= -1;
}
/*
El archipiélago de Tombuctú, está formado por un número indeterminado de islas,
cada una de las cuales tiene, a su vez, un número indeterminado de ciudades. En
cambio, sí es conocido el número total de ciudades de Tombuctú (podemos llamarlo n,
por ejemplo).
Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
las ciudades de la isla. Se dispone de las coordenadas cartesianas (x, y) de todas y cada
una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en
el que se indica si existe carretera directa entre cualesquiera dos ciudades del
archipiélago. El objetivo de nuestro problema es encontrar qué ciudades de Tombuctú
pertenecen a cada una de las islas del mismo y cuál es el coste mínimo de viajar entre
cualesquiera dos ciudades de una misma isla de Tombuctú.
Así pues, dados los siguientes datos:
• Lista de ciudades de Tombuctú representada cada una de ellas por sus
coordenadas cartesianas,
• y matriz de adyacencia de Tombuctú, que indica las carreteras existentes en
dicho archipiélago,

implementa un subprograma que calcule y devuelva la distribución en islas de las
ciudades de Tombuctú, así como el coste mínimo de viajar entre cualesquiera dos
ciudades de una misma isla del archipiélago.
*/

//La funcion devuelve los costes minimos, y una particion por referencia con la distribucion de las ciudades entre las islas
matriz<double> tombuctu(Grafo& G, std::vector<tipo_coordenada> ciudades, Particion& P)
{
    //Debemos recorrer la matriz de adyacencia (G). Para cada par de vertices unidos, se unen en la particion
    GrafoP<double> distancias(G.numVert());
    for(size_t i=0;i<G.numVert();++i)
    {
        for(size_t j=0;j<G.numVert();++j)
        {
            if(G[i][j] || G[j][i])
            {
                //Rellenamos la particion
                if(P.encontrar(i)!=P.encontrar(j)) //Si los vertices i,j pertenecen a subarboles diferentes, se unen
                    P.unir(i,j);
                //Rellenamos el grafo ponderado con las distancias entra ciudades
                if(G[i][j])
                    distancias[i][j]=distancia(ciudades[i], ciudades[j]);
                if(G[j][i])
                    distancias[j][i]=distancia(ciudades[j], ciudades[i]);
            }
        }
    }
    //Tengo en la particion los conjuntos de ciudades y un grafo de costes con las distancias entre las ciudades conectadas
    matriz<typename GrafoP<double>::vertice> Caminos;
    matriz<double> costes=Floyd(distancias, Caminos); //Coste minimo para viajar entre cualesquiera dos ciudades del archipielago
    return costes;
}

/*
El archipiélago de Tombuctú está formado por un número desconocido de islas, cada
una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales tienen
en común que todas y cada una de ellas dispone de un aeropuerto.
Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la
opción de comunicación más económica de implantar será el avión.

Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las
ciudades del archipiélago. 

Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa 
entre cualesquiera dos ciudades del archipiélago. 

El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para
poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:

1) Se implantará una y sólo una línea aérea entre cada par de islas.
2) La línea aérea escogida entre cada par de islas será la más corta entre todas
las posibles.

Así pues, dados los siguientes datos:
• Lista de ciudades de Tombuctú representada cada una de ellas por sus
coordenadas cartesianas
• Matriz de adyacencia de Tombuctú que indica las carreteras existentes en
dicho archipiélago,

implementa un subprograma que calcule y devuelva las líneas aéreas necesarias para
comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente
expuestos.
*/
template<typename tCoste>
void tombuctu2(Grafo& g, std::vector<tipo_coordenada> ciudades)
{
    Particion p(g.numVert());
    typename Grafo::vertice origen, destino;
    tCoste costeMin=GrafoP<tCoste>::INFINITO;

    //Rellenamos la particion para agrupar las ciudades en islas
    for(size_t i=0;i<g.numVert();++i)
    {
        for(size_t j=0;j<g.numVert();++j)
        {
            if(g[i][j] || g[j][i])
            {
                if(p.encontrar(i)!=p.encontrar(j)) //Si i,j no pertenecen al mismo subarbol
                    p.unir(i,j);
            }
        }
    }
    //-----------------------------------------
    while(esBosque(p,g.numVert())) //Mientras haya islas desconectadas (Si una particion es un bosque es que tiene mas
        //de un subarbol, por lo que aun existen nodos no conectados entre si)
    {
        for(size_t i=0;i<g.numVert();++i)
        {
            for(size_t j=0;j<g.numVert();++j)
            {
                if(p.encontrar(i)!=p.encontrar(j)) //Si i,j no pertenecen al mismo subarbol o subconjunto
                {
                    if(costeMin>distancia(ciudades[i], ciudades[j])) //Calcula el menor coste posible para unir ciudades de 
                                                                    // distintas islas
                    {
                        costeMin=distancia(ciudades[i], ciudades[j]);
                        origen=i;
                        destino=j;
                    }
                }
            }
        }
        g[origen][destino]=true;
        g[destino][origen]=true;
        p.unir(origen,destino);
        std::cout << "Linea aerea entre " << origen << " y " << destino << std::endl;
    } //Fin de mientras
}

/* 3.-
Implementa un subprograma para encontrar un árbol de extensión máximo. ¿Es más
difícil que encontrar un árbol de extensión mínimo?
*/
template <typename tCoste>
GrafoP<tCoste> arbol_maximo (GrafoP<tCoste> grafo){
	invertir(grafo);
	GrafoP<tCoste> maximo = Kruskal (grafo);
	invertir(maximo);
	return maximo;
}
/* 4.-
La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del
valle del Jerte (Cáceres). Calcula qué canales y de qué longitud deben construirse
partiendo del grafo con las distancias entre las ciudades y asumiendo las siguientes
premisas:
− el coste de abrir cada nuevo canal es casi prohibitivo, luego la solución final
debe tener un número mínimo de canales. (Kruskal/Prim)
− el Ministerio de Fomento nos subvenciona por Km. de canal, luego los canales
deben ser de la longitud máxima posible. (Grafo inverso)
*/
template<typename tCoste>
GrafoP<tCoste> canales(GrafoP<tCoste> g)
{
    invertir(g);
    GrafoP<tCoste> Grafo_Canales=Kruskal(g);
    invertir(Grafo_Canales);
    return Grafo_Canales;
}
/* 5.-
La nueva compañía de telefonía RETEUNI3 tiene que conectar entre sí, con fibra
óptica, todas y cada una de las ciudades del país. Partiendo del grafo que representa las
distancias entre todas las ciudades del mismo, implementad un subprograma que
calcule la longitud mínima de fibra óptica necesaria para realizar dicha conexión.
*/
double fibra(GrafoP<double>& g)
{
    double coste=GrafoP<double>::INFINITO;
    GrafoP<double> costes=Kruskal(g); //Calcula el grafo con todos los nodos conectados al menor coste (minimas aristas posibles)
    for(size_t i=0;i<g.numVert();++i)
    {
        for(size_t j=0;j<g.numVert();++j)
        {
            if(costes[i][j]!=GrafoP<double>::INFINITO) //Recorre el grafo proporcionado por Kruskal y calcula la suma de todos 
                                                        // los costes
                coste+=costes[i][j];
        }
    }
    return coste;
}
/* 6.-
La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del
valle del Jerte (Cáceres), teniendo en cuenta las siguientes premisas:
− El coste de abrir cada nuevo canal es casi prohibitivo, luego la solución final debe
tener un número mínimo de canales. (Kruskal/Prim)
− El Ministerio de Fomento nos subvenciona por m3/sg. de caudal, luego el
conjunto de los canales debe admitir el mayor caudal posible; pero por otra parte,
el coste de abrir cada canal es proporcional a su longitud, por lo que el conjunto de
los canales también debería medir lo menos posible. Así pues, la solución óptima
debería combinar adecuadamente ambos factores.

Dada la matriz de distancias entre las diferentes ciudades del valle del Jerte, otra
matriz con los diferentes caudales máximos admisibles entre estas ciudades teniendo en
cuenta su orografía, la subvención que nos da Fomento por m3/sg. de caudal y el coste
por km. de canal, escribid un subprograma que calcule qué canales y de qué longitud y
caudal deben construirse para minimizar el coste total de la red de canales.
*/
template<typename tCoste>
GrafoP<tCoste> subvencion(GrafoP<tCoste> distancias, GrafoP<tCoste> caudales, double subvencion, double costeKm, GrafoP<tCoste>& caudal)
{
    //Coste de menor longitud posible
    for(size_t i=0;i<distancias.numVert();++i)
    {
        for(size_t j=0;j<distancias.numVert();++j)
        {
            distancias[i][j]*=costeKm;
        }
    }
    //Subvencion del Mayor caudal posible
    for(size_t i=0;i<caudales.numVert();++i)
    {
        for(size_t j=0;j<caudales.numVert();++j)
        {
            caudales[i][j]*=subvencion;
        }
    }
    //Nos tenemos que quedar con el menor coste y la mayor subvencion. Creamos un nuevo grafo con las diferencias
    //entre el coste y las ganancias
    GrafoP<tCoste> costes_minimos(distancias.numVert());
    for(size_t i=0;i<costes_minimos.numVert();++i)
    {
        for(size_t j=0;j<costes_minimos.numVert();++j)
        {
            costes_minimos[i][j]=distancias[i][j]-caudales[i][j];
        }
    }
    GrafoP<tCoste> coste_Final=Kruskal(costes_minimos);

    GrafoP<tCoste> distancia(distancias.numVert()); //Para devolver las distancias

    //Rellenamos la matriz de caudal y de distancia
    for(size_t i=0;i<distancias.numVert();++i)
    {
        for(size_t j=0;j<distancias.numVert();++j)
        {
            if(coste_Final[i][j]!=GrafoP<tCoste>::INFINITO)
            {
                caudal[i][j]=caudales[i][j];
                distancia[i][j]=distancias[i][j];
            }
        }
    }
    return distancia;
}

/* 7.-
El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas,
Fobos y Deimos, que tienen n1 y n2 ciudades, respectivamente, de las cuales c1 y c2 son
costeras. Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las
ciudades del archipiélago. El huracán Isadore acaba de devastar el archipiélago, con lo
que todas las carreteras y puentes construidos en su día han desaparecido. En esta
terrible situación se pide ayuda a la ONU, que acepta reconstruir el archipiélago (es
decir volver a comunicar todas las ciudades del archipiélago) siempre que se haga al
mínimo coste.
De cara a poder comparar costes de posibles reconstrucciones se asume lo
siguiente:
1. El coste de construir cualquier carretera o cualquier puente es proporcional a su
longitud (distancia euclídea entre las poblaciones de inicio y fin de la carretera o
del puente).
2. Cualquier puente que se construya siempre será más caro que cualquier carretera
que se construya.
De cara a poder calcular los costes de viajar entre cualquier ciudad del
archipiélago se considerará lo siguiente:
1. El coste directo de viajar, es decir de utilización de una carretera o de un puente,
coincidirá con su longitud (distancia euclídea entre las poblaciones origen y
destino de la carretera o del puente).
En estas condiciones, implementa un subprograma que calcule el coste mínimo
de viajar entre dos ciudades de Grecoland, origen y destino, después de haberse
reconstruido el archipiélago, dados los siguientes datos:
1. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
2. Lista de ciudades de Deimos representadas mediante sus coordenadas
cartesianas.
3. Lista de ciudades costeras de Fobos.
4. Lista de ciudades costeras de Deimos.
5. Ciudad origen del viaje.
6. Ciudad destino del viaje.
*/
template<typename tCoste>
tCoste Grecoland_Huracan(std::vector<tipo_coordenada> ciudades_Fobos, std::vector<tipo_coordenada> ciudades_Deimos,
std::vector<typename GrafoP<tCoste>::vertice> costeras_Fobos, std::vector<typename GrafoP<tCoste>::vertice> costeras_Deimos,
 typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino)
 {
    tCoste puente=GrafoP<tCoste>::INFINITO;
    typename GrafoP<tCoste>::vertice c1, c2; //Ciudades que enlaza el puente

    //Creamos los grafos de fobos y deimos
    GrafoP<tCoste> gFobos(ciudades_Fobos.size());
    GrafoP<tCoste> gDeimos(ciudades_Deimos.size());
    for(size_t i=0;i<gFobos.numVert();++i)
    {
        for(size_t j=0;j<gFobos.numVert();++j)
        {
            gFobos[i][j]=distancia(ciudades_Fobos[i], ciudades_Fobos[j]);
        }
    }
    for(size_t i=0;i<gDeimos.numVert();++i)
    {
        for(size_t j=0;j<gDeimos.numVert();++j)
        {
            gDeimos[i][j]=distancia(ciudades_Deimos[i], ciudades_Deimos[j]);
        }
    }
    //Creamos los caminos minimos que unen las ciudades
    GrafoP<tCoste> Fobos=Kruskal(gFobos);
    GrafoP<tCoste> Deimos=Kruskal(Deimos);

    //Calculamos cual es el puente mas barato
    for(size_t i=0;i<costeras_Fobos.size();++i)
    {
        for(size_t j=0;j<costeras_Deimos.size();++j)
        {
            if(distancia(ciudades_Fobos[i],ciudades_Deimos[j])<puente)
            {
                puente=distancia(ciudades_Fobos[i],ciudades_Deimos[j]);
                c1=i;
                c2=j;
            }
        }
    }
    //Creamos el supergrafo de las dos islas
    GrafoP<tCoste> Islas(Fobos.numVert()+Deimos.numVert());
    Islas=SuperGrafo(Fobos, Deimos);
    //Colocamos el puente mas pequeño/barato
    Islas[c1][c2+Fobos.numVert()]=puente;
    Islas[c2+Fobos.numVert()][c1]=puente;

    std::vector<typename GrafoP<tCoste>::vertice> caminos;
    std::vector<tCoste> costes=Dijkstra(Islas, origen, caminos);

    return costes[destino];
 }
/*
El archipiélago de las Huríes acaba de ser devastado por un maremoto de
dimensiones desconocidas hasta la fecha. La primera consecuencia ha sido que todos y
cada uno de los puentes que unían las diferentes ciudades de las tres islas han sido
destruidos. En misión de urgencia las Naciones Unidas han decidido construir el
mínimo número de puentes que permitan unir las tres islas. Asumiendo que el coste de
construcción de los puentes implicados los pagará la ONU, por lo que se considera
irrelevante, nuestro problema es decidir qué puentes deben construirse. Las tres islas de
las Huríes tienen respectivamente N1, N2 y N3 ciudades, de las cuales C1, C2 y C3 son
costeras. Nuestro problema es elegir los puentes a construir entre todos los posibles. Por
tanto, escogeremos aquellos puentes que minimicen el coste global de viajar entre todas
las ciudades de las tres islas, teniendo en cuenta las siguientes premisas:
1. Se asume que el coste viajar entre las ciudades que unan los puentes es 0.
2. La ONU subvencionará únicamente el número mínimo de puentes necesario
para comunicar las tres islas.
3. Para poder plantearse las mejoras en el transporte que implica la construcción de
un puente frente a cualquier otro, se asume que se realizarán exactamente el
mismo número de viajes entre cualesquiera ciudades del archipiélago. Dicho de
otra forma, todos los posibles trayectos a realizar dentro del archipiélago son
igual de importantes.
Dadas las matrices de costes directos de las tres islas y las listas de ciudades
costeras del archipiélago, implementad una función que calcule los puentes a construir
en las condiciones anteriormente descritas.
*/
template<typename tCoste>
void Huries(GrafoP<tCoste>& Isla1, GrafoP<tCoste>& Isla2,GrafoP<tCoste>& Isla3, std::vector<typename GrafoP<tCoste>::vertice> C1,
std::vector<typename GrafoP<tCoste>::vertice> C2,std::vector<typename GrafoP<tCoste>::vertice> C3)
{

    tCoste costeMin=GrafoP<tCoste>::INFINITO, costeTotal=0;
    matriz<typename GrafoP<tCoste>::vertice> caminos; //Para Floyd
    //Creamos un superGrafo con los 3 grafos
    GrafoP<tCoste> Archipielago(Isla1.numVert()+Isla2.numVert()+Isla3.numVert());
    typename GrafoP<tCoste>::vertice origen_puente1, destino_puente1, origen_puente2, destino_puente2;

    //El minimo numero de puentes para comunicar 3 islas es 2
    //Para colocar los puentes hay tres posibilidades:

    //Entre Isla1-Isla2 y Isla1-Isla3
    for(size_t puente1_i=0;puente1_i<C1.size();++puente1_i)
    {
        for(size_t puente1_j=0;puente1_j<C2.size();++puente1_j)
        {
            Archipielago[C1[puente1_i]][C2[puente1_j]+Isla1.numVert()]=0;
            Archipielago[C2[puente1_j]+Isla1.numVert()][C1[puente1_i]]=0;

            for(size_t puente2_i=0;puente2_i<C1.size();++puente2_i)
            {
                for(size_t puente2_j=0;puente2_j<C3.size();++puente2_j)
                {
                    Archipielago[C1[puente2_i]][C3[puente2_j]+Isla1.numVert()+Isla2.numVert()]=0;
                    Archipielago[C3[puente2_j]+Isla1.numVert()+Isla2.numVert()][C1[puente2_j]]=0;

                    //Comprobar costes
                    matriz<tCoste> costes=Floyd(Archipielago, caminos);
                    costeTotal=CalcularCoste(costes);
                    if(costeTotal<costeMin)
                    {
                        costeTotal=costeMin;
                        origen_puente1=C1[puente1_i];
                        destino_puente1=C2[puente1_j];
                        origen_puente2=C1[puente2_i];
                        destino_puente2=C3[puente2_j];
                    }

                }
            }
        }
    }
    //Entre Isla1-Isla2 y Isla2-Isla3
    for(size_t puente1_i=0;puente1_i<C1.size();++puente1_i)
    {
        for(size_t puente1_j=0;puente1_j<C2.size();++puente1_j)
        {
            Archipielago[C1[puente1_i]][C2[puente1_j]+Isla1.numVert()]=0;
            Archipielago[C2[puente1_j]+Isla1.numVert()][C1[puente1_i]]=0;

            for(size_t puente2_i=0;puente2_i<C2.size();++puente2_i)
            {
                for(size_t puente2_j=0;puente2_j<C3.size();++puente2_j)
                {
                    Archipielago[C2[puente2_i]+Isla1.numVert()][C3[puente2_j]+Isla1.numVert()+Isla2.numVert()]=0;
                    Archipielago[C3[puente2_j]+Isla1.numVert()+Isla2.numVert()][C2[puente2_j]+Isla1.numVert()]=0;

                    //Comprobar costes
                    matriz<tCoste> costes=Floyd(Archipielago, caminos);
                    costeTotal=CalcularCoste(costes);
                    if(costeTotal<costeMin)
                    {
                        costeTotal=costeMin;
                        origen_puente1=C1[puente1_i];
                        destino_puente1=C2[puente1_j];
                        origen_puente2=C2[puente2_i];
                        destino_puente2=C3[puente2_j];
                    }
                }
            }
        }
    }
    //Entre Isla1-Isla3 y Isla2-Isla3
    for(size_t puente1_i=0;puente1_i<C1.size();++puente1_i)
    {
        for(size_t puente1_j=0;puente1_j<C3.size();++puente1_j)
        {
            Archipielago[C1[puente1_i]][C3[puente1_j]+Isla1.numVert()+Isla2.numVert()]=0;
            Archipielago[C3[puente1_j]+Isla1.numVert()+Isla2.numVert()][C1[puente1_i]]=0;

            for(size_t puente2_i=0;puente2_i<C2.size();++puente2_i)
            {
                for(size_t puente2_j=0;puente2_j<C3.size();++puente2_j)
                {
                    Archipielago[C2[puente2_i]+Isla1.numVert()][C3[puente2_j]+Isla1.numVert()+Isla2.numVert()]=0;
                    Archipielago[C3[puente2_j]+Isla1.numVert()+Isla2.numVert()][C2[puente2_j]+Isla1.numVert()]=0;

                    //Comprobar costes
                    matriz<tCoste> costes=Floyd(Archipielago, caminos);
                    costeTotal=CalcularCoste(costes);
                    if(costeTotal<costeMin)
                    {
                        costeTotal=costeMin;
                        origen_puente1=C1[puente1_i];
                        destino_puente1=C3[puente1_j];
                        origen_puente2=C2[puente2_i];
                        destino_puente2=C3[puente2_j];
                    }
                }
            }
        }
    }
    std::cout << "Puente 1 une " << origen_puente1 << " con " << destino_puente1 << std::endl;
    std::cout << "Puente 2 une " << origen_puente2 << " con " << destino_puente2 << std::endl;
}
