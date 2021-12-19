#include<iostream>
class Celda
{
public:
    int row, col; //enteros fila y columna
    float valor;  //valor real de la celda

    //constructor
    Celda(int row_, int col_, float valor_) : row(row_), col(col_), valor(valor_){};
    //constructor por defecto
    Celda(){};
    void operator=(Celda cell)
    {
        this->row = cell.row;
        this->col = cell.col;
        this->valor = cell.valor;
    }
};
//sobrecargas del operador <= para ordenación
bool operator<=(const Celda cellA, const Celda cellB)
{
    return (cellA.valor <= cellB.valor);
}
//sobrecargas del operador < para ordenación
bool operator<(const Celda cellA, const Celda cellB)
{
    return (cellA.valor < cellB.valor);
}
//sobrecargas del operador > para ordenación
bool operator>(const Celda cellA, const Celda cellB)
{
    return (cellA.valor > cellB.valor);
}

using namespace std;

void fusion(vector<Celda>& vec, int inicio, int k, int fin)
{
    int n = fin - inicio + 1;
    int p = inicio;
    int q = k+1;
    vector<Celda> aux;
    for (int l = 0; l < n; l++)
    {
        if (p < k && (q > fin || vec[p] <= vec[q]))
        {
            aux.push_back(vec[p]);
            p++;
        }
        else
        {
            aux.push_back(vec[q]);
            q++;
        }
    }
    for (int l = 0; l < n; l++)
    {
        vec[inicio + l] = aux[l];
    }    
}

void ordenacion_insercion(vector<Celda>& vec, int inicio, int fin)
{
    int n = fin - inicio + 1;
    int aux, j;
    for (int i = 1; i < n; i++)
    {
        aux = vec[i];
        j = i-1;
        while (j >= 0 && vec[j] > aux)
        {
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1] = aux;
    }
}

void ordenacion_fusion(vector<Celda>& vec, int inicio, int fin)
{
    int n = fin - inicio + 1;
    if (n <= inicio)
    {
        ordenacion_insercion(vec, inicio, fin);
    }
    else
    {
        int k = inicio + n/2;
        ordenacion_fusion(vec, inicio, k);
        ordenacion_fusion(vec, k+1, fin);
        fusion(vec, inicio, k, fin);
    }
    
}