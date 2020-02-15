#ifndef __MODEL_H__
#include <map>
#include "Graph.h"
#include "parameter.h"

class UpdateParam : public Parameter
{
public:
	Parameter Param;
	UpdateParam()
	{
		Param.Is_W_B = true;
		Param.Is_Grad = false;
	}
};

class Model
{
public:
	map<string, Graph*> graph;
	UpdateParam *Update;

	Model();
	~Model();
	
	void Put_FCNN(string N, Parameter &Input, Parameter &output, double *Weight_Size, string act_name); // Weight_size dim == 2
	

	void Compile();
	void Fit(double learning_rate);

};

#endif // !__MODEL_H__
#pragma once
