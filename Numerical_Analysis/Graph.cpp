#include "Graph.h"

// tpye 0: Fully Connected layer
// type 1: Convolution Layer
// type 2: Pooling layer
// type 3: BPTT RNN layer 1 hidden
// type 4: LSTM
// type 5: GRU
// and so on...

Graph::Graph(int type_Block, FunctionFullyConnectWeight &F1, Function *Act)
{
	if (type_Block != 0) cout << "Type Fail!" << endl;
	this->Layer_block = new Function[2];
	this->Block_type = type_Block;

	this->Layer_block[0] = F1;
	this->Layer_block[1] = (*Act);

}

Graph::Graph(int type_Block, Function *Error)
{
	if (type_Block != 1) cout << "Type Fail!" << endl;
	this->Layer_block = new Function[1];
	this->Block_type = type_Block;

	this->Layer_block[0] = *Error;

}

Graph::~Graph()
{
	if (this->Block_type == 0 || this->Block_type == 1)delete[] this->Layer_block;
}

void Graph::Feed_forward()
{
	if (this->Block_type == 0)
	{
		// U^(l) has Delta
		this->Layer_block[0].forward(); // Weight Sum, input: Z^(l-1) output: U^(l)
		this->Layer_block[1].forward(); // Activation input: U^(l), output: Z^(l)
	}
}

void Graph::Back_propagation()
{
	if (this->Block_type == 0)
	{

	}
	if (this->Block_type == 1)
	{

	}
}
