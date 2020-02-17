#include "Model.h"
#include <ctime>

Function Act_det(string N)
{
	if (N == "ReLu")
	{
		FunctionReLU R;
		return R;
	}
	else if (N == "Sigmoid")
	{
		FunctionSigmoid S;
		return S;
	}
	else if (N == "Tanh")
	{
		FunctionTanh T;
		return T;
	}
	else if (N == "Identity")
	{
		FunctionIdentity I;
		return I;
	}
}

Model::Model()
{
	this->Layer_num = 0;
	this->Up_initial_Algo = "Psuedo_rand";
}

Model::Model(string initial)
{
	this->Up_initial_Algo = initial;
}

Model::~Model()
{
}

void Model::Put_FCNN(string N, Parameter & Input, Parameter & output, int * Weight_Size, string act_name)
{// Compile 빼고 여기서 그냥 확인시켜?
	this->Layer_num++;
	int bias_size[2]; bias_size[0] = Weight_Size[0]; bias_size[1] = 1;
	Tensor Weight_(Weight_Size);
	Tensor Bias_(bias_size);
	Parameter w(Weight_,2), b(Bias_, 3);
	UpdateParam Up;
	Up.weight = w; Up.bias = b;
	Up.Parameter_Initialize("Psuedo_rand", false);
	this->Update.push_back(Up);
	FunctionFullyConnectWeight F1(&this->Update[this->Layer_num-1].weight, &this->Update[this->Layer_num - 1].bias);
	Function Act = Act_det(act_name);

	F1.input = &Input;
	Act.input = &output;

	Graph FCNN(0,F1,Act);
	this->graph[N] = &FCNN;

}

void Model::Feed_forward()
{
	for (auto &g : this->graph)
	{
		g.second->Feed_forward();
	}
}

void Model::Back_propagation()
{// Last Layer에 대한 것을 생각하자. 
	map<string, Graph*>::reverse_iterator rit;
	bool Is_last = true;
	for (rit = this->graph.rbegin(); rit != this->graph.rend(); rit++)
	{
		if (rit->second->Block_type == 0) { rit->second->Back_propagation(); }
		if (Is_last)Is_last = false;
	}
	
}

void Model::Compile()
{// 아오 씨발 너무 스케일이 커져 버렸네

}

void Model::Fit(double learning_rate, int total_epoch)
{// 이눔이 training을 시키는데 야발 Optimizer를 넣어야 할 텐데

}

void UpdateParam::Parameter_Initialize(string init, bool another_bias_init)// Weight & Bias initialize.
{
	if (init == "Pseudo_rand")
	{
		srand((size_t)time(NULL));
		if (this->weight.Weight.Dim == 2)
		{
			int *size_ = this->weight.Weight.size;

			for (int i = 0; i < size_[0]; i++)
			{
				for (int j = 0; j < size_[1]; j++)
				{
					this->weight.Weight(i, j) = (rand()/((double)RAND_MAX)*2.) - 1;
				}
			}
		}
		else if (this->weight.Weight.Dim == 3)
		{
			int *size_ = this->weight.Weight.size;
			for (int d = 0; d < size_[2]; d++)
			{
				for (int i = 0; i < size_[0]; i++)
				{
					for (int j = 0; j < size_[1]; j++)
					{
						this->weight.Weight(i, j, d) = (rand() / ((double)RAND_MAX)*2.) - 1;
					}
				}
			}
		}
		else if (this->weight.Weight.Dim == 4)
		{
			int *size_ = this->weight.Weight.size;
			for (int d2 = 0; d2 < size_[3]; d2++)
			{
				for (int d = 0; d < size_[2]; d++)
				{
					for (int i = 0; i < size_[0]; i++)
					{
						for (int j = 0; j < size_[1]; j++)
						{
							this->weight.Weight(i, j, d, d2) = (rand() / ((double)RAND_MAX)*2.) - 1;
						}
					}
				}
			}
		}
	}
}

