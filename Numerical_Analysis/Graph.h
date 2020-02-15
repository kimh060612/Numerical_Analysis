#ifndef __GRAPH_H__
#include <map>
#include "Function.h"

// Conv layer, FCNN layer, Pooling ...etc Store 1 structure to compute Forward & Backwrad
class Graph // Store 1 Block of Computational Graph
{
private:
	int Block_type;
public:

	Function *Layer_block; // N 개 function을 묶어서 1 layer block 구성

	Graph(int type_Block); // type 0, FCNN Graph
	//Graph(int type_Block); // type 1, FCNN Graph
	//Graph(int type_Block); // type 2, FCNN Graph
	//Graph(int type_Block); // type 3, FCNN Graph
	~Graph();

	void Feed_forwar();
	void Back_propagation();

};

#endif // !__GRAPH_H__
#pragma once
