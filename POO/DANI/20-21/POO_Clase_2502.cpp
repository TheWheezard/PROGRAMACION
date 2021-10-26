class coche
{
public: //metodos
	void arrancar();
	void acelerar();
	void frenar();
	void estacionar();
	void asignar_puertas(size_t numero)
	{
		if(numero>=3 && numero<=5)
			numero_puertas=numero;
	}
private: //atributos
	size_t numero_puertas;
	int bastidor;
};

class A
{
public:
	//constructores
	A(){} //Constructor por defecto
	explicit A(int a_=0, int b_=0):a(a_),b(b_){} //Constructor (parametrizado)
	A(int a_):a(a_){} //Constructor de conversion (parametrizado)

	A(int n_):n(n_),p(new int[n]) //Constructor de conversion (parametrizado)
	{
		for(int i=0;i<n;++i)
			p[i]=0;
	}
	A(const A& x) //Constructor de copia
	{
		this->a=x.a;
		this->b=x.b;
		this->n=x.n;

		p=new int[this->n];
		for(int i=0;i<this->n;++i)
			this->p[i]=x.p[i];
	}
	A(A&& x)
	{
		this->a=x.a;
		this->b=x.b;
		this->n=x.n;

		this->p=x.p;

		x.p=null;
		x.a=0;
		x.b=0;
		x.n=0;

	}
	//Observadores

	//Modificadores

	//Sobrecargas

	//Destructor

	//Otros metodos

	
private:
	int a,b;
	int n; //Tamaño del vector
	int *p; //Vector de enteros
};


A obj1={6,4};  //1  Conversion implicita
A obj2{2,2}; //2
A obj3(4,4); //3
B y;


A obj4(obj3);

obj3                    obj4

p ---> [1,2,3,4]          p-----> [ 1, 2, 3, 4]


A obj5(std::move(obj3));

obj3                    obj5

                        [1,2,3,4]  <-----p

obj4.a=obj3.a
obj4.b=obj3.b
obj4.n=obj3.n
obj4.p=obj3.p


obj.a=6; //No se puede hacer porque a es private






