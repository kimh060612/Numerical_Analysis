#ifndef __PARAM_H__
#include "Tensor.h"

class Parameter
{
	// Parameter has two type
	// Trainable parameter: Weights, Bias
	// Non-Trainable Parameter: Input, Output, Hidden layer node
	// Hyper-parameter: learning rate, drop-out rate, layer Dimension etc...
	// Here we manage Trainable, Non-trainable param.
public:

	// 0:input 1: output or Hidden Layer that has Gradient 2: weight, 3: bias
	// 0: has Data, no Gradient
	// 1: has Data also Gradient
	// 2,3 : has Data no Gradient

	Tensor Gradient;
	Tensor Data;
	Tensor Weight;
	Tensor Bias;
	bool Is_Grad = true;
	bool Is_W_B = false;
	bool Is_last_Grad = false; // Last Gradient must be Calculated differently

	Parameter();
	Parameter(Parameter &a); 
	Parameter(int *A, bool isGrad); 
	Parameter(Matrix &Mat, bool isGrad); 
	Parameter(Tensor &Mat, bool isGrad); 
	Parameter(Matrix &Mat, int Weight_or_bias); 
	Parameter(Tensor &Mat, int Weight_or_bias);

	~Parameter();

};

#endif // !__PARAM_H__


#pragma once
