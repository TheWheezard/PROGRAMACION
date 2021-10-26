#include <iostream>
#include <cstdlib>
#include <ctime>

int inter_directo(int*,int);
	int test(int*,int,int);
int sel_directa(int*,int);
int ord_directa(int*,int);

int main()
{
	using namespace std;
	int n,op,i;
	cout << "INTRODUZCA TAMANIO DE VECTOR: " ;
	cin >> n;
	int v[n];
	int res[n];
	cout << "INRODUZCA " << n << " ELEMENTOS EN EL VECTOR: ";
	for(i=0;i<n;i++)
	{
		cin >> v[i];
	}
	cout << "INDIQUE ALGORITMO QUE DESEA USAR:\n\t1- Intercambio Directo\n\t2- Seleccion Directa\n\t3- Insercion Directa\n\t  0-SALIR";
	cin >> op;
	switch (op)
	{
		case 1: res = inter_directo(v,n);break;
		case 2: res = sel_directa(v,n);break;
		case 3: res = ord_directa(v,n);break;
		case 0: break;
		default: cout << "\nERROR"<<endl;break;
	}
	
	return 0;
}

int inter_directo(int* v,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		v=test(v,i,n);
	}
	return v;
}
int test(int* v,int i,int j)
{
	int k,aux;
	for(k=j-1;k<=i;k--)
	{
		if(v[k] < v[k-1])
		{
			aux=v[k];
			v[k]=v[k-1];
			v[k-1]=aux;
		}
	}
	return v;
}


int sel_directa(int* v,int i)
{
	int i;
	for(i=1;i<n-1;i++)
	{
		
	}
}
