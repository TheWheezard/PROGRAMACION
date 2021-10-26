#include<iostream>

#include <iostream>
using namespace std;

class B{
public:
    void f() { cout << "f() de B" << endl;}
    virtual void g(){cout << "g() de B" << endl;}
    virtual void h() = 0;
    virtual ~B(){}
protected:
    int b;
};

class D1: virtual public B{
public:
    void f(){cout << "f() de D1" << endl;}
    virtual void g(){cout << "g() de D1" << endl;}
    virtual void h(){ cout << "h() de D1" << endl;}//No existia
protected:
    int d1;
};

class D2: virtual public B{
public:
    void f(int i){cout << "f(" <<i<< ") de D2" << endl;}
    virtual void g(int n){cout << "g() de D1" << endl;}
    virtual void h(){ cout << "h() de D2" << endl;}
private:
    int d2;
};

class D3: public D1{
public:
    void g(){cout << " g() de D3" << endl;}
    void h(){cout << "h() de D3" << endl;}
private:
    int d3;
};
//D4 al no tener el metodo g() y derivar de D1 y D2 de manera no virtual y estos tener un método g() cada uno se produce ambiguedad 
class D4: public D1, public D2{
public:
//No existia ningun metodo
    void g(){cout << " g() de D4" << endl;} //overshadow
private:
int d4;
};

void f(B& b){
cout << "f() externa" << endl;
b.f();
b.g();
b.h();
}
/*
int main(){
    B b, *pb;
    D1 d1;
    D2 d2;
    D3 d3;
    D4 d4;  B() D1() D2() D4()

    f(b); 
    f(d1);
    f(d2);
    f(d3);
    f(d4);

    d4.D1::f();
    d4.f(5);
    d4.f(3.7);
    d4.g();
    d4.h();
    pb = new D4;
    pb->f();
    pb->D4::f(3);
    pb->f();

    B() D1() D2() D4()

    pb->g(); B -> D4 -> D1/D2 Sin ambiguedad
    D4 *objeto=new D4;
    objeto->g(7); D4 hacia arriba - si encuentra 2 metodos de igual nombre -> ambiguo
    
    pb->h();

    delete pb;
}

Aquí estará el codigo arreglado, lo primero es que no se pueden declarar objetos de métodos abstractos

*/
int main(){
    B  *pb; //El objeto b lo eliminé porque es una clase abstracta
    D1 d1; //Para arreglar d1,d2,d4 he creado un void h() en D1 y D2
    D2 d2;
    D3 d3;
    D4 d4;

    //f(b); 
    f(d1); 
    f(d2);
    f(d3);
    f(d4);
    
    d4.D1::f(); //No problem especifica el f() que usa
    d4.D2::f(5); //d4.f() es ambiguo , he añadido D2::
    d4.D2::f(3.7);//era ambiguo igual, he añadido D2::
    d4.D1::g();//ambiguo, he añadido D1::
    d4.D2::h();//ambiguo, he añadido D2::
    pb = new D4;
    pb->f();//f() de b
    //pb->D4::f(3);//Error *pb no tiene acceso a D4
    pb->f(); // f() de b
    pb->g(); // g() de b
    pb->h(); // h() de d1 (por que la implementé yo) REVISARRRRRR

    delete pb; //añadiría el destructor virtual en B
}

//2007-2008
 pb->B::f();// pb->f(); Puede ser ambiguo ? pb->B::f(); Ya no es ambiguo /Metodo f() de B
