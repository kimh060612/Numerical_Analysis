#include "parameter.h"
#include "Function.h"

Parameter::Parameter()
{
}

Parameter::Parameter(Parameter & a)
{
	this->Data = a.Data;
	this->Delta = a.Delta;
	this->Is_Grad = a.Is_Grad;
	this->Is_last_Grad = a.Is_last_Grad;
}

Parameter::Parameter(int * A, bool isGrad)
{
	Tensor Mat_D(A);
	Tensor Mat_G(A);
	this->Data = Mat_D;
	if (isGrad)this->Delta = Mat_G;
	this->Is_Grad = isGrad;

}

Parameter::Parameter(Matrix & Mat, bool isGrad)
{
	Matrix Mat_G(Mat.row, Mat.col);
	Tensor tmp(Mat);
	this->Data = tmp;
	if (isGrad) { this->Delta = Mat_G; }
	this->Is_Grad = isGrad;
}

Parameter::Parameter(Tensor & Mat, bool isGrad)
{
	Tensor Mat_G(Mat.size);
	this->Data = Mat;
	if (isGrad)this->Delta = Mat_G;
	this->Is_Grad = isGrad;
}

Parameter::Parameter(Matrix & Mat, int Weight_or_bias)
{
	if (Weight_or_bias == 2) { this->Weight = Mat; this->Is_W_B = true; this->Is_Grad = false; }
	else if (Weight_or_bias == 3) { this->Bias = Mat; this->Is_W_B = true; this->Is_Grad = false; }
	else cout << "Input Error!" << endl;
}

Parameter::Parameter(Tensor & Mat, int Weight_or_bias)
{
	if (Weight_or_bias == 2) { this->Weight = Mat; this->Is_W_B = true; this->Is_Grad = false; }
	else if (Weight_or_bias == 3) { this->Bias = Mat; this->Is_W_B = true; this->Is_Grad = false; }
	else cout << "Input Error!" << endl;
}

Parameter::~Parameter()
{
}
