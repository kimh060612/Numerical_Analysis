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
				res.MAT[i][j] = F.Forward_Func(U.Data.Tensor_2D.MAT[i][j]);
			}
		}
		RES.Tensor_2D = res;
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
					res.Tensor_3D[d].MAT[i][j] = F.Forward_Func(U.Data.Tensor_3D[d].MAT[i][j]);
				}
			}
		}
		RES = res;
	}

	else if (N == 4) // Delete This if-state when needed  
	{
		Tensor res(U.Data.size);
		for (int d1 = 0; d1 < U.Data.size[2]; d1++)
		{
			for (int d2 = 0; d2 < U.Data.size[3]; d2++)
			{
				for (int i = 0; i < U.Data.size[0]; i++)
				{
					for (int j = 0; j < U.Data.size[1]; j++)
					{
						res.Tensor_4D[d1][d2].MAT[i][j] = F.Forward_Func(U.Data.Tensor_4D[d1][d2].MAT[i][j]);
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
	this->output->Data = this->W->Data * this->input->Data + this->B->Data;
}

void FunctionFullyConnectWeight::BackProp(Function & Pre_func)
{

}
