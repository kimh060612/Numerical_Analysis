#include <math.h>

class ADALINE
{
public:

    ADALINE(int _nIn, int _nOut);
    ~ADALINE();
    void backward(double *target, double *InputVector,double lr);
    double* predict(double *InputVector);

private:
    double* forward(double *InputVector);
    int nIn;
    int nOut;
    double **W;
    double *b;
};

double* Allocate1D(int N);
double** Allocate2D(int row, int col);
void Free1D(double *vec);
void Free2D(double **matrix, int row);
#pragma once