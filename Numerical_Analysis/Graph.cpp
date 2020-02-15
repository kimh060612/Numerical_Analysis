#include "Graph.h"

Graph::Graph(int type_Block)
{
	// tpye 0: Fully Connected layer
	// type 1: Convolution Layer
	// type 2: Pooling layer
	// type 3: BPTT RNN layer 1 hidden
	// type 4: LSTM
	// type 5: GRU
	// and so on...

	if (type_Block == 0)
	{
		this->Layer_block = new Function[2];
		this->Block_type = type_Block;
	}

}

Graph::~Graph()
{
	if (this->Block_type == 0)delete[] this->Layer_block;

}
