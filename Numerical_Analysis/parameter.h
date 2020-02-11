#ifndef __PARAM_H__
#include "Tensor.h"

class Parameter
{
	// Parameter has two type
	// Trainable parameter: Weights, Bias
	// Non-Trainable Parameter: Input, Output, Hidden layer node
	// Hyper-parameter: learning rate, drop-out rate, layer Dimension etc...
	// Here we manage Trainable, Non-trainable param.
private:

	Tensor Gradient;
	Tensor Data;
	Tensor Weight;
	bool Is_Grad = true;
	bool Is_last_Grad = false;

public:

	Parameter(const Parameter &a); // constant
	Parameter(int *A, bool isGrad); // input, output
	Parameter(Matrix &Mat, bool isGrad); // bias, Hidden layer
	Parameter(Tensor &Mat, bool isGrad); // weight

	void Backword(Parameter &P);

	~Parameter();

};

#endif // !__PARAM_H__


#pragma once
