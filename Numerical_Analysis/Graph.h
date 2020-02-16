#ifndef __GRAPH_H__
#include <map>
#include "Function.h"

// Conv layer, FCNN layer, Pooling ...etc Store 1 structure to compute Forward & Backwrad
class Graph // Store 1 Block of Computational Graph
{
public:

	Function *Layer_block; // N 개 function을 묶어서 1 layer block 구성
	int Block_type;

	Graph(int type_Block, FunctionFullyConnectWeight &F1, Function &Act); // type 0, FCNN Graph Layer_block[0] :: FunctionFullyConnectedWeight, Layer_block[1] :: Activation Function
	//Graph(int type_Block); // type 1, FCNN Graph
	//Graph(int type_Block); // type 2, FCNN Graph
	//Graph(int type_Block); // type 3, FCNN Graph
	~Graph();

	void Feed_forward();
	void Back_propagation();

};

#endif // !__GRAPH_H__
#pragma once
