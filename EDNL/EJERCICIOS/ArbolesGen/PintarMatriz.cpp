#include<iostream>
#include "..\..\EDNL\Arboles\Implementaciones\Agen.hpp"
#include<vector>
//Pintar Matriz a partir de arbol cuaternario sin coordenadas---------------------------

const int N=8;

template <typename T> class matriz {
public:
    matriz() {}
    matriz(size_t n, const T& x = T()): m(n, vector<T>(n, x)) {}
    size_t dimension() const {return m.size();}
    const vector<T>& operator [](size_t i) const {return m[i];}
    vector<T>& operator [](size_t i) {return m[i];}
private:
    vector<vector<T> > m;
};

enum Color{b,n, sin_color};

struct cuadrante
{
    int x_ini, y_ini, x_fin, y_fin;
    cuadrante(int xi,int yi,int xf,int yf):x_ini(xi), x_fin(xf), y_ini(yi), y_fin(yf){}
};

void pintaMatriz_rec(matriz<Color>& matriz, const typename Agen<Color>::nodo n, cuadrante c, const Agen<Color>& a){
    if(a.hijoIzqdo(n) == Agen<Color>::NODO_NULO){ //n Es hoja
        for(int i = c.x_ini ; i <= c.x_fin ; i++)
            for(int j = c.y_ini ; j <= c.y_fin ; j++)
                matriz[i][j] = a.elemento(n);
    }
    else{ //n no es hoja
        if(a.elemento(n)==sin_color)
        {
            unsigned n_cuad=0;
            Agen<Color>::nodo aux = a.hijoIzqdo(n);
            while(aux != Agen<Color>::NODO_NULO){
                switch(n_cuad)
                {
                    case 0:
                        c.x_fin = c.x_fin/2;
                        c.y_fin /=2;
                        break;
                    case 1:
                        c.x_ini=c.x_fin+1;
                        c.x_fin=2*c.x_fin+1;
                        break;
                    case 2:
                        c.y_ini=c.y_fin+1;
                        c.y_fin=2*c.y_fin+1;
                        break;
                    case 3:
                        c.x_ini=0;
                        c.x_fin/=2;
                }
                pintaMatriz_rec(matriz,aux,c,a);
                n_cuad++;
                aux = a.hermDrcho(aux);
            }
        }
    }
}
//Funcion llamada
matriz<Color> pintaMatriz(const Agen<Color>& a){
    matriz<Color> matriz(N); //Tamaño de la matriz
    cuadrante c(0,0, N-1, N-1); //matriz completa 1 solo cuadrante
    pintaMatriz_rec(matriz,a.raiz(),c,a);
    return matriz;
}

int main(){
    Agen<Color> a;
    
    a.insertarRaiz(sin_color);
    a.insertarHijoIzqdo(a.raiz(),b);
    a.insertarHermDrcho(a.hijoIzqdo(a.raiz()),n);
    a.insertarHermDrcho(a.hermDrcho(a.hijoIzqdo(a.raiz())),b);
    a.insertarHermDrcho(a.hermDrcho(a.hermDrcho(a.hijoIzqdo(a.raiz()))),n);
    matriz<Color> tab = pintaMatriz(a);
    
    //Imprimir la matriz
    for(size_t i = 0 ; i < tab.dimension() ; i++){
        for(size_t j = 0 ; j < tab.dimension() ; j++)
            cout << tab[i][j] << " ";
        cout << endl;
    }    
    return 0;
}                