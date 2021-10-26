#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int aleatorio(int,int);

int main()
{
	//srand(time(0));
	int a,b;
	cout << "Introduzca a: " << endl;
	cin >> a;
	cout << "\nIntroduzca b: " << endl;
	cin >> b;
	cout << "Solucion =" << aleatorio(a,b) << endl;
	return 0;
}

int aleatorio (int a, int b)
{
	return a + rand() % (b - a + 1);
}
