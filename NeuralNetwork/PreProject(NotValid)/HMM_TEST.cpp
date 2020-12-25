#include <iostream>
#include <fstream>
#include "HMM.h"

using namespace std;

ifstream fin;
ofstream fout;

int main()
{
	fin.open("input.txt");
	fout.open("output.txt");

	int num_state, Time, num_observation;
	fin >> num_state >> num_observation;
	Matrix A(num_state, num_state);
	Matrix B(num_state, num_observation);
	double *PI = new double[num_state]();
	for (int i = 0; i < num_state; i++)
	{
		for (int j = 0; j < num_state; j++)
		{
			fin >> A.MAT[i][j];
		}
	}
	for (int i = 0; i < num_state; i++)
	{
		fin >> PI[i];
	}
	for (int i = 0; i < num_state; i++)
	{
		for (int j = 0; j < num_observation; j++)
		{
			fin >> B.MAT[i][j];
		}
	}

	fin >> Time;
	int *Observ1 = new int[Time];
	for (int i = 0; i < Time; i++)
	{
		fin >> Observ1[i];
	}
	int Time2;
	fin >> Time2;
	int *Observ2 = new int[Time2];
	for (int i = 0; i < Time2; i++)
	{
		fin >> Observ2[i];
	}
	
	double Eval;
	Eval = Evaluate(A,B, PI, Observ1);
	cout << "일주일 연속 쇼핑만 할 확률: " << Eval << endl;

	int *State;
	State = Viterbi(A, B, PI, Observ2);
	cout << "산책, 산책, 청소를 했을때 날씨는?" << endl;
	for (int i = 0; i < Time2; i++)
	{
		cout << State[i] << " ";
	}
	cout << endl;

	delete[]Observ1;
	delete[]Observ2;

	fin.close();
	fout.close();
	return 0;
}