/*
Una matriz dispersa es aquella en la que la mayoria de las posiciones estan vacias o almacenan elementos nulos.
En lugar de almacenar la matriz en un espacio proporcional a su tamaño, se puede obtener una reduccion de espacio
considerable almacenandola en un espacio proporcional al numero de valores no nulos.

Un objeto de la clase MatrizDispersa representa una matriz bidimensional dispersa de valores de tipo double, 
la mayoria de los cuales son 0.

Una matriz de este tipo tiene 5 atributos: 
-Las dos dimensiones
-Tres vectores paralelos para almacenar los valores distintos de 0 y sus coordenadas.
La posicion i-esima de los vectores compone una terna (x,y,v) donde v es el valor almacenado en la fila x , 
columna y de la matriz.

Los elementos se almacenan en los vectores en orden creciente de filas y columnas. Esto es: si tenemos una matriz de 2x3, 
su elemento m[0][1] ira antes que el m[0][2] y este a su vez antes que el m[1][0].

La clase MatrizDispersa debera proporcionar metodos publicos para realizar al menos las siguientes operaciones:

-Crear una matriz nula de dimensiones dadas, por defecto 1x1. No se permitiran conversiones implicitas.
-asignar(): asigna un nuevo valor en una posicion dada.
-valor(): leer el valor de una posicion dada. (observador)
-n_valores(): obtener el numero de valores distintos de 0.

Se incluira asi mismo el siguiente metodo privado:
-buscar(): comprueba y devuelve si una posicion de la matriz contiene un valor distinto de 0 o no. 
Si es distinto de 0, ademas devuelve por parametro de salida el indice de este elemento dentro de los vectores,
en caso contrario devuelve por dicho parametro el indice del siguiente valor distinto de 0 o n_valores() si
todos los que siguen son 0.

a)Complete la siguiente definicion de la clase MatrizDispersa con las declaraciones de los miembros requeridos
segun la especificacion anterior:
*/
class MatrizDispersa
{
public:
	explicit MatrizDispersa(size_t m_=1, size_t n_=1):m(m_), n(n_){}
	void asignar(size_t fila, size_t columna, double valor);
	double valor(size_t fila, size_t columna) const;
	size_t n_valores(){ return fil.size();}
private:
	size_t m,n;
	std::vector<size_t> fil, col;
	std::vector<double> val;
	bool buscar(size_t, size_t,size_t&);
};

/*
b) Definir externamente los metodos declarados anteriormente, excepto buscar(). Donde sea necesario utilice
la funcion assert para controlar las precondiciones, esto es, que las coordenads esten dentro del rango de las 
dimensiones de la matriz. En el constructor no emplee asignaciones, en el metodo valor() use buscar() y
en la funcion asignar() utilice buscar(), insert() y erase() de la clase std::vector
*/
double MatrizDispersa::valor(size_t fila, size_t columna) const
{
	size_t v;
	if(buscar(fila, columna, v))
		return val[v];
	else
		return 0;
}
//NUEVO
void MatrizDispersa::asignar(size_t fila, size_t columna, double valor){
	assert(fila < m && columna < n);
	size_t v;
	if (buscar(fila, columna, v)){
		if(valor == 0){
			val.erase(val.begin()+v);
			col.erase(col.begin()+v);
			fil.erase(fil.begin()+v);
		}
		else{
			val[v] = valor;
		}
	}
	else{
		if (v == n_valores()){
			fil.push_back(fila);
			col.push_back(columna);
			val.push_back(valor);
		}
		else{
			fil.insert(fil.begin()+v-1, fila);
			col.insert(col.begin()+v-1, columna);
			val.insert(val.begin()+v-1, valor);
		}
	}
}
/*
c) Si es necesario implementar el destructor de la clase MatrizDispersa, escribalo. Si no, explique por que 
no hace falta.
*/



0 9 0 8 0 
0 0 4 0 0
1 0 0 0 0
0 0 0 0 0
0 0 2 0 0

5x5

f=5
c=5

fil  0 0 1 2 4
col  1 3 2 0 2
val  9 8 4 1 2
     

int main()
{
	MatrizDispersa m(5,5);
	m.asignar(0,1,9);
	m.asignar(4,2,2);
	m.asignar(0,3,8);