//CONSULTORIO.HPP
#include <iostream>
#include "lista.hpp"
#include "cola.hpp"
#ifndef TAD_CONSULTA
#define TAD_CONSULTA

class Consultorio()
{
	struct paciente;
public:
	Consultorio(); //constructor
	void AltaMedico(int id_medico);
	void BajaMedico(int id_medico);
	void NuevoPaciente(int id_paciente, int id_medico);
	const void ConsultarPaciente(int id_medico) const;
	void AtenderPaciente(int id_medico);
	const bool ComprobarEspera(int id_medico) const;
	~Consultorio(); //destructor
private:
	struct paciente
	{
		int idp;
		//se anadirian mas categorias en funcion de las necesidades
	};
	struct medico
	{
		int idm; //id del medico
		Cola<paciente>* lista_m; //listado de pacientes del medico, simplemente enlazada
	};
	Lista<medico>* consultorio; //medicos que forman el consultorio, doblemente enlazada
	typedef typename Lista<medico>::posicion posicion;
}
//metodos privados

//metodos publicos

Consultorio::Consultorio() //constructor
{
	lista_m = new Cola<paciente>();
}
void Consultorio::AltaMedico(int id_medico)
{
	if(!consultorio.buscar(medico.id_medico))
	{
		medico m;
		m.idp = id_medico;
		consultorio.insertar(m);
	}
}
void Consultorio::BajaMedico(int id_medico)
{
	posicion pos = consultorio.buscar(medico.id_medico);
	if(pos)
	{
		consultorio.eliminar(pos);
	}
}
void Consultorio::NuevoPaciente(int id_paciente, int id_medico)
{
	posicion m = consultorio.buscar(medico.id_medico);
	assert(m);
	paciente p;
	p.idp = id_paciente;
	consultorio.elemento(m).push(p);
}
const void Consultorio::ConsultarPaciente(int id_medico) const
{
	posicion m = consultorio.buscar(medico.id_medico);
	assert(m);
	paciente p;
	p.idp = id_paciente;
	consultorio.elemento(m).frente(p);
}
void Consultorio::AtenderPaciente(int id_medico)
{
	posicion m = consultorio.buscar(medico.id_medico);
	assert(m);
	paciente p;
	p.idp = id_paciente;
	consultorio.elemento(m).pop(p);
}
const bool Consultorio::ComprobarEspera(int id_medico) const
{
	posicion m = consultorio.buscar(medico.id_medico);
	assert(m);
	paciente p;
	p.idp = id_paciente;
	consultorio.elemento(m).vacia();
}
Consultorio::~Consultorio()
{
	delete consultorio; // llama al destructor de la lista consultorio, que llamará a los destructores de las colas almacenadas una por una
}


#endif