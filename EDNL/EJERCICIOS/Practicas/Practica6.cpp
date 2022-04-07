#include "..\Implementaciones\Apo.hpp"
#include "..\Implementaciones\Abin.hpp"
#include "..\Implementaciones\Agen.hpp"
#include<iostream>
#include<vector>
#include <cassert>
#include <cstddef>
#include <cmath>

using namespace std;
/*
Dado un árbol binario de enteros donde el valor de cada nodo es menor que el de sus
hijos, implementa un subprograma para eliminar un valor del mismo preservando la
propiedad de orden establecida. Explica razonadamente la elección de la estructura de
datos.
Nota: Se supone que en el árbol no hay elementos repetidos, y que el número de
nodos del mismo no está acotado
*/
//using namespace std;

template <typename T>
void suprimir(Abin <T>& A, int valor){
	typename Abin<T>::nodo n = Abin<T>::NODO_NULO;
	buscar(A, valor, A.raizB(), n);
	if(n == Abin<T>::NODO_NULO){
		std::cout<<"Elemento no encontrado"<<std::endl;
	}
	else{
		if(es_hoja(A, n))
			destruir(A, n);
		else
			reorganizar(A, n);
	}
}

template <typename T>
bool es_hoja (Abin <T>& A, typename Abin<T>:: nodo n){
	return (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO and A.hijoDrchoB(n) == Abin<T>::NODO_NULO);
}

template <typename T>
void reorganizar (Abin<T>& A, typename Abin<T>::nodo n){

	if(es_hoja(A, n))
		destruir(A, n);
	else{
		if(A.hijoIzqdoB(n) == Abin<T>::NODO_NULO){
			A.elemento(n) = A.elemento(A.hijoDrchoB(n));
			reorganizar(A, A.hijoDrchoB(n));
		}
		if(A.hijoDrchoB(n) == Abin<T>::NODO_NULO){
			A.elemento(n) = A.elemento(A.hijoIzqdoB(n));
			reorganizar(A, A.hijoIzqdoB(n));
		}
		if(A.hijoDrchoB(n) != Abin<T>::NODO_NULO && A.hijoIzqdoB(n) != Abin<T>::NODO_NULO){
			if(A.elemento(A.hijoIzqdoB(n)) < A.elemento(A.hijoDrchoB(n))){
				A.elemento(n) = A.elemento(A.hijoIzqdoB(n));
				reorganizar(A, A.hijoIzqdoB(n));
			}
			else{
				A.elemento(n) = A.elemento(A.hijoDrchoB(n));
				reorganizar(A, A.hijoDrchoB(n));
			}
		}
	}
}
/*
              1
      10               4
         15        11    13


  quiero eliminar el 4 -> reorganizar(4)
  no es hoja -> miramos si el hijo izq o el hijo dcho son NODO_NULO -> no lo son
  si 10 < 15 -> en el nodo donde esta el 4 metemos el 10 -> reorganizar(10)
  10 es hoja -> suprimir el 10

              1
      10               9
         15        11    13
*/
//Debe ser hoja
template <typename T>
void destruir (Abin<T>& A, typename Abin<T>::nodo n){
	typename Abin<T>::nodo pare = A.padreB(n);
	if(pare == Abin<T>::NODO_NULO)
		A.eliminarRaizB();
	else{
		if(n == A.hijoIzqdoB(pare))
			A.eliminarHijoIzqdoB(pare);
		if(n == A.hijoDrchoB(pare))
			A.eliminarHijoDrchoB(pare);
	}
}
template <typename T>
void buscar(Abin <T>& A, int valor, typename Abin <T>::nodo r, typename Abin <T>::nodo& n){
	if(r != Abin<T>::NODO_NULO){
		if(A.elemento(r) == valor)
			n = r;
			buscar(A, valor, A.hijoIzqdoB(r), n);
			buscar(A, valor, A.hijoDrchoB(r), n);
	}
}

/*
2.-Un montículo min-max tiene una estructura similar a la de un montículo ordinario
(árbol parcialmente ordenado), pero la ordenación parcial consiste en que los elementos
que se encuentran en un nivel par (0, 2, 4,...) son menores o iguales que sus elementos
descendientes, mientras que los elementos que se encuentran en un nivel impar (1, 3,
5,...) son mayores o iguales que sus descendientes. Esto quiere decir que para cualquier
elemento e de un nivel par se cumple abuelo ≤ e ≤ padre y para cualquier elemento e de
un nivel impar padre ≤ e ≤ abuelo.
Implementa una operación de orden logarítmico para añadir un elemento a un
montículo min-max almacenado en un vector de posiciones relativas.
*/

/*
3.-Implementa una operación de orden logarítmico para eliminar el elemento máximo de
un montículo min-max definido como en el problema anterior.
*/

template <typename T>
class ApoMinMax {
public:
  explicit ApoMinMax(const size_t maxNodos);
  ApoMinMax(const ApoMinMax<T>&);
  ApoMinMax<T>& operator=(const ApoMinMax<T>&);
  
  void insertar(const T&);
  void suprimir();
  const T& cima() const;
  bool vacio() const;
  
  ~ApoMinMax();
  
  template <typename T1>
  friend ostream& operator<<(ostream&, const ApoMinMax<T1>&);
private:
  const size_t maxNodos;
  T* nodos;
  size_t fin;
};

template <typename T>
ostream& operator<<(ostream& salida, const ApoMinMax<T>& a) {
  for(size_t i = 0; i != a.fin; ++i)
    salida << a.nodos[i] << ' ';
  return salida;
}

template <typename T>
ApoMinMax<T>::ApoMinMax(size_t maxNodos) : maxNodos(maxNodos), nodos(new T[maxNodos]), fin(0) {
}

template <typename T>
ApoMinMax<T>::ApoMinMax(const ApoMinMax<T>& a) : maxNodos(a.maxNodos), nodos(new T[maxNodos]), fin(a.fin) {
  for(size_t i = 0; i != fin; ++i)
    nodos[i] = a.nodos[i];
}

template <typename T>
ApoMinMax<T>& ApoMinMax<T>::operator=(const ApoMinMax<T>& a) {
  if(this != &a) {
    if(maxNodos != a.maxNodos) {
      size_t* p = const_cast<size_t*>(&maxNodos);
      *p = a.maxNodos;
      delete[] nodos;
      nodos = new T[maxNodos];
    }
    fin = a.fin;
    for(size_t i = 0; i != fin; ++i)
      nodos[i] = a.nodos[i];
  }
  return *this;
}

bool nivel_par(size_t i) {return int(log(i+1)/log(2.0))%2==0;}

template <typename T>
void ApoMinMax<T>::insertar(const T& e) {
  assert(fin < maxNodos); // ApoMinMax no está lleno
  size_t aux,pos;
  bool final = false;
  aux = pos = fin++;
  while(pos!=0 && !final) { 
    if(nivel_par(pos)) {
      if(e > nodos[(pos-1)/2] || e < nodos[(pos-3)/4])
        nodos[pos] = nodos[(pos-1)/2];
      else
        final = true;
    }else {
      if(pos<3 && e < nodos[(pos-1)/2])
        nodos[pos] = nodos[(pos-1)/2];
      else if(pos>=3 && (e < nodos[(pos-1)/2] || e > nodos[(pos-3)/4]))
        nodos[pos] = nodos[(pos-1)/2];
      else
        final = true;
    }
    pos = (pos-1)/2;
  }
  nodos[pos] = e;
  // Volvemos a hacer el mismo recorrido para reorganizar la rama
  pos = aux;
  /*while(pos!=0 && !final) {
    if(nivel_par(pos)) {
      if(nodos[pos] > nodos[(pos-1)/2] || nodos[pos] < nodos[(pos-3)/4])
        nodos[pos] = nodos[(pos-1)/2];
      else
        final = true;
    }else {
      if(pos<3 && e <= nodos[(pos-1)/2])
        nodos[pos] = nodos[(pos-1)/2];
      else if(pos>=3 && (nodos[pos] < nodos[(pos-1)/2] || nodos[pos] > nodos[(pos-3)/4]))
        nodos[pos] = nodos[(pos-1)/2];
      else
        final = true;
    }
    pos= (pos-1)/2;
  }*/
}

template <typename T>
void ApoMinMax<T>::suprimir() {
  /*assert(fin); // ApoMinMax no está vacío
  size_t pos = 0, pos_min;
  bool encontrado = false;
  T e = nodos[--fin];
  while(2*pos+1 < fin and !encontrado) {
    pos_min = 2*pos+1;
    if(pos_min+1 != fin and nodos[pos_min+1] < nodos[pos_min])
      ++pos_min;
    if(nodos[pos_min] < e) {
      
      
      nodos[pos] = nodos[pos_min];
      pos = pos_min;
    }else
      encontrado = true;
  }
  nodos[pos] = e;*/
}

template <typename T> inline
const T& ApoMinMax<T>::cima() const {assert(fin); return nodos[fin-1];}

template <typename T>
bool ApoMinMax<T>::vacio() const {return !fin;}

template <typename T>
ApoMinMax<T>::~ApoMinMax() {
  delete[] nodos;
  nodos = 0;
}
/*
4.-Implementa un subprograma que dado un árbol ternario (grado 3) devuelva una copia
del mismo. La representación de árboles debe ser una estructura de datos enlazada con
puntero al padre.
*/
//IMPLEMENTACION DE UN ARBOL TERCIARIO

template <typename T> class Ater {
    struct celda; // declaración adelantada privada
public:
    typedef celda* nodo;
    static const nodo NODO_NULO;
    Ater(); // constructor
    void crearRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHijoCentral(nodo n, const T& e);
    void insertarHijoDrcho(nodo n, const T& e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoCentral(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    T elemento(nodo n) const; // acceso a elto, lectura
    T& elemento(nodo n); // acceso a elto, lectura/escritura
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoCentral(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    Ater(const Ater<T>& a); // ctor. de copia
    Ater<T>& operator =(const Ater<T>& a); // asignación de árboles
    ~Ater(); // destructor
private:
    struct celda {
        T elto;
        nodo padre, hizq, hcent, hder;
        celda(const T& e, nodo p = NODO_NULO): elto(e),
        padre(p), hizq(NODO_NULO), hcent(NODO_NULO), hder(NODO_NULO) {}
    };
    nodo r; // nodo raíz del árbol
    void destruirNodos(nodo& n);
    nodo copiar(nodo n);
};

/* Definición del nodo nulo */
template <typename T>
const typename Ater<T>::nodo Ater<T>::NODO_NULO(0);

template <typename T>
inline Ater<T>::Ater() : r(NODO_NULO) {}

template <typename T>
inline void Ater<T>::crearRaiz(const T& e)
{
    assert(r == NODO_NULO); // árbol vacío
    r = new celda(e);
}

template <typename T>
inline void Ater<T>::insertarHijoIzqdo(Ater<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hizq == NODO_NULO);// no existe hijo
    n->hizq = new celda(e, n);
}

template <typename T>
inline void Ater<T>::insertarHijoDrcho(Ater<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hder == NODO_NULO); // no existe hijo
    n->hder = new celda(e, n);
}

template <typename T>
inline void Ater<T>::insertarHijoCentral(Ater<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hcent == NODO_NULO); // no existe hijo
    n->hcent = new celda(e, n);
}

template <typename T>
inline void Ater<T>::eliminarHijoIzqdo(Ater<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hizq != NODO_NULO); // existe hijo izqdo.
    assert(n->hizq->hizq == NODO_NULO && n->hizq->hder == NODO_NULO); // hijo izqdo. // es hoja
    delete(n->hizq);
    n->hizq = NODO_NULO;
}

template <typename T>
inline void Ater<T>::eliminarHijoDrcho(Ater<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hder != NODO_NULO); // existe hijo drcho.
    assert(n->hder->hizq == NODO_NULO && // hijo drcho.
    n->hder->hder == NODO_NULO); // es hoja
    delete(n->hder);
    n->hder = NODO_NULO;
}

template <typename T>
inline void Ater<T>::eliminarHijoCentral(Ater<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hcent != NODO_NULO); // existe hijo drcho.
    assert(n->hcent->hizq == NODO_NULO && // hijo drcho.
    n->hcent->hder == NODO_NULO); // es hoja
    delete(n->hcent);
    n->hcent = NODO_NULO;
}

template <typename T>
inline void Ater<T>::eliminarRaiz()
{
    assert(r != NODO_NULO); // árbol no vacío
    assert(r->hizq == NODO_NULO); // la raíz es hoja
    delete(r);
    r = NODO_NULO;
}

template <typename T>
inline bool Ater<T>::arbolVacio() const
{
    return (r == NODO_NULO);
}

template <typename T>
inline T Ater<T>::elemento(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline T& Ater<T>::elemento(Ater<T>::nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline typename Ater<T>::nodo Ater<T>::raiz() const
{
    return r;
}

template <typename T>
inline typename Ater<T>::nodo Ater<T>::padre(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}

template <typename T>
inline typename Ater<T>::nodo Ater<T>::hijoIzqdo(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}

template <typename T>
inline typename Ater<T>::nodo Ater<T>::hijoDrcho(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hder;
}

template <typename T>
inline typename Ater<T>::nodo Ater<T>::hijoCentral(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hcent;
}

template <typename T>
Ater<T>::Ater(const Ater<T>& a)
{
    r = copiar(a.r);
}

template <typename T>
Ater<T>& Ater<T>::operator =(const Ater<T>& a)
{
    if (this != &a) { // evitar autoasignación
        this->~Ater(); // vaciar el árbol
        r = copiar(a.r);
    }
    return *this;
}

template <typename T>
inline Ater<T>::~Ater()
{
    destruirNodos(r); // vacía el árbol
}

// Métodos privados
// Destruye un nodo y todos sus descendientes
template <typename T>
void Ater<T>::destruirNodos(Ater<T>::nodo& n)
{
    if (n != NODO_NULO) {
        destruirNodos(n->hizq);
        destruirNodos(n->hcent);
        destruirNodos(n->hder);
        delete n;
        n = NODO_NULO;
    }
}

// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Ater<T>::nodo Ater<T>::copiar(Ater<T>::nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO) {
        m = new celda(n->elto); // copiar n
        m->hizq = copiar(n->hizq); // copiar subárbol izqdo.
        if (m->hizq != NODO_NULO)
                m->hizq->padre = m;
        m->hcent = copiar(n->hcent); // copiar subárbol central.
        if (m->hcent != NODO_NULO)
                m->hcent->padre = m;
        m->hder = copiar(n->hder); // copiar subárbol drcho.
        if (m->hder != NODO_NULO)
                m->hder->padre = m;
    }
    return m;
}

//FUNCION QUE COPIA UN ARBOL TERCIARIO

template <typename T> 
Ater<T> copiarAter(Ater<T>& A){
	Ater<T> copia;
	
	if(!A.arbolVacio()){
		copia.crearRaiz(A.elemento(A.raiz()));
		copiarSubarboles(A, A.raiz(), copia, copia.raiz());
	}
	return copia;
}

template <typename T>
void copiarSubarboles(Ater<T>& A, typename Ater<T>::nodo n, Ater<T>& copia, typename Ater<T>::nodo m){
	
	if(n != Ater<T>::NODO_NULO){
		if(A.hijoIzqdo(n) != Ater<T>::NODO_NULO){
			copia.insertarHijoIzqdo(m, A.elemento(A.hijoIzqdo(n)));
			copiarSubarboles(A, A.hijoIzqdo(n), copia, copia.hijoIzqdo(m));
		}
		if(A.hijoCentral(n) != Ater<T>::NODO_NULO){
			copia.insertarHijoCentral(m, A.elemento(A.hijoCentral(n)));
			copiarSubarboles(A, A.hijoCentral(n), copia, copia.hijoCentral(m));
		}
		if(A.hijoDrcho(n) != Ater<T>::NODO_NULO){
			copia.insertarHijoDrcho(m, A.elemento(A.hijoDrcho(n)));
			copiarSubarboles(A, A.hijoDrcho(n), copia, copia.hijoDrcho(m));
		}
	}
}



/*
5.-Un árbol es estrictamente terciario si todos sus nodos son hojas o tienen tres hijos.
Escribe una función que, dado un árbol terciario, nos indique si es o no estrictamente
terciario.
*/
int contarHijos(Ater<char>& a, typename Ater<char>::nodo n)
{
    if(a.hijoIzqdo(n)!=Ater<char>::NODO_NULO && a.hijoCentral(n)!=Ater<char>::NODO_NULO && a.hijoDrcho(n)!=Ater<char>::NODO_NULO)
        return 3;
    else
        return 0;
}
bool esTerciarioEstricto(Ater<char>& a, typename Ater<char>::nodo n, bool estricto)
{
    //bool estricto=true;
    if(n!=Ater<char>::NODO_NULO)
    {
        if(contarHijos(a,n)!=3)
            estricto=false;
        esTerciarioEstricto(a, a.hijoIzqdo(n), estricto);
        esTerciarioEstricto(a, a.hijoCentral(n), estricto);
        esTerciarioEstricto(a, a.hijoDrcho(n), estricto);
    }
    return estricto;
}
/*
6.-Una forma de representar una figura plana en blanco y negro consiste en utilizar un
árbol cuaternario en el que cada nodo o tiene exactamente cuatro hijos, o bien es una
hoja. Un nodo hoja puede ser blanco o negro y un nodo interno no tiene color.
Una figura dibujada dentro de un cuadrado de lado 2 k se representa de la forma
siguiente: Se divide el cuadrado en cuatro cuadrantes y cada uno se representa como un
hijo del nodo raíz. Si un cuadrante está completamente negro corresponde a una hoja
negra; si, por el contrario, el cuadrante está completamente blanco, éste corresponde a
una hoja blanca; y si un cuadrante está parcialmente ocupado por negro y blanco,
entonces corresponde a un nodo interno del árbol y este cuadrante se representa
siguiendo el mismo método subdividiéndolo en otros cuatro cuadrantes. Como ejemplo
se muestra una figura en blanco y negro y su árbol asociado, tomando los cuadrantes en
el sentido de las agujas del reloj a partir del cuadrante superior izquierdo.

Implementa una función que dado un árbol de esta clase, con k+1 niveles,
devuelva la figura asociada, representada como una matriz cuadrada de tamaño 2 k en la
que cada celda representa un punto blanco o negro.
Nota: Por simplificar el problema, se asume que en cada nodo del árbol se
incluyen las coordenadas de la esquina superior izquierda y de la esquina inferior
derecha del cuadrante que representa.
*/

template <typename T> class matriz {
public:
    matriz() {}
    matriz(size_t n, const T& x = T()): m(n, vector<T>(n, x)) {}
    size_t dimension() const {return m.size();}
    const vector<T>& operator [](size_t i) const {return m[i];}
    vector<T>& operator [](size_t i) {return m[i];}
private:
    vector< vector<T> > m;
};

struct color{
        int x1,y1,x2,y2; //Coordenadas (x1,y1) y (x2,y2)
        char col;
};

void tablerorec(matriz<char>& tab, Agen<color>::nodo n, const Agen<color>& a){
    if(a.hijoIzqdo(n) == Agen<color>::NODO_NULO){
        for(int i = a.elemento(n).x1 ; i <= a.elemento(n).x2 ; i++)
            for(int j = a.elemento(n).y1 ; j <= a.elemento(n).y2 ; j++)
                tab[i][j] = a.elemento(n).col;
    }
    else{
        Agen<color>::nodo aux = a.hijoIzqdo(n);
        while(aux != Agen<color>::NODO_NULO){
                tablerorec(tab,aux,a);
                aux = a.hermDrcho(aux);
        }
    }
}
//Funcion llamada
matriz<char> tablero(const Agen<color>& a){
    matriz<char> tab(a.elemento(a.raiz()).x2 + 1); //Tamaño de la matriz
    tablerorec(tab,a.raiz(),a);
    return tab;
}

int main(){
    Agen<color> a;
    color c1 = {0,0,3,3,'*'};
    color c2 = {0,0,1,1,'B'};
    color c3 = {0,2,1,3,'N'};
    color c4 = {2,2,3,3,'B'};
    color c5 = {2,0,3,1,'N'};
    
    a.insertarRaiz(c1);
    a.insertarHijoIzqdo(a.raiz(),c2);
    a.insertarHermDrcho(a.hijoIzqdo(a.raiz()),c3);
    a.insertarHermDrcho(a.hermDrcho(a.hijoIzqdo(a.raiz())),c4);
    a.insertarHermDrcho(a.hermDrcho(a.hermDrcho(a.hijoIzqdo(a.raiz()))),c5);
    matriz<char> tab = tablero(a);
    
    //Imprimir la matriz
    for(size_t i = 0 ; i < tab.dimension() ; i++){
        for(size_t j = 0 ; j < tab.dimension() ; j++)
            cout << tab[i][j] << " ";
        cout << endl;
    }    

    return 0;
}                
