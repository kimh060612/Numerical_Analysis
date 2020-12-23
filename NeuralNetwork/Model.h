#ifndef __MODEL_H__
#include <map>
#include <vector>
#include "Graph.h"
#include "parameter.h"

using std::vector;

class UpdateParam : private Parameter
{
public:
	Parameter weight;
	Parameter bias;
	UpdateParam()
	{
		weight.Is_W_B = true;
		weight.Is_Grad = false;
		bias.Is_W_B = true;
		bias.Is_Grad = false;
	}
	void Parameter_Initialize(string init, bool another_bias_init);
	// Gaussian Distribution, Xavier, Just Rand etc... 나중에 추가하기
};

class Model // Model Class가 Update 해야할 parameter들을 저장함. Weight와 bias를 저장하는 부분.
{
private:
	int Layer_num;
public:
	map<string, Graph*> graph;
	vector<UpdateParam> Update;
	string Up_initial_Algo; // ?

	Model();
	Model(string initial);
	~Model();
	
	void Put_FCNN(string N, Parameter &Input, Parameter &output, int *Weight_Size, string act_name); 
	// Weight_size dim == 2, Fully Connected Input: &Input, Activation Input(Fully Connected output): &output
	
	void Feed_forward();
	void Back_propagation(); // 본격적인 신경망 연산
	void Compile();
	void Fit(double learning_rate, int total_epoch);

};

#endif // !__MODEL_H__
#pragma once
