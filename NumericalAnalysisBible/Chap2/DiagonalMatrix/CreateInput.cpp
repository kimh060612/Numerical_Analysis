#include <iostream>
#include <fstream>

using namespace std;

ofstream fout("input.txt");

int main()
{
    int n = 50;
    double *A = new double[n];
    double *D = new double[n];
    double *C = new double[n];
    double *B = new double[n];

    for (int i = 0; i < n - 1; i++)A[i] = -1.;
    for (int i = 0; i < n; i++)D[i] = 5.;
    for (int i = 0; i < n - 1; i++)C[i] = -1.;
    for (int i = 0; i < n; i++)B[i] = i + 2;
    B[n - 1] = 1;
    // Exercise 4
    /*for (int i = 0; i < n - 1; i++)A[i] = 1.;
    for (int i = 0; i < n; i++)D[i] = -4.;
    for (int i = 0; i < n - 1; i++)C[i] = 1.;
    for (int i = 0; i < n; i++)B[i] = 40; */
    // A[n - 2] = -1.; C[0] = -1.;
    // B[0] = -20; B[n - 1] = -20;
    // D[0] = 4.; D[n - 1] = 4.;

    fout << n << endl;
    for (int i = 0; i < n - 1; i ++)fout << A[i] << " ";
    fout << endl;
    for (int i = 0; i < n; i ++)fout << D[i] << " ";
    fout << endl;
    for (int i = 0; i < n - 1; i ++)fout << C[i] << " ";
    fout << endl;
    for (int i = 0; i < n; i ++)fout << B[i] << " ";
    fout << endl;
    delete[] A;
    delete[] D;
    delete[] C;
    delete[] B;
    return 0;
}