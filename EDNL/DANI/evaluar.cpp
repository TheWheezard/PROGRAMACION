//Estructura a usar, se encuentra declarada dentro del fichero Abin.hpp, fuera de la clase

struct elem
{
    char op;
    double valor;
    elem(char o=' ', double v=0.0):op(o), valor(v){} //Constructor
};

double evaluar(const Abin<elem>& a, typename Abin<elem>::nodo n)
{
    if(n!=Abin<elem>::NODO_NULO)
    {
        if(a.elemento(n)!=' ')
        //if(a.elemento(n).op=='+' || a.elemento(n).op=='-' || a.elemento(n).op=='*' || a.elemento(n).op=='/' )
        {
            if(a.elemento(n).op=='+')
                return evaluar(a, a.hijoIzqdoB(n))+evaluar(a, a.hijoDrchoB(n));
            if(a.elemento(n).op=='-')
                return evaluar(a, a.hijoIzqdoB(n))-evaluar(a, a.hijoDrchoB(n));
            if(a.elemento(n).op=='*')
                return evaluar(a, a.hijoIzqdoB(n))*evaluar(a, a.hijoDrchoB(n));
            if(a.elemento(n).op=='/')
                return evaluar(a, a.hijoIzqdoB(n))/evaluar(a, a.hijoDrchoB(n));
        }
        else
        {
            return a.elemento(n).valor;
        }
    }
    else
        return 0;
}