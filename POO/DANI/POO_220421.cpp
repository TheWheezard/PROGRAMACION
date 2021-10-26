class A{
public:
	void rel1(C&);
private:
	std::map<int, C*> asociacion;
};
class B{
public:
	void rel3(D&);
private:
	C c;
	std::set<D*> asociacion;
	std::map<D*, X> asociacion_atrib_enlace;
};
class C{
public:
	int getC1() const;
	void rel4(D&);
private:
	int c1;
	std::set<D*> asociacion;
};
class D{
public:
	void rel4(C&);
private:
	C* c;
};

class rel4
{
public:
	void asocia(D&);
	void asocia(C&);
	std::set<D*>& asociados(C&);
	C& asociados(D&);
private:
	std::map<C*, std::set<D*>> directa;
	std::multimap<D*, C*> inversa;
};

class Empresa
{
public:
	cambiarTelefono()
cambiarDireccion()
private:
    nombre
    telefono
    direccion
};

class Persona
{
public:
	cambiarTelefono()
cambiarDireccion()
private:
	nombre
edad
telefono
direccion

};

class AEE
{
public:
	calcularSueldo()
private:
sueldoBase
complemento
categoria

std::map<Empresa*, Persona*> asociacion;

}


A 0..1 _____________________________ 0..* B
				|
				|
				|
				|
				C (aux)
				int h;
				int c;
				void f();

class B;
class A
{
private:
	
};
class B
{
private:
	
};

class aux
{
public:
	void f();
private:
	int h;
	int c;
};
class C //Clase de asociacion
{
public:
	void asocia(A&, B&); //directa
	std::set<B*>& asociados(A&) const; //observador directa

	void asocia(B&,A&); //inversa
	A& asociados(B&) const; //observador inversa
private:
	std::map<A*, std::map<B*, aux>> asociacion_directa;
	//std::multimap<A*, B*> asociacion_directa2;
	std::map<B*, pair<A*,aux>> asociacion_inversa;
};

void C::asocia(A& a,B& b, aux& aux1)
{
	if(asociacion_directa[&a])
		asociacion_directa[&a].insert(make_pair(&b, &aux1));
	else

}

A a1,a2;
B b1, b2;
C asociacion;

asociacion.asocia(a1, b1);
asociacion.asocia(a1,b2);

b1 ----> <a1, aux1>


b1 ---> a1,aux1
        a2,aux4
        a4,aux6




a1 ----> b1
a2 ----> b2
a1 ----> b3
a4 ----> b5

directa
a1 ------> { b1, b3}
a2----> b2
a4 ---> b5

inversa
b1 ----- a1
b2 ----- a2
b3 ----- a1
b5 ----- a4

/*
set<int>  1 3 4 6 8 10 11 15

map<int, string>

first 	second
1		hola
3		pepe
6		adios
8		pepe

multimap<int, string>

first 	second
1		hola
1		pepe
1		xxx
1       aaa
6		adios
8		pepe
*/

//-----------------------------------------------------------------------------------------


class Asignatura;
class Grupo;

class Alumno{
public:
	void matriculado_en(Asignatura&, Grupo&);
private:
	std::map<Asignatura*, Grupo*> asociacionAsignatura;
};

class Asignatura{
private:
	std::map<Alumno*, Grupo*> asociacionAlumno;
	std::set<Grupo*> asociacionGrupos;
};

class Profesor{
public:
	void imparte(Grupo&);
private:
	std::set<Grupo*> asociacionGrupo;
};

class Grupo{
private:
	string aula;
	int h_semana;
	Asignatura* a;
	Profesor* p;
};

int main()
{
	pepe.matriculas();
}