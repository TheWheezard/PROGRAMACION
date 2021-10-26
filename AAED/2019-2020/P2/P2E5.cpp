#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
int aleatorio(int*,int);
bool ordenado(int*,int);

int main()
{
	int i;
	int A[6];
	for(i=0;i<6;i++)
	{
		A[i] = i + 1;
	}

	//srand(time(0));
	cout << aleatorio(A, 6);
	return 0;
}

int aleatorio (int *A, int n)
{
	int i,j,cont=0;
	const size_t x = sizeof A / sizeof *A;
	for(i=0;i<10000000;i++)
	{
		random_shuffle(A, A + x);
		cout << "\n" << i;  
		cout << " VECTOR[ ";
		for(j=0;j<6;j++)
		{
			cout << A[j] << " ";
		}
		cout << "]" << endl;
		if(ordenado(A, n) == true)
			cont += 1;
	}
	return cont;
}

bool ordenado(int *A, int n)
{
	int i=1;
	bool x=true;
	while(i < n && x != false)
	{
		if(A[i]<A[i-1])
			x = false;
		i += 1;
	}
	return x;
}

