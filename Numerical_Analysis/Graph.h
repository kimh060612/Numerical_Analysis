#ifndef __GRAPH_H__
#include <map>
#include "Function.h"

class Graph
{
public:

	Function *Layer_block; // N �� function�� ��� 1 layer block ����

	Graph(int type_Block);
	~Graph();

};

#endif // !__GRAPH_H__
#pragma once
