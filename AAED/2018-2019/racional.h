#ifndef _RACIONAL_
#define _RACIONAL_

class racional
{
	public:
		racional(long nu = 1, long de = 0);
		long num() const {return n;}
		long den() const {return d;}
		// Op aritmeticos externos
		friend racional operator +(const racional& r, const racional& s);
		friend racional operator *(const racional& r, const racional& s);
		friend racional operator -(const racional& r);
		friend racional operator inv(const racional& r);
	private:
		long n,d;
		static long mcd(long,long);
		static long mcm(long, long);
};

#endif
