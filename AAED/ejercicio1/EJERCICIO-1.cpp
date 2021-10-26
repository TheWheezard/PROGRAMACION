//EJERCICIO-1.cpp
#include <iostream>
#include <cstdlib>
#include "pila_vec1.h"

using namespace std;

bool compara(Pila<char>,Pila<char>);
int main()
{
	string XY;
	cout << "INTRODUZCA LA CADENA" <<endl;
	cin >> XY;
    unsigned int i;
	Pila<char> pila1;
	Pila<char> pila2;
	for(i=0; XY[i]!='&' || i<XY.length(); i++)
	{
		pila1.push(XY[i]);

	}
	for(i=XY.length();XY[i]!='&' || i>0; i--)
	{
		pila2.push(XY[i]);
	}
	if(compara(pila1,pila2)==true)
		cout << "El lado X es igual al lado Y" <<endl;
	else
		cout << "El lado X es distinto al lado Y" <<endl;
}

bool compara(Pila<char> pila1, Pila<char> pila2)
{
	string X;
	string Y;
	bool cmp = false;
	while(pila1.vacia()==false||pila2.vacia()==false)
	{
		if(pila1.tope()==pila2.tope())
			cmp = true;
		else
			cmp = false;
		pila1.pop();
		pila2.pop();
	}
	if(pila1.vacia()==false||pila2.vacia()==false)
		return false;
	else
		return cmp;
}
