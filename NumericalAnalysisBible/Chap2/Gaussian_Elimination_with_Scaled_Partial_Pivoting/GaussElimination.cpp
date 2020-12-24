/*
Gaussian Elimination With Scaled Partial Pivoting
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace std;

double max(double a, double b) {return a > b ? a : b;}
void swap(int &a, int &b);

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
    int N;
    fin >> N;
    double **A = new double*[N];
    double *X = new double[N];
    double *B = new double[N];
    int *L = new int[N];
    double *S = new double[N];
    for (int i = 0; i < N; i++)A[i] = new double[N];
    for (int i = 0; i < N; i++)X[i] = 0.;
    for (int i = 0; i < N; i++)L[i] = i;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            fin >> A[i][j];
    for (int i = 0; i < N; i++)fin >> B[i];

    for (int i = 0; i < N; i++)
    {
        double smax = 0.;
        for (int j = 0; j < N; j++)
        {
            smax = max(smax, abs(A[i][j]));
        }
        S[i] = smax;
    }

    for (int k = 0; k < N - 1; k++)
    {
        int j;
        double rmax = 0.;
        for (int i = k; i < N; i++)
        {
            double r = abs(A[L[i]][k]/S[L[i]]);
            if (r > rmax)
            {
                rmax = r;
                j = i;
            }
        }
        swap(L[j], L[k]);
        for (int i = k + 1; i < N; i++)
        {
            double coeff = A[L[i]][k]/A[L[k]][k];
            for (int j = k; j < N; j++)
            {
                A[L[i]][j] = A[L[i]][j] - coeff*A[L[k]][j];
            }
            B[L[i]] = B[L[i]] - coeff*B[L[k]];
        }
    }
    
    X[N - 1] = B[L[N-1]]/A[L[N - 1]][N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        double sum = B[L[i]];
        for (int j = i + 1; j < N; j++)
        {
            sum = sum - A[L[i]][j]*X[j];
        }
        X[i] = sum/A[L[i]][i];
    }

    for (int i = 0; i < N; i++)
    {
        fout << X[i] << setw(10);
    }

    for (int i = 0; i < N; i++) delete A[i];
    delete A;
    delete B;
    delete X;
    delete L;
    delete S;
    fin.close();
    fout.close();
    return 0;
}

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}