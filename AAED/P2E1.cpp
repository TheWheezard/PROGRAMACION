#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>


int main()
{
	using namespace std;
	int cont,n=0;
	double a,b,c,d,e,f;
	a=b=c=e=f=cont=0;
	system("pause");
	for (int i = 0; i < 10000000; ++i)
	{
		n = 1+rand()%(6);
		cont+=1;
		cout << n << "\t";
		cout << cont <<endl;
		
		switch (n)
		{
			case 1: a+=1;break;
			case 2: b+=1;break;
			case 3: c+=1;break;
			case 4: d+=1;break;
			case 5: e+=1;break;
			case 6: f+=1;break;
			default: cout << "\nERROR" <<endl;break;
		}
	}
	cout << "FRECUENCIA NUMERO 1: " << a << "\tF.R.: " << a/10000000;
	cout << "\nFRECUENCIA NUMERO 2: " << b << "\tF.R.: " << b/10000000;
	cout << "\nFRECUENCIA NUMERO 3: " << c << "\tF.R.: " << c/10000000;
	cout << "\nFRECUENCIA NUMERO 4: " << d << "\tF.R.: " << d/10000000;
	cout << "\nFRECUENCIA NUMERO 5: " << e << "\tF.R.: " << e/10000000;
	cout << "\nFRECUENCIA NUMERO 6: " << f << "\tF.R.: " << f/10000000;	 
}

