#include <iostream>
//no es la mejor forma. Mejor usar metodos propios de las clases para no tener que recurrir a funciones externas
class Instrumento
{
    virtual void tocar() const = 0;
};

class Bombo: public Instrumento
{
public:
    void tocar() const override;
private:
    //lo que sea
}

void Bombo::tocar() const
{
    std::cout << "Tocar bombo" << std::endl;
}


class Guitarra : public Instrumento
{
public:
    void tocar() const override;
private:
    //lo que sea
}

void Guitarra::tocar() const
{
    std::cout << "Tocar guitarra" << std::endl;
}

class Clarinete : public Instrumento
{
public:
    void tocar() const override;
private:
    //lo que sea
}

void Clarinete::tocar() const
{
    std::cout << "Tocar clarinete" << std::endl;
}

//ahora simplemente llamamos al metodo del objeto que sea con .tocar()