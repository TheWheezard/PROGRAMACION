// racional.cpp --- Implementacion del TAD racional

#include <cstdlib>
#include <cassert>
#include "racional.h"

// Metodos privados

long racional::mcd(long x, long y)
{
	long a;
	// Algoritmo de Euclides
	if (x<y)
	{
		a=x;
		x=y;
		y=a;
	}
	while ((a = x % y))
	{
		x=y;
		y=a;
	}
	return y;
}

inline long racional::mcm(long x, long y)
{
	return x / mcd(x,y) * y;
}

// CONSTRUCTOR
racional::racional(long nu, long de) : n(nu), d(de)
{
	assert(d != 0); // Verificar precondicion
	if (n == 0)
		d = 1;
	else
	{
		if (d < 0) // Poner signo en el numerador
		{
			n = -n;
			d = -d;
		}
		// Reducir fraccion
		long m = mcd(abs(n),d);
		if (m != 1)
		{
			n /= m;
			d /= m;
		}
	}
}

// OPERADORES ARITMETICOS EXTERNOS
racional operator +(const racional& r, const racional& s)
{
	long m = racional::mcd(r.d, s.d);
	return racional(s.d / m * r.n + r.d / m * s.n,
				 racional::mcm(r.d,s.d))
}

racional operator *(const racional& r, const racional& s)
{
	racional t;  // racional 0/1
	if (r.n && s.n)
	{
		long a = racional::mcd(abs(r.n), s.d);
		long b = racional::mcd(r.d, abs(s.n));
		t.n = (r.n / a) * (s.n / b);
		t.d = (r.d / b) * (s.d / a);
	}
	return t;
}

racional operator -(const racional& r)
{
	racional s; // racional 0/1
	
	if (r.n != 0)
	{
		s.n = -r.n;
		s.d = r.d;
	}
	return s;
}

racional inv(const racional& r)
{
	racional s;
	
	assert(r.n != 0); // Verificar precondicion
	if (r.n > 0)
	{
		s.n = r.d;
		s.d = r.n;
	}
	else // Poner signo en el numerador
	{
		s.n = -r.d;
		s.d = -r.n;
	}
	return s;
}

racional operator +=(const racional& r, const racional& s)
{
	return r+s;
}

racional operator -=(const racional& r, const racional& s)
{
	s = -s;
	return r+s;
}

racional operator *=(const racional& r, const racional& s)
{
	return r*s;
}

racional operator /=(const racional& r, const racional& s)
{
	s = inv(s);
	return r*s;
}
