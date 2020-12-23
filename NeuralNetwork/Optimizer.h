#ifndef __OPTIMIZER_H__
#include "Graph.h"

class Optimizer
{
public:
	Function *Loss;
	string Optimizer_tpye;
	Optimizer();
	~Optimizer();
};

class Normal_Gradient_Descent : public Optimizer // 1 Compute, 1 
{

};

class SGD : public Optimizer
{

};

#endif // !__OPTIMIZER_H__
#pragma once
