#include "parameter.h"
#include "Function.h"

Parameter::Parameter(const Parameter & a)
{
	this->Data = a.Data;
	this->Gradient = a.Gradient;

	this->Is_Grad = a.Is_Grad;
	this->Is_last_Grad = a.Is_last_Grad;

}

Parameter::Parameter(int * A, bool isGrad)
{
	int N = sizeof(A) / sizeof(int);

	if (N == 2)
	{
		this->Data = Tensor(A[0], A[1]);
		this->Gradient = Tensor(A[0], A[1]);
	}
	else if (N == 3)
	{
		this->Data = Tensor(A[0], A[1], A[2]);
		this->Gradient = Tensor(A[0], A[1], A[2]);
	}
	else if (N == 4)
	{
		this->Data = Tensor(A[0], A[1], A[2], A[3]);
		this->Gradient = Tensor(A[0], A[1], A[2], A[3]);
	}
	else cout << "Size Error" << endl;
	
	this->Is_Grad = isGrad;

}

Parameter::Parameter(Matrix & Mat, bool isGrad)
{

	this->Data = Mat;
	this->Gradient = Matrix(Mat.row, Mat.col);
	this->Is_Grad = isGrad;
}

Parameter::Parameter(Tensor & Mat, bool isGrad)
{
	this->Data = Mat;
	
	this->Is_Grad = isGrad;
}

void Parameter::Backword(Parameter & P)
{
}

Parameter::~Parameter()
{
}
