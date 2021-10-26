#include <iostream>

template <class T1, class T2>
class par
{
public:
    par(const T1& x = T1(), const T2& y = T2()) : prime(x), segun(y){}
    T1 primero() const {return prime;}
    T1& primero() {return prime;}
    T2 segundo() const {return segun;}
    T2& segundo() {return segun;}
    virtual void impresionEspecifica(std::ostream& os) const
    { 
        os <<  "Primero: " << prime << std::endl
           <<  "Segundo: " << segun << std::endl;
    }
protected:
    T1 prime;
    T2 segun;
};

template <class T1, class T2>
std::ostream& operator<<(std::ostream& os, const par<T1, T2>& par_)
{
    par_.impresionEspecifica(os);
    return os;
}


class racional : public par<int, unsigned>
{
public:
    racional(int num = 0, unsigned denom = 1) : par<int, unsigned>(num, denom) {};
    void impresionEspecifica(std::ostream& os) const override
    { 
        os <<  "Numerador: " << prime << std::endl
           <<  "Denominador: " << segun << std::endl;
    }
};


racional operator+(const racional& r1, const racional& r2)
{
    racional r3;
    if(r1.segundo() == r2.segundo()) //si tienen el mismo denominador
    {
        r3.primero() = r1.primero() + r2.primero();
        r3.segundo() = r1.segundo(); 
    }
    else
    {
        r3.segundo() = r1.segundo() * r2.segundo();
        r3.primero() = r1.primero() * r2.segundo() + r2.primero() * r1.segundo();
    }
    return r3;
}

class complejo : public par<double, double>
{
public:
    complejo(double real, double imaginario) : par<double, double>(real, imaginario) {};
    void impresionEspecifica(std::ostream& os) const override
    { 
        os <<  "Real: " << prime << std::endl
           <<  "Imaginario: " << segun << std::endl;
    }
    complejo& operator+=(const complejo& com)
    {
        prime += com.primero();
        segun += com.segundo();
        return *this;
    }
};


int main()
{
    par<int, int> par(1, 2);
    std::cout << par;
    std::cout << "=================================\n";
    racional r(1, 2), r2(2, 3);
    std::cout << r+r2;
    std::cout << "=================================\n";
    complejo com(1, 3), com2(2, 4);
    std::cout << com;
    com += com2;
    std::cout << "=================================\n";
    std::cout << com;

}