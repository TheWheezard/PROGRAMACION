#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
double aleatorio(double,double);

int main()
{
	srand(time(0));
	double a,b;
	cout << "Introduzca a: " << endl; // min
	cin >> a;
	cout << "\nIntroduzca b: " << endl; // max
	cin >> b;
	cout << "Solucion = " << aleatorio(a,b) << endl;
	return 0;
}

double aleatorio (double a, double b)
{
	double f =  (double)rand() /RAND_MAX;
	return a + f * (b - a);
}
