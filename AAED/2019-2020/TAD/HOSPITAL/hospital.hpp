/** TAD_HOSPITAL **/
#include iostream
#ifndef TAD_HOSPITAL
#define TAD_HOSPITAL
class Hospital
{
	struct paciente;
public:
	Hospital(int n_uci, int n_planta);   // constructor
	void Ingreso(int codigo, int gravedad); // Ingresar paciente
	void Alta(int codigo, int gravedad);
	void Muerte(int codigo, int gravedad);
	void const PacientesUCI() const;
	void const PacientesPlanta() const;
	void const PacientesGrav(int grav) const;  // muestra los pacientes de una gravedad grav determinada
	~Hospital();
private:
	int uci_,planta_,cuci,cpl;//tam uci, tam planta, plazas ocup uci, plazas ocup planta
	struct paciente
	{
		int codp; //codigo de paciente, identificador, unico
		int g; // codigo de gravedad; 0: muerto, 1-5 req UCI, 6-9 req planta
	};
	paciente *uci;
	paciente *planta;
	//metodos privados
	int buscarPlanta(int);
	int buscarUci(int);
	int buscarGravePL(int);
	void insertaGrave(paciente);
	void insertaPlanta(paciente);
	void organizaUci(int);
	void organizaPlanta(int);
}

//METODOS PRIVADOS
int Hospital::buscarPlanta(int cod)
{
	int res,i=0;
	res=-1
	while(i<planta_)
	{
		if(planta[i].codp==cod)
		{
			res=i;
			i=planta_;
		}
		i++;
	}
	return res;
}
int Hospital::buscarUci(int cod)
{
	int res,i=0;
	res=-1;
	while(i<uci_)
	{
		if(uci[i].codp==cod)
		{
			res=i;
			i=uci_;
		}
		i++;
	}
	return res;
}
int Hospital::buscarGravePL()
{
	int plaza,gr, i=0;
	plaza = 0;
	for(i=1;i<planta_;i++)
	{
		if(planta[i].g < planta[plaza].g) //buscamos la g mas pequena, que es mayor gravedad
		{
			plaza = i;
		}
	}
	if(planta[plaza].g <=5)
		return plaza;
	else return -1;
}
void Hospital::insertaGrave(paciente p)
{
	int plaza, i = 0;
	plaza = i;
	for(i=1;i<uci_;i++)
	{
		if(uci[i].g == 0)
		{
			plaza = i;
			i=uci_;
		}
		else if(uci[i].g > uci[plaza].g)
		{
			plaza = i;
		}
	}
	if(p.g < uci[plaza].g || uci[plaza].g == 0) //si el paciente p esta mas grave que el ingresado en uci (o paciente en uci tiene g==0)
	{
		if(uci[plaza].g!=0){
			cout<<"EL PACIENTE "<<uci[plaza].codp<<" SERA TRASLADADO A PLANTA PARA INTRODUCIR PACIENTE MAS GRAVE"<<endl;
			insertaPlanta(uci[plaza]);
		}
		else
			cout<<"ADMITIDO NUEVO PACIENTE POR DEFUNCION DE "<<uci[plaza].codp<<endl;
		uci[plaza] = p;
	}
	else
	{
		cout<<"PLANTA LLENA CON PACIENTES MAS GRAVES, TRASLADO A PLANTA"<<endl;
		insertaPlanta(p);
	}
}
void Hospital::insertaPlanta(paciente p)
{
	int plaza, i = 0;
	plaza = i;
	for(i=1;i<planta_;i++)
	{
		if(planta[i].g == 0)
		{
			plaza = i;
			i = planta_;
		}
		else if(planta[i].g > planta[plaza].g)
		{
			plaza = i;
		}
	}
	if(p.g < planta[plaza].g || planta[plaza].g == 0 ) //si el paciente p esta mas grave que el ingresado en planta (o paciente en planta tiene g==0)
	{
		if(planta[plaza].g != 0)
			cout<<"EL PACIENTE "<<planta[plaza].codp<<" SERA DADO DE ALTA PARA INTRODUCIR PACIENTE MAS GRAVE"<<endl;
		else
			cout<<"ADMITIDO NUEVO PACIENTE POR DEFUNCION DE "<<planta[plaza].codp<<endl;
		planta[plaza] = p;
	}
	else
	{
		cout<<"PLANTA LLENA CON PACIENTES MAS GRAVES, ADMISION IMPOSIBLE"<<endl;
	}
}

void Hospital::organizaUci(int res)
{
	int plaza;
	while(res+1<uci_)
	{
		uci[res]=uci[res+1];
		res++;
	}
	uci_ -=1;
	plaza = buscarGravePL();
	if(plaza!=-1)
	{
		uci[uci_]=plaza;
		uci_ += 1;
		organizaPlanta(plaza);
	}
}
void Hospital::organizaPlanta(int res)
{
	while(res+1<planta_)
	{
		planta[res]=planta[res+1];
		res++;
	}
	planta_ -=1;
}
//METODOS PUBLICOS
Hospital::Hospital(int n_uci, int n_planta)
{
	contu=contp=0;
	uci_=n_uci; planta_=n_planta;
	uci = new paciente(uci_);
	planta = new paciente(planta_);
}

void Hospital::Ingreso(int codigo, int gravedad)
{
	paciente p;
	p.codp = codigo; p.g = gravedad;
	if(gravedad <= 5) //si es muy grave
	{
		if(cuci < uci_) //solo se aumenta cuci en este caso, porque en else estamos sustituyendo uno por otro
		{
			uci[cuci] = p;
			cuci += 1;
		}
		else
		{
			insertaGrave(p);
		}
	}
	else // si su gravedad solo admite ingreso en planta
	{
		if(cpl < planta_)  //solo se aumenta cpl en este caso, porque en else estamos sustituyendo uno por otro
		{
			planta[cpl] = p;
			cpl += 1;
		}
		else
		{
			insertaPlanta(p);
		}
	}
}
void Hospital::Alta(int codigo, int gravedad)
{
	int res;
	if(gravedad<=5)
	{
		res = buscarUci(codigo);
		if(res==-1)
		{
			res = buscarPlanta(codigo);
			if(res==-1)
			cout<<"EL PACIENTE NO ESTA INGRESADO"<<endl;
			else
			{
				organizaPlanta(res)
			}
		}
		else
		{
			organizaUci(res);
		}
	}
	else
	{
		res = buscarPlanta(codigo);
		if(res==-1)
			cout<<"EL PACIENTE NO ESTA INGRESADO"<<endl;
		else
			organizaPlanta(res);
	}
}
void Hospital::Muerte(int codigo, int gravedad)
{
	int res;
	if(gravedad<=5)
	{
		res = buscarUci(codigo);
		if(res==-1)
		{
			res = buscarPlanta(codigo);
			if(res==-1)
			cout<<"EL PACIENTE NO ESTA INGRESADO"<<endl;
			else
			{
				planta[res].g=0;
			}
		}
		else
		{
			uci[res].g=0;
		}
	}
	else
	{
		res = buscarPlanta(codigo);
		if(res==-1)
			cout<<"EL PACIENTE NO ESTA INGRESADO"<<endl;
		else
			planta[res].g=0;
	}
}
void const Hospital::PacientesUCI() const
{
	int i;
	cout << "CODIGO PACIENTE          GRAVEDAD" << endl;
	for(i=0;i<uci_;i++)
		cout << uci[i].codp << "          " << uci[i].g << endl;
	cout << "---------------------------------" << endl;
}
void const Hospital::PacientesPlanta() const
{
	int i;
	cout << "CODIGO PACIENTE          GRAVEDAD" << endl;
	for(i=0;i<planta_;i++)
		cout << planta[i].codp << "          " << planta[i].g << endl;
	cout << "---------------------------------" << endl;
}
void const Hospital::PacientesGrav(int grav) const  // muestra los pacientes de una gravedad grav determinada
{
	int i;
	cout << "CODIGO PACIENTE          GRAVEDAD          UBICACION" << endl;
	if(grav >= 6)
	{
		for(i=0;i<planta_;i++)
		{
			if(planta[i].g == grav)
				cout << planta[i].codp << "          " << planta[i].g << "          PLANTA" << endl;
		}
	}
	else
	{
		for(i=0;i<planta_;i++)
		{
			if(planta[i].g == grav)
				cout << planta[i].codp << "          " << planta[i].g << "          PLANTA" << endl;
		}
		for(i=0;i<uci_;i++)
		{
			if(uci[i].g == grav)
				cout << uci[i].codp << "          " << uci[i].g << "          UCI" << endl;
		}
	}
	cout << "-------------------------------------------------" << endl;
}
Hospital::~Hospital()
{}

#endif