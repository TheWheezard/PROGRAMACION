
class V{ //abstracta
public:
	void f() {cout << "f() de v" << endl;}
	virtual void g()=0;
protected:
	int v_;
};

class W: virtual public V{
public:
	void f(int i){cout<<"f("<<i<<") de W"<<endl;}
	void g(){cout<<"g() de W"<<endl;}
protected:
	int w_;
};

class X: virtual public V{ //abstracta
public:
	void f() {cout<<"f() de X"<<endl;}
	void h() {cout<<"h() de X"<<endl;}
protected:
	int x_;
};
class Z: public W, public X {
int z_;
public:
	void g(){}
};

//En este codigo determine si existe algun error y si existe diga cual es la primera linea que da error
Z z; //ok
V* pv; //ok
pv=&z; //ok
pv->f(); //ok V::f()



/*
    V() 
  |	    |
  |     |
  |     |
 W()   X()
   \    |
    \   |
     \  |
      Z()         

*/
//CLASES
class V{ //abstracta
public:
	void f() {cout << "f() de v" << endl;}
	virtual void g()=0;
	virtual void g(int i){cout<<"g("<<i<<") de V"<<endl;}
	virtual void h(){cout<<"h() de V"<<endl;}
	virtual ~V(){}
protected:
	int v_;
};

class W: virtual public V{
public:
	void f(int i){cout<<"f("<<i<<") de W"<<endl;}
	void g(){cout<<"g() de W"<<endl;}
protected:
	int w_;
};

class X: virtual public V{ //abstracta
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
public:
	void g(){} //overshadow
};


/*
     V()  <---------- v 
  |	     |
  |      |
  |      |
 W()    X()
  | \    |
  |  \   |
  |   \  |
 Y()    Z()         

*/

//FUNCIONES
void f(V& v){
	v.f();
	v.g();
	v.h();
}

V() <------v
 |
 |
 |
W()

int main(){
	V v; //error porque V es abstracta
	V *pV; //ok
	W w; //ok V()<----W()
	X x; //error
	Y y; //ok
	Z z; //ok
	f(v); //error
	f(w); // V::f() W::g() V::h()
	f(x); // error
	f(z); // V::f() Z::g() V::h()
	z.X::f(); // X::f()
	z.f(); //ambiguo
	z.f(5); //ambiguo
	z.g(3); //error
	z.h(); // X::h()
	pV = new Z; // ok
	pV->f(); // V::f()
	pV->X::f(); //mal
	pV->g(); // Z::g()
	pV->g(2.5); // V::g(int)
	pV->h(); //V::f()
	delete pV; 
	return 0;
}


//---------------------------------------------------

class F{};
class C{};

class A{};

class B:public A{
private:
	F f;
	C c;
};

B b; //A() F() C() B()
	  // ~B() ~C() ~F() ~Ã()