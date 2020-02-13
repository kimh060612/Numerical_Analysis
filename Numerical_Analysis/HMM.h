#ifndef __HMM_H__
#include "Matrix.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define INF 1001

using namespace std;

struct Theta
{
	Matrix STP;
	Matrix OP;
	double *ISP;
};

int *Create_Observation(Theta T);
double Evaluate(Matrix STP, Matrix OP, double * ISP, int *Observation);
int * Viterbi(Matrix STP, Matrix OP, double *ISP, int *Observation);
Theta Learning_HMM(int *Observation, int num_state, int learning_epoch, int Threshold);
Theta Initialize_Theta(int T, int N);
double * Random_Probability_Vector_Generator(int n);
Matrix Calc_Alpha(Theta Model, int T, int N, int *Observation);
Matrix Calc_Beta(Theta Model, int T, int N, int *Observation);
double element_product_Sum(double *A, double *B, int N);
double Over_Kappa(Matrix A, Matrix B, int t, int N, Theta Model, int *Observation);

double Evaluate(Matrix STP, Matrix OP, double *ISP, int *Observation)
{
	//double EVAL_DP[INF][INF] = { 0, };
	double sum = 0;
	int T = _msize(Observation)/sizeof(int), N = OP.row, M = OP.col;
	Matrix EVAL_DP(T,N);
	for (int i = 0; i < N; i++)
	{
		EVAL_DP.MAT[0][i] = ISP[i] * OP.MAT[i][Observation[0]];
	}

	for (int t = 1; t < T; t++)
	{
		for (int i = 0; i < N; i++)
		{
			double tmp = 0;
			for (int j = 0; j < N; j++)
			{
				tmp += EVAL_DP.MAT[t - 1][j] * STP.MAT[j][i];
			}
			EVAL_DP.MAT[t][i] = tmp * OP.MAT[i][Observation[t]];
		}
	}

	for (int i = 0; i < N; i++)sum += EVAL_DP.MAT[T - 1][i];

	return sum;
}

int *Viterbi(Matrix STP, Matrix OP, double *ISP, int *Observation)
{
	int T = _msize(Observation)/sizeof(int), N = OP.row, M = OP.col;
	Matrix Decoding_DP(T,N);
	Matrix Decoding_index(T, N);

	for (int i = 0; i < N; i++)
	{
		Decoding_DP.MAT[0][i] = ISP[i] * OP.MAT[i][Observation[0]];
	}

	for (int t = 1; t < T; t++)
	{
		for (int i = 0; i < N; i++)
		{
			int max = -987654321, k;
			for (int j = 0; i < N; i++)
			{
				int Val = Decoding_DP.MAT[t - 1][j] * STP.MAT[j][i];
				if (Val > max)k = j;
			}

			Decoding_DP.MAT[t][i] = Decoding_DP.MAT[t - 1][k] * STP.MAT[k][i] * OP.MAT[i][Observation[t]];
			Decoding_index.MAT[t][i] = k;
		}
	}

	int Q_hat[INF];

	Q_hat[T] = argmax_1d(Decoding_DP.MAT[T], 1, N);

	for (int t = T - 1; t > 0; t--)
	{
		Q_hat[t] = Decoding_DP.MAT[t + 1][Q_hat[t + 1]];
	}

	return Q_hat;

}

double * Random_Probability_Vector_Generator(int n)
{
	double C[INF] = { 0, };
	double sum = 0;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		C[i] = rand() % 1000;
		sum += C[i];
	}

	for (int i = 0; i <= n; i++)
	{
		C[i] = C[i] / sum;
	}

	return C;

}

Theta Initialize_Theta(int N, int M)
{
	Theta initial;

	double ** A;
	double ** B;
	double *PI = new double[N];

	A = new double*[N];
	B = new double*[N];

	for (int i = 0; i < N; i++)
	{
		double *Ran_initial = Random_Probability_Vector_Generator(N);
		A[i] = new double[N];
		for (int j = 0; j < N; j++)
		{
			A[i][j] = Ran_initial[j];
		}
	}

	for (int i = 0; i < N; i++)
	{
		double *Ran_initial = Random_Probability_Vector_Generator(N);
		B[i] = new double[M];
		for (int j = 0; j < M; j++)
		{
			B[i][j] = Ran_initial[j];
		}
	}

	double *Ran_initial = Random_Probability_Vector_Generator(N);
	for (int i = 0; i < N; i++)
	{
		PI[i] = Ran_initial[i];
	}

	initial.STP = A;
	initial.OP = B;
	initial.ISP = PI;

	return initial;

}

int *Create_Observation(Theta T)
{
	int *A;
	int b = 5;
	A = &b;
	return A;
}

Matrix Calc_Alpha(Theta Model, int T, int N, int *Observation)
{
	Matrix Alpha(T,N);


	for (int i = 0; i < N; i++)
	{
		Alpha.MAT[0][i] = Model.ISP[i] * Model.OP.MAT[i][Observation[0]];
	}

	for (int t = 1; t < T; t++)
	{
		for (int i = 0; i < N; i++)
		{
			int tmp = 0;
			for (int j = 0; j < N; j++)
			{
				tmp += Alpha.MAT[t - 1][j] * Model.STP.MAT[j][i];
			}
			Alpha.MAT[t][i] = tmp * Model.OP.MAT[i][Observation[t]];
		}
	}

	return Alpha;

}

Matrix Calc_Beta(Theta Model, int T, int N, int *Observation)
{

	Matrix Beta(T, N);

	for (int i = 0; i < N; i++)
	{
		Beta.MAT[T - 1][i] = 1;
	}

	for (int t = T - 2; t >= 0; t--)
	{
		for (int i = 0; i < N; i++)
		{
			int sum = 0;
			for (int j = 0; j < N; j++)
			{
				sum += Model.STP.MAT[j][i] * Model.OP.MAT[j][Observation[t]] * Beta.MAT[t + 1][j];
			}
			Beta.MAT[t][i] = sum;
		}
	}

	return Beta;

}

double element_product_Sum(double *A, double *B, int N)
{
	int sum = 0;

	for (int i = 0; i < N; i++)
	{
		sum += A[i] * B[i];
	}

	return sum;
}

double Over_Kappa(Matrix A, Matrix B, int t, int N, Theta Model, int *Observation)
{
	double Total_Sum = 0;

	for (int p = 0; p < N; p++)
	{
		double sum = 0;
		for (int q = 0; q < N; q++)
		{
			sum += A.MAT[t][p] * Model.STP.MAT[p][q] * Model.OP.MAT[q][Observation[t + 1]] * B.MAT[t + 1][q];
		}
		Total_Sum += sum;
	}

	return Total_Sum;
}

Theta Learning_HMM(int *Observation, int N, int M, int learning_epoch, int Threshold) // N: number of state
{
	int T = _msize(Observation)/sizeof(int); // time seq.
	Theta T_initial;
	Matrix Alpha(T,N);
	Matrix Beta(T, N);
	Matrix Gamma(T,N);
	double Kappa[INF][INF][100] = { 0, };
	double Probability_O_Theta[10001];

	T_initial = Initialize_Theta(N, M);

	Theta Model;
	Model = T_initial;

	for (int epoch = 1; epoch <= learning_epoch; epoch++)
	{
		// Step E
		Alpha = Calc_Alpha(Model, T, N, Observation);
		Beta = Calc_Beta(Model, T, N, Observation);

		for (int t = 0; t < T; t++)
		{
			for (int i = 0; i < N; i++)
			{
				double OSum = element_product_Sum(Alpha.MAT[t], Beta.MAT[t], N);
				Gamma.MAT[t][i] = Alpha.MAT[t][i] * Beta.MAT[t][i] / OSum;
			}
		}

		for (int t = 0; t < T; t++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					double OverSum = Over_Kappa(Alpha, Beta, t, N, Model, Observation);
					Kappa[t][i][j] = (Alpha.MAT[t][i] * Model.STP.MAT[i][j] * Model.OP.MAT[j][Observation[t + 1]] * Beta.MAT[t + 1][j]) / OverSum;
				}
			}
		}

		// Step M

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				double Sum_Gamma = 0, Sum_Kappa = 0;
				for (int k = 0; k < T - 1; k++)
				{
					Sum_Gamma += Gamma.MAT[k][i];
					Sum_Kappa += Kappa[k][i][j];
				}
				Model.STP.MAT[i][j] = Sum_Kappa / Sum_Gamma;
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				double Sum_Gamma_UP = 0, Sum_Gamma_Down = 0;
				for (int k = 0; k < T; k++)
				{
					Sum_Gamma_Down += Gamma.MAT[k][i];
					if (Observation[k] == j)Sum_Gamma_UP += Gamma.MAT[k][i];
				}
				Model.OP.MAT[i][j] = Sum_Gamma_UP / Sum_Gamma_Down;
			}
		}

		for (int i = 0; i < N; i++)
		{
			Model.ISP[i] = Gamma.MAT[1][i];
		}

		Probability_O_Theta[epoch] = Evaluate(Model.STP, Model.OP, Model.ISP, Observation);
		double Difference = Probability_O_Theta[epoch] - Probability_O_Theta[epoch - 1];
		if (Difference < Threshold)break;

	}

	return Model;
}


#endif // !__HMM_H__
#pragma once
