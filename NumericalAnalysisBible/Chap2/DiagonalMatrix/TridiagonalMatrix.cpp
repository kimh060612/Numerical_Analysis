#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int N;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
    fin >> N;
    double *a = new double[N]; double *d = new double[N];
    double *c = new double[N]; double *b = new double[N];
    double *X = new double[N];    
    for (int i = 0; i < N - 1; i++) fin >> a[i];
    for (int i = 0; i < N; i++) fin >> d[i];
    for (int i = 0; i < N - 1; i++)fin >> c[i];
    for (int i = 0; i < N; i++) fin >> b[i];
    

    for (int i = 1; i < N; i++)
    {
        double coeff = a[i - 1]/d[i - 1];
        d[i] = d[i] - coeff*c[i - 1];
        b[i] = b[i] - coeff*b[i - 1];
    }

    X[N-1] = b[N - 1]/d[N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        X[i] = (b[i] - c[i]*X[i+1])/d[i];
    }

    for (int i = 0; i < N; i++)
    {
        fout << X[i] << endl;
    }

    delete[] a; delete[] d;
    delete[] c; delete[] b;
    delete[] X;
    return 0;
}