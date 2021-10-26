template<typename T>
class A
{
	public:
		//Constructores	
			A(); //Por defecto
			A(parametro1, parametro2,...); //Constructor de conversion
			explicit A(parametro1, parametro2, ...); //Constructor con n parametros
			A(const A&); //de copia
			A(A&&); //de movimiento 


		//Sobrecarga de operadores
			//Operadores aritmeticos
			A& operator=(parametro); //operador de asignacion
			A& operator+(parametro); //operador de suma (suma el parametro con this)
			A& operator-(parametro); //operador de resta (resta el parametro con this)
			A& operator*(parametro); //operador de producto (multiplica el parametro con this)
			A& operator/(parametro); //operador de division (divide el parametro con this)
			A& operator++(int); //postautoincremento (primero devuelve y despues incrementa)
			A& operator++(); //preautoincremento (primero incrementa y luego devuelve)
			//Todos los operadores pueden implementarse dentro de la clase o fuera mediante el uso de funciones amigas
			//cuando un operador aritmetico binario se implementa dentro de la clase solo hay un posible orden (a+2). Cuando
			//se hace uso de funciones amigas se puede poner el parametro a la derecha del objeto.
			friend A& operator+(parametro1, parametro2);
			friend ostream& operator<<(ostream&, const A&); //sobrecarga de salida
			friend istream& operator>>(istream&, const A&); //sobrecarga de entrada
			const operator double() const; //operador de conversion. El nombre del operador es el tipo de devolucion.En este
			//caso convierte un objeto A en double cuando haga falta.
		//Destructor
			~A(); //El destructor nunca lleva parametros y se encarga de eliminar toda la memoria dinamica reservada por el constructor.
		//Metodos observadores
			int getTam() const;
			int geta() const;
		//Metodos modificadores
			void setTam(int);
			void seta(int)
		//Metodo observador y modificador a la vez
			int& getsetTam(); //modificar:a.getsetTam()=5; observar: a.getsetTam()
			int& getseta();
		//Excepciones





		//atributos
			static const int f; //declaracion de un atributo estatico
	private:
		T *p;
		int tam;
		mutable int a; //atributo que puede ser modificado dentro de un metodo const
}; //fin de la clase
f=0; //definicion de un atributo estatico

----------------------------------------------------------------------------------------------
A<T>::A():tam(0), a(0){}
int A<T>::getTam() const
{
	a++; //se puede porque a es mutable
	return tam;
}
A& operator++(int n) //post
{
	A *temp=new A;
	*temp=*this;
	a++;
	return *temp;
}
A& operator++()
{
	a++;
	return *this;
}
//funcion amiga
ostream& operator<<(ostream& os, const A& a)  //sobrecarga de salida
{
	os << "El valor de a es " a.a << " y el valor de tam es " << a.tam << endl;
	return os;
}
istream& operator>>(istream& is, const A& a)
{
    is >> a.a >> a.tam;
    return is;
}
-----------------------------------------------------------------------------------------------
int main()
{
	A a;
	cin >> a;
	cout << a++ << endl;
	cout << a << endl; 
}

---------------------------------------------------------------------------------
class B
{
public:
	B(int x=0):n(x), v(new int[n]){} //Constructor de conversion
	//explicit B(int x=0):n(x){} //Constructor (prohíbe las conversiones implicitas B a=6)
	//B(int x=0, int y=0):n(x), p(y){}
	//B(int x=0){n=x;}
	B(const B& b) //Constructor de copia -> Obligatorio cuando existe asignacion dinamica de memoria
	{
		n=b.n;
		p=b.n;
		v=new int[n];
		for(int i=0;i<n;i++)
			v[i]=b.v[i];
	}
	B(B&& b)
	{
		n=b.n;
		p=b.p;

		v=b.v;
		b.v=0;

		b.n=0;
		b.p=0;
	}

	this				b
	n=5 					n=5
	p=6 					p=6
	v---------------->12345  v=null
	//Observadores
	int getn() const {return n;}
	//Modificador
	void setn(const int& x)
	{ 	if(x<100)
		n=x;}
	//Observador y modificador
	int& getsetn() const {return n;}
	~B()
	{
		delete[] v;
	}
private:
	int n,p;
	int *v;
}


a
n=5=a.getsetn()
p=0;
v=null;


int main()
{
	B a={3,5};
	//a.n=3, a.p=5, v=_ _ _
	//B b(a); // b.n=a.n , b.p=a.p (Constructor de copia por defecto)
	B b(a); //b.n=3, b.p=5, v=a.v
	B c(std::move(a)); //Llama al constructor de movimiento
	cout << c.getn();
	a.setn(4);
	a.getsetn()=5; //error
	cout << a.getsetn();






