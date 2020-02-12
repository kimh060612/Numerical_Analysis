#ifndef __GRAPH_H__
#include <map>
#include "Function.h"

class Graph
{
public:

	Function *Layer_block; // N 개 function을 묶어서 1 layer block 구성

	Graph(int type_Block);
	~Graph();

};

#endif // !__GRAPH_H__
#pragma once
