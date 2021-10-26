#include<iostream>
using namespace std;
//CLASES
class V{
public:
	void f() {cout << "f() de v" << endl;}
	virtual void g()=0;
	virtual void g(int i){cout<<"g("<<i<<") de V"<<endl;}
	virtual void h(){cout<<"h() de V"<<endl;}
    void j(){}
protected:
	int v_;
};

class W:  public V{
public:
	void f(int i){cout<<"f("<<i<<") de W"<<endl;}
	void g(){cout<<"g() de W"<<endl;}
protected:
	int w_;
};

class X:  public V{
public:
	void f() {cout<<"f() de X"<<endl;}
	void h() {cout<<"h() de X"<<endl;}
protected:
	int x_;
};

class Y: public W{
public:
	void g() {cout<<"g() de Y"<<endl;}
	void h() {cout<<"h() de Y"<<endl;}
private:
	int y_;
};

class Z: public W, public X {
	int z_;
};

//FUNCIONES
void f(V& v){
	cout<<"f() externa"<<endl;
	v.f();
	v.g();
	v.h();
}

void prueba()
{
    V v; 
	V *pV;
	W w;
	X x; 
	Y y;
	Z z;
	f(v); 
	f(w); 
	f(x); 
	f(z);
	z.x::f(); 
	z.f(); 
	z.f(5); 
	z.g(3); 
	z.h();
	pV = new Z;
	pV->f();
	pV->x::f(); 
	pV->g();
	pV->g(2.5);
	pV->h();
	delete pV;
	return 0;
}
/*
int main(){
    
	V v; 
	V *pV;
	W w;
	X x; 
	Y y;
	Z z;
	f(v); 
	f(w); 
	f(x); 
	f(z);
	z.x::f(); 
	z.f(); 
	z.f(5); 
	z.g(3); 
	z.h();
	pV = new Z;
	pV->f();
	pV->x::f(); 
	pV->g();
	pV->g(2.5);
	pV->h();
	delete pV;
	return 0;
}


Salida del programa tal cual está codificado aqui:
f() externa
f() de v
g() de W
h() de V
f() externa
f() de v
g() de Y
h() de Y
f() externa
f() de v
g() de W
h() de X
h() de X
f() de v
g() de W
g(2) de V
h() de X
*/
