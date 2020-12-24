/*
Naive Gaussian Elimination
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
    int N;
    fin >> N;
    double **A = new double*[N];
    double *X = new double[N];
    double *B = new double[N];
    for (int i = 0; i < N; i++)A[i] = new double[N];
    for (int i = 0; i < N; i++)X[i] = 0.;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            fin >> A[i][j];
    for (int i = 0; i < N; i++)fin >> B[i];

    for (int k = 0; k < N-1; k++)
    {
        for (int i = k + 1; i < N; i++)
        {
            double coeff = A[i][k]/A[k][k];
            for (int j = k; j < N; j++)
            {
                A[i][j] = A[i][j] - coeff*A[k][j];
            }
            B[i] = B[i] - coeff * B[k];
        }
    }

    X[N - 1] = B[N - 1]/A[N - 1][N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        double sum = B[i];
        for (int j = i+1; j < N; j++)
        {
            sum = sum - A[i][j]*X[j];
        }
        X[i] = sum/A[i][i];
    }

    for (int i = 0; i < N; i++)
    {
        fout << X[i] << setw(10);
    }

    for (int i = 0; i < N; i++) delete A[i];
    delete A;
    delete B;
    delete X;
    fin.close();
    fout.close();
    return 0;
}