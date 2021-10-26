//Destructor
class A
{
public:
	A(int x=0):n(x), p(new int[n]){}
	~A()
	{
		delete[] p;
	}
	//Observadores (getters)
	int getn() const { return n;}
	int* getp() const { return p; } 
	const B& getb() const {return b;}

	int& getnum() const { return n; } //metodo observador-modificador. MAL
	//Modificadores (setters)
	void setn(int n_)
	{
		if(n_>=1 && n_<=28)
		{
			n=n_;
			//copiar los elementos de p
			//***
			delete[] p;
			p=new int[n];
		}
	}
	void setp(int* p_)
	{
		delete[] p;
		int cont=0;
		p=p_;
		int* aux=p;
		while(aux)
		{
			cont++;
			aux++;
		}
		n=cont;
	}
	//operador binario (+) Recibe un solo parametro si se implementa dentro de la clase
	//Si se implementa fuera de la clase, recibe 2 parametros
	A operator+(const A& a)
	{
		A solucion;

		solucion.n=this->n+a.n;

		return solucion;
	}
private:
	int n;
	int* p;
	B b;
	void copiar();
};


int main()
{
	int x,y;
	A a(1); //memory leak si no hemos creado un destructor que elimine la memoria dinamica reservada por el constructor
	A b(a); //llama a constructor de copia
	int y=a.getn();

	a.setn(5);

	/*
	a.n=5;
	a.p --> 4 3 2 6 5 
	*/

	//cout << a.getnum(); // imprime 5. El metodo getnum actua como observador
	//a.getnum()=9; //el metodo getnum actua como modificador

	//int v[10]={1,2,3,4,5,6,67,7,8,9};
	//a.setp(v);

	A c;

	c=a+b;

	cout << a.getn(); //6



}