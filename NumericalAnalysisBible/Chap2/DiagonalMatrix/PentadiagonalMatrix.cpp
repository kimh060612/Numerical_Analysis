#include <iostream>
#include <fstream>

using namespace std;

int N;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
    fin >> N;
    double *a = new double[N]; double *d = new double[N];
    double *c = new double[N]; double *e = new double[N];
    double *f = new double[N];
    double *b = new double[N]; double *X = new double[N];    
    for (int i = 0; i < N - 2; i++) fin >> e[i];
    for (int i = 0; i < N - 1; i++) fin >> a[i];
    for (int i = 0; i < N; i++) fin >> d[i];
    for (int i = 0; i < N - 1; i++)fin >> c[i];
    for (int i = 0; i < N - 2; i++)fin >> f[i];
    for (int i = 0; i < N; i++) fin >> b[i];

    double r = a[0], s = a[1], t = e[0];

    for (int i = 1; i < N - 1; i++)
    {
        double coeff = r / d[i - 1];
        d[i] = d[i] - coeff*c[i - 1];
        c[i] = c[i] - coeff*f[i - 1];
        b[i] = b[i] - coeff*b[i - 1];
        coeff = t/d[i - 1];
        r = s - coeff*c[i - 1];
        d[i+1] = d[i+1] - coeff*f[i-1];
        b[i+1] = b[i+1] - coeff*b[i-1];
        s = a[i];
        t = e[i - 1];
    }

    double coeff = r / d[N - 2];
    d[N - 1] = d[N - 1] - coeff*c[N - 2];
    X[N - 1] = (b[N - 1] - coeff*b[N - 2])/d[N - 1];
    X[N - 2] = (b[N - 2] - c[N - 2]*X[N - 1])/d[N - 2];

    for (int i = N - 3; i >= 0; i--)
    {
        X[i] = (b[i] - f[i]*X[i + 2] - c[i]*X[i + 1])/d[i];
    }

    for (int i = 0; i < N; i++)
    {
        fout << X[i] << endl;
    }

    delete[] a; delete[] d;
    delete[] c; delete[] e;
    delete[] f;
    delete[] X; delete[] b;
    return 0;
}