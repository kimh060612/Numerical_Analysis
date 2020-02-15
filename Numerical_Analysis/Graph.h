#ifndef __GRAPH_H__
#include <map>
#include "Function.h"

// Conv layer, FCNN layer, Pooling ...etc Store 1 structure to compute Forward & Backwrad
class Graph // Store 1 Block of Computational Graph
{
private:
	int Block_type;
public:

	Function *Layer_block; // N �� function�� ��� 1 layer block ����

	Graph(int type_Block);
	~Graph();

};

#endif // !__GRAPH_H__
#pragma once
