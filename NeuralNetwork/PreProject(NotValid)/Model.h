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
	// Gaussian Distribution, Xavier, Just Rand etc... ���߿� �߰��ϱ�
};

class Model // Model Class�� Update �ؾ��� parameter���� ������. Weight�� bias�� �����ϴ� �κ�.
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
	void Back_propagation(); // �������� �Ű�� ����
	void Compile();
	void Fit(double learning_rate, int total_epoch);

};

#endif // !__MODEL_H__
#pragma once
