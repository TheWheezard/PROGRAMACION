#include "..\..\Implementaciones\Abin.hpp"
/*
Tarea 1
Especificar el TAD proposición con las siguientes operaciones:
Crear una proposición con un único símbolo del conjunto A = {s1, s2, ..., sn}, con n constante.
Crear una nueva proposición a partir de otra previamente creada y una conectiva ¬ (NO).
Crear una nueva proposición a partir de otras (dos) previamente creadas y una conectiva que puede ser ∧ (Y) o ∨ (O).
Calcular el valor de verdad de una proposición, a partir de una valoración del conjunto de símbolos A = {s1, s2, ..., sn}.

Tarea 2
Implementación del TAD proposición (parte I)
Definir la representación de los siguientes tipos de datos: (2 puntos)
símbolo (int)
conectiva (enum)
valoración de un conjunto de n símbolos. (vector<bool>)
proposición TAD
Implementar las operaciones del TAD proposición, salvo la de cálculo del valor de verdad.
p^q^r
*/
/* Si hizd(n) && hder(n) son nulos, n es hoja --> devuelve T/F */
/* Si hizd(n) || hder(n) son nulos, n no es hoja --> devuelve ¬hizd(n) || ¬hder(n) */
/* Si hizd(n) && hder(n) NO son nulos, n NO es hoja --> devuelve hizd(n) |/& hder(n) */


class Proposicion{
    struct tnodo;
public:
    typedef int simbolo;
    static int SIMBOLO_NULO;
    typedef tnodo nodo;
    enum tConectiva {NOT, AND, OR, VACIO};
    Proposicion(simbolo s){
        p.insertarRaiz(nodo(VACIO, s));
    }
    Proposicion(Proposicion& p1){
        this->p.insertarRaiz(nodo(NOT, SIMBOLO_NULO));
        if (!p1.p.arbolVacio()){
            this->p.insertarHijoIzqdo(this->p.raiz(), p1.p.elemento(p1.p.raiz()));
            copiar(this->p, this->p.hijoIzqdo(this->p.raiz()), this->p, this->p.raiz());
        }
    }
    Proposicion(Proposicion& p1, Proposicion& p2, tConectiva conector){
        this->p.insertarRaiz(nodo(conector, SIMBOLO_NULO));
        if(!p1.p.arbolVacio()){
            this->p.insertarHijoIzqdo(this->p.raiz(), p1.p.elemento(p1.p.raiz()));
            copiar(this->p, this->p.hijoIzqdo(this->p.raiz()), this->p, this->p.raiz());
        }
        if(!p2.p.arbolVacio()){
            this->p.insertarHijoDrcho(this->p.raiz(), p2.p.elemento(p2.p.raiz()));
            copiar(this->p, this->p.hijoDrcho(this->p.raiz()), this->p, this->p.raiz());
        }
    }

    int evaluar(Abin<nodo>::nodo n){
        if (!p.arbolVacio() && p.elemento(n).conector != VACIO)
        {
            if (p.hijoIzqdo(n) != Abin<nodo>::NODO_NULO && p.hijoDrcho(n) != Abin<nodo>::NODO_NULO){
                if (p.elemento(n).conector == AND) return evaluar(p.hijoIzqdo(n)) && evaluar(p.hijoDrcho(n));
                else if (p.elemento(n).conector == OR) return evaluar(p.hijoIzqdo(n)) || evaluar(p.hijoDrcho(n));
            }
            else if (p.hijoIzqdo(n) != Abin<nodo>::NODO_NULO && p.hijoDrcho(n) == Abin<nodo>::NODO_NULO){
                return !evaluar(p.hijoIzqdo(n));
            }
            else if (p.hijoIzqdo(n) == Abin<nodo>::NODO_NULO && p.hijoDrcho(n) != Abin<nodo>::NODO_NULO){
                return !evaluar(p.hijoDrcho(n));
            }
            else if (p.hijoIzqdo(n) == Abin<nodo>::NODO_NULO && p.hijoDrcho(n) == Abin<nodo>::NODO_NULO){
                return p.elemento(n).s;
            }
        }
    }
private:
    struct tnodo{
        tConectiva conector;
        simbolo s; //0: false, 1: true, -1: nulo
        tnodo(tConectiva conec = VACIO, simbolo op = SIMBOLO_NULO): conector(conec), s(op){};
    };
    Abin<tnodo> p;

    void copiar(Abin<nodo>& s, Abin<nodo>::nodo sn, Abin<nodo>& p, Abin<nodo>::nodo pn)
    {
        if(pn!=Abin<nodo>::NODO_NULO)
        {
            if(p.hijoIzqdo(pn)!=Abin<nodo>::NODO_NULO)
                s.insertarHijoIzqdo(sn, p.elemento(p.hijoIzqdo(pn)));
            if(p.hijoDrcho(pn)!=Abin<nodo>::NODO_NULO)
                s.insertarHijoDrcho(sn, p.elemento(p.hijoDrcho(pn)));
            copiar(s, s.hijoIzqdo(sn), p, p.hijoIzqdo(pn));
            copiar(s, s.hijoDrcho(sn), p, p.hijoDrcho(pn));
        }
    }
};
static int SIMBOLO_NULO = -1;