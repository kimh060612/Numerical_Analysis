#ifndef __FUNC_H__
#include "parameter.h"
#include <string>

class Act_Func
{
public:
	// Feed forward Activation Func.
	double Sigmoid(double x)
	{
		return 1. / (1. + exp(-x));
	}
	double Tanh(double x)
	{
		return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
	}
	double ReLU(double x)
	{
		return x > 0 ? x : 0;
	}
	double Identity(double x)
	{
		return x;
	}
	double *Softmax(double *OUT)
	{
		int N = sizeof(OUT) / sizeof(double);
		double *Pr = new double[N];
		double sum = 0;
		for (int i = 0; i < N; i++)
		{
			sum += OUT[i];
		}
		for (int i = 0; i < N; i++)
		{
			Pr[i] = OUT[i] / sum;
		}
		return Pr;
	}
	// Derivative of Activation Func.
	double De_Sigmoid(double x)
	{
		double tmp = Sigmoid(x);
		return tmp * (1. - tmp);
	}
	double De_tanh(double x)
	{
		double tmp = Tanh(x);
		return 1. - tmp * tmp;
	}
	double De_ReLU(double x)
	{
		return x > 0 ? 1. : 0;
	}
	double De_Identity(double x)
	{
		return 1.;
	}
	
	string name;

	Act_Func(string Name)
	{
		this->name = Name;
	}

	double Forward_Func(double x)
	{
		if (this->name == "Sigmoid")return this->Sigmoid(x);
		else if (this->name == "Tanh")return this->Tanh(x);
		else if (this->name == "ReLU")return this->ReLU(x);
		else if (this->name == "Identity")return this->Identity(x);
	}
	double *Forward_vector_Function(double *X)
	{
		if (this->name == "Softmax")return this->Softmax(X);
	}

	double Backward_Func(double x)
	{
		if (this->name == "Sigmoid")return this->De_Sigmoid(x);
		else if (this->name == "Tanh")return this->De_tanh(x);
		else if (this->name == "ReLU")return this->De_ReLU(x);
		else if (this->name == "Identity")return this->De_Identity(x);
	}

	//Softmax? 

};

// convolution 연산, correlation 연산, Fully Connected, Activation, etc... 의 Forward, back-propagation 을 진행하는 class.

class Function
{
public:

	Function();
	Function(Parameter *U, Parameter *Z);

	Parameter *input; // Function input
	Parameter *output; // Function output

	string name;

	virtual void forward();
	virtual void Backprop(Function &Pre_func);
};

class FunctionFullyConnectWeight : public Function
{
public:
	Parameter *W, *B;
	// Weight의 Dimension == 2, Bias 의 Dim은 1, U의 N*1
	FunctionFullyConnectWeight(Parameter *Weight, Parameter *bias);
	void forward();
	void BackProp(Function &Pre_func, FunctionFullyConnectWeight & next_layer);
	// Gradient Matrix를 구하는 부분 Update는 Optimizer에서 진행함. Model이 이러한 Class들을 총 병합해서 관리함.
};

class FunctionIdentity : public Function
{
public:
	FunctionIdentity();
	void forward();
};

class FunctionReLU : public Function
{
public:
	FunctionReLU();
	void forward();
};

class FunctionTanh : public Function
{
public:
	FunctionTanh();
	void forward();
};

class FunctionSigmoid : public Function
{
public:
	FunctionSigmoid();
	void forward();
};



#endif // !__FUNC_H__
#pragma once
