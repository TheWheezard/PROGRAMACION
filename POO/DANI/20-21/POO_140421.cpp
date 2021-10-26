class A{};
class B{
public:
    B(int i, const char* s="", int j=0);
    B& operator=(const B& b);
    B& operator=(const A& a);
    operator A() const;
private:
};

int main()
{
    A a1, a2; //ok constructor pred. de la clase A 
    B b1=0; //ok constructor de conversion de B
    B* p=new B(10); //p->f(); ok
    B p(10); // p.f(); ok
    B* q=new B[10]; //dando valor por defecto a i (ok)
    B b2="examen"; //mal
    A a3(b1); //mal
    a2=a1=*q; //ok
    B b3=a2; //mal
}
const B& f() const 
{
    B* p=new B(10);
    return *p;
}
//-------------------------------------------------------
class Complejo {
public:
  Complejo(double r_=0, double i_=0):r(r_), i(i_){}
  double& real() {return r;} //devuelve un lvalue y un rvalue a la vez
  double& imag() {return i;}
  Complejo& operator-();
private:
double r, i; //parte real, parte imaginaria
};

Complejo operator*(const Complejo& c1, const Complejo& c2)
{
    Complejo resultado;

    return resultado;
}
bool operator==(const Complejo& c1, const Complejo& c2)
{
    return (c1.r==c2.r && c1.i==c2.i);
}
bool operator!=(const Complejo& c1, const Complejo& c2)
{
    return !(c1==c2);
}
Complejo operator+(const Complejo& c1, const Complejo& c2);
Complejo operator-(const Complejo& c);

    Complejo v(1.);
    Complejo w;
    Complejo x(2, -1.2);
    Complejo y (x);
    Complejo z = y;
    Complejo i2 = -1;
    x = -3.5;



    Complejo i, i2, z, y;
    i.real() = 0;
    i.imag() = 1;
    i2 = i * i;
    if(i2==Complejo(-1.0)) std::cout << "OK\n";
    if(i2!=-1.0) std::cout << "MAL\n";
    z = y = Complejo(2.5, 1);
    y.imag() = -y.imag();
    if ( z + y == 2 * z.real()) std::cout << "OK\n";
    else std::cout << "MAL\n";
    if ( z + -y != Complejo(0,2 * z.imag())) std::cout << "MAL\n";
    else std::cout << "OK\n";
