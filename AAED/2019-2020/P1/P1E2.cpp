#include <iostream>

using namespace std;

void muestra_temperatura(int);
int main()
{
	int temperatura;
	cout << "Introduzca valor temperatura (numero):" << endl;
	cin >> temperatura;
	muestra_temperatura(temperatura);
	return 0;
}

void muestra_temperatura(int temperatura)
{
	cout << "Temperatura: " << temperatura << " grados ";
	if (20 < temperatura && temperatura < 30)
		cout << "(normal)";
	else
		cout << "(anormal)";
	cout << endl;
}

