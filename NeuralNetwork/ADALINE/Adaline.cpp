#include "Adaline.h"
#include <exception>
#include <iostream>

using namespace std;

double* Allocate1D(int N)
{
    double *vec;
    vec = new double[N];
    return vec;
}

double** Allocate2D(int row, int col)
{
    double **mat = new double*[row];
    for (int i = 0; i < row; i++)mat[i] = new double[col];
    return mat;
}

void Free1D(double *vec)
{
    delete[] vec;
}

void Free2D(double **matrix, int row)
{
    for (int i = 0; i < row; i++)
        delete[] matrix[i];
    delete[] matrix;
}

ADALINE::ADALINE(int _nIn, int _nOut)
{
    this->nIn = _nIn;
    this->nOut = _nOut;
    this->W = Allocate2D(_nOut, _nIn);
    this->b = Allocate1D(_nOut);
    for (int i = 0; i < _nOut; i++)
    {
        for (int j = 0; j < _nIn; j++)
        {
            this->W[i][j] = 0.0;
        }
        this->b[i] = 0.0;
    }
}

ADALINE::~ADALINE()
{
    for (int i = 0; i < this->nOut; i++)
    {
        for (int j = 0; j < this->nIn; j++)
        {
            cout << this->W[i][j] << " ";
        }
        cout << endl;
    }
    Free2D(this->W, this->nOut);
    Free1D(this->b);
}

double* ADALINE::forward(double *InputVector)
{
    double *OutputVector = Allocate1D(this->nOut);
    
    for (int i = 0; i < this->nOut; i++)
    {
        double sum = 0.;
        for (int j = 0; j < this->nIn; j++)
            sum += this->W[i][j] * InputVector[j];
        OutputVector[i] = sum + this->b[i];
    }
    return OutputVector;
}   

void ADALINE::backward(double *target, double *InputVector, double lr)
{
    double **gradW = Allocate2D(this->nOut, this->nIn);
    double *gradB = Allocate1D(this->nOut);
    double *error = Allocate1D(this->nOut);
    double *y = this->forward(InputVector);
    for (int i = 0; i < this->nOut; i++)
        error[i] = target[i] - y[i];
    for (int i = 0; i < this->nOut; i++)
    {
        for (int j = 0; j < this->nIn; j++)
        {
            gradW[i][j] = 2 * error[i] * InputVector[j];
        }
        gradB[i] = 2*error[i];
    }

    for (int i = 0; i < this->nOut; i++)
    {
        for (int j = 0; j < this->nIn; j++)
        {
            this->W[i][j] += lr * gradW[i][j];
        }
        this->b[i] += lr * gradB[i];
    }

    Free1D(y);
    Free1D(error);
    Free1D(gradB);
    Free2D(gradW, this->nOut);
}

double* ADALINE::predict(double *InputVector)
{
    return this->forward(InputVector);
}
