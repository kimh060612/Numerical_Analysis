#include "Function.h"

Tensor Feed_Function(Parameter U, Act_Func F)
{
	int N = U.Data.Dim;

	Tensor RES(U.Data.size);

	if (N == 2)
	{
		Matrix res(U.Data.size[0], U.Data.size[1]);
		for (int i = 0; i < U.Data.size[0]; i++)
		{
			for (int j = 0; j < U.Data.size[1]; j++)
			{
				res(i,j) = F.Forward_Func(U.Data.Tensor_2D(i,j));
			}
		}
		RES = res;
	}

	else if (N == 3)
	{
		Tensor res(U.Data.size);
		for (int d = 0; d < U.Data.size[2]; d++)
		{
			for (int i = 0; i < U.Data.size[0]; i++)
			{
				for (int j = 0; j < U.Data.size[1]; j++)
				{
					res(i,j,d) = F.Forward_Func(U.Data(i,j,d));
				}
			}
		}
		RES = res;
	}

	else if (N == 4) // Delete This if-state when needed  
	{
		Tensor res(U.Data.size);
		for (int d2 = 0; d2 < U.Data.size[3]; d2++)
		{
			for (int d1 = 0; d1 < U.Data.size[2]; d1++)
			{
				for (int i = 0; i < U.Data.size[0]; i++)
				{
					for (int j = 0; j < U.Data.size[1]; j++)
					{
						res(i,j,d1,d2) = F.Forward_Func(U.Data(i,j,d1,d2));
					}
				}
			}
		}
		RES = res;
	}

	return RES;
}

Tensor Backward_Function(Parameter U, Act_Func De)
{
	int Dim = U.Data.Dim;

	Tensor RES(U.Data.size);

	if (Dim == 2)
	{
		Matrix res(U.Data.size[0], U.Data.size[1]);
		for (int i = 0; i < U.Data.size[0]; i++)
		{
			for (int j = 0; j < U.Data.size[1]; j++)
			{
				res(i, j) = De.Backward_Func(U.Data.Tensor_2D(i, j));
			}
		}
		RES = res;
	}
	else if (Dim == 3)
	{
		Tensor res(U.Data.size);
		for (int d = 0; d < U.Data.size[2]; d++)
		{
			for (int i = 0; i < U.Data.size[0]; i++)
			{
				for (int j = 0; j < U.Data.size[1]; j++)
				{
					res(i, j, d) = De.Backward_Func(U.Data(i, j, d));
				}
			}
		}
		RES = res;
	}
	else if (Dim == 4)
	{
		Tensor res(U.Data.size);
		for (int d2 = 0; d2 < U.Data.size[3]; d2++)
		{
			for (int d1 = 0; d1 < U.Data.size[2]; d1++)
			{
				for (int i = 0; i < U.Data.size[0]; i++)
				{
					for (int j = 0; j < U.Data.size[1]; j++)
					{
						res(i, j, d1, d2) = De.Backward_Func(U.Data(i, j, d1, d2));
					}
				}
			}
		}
		RES = res;
	}
	return RES;
}

Function::Function()
{
}

Function::Function(Parameter * U, Parameter * Z)
{
	this->input = U;
	this->output= Z;
}

void Function::forward()
{
}

void Function::Backprop(Function & Pre_func)
{
}

FunctionIdentity::FunctionIdentity()
{
	this->name = "Identity";
}

void FunctionIdentity::forward()
{
	this->output = this->input;
}

FunctionReLU::FunctionReLU()
{
	this->name = "ReLU";
}

void FunctionReLU::forward()
{
	if (this->input->Is_Grad) // Hidden layer or output
	{
		Act_Func ReLU("ReLU");
		this->output->Data = Feed_Function(*this->input, ReLU);
	}
	else cout << "Wrong Parameter" << endl;// Weight or Bias or input
}

FunctionTanh::FunctionTanh()
{
	this->name = "Tanh";
}

void FunctionTanh::forward()
{
	if (this->input->Is_Grad) // Hidden layer or output
	{
		Act_Func Tanh("Tanh");
		this->output->Data = Feed_Function(*this->input, Tanh);
	}
	else cout << "Wrong Parameter" << endl;// Weight or Bias or input
}

FunctionSigmoid::FunctionSigmoid()
{
	this->name = "Sigmoid";
}

void FunctionSigmoid::forward()
{
	if (this->input->Is_Grad) // Hidden layer or output
	{
		Act_Func Sigmoid("Sigmoid");
		this->output->Data = Feed_Function(*this->input, Sigmoid);
	}
	else cout << "Wrong Parameter" << endl;// Weight or Bias or input
}

FunctionFullyConnectWeight::FunctionFullyConnectWeight(Parameter * Weight, Parameter * bias)
{
	this->W = Weight;
	this->B = bias;
	this->name = "FCNN";
}

void FunctionFullyConnectWeight::forward()
{
	this->output->Data = this->W->Data.Tensor_2D * this->input->Data.Tensor_2D + this->B->Data.Tensor_2D;
}

void FunctionFullyConnectWeight::BackProp(Function & Pre_func, FunctionFullyConnectWeight & next_layer)
{
	Tensor De_func;
	Act_Func Back(Pre_func.name);
	De_func = Backward_Function(*Pre_func.input, Back);
	this->output->Delta = (Trans(next_layer.W->Weight.Tensor_2D) * next_layer.output->Delta.Tensor_2D)->*(De_func.Tensor_2D);
	this->B->Gradient = this->output->Delta;
	this->output->Gradient = (this->output->Delta.Tensor_2D) * (this->input->Data.Tensor_2D);
}
