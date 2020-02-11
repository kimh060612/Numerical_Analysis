#include "Tensor.h"

Tensor::Tensor()
{
}

Tensor::Tensor(int W, int H)
{
	this->H = H; this->W = W;
	this->Dim = 2;
	this->Depth_1 = 1;
	this->Tensor_2D = Matrix(H, W);
}

Tensor::Tensor(int W, int H, int D)
{
	this->H = H; this->W = W;
	this->Dim = 3;
	this->Depth_1 = 4;
	this->Tensor_3D = new Matrix[D];
	for (int i = 0; i < D; i++)
	{
		this->Tensor_3D[i] = Matrix(H, W);
	}
}

Tensor::Tensor(int W, int H, int D1, int D2)
{
	this->H = H; this->W = W;
	this->Dim = 4;
	this->Depth_1 = D1;
	this->Depth_2 = D2;
	this->Tensor_4D = new Matrix*[D1];
	for (int i = 0; i < D1; i++)
	{
		this->Tensor_4D[i] = new Matrix[D2];
	}
	for (int i = 0; i < D1; i++)
	{
		for (int j = 0; j < D2; j++)
		{
			this->Tensor_4D[i][j] = Matrix(H, W);
		}
	}
}

Tensor::Tensor(int * A)
{
	int N = sizeof(A) / sizeof(int);

	if (N == 2)
	{

	}
	else if (N == 3)
	{
	}
	else if (N == 4)
	{
	}
	else cout << "Size Error" << endl;

}

Tensor &Tensor::operator=(Matrix & op1)
{
	this->Tensor_2D = op1;
	return *this;
}

Tensor &Tensor::operator=(Tensor & op1)
{
	*this = op1;
	return *this;
}

Tensor::~Tensor()
{
	if (this->Dim == 3)delete[] this->Tensor_3D;

	if (this->Dim == 4)
	{
		for (int i = 0; i < this->Depth_1; i++)
		{
			delete[] this->Tensor_4D[i];
		}
		delete[] this->Tensor_4D;
	}

}
