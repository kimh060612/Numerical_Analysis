#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"
#define INF 1001

using namespace std;

struct Theta
{
    Matrix STP;
    Matrix OP;
	vector<double> ISP;
};

vector<int> Create_Observation(Theta T);
double Evaluate(Matrix STP, Matrix OP, vector<double> ISP, vector<double> Observation);
int * Viterbi(Matrix STP, Matrix OP,vector<double> ISP, vector<double> Observation);
Theta Learning_HMM(vector<double> Observation, int num_state, int learning_epoch, int Threshold);
Theta Initialize_Theta(int T, int N);
double * Random_Probability_Vector_Generator(int n);
double (*Calc_Alpha(Theta Model))[INF];
double (*Calc_Beta(Theta Model))[INF];
double element_product_Sum(double *A, double *B, int N);
double Over_Kappa(double(*A)[INF], double(*B)[INF], int t, int N, Theta Model);

int main()
{

    return 0;
}

double Evaluate(Matrix STP, Matrix OP, vector<double> ISP, vector<double> Observation)
{

    double EVAL_DP[INF][INF] = {0,};
    double sum = 0;

    int T = Observation.size(), N = OP.row;
    for (int i = 0; i < N;i++)
    {
        EVAL_DP[0][i] = ISP[i]*OP.MAT[i][Observation[0]];
    }

    for (int t = 1; t < T; t++)
    {
        for (int i = 0; i < N; i++)
        {
            int tmp = 0;
            for (int j = 0; j < N; j++)
            {
                tmp += EVAL_DP[t-1][j]*STP.MAT[j][i];
            }
            EVAL_DP[t][i] = tmp*OP.MAT[i][Observation[t]];
        }
    }

    for (int i = 0; i < N; i++)sum += EVAL_DP[T - 1][i];

    return sum;

}

int *Viterbi(Matrix STP, Matrix OP, vector<double> ISP, vector<double> Observation)
{
	double Decoding_DP[INF][INF];
	double Decoding_index[INF][INF];

	int T = Observation.size(), N = OP.row;

	for (int i = 0; i < N; i++)
	{
		Decoding_DP[0][i] = (ISP[i]) * (OP.MAT[i][Observation[0]]);
	}

	for (int t = 1; t < T; t++)
	{
		for (int i = 0; i < N; i++)
		{
			int max = -987654321, k;
			for (int j = 0; i < N; i++)
			{
				int Val = Decoding_DP[t - 1][j] * STP.MAT[j][i];
				if (Val > max)k = j;
			}

			Decoding_DP[t][i] = Decoding_DP[t - 1][k] * STP.MAT[k][i] * OP.MAT[i][Observation[t]];
			Decoding_index[t][i] = k;
		}
	}

	int Q_hat[INF];

	Q_hat[T] = argmax_1d(Decoding_DP[T], 1, N);

	for (int t = T - 1; t > 0; t--)
	{
		Q_hat[t] = Decoding_DP[t + 1][Q_hat[t + 1]];
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

Theta Initialize_Theta(int T, int N)
{
	Theta initial;

	vector<vector<double>> A(N);
	vector<vector<double>> B(N);
	vector<double> PI(N, 0);

	for (int i = 0; i < N; i++)
	{
		double *Ran_initial = Random_Probability_Vector_Generator(N);
		A[i].assign(N, 0);
		for (int j = 0; j < N; j++)
		{
			A[i][j] = Ran_initial[j];
		}
	}

	for (int i = 0; i < T; i++)
	{
		double *Ran_initial = Random_Probability_Vector_Generator(N);
		B[i].assign(T, 0);
		for (int j = 0; j < N; j++)
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

vector<int> Create_Observation(Theta T)
{
	return vector<int>();
}

double (* Calc_Alpha(Theta Model, int T, int N, vector<double> Observation))[INF]
{
	double Alpha[INF][INF];

	for (int i = 0; i < N; i++)
	{
		Alpha[0][i] = Model.ISP[i] * Model.OP.MAT[i][Observation[0]];
	}

	for (int t = 1; t < T; t++)
	{
		for (int i = 0; i < N; i++)
		{
			int tmp = 0;
			for (int j = 0; j < N; j++)
			{
				tmp += Alpha[t - 1][j] * Model.STP.MAT[j][i];
			}
			Alpha[t][i] = tmp * Model.OP.MAT[i][Observation[t]];
		}
	}

	return Alpha;

}

double(* Calc_Beta(Theta Model, int T, int N, vector<double> Observation))[INF]
{

	double Beta[INF][INF];

	for (int i = 0; i < N; i++)
	{
		Beta[T - 1][i] = 1;
	}

	for (int t = T - 2; t >= 0; t--)
	{
		for (int i = 0; i < N; i++)
		{
			int sum = 0;
			for (int j = 0; j < N; j++)
			{
				sum += Model.STP.MAT[j][i] * Model.OP.MAT[j][Observation[t]] * Beta[t + 1][j];
			}
			Beta[t][i] = sum;
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

double Over_Kappa(double (*A)[INF],double (*B)[INF], int t,int N, Theta Model, vector<double> Observation)
{
	double Total_Sum = 0;

	for (int p = 0; p < N; p++)
	{
		double sum = 0;
		for (int q = 0; q < N; q++)
		{
			sum += A[t][p] * Model.STP.MAT[p][q] * Model.OP.MAT[q][Observation[t + 1]] * B[t + 1][q];
		}
		Total_Sum += sum;
	}

	return Total_Sum;
}

Theta Learning_HMM(vector<double> Observation, int num_state, int learning_epoch, int Threshold)
{
	int T = Observation.size();
	Theta T_initial;
	double (*Alpha)[INF];
	double (*Beta)[INF];
	double Gamma[INF][INF] = { 0, };
	double Kappa[INF][INF][100] = { 0, };
	double Probability_O_Theta[10001];

	T_initial = Initialize_Theta(T, num_state);

	int N = num_state;

	Theta Model;
	Model = T_initial;

	for (int epoch = 1; epoch <= learning_epoch; epoch++)
	{
		// Step E
		Alpha = Calc_Alpha(Model, T, N, Observation);
		Beta = Calc_Beta(Model, T ,N, Observation);

		for (int t = 0; t < T; t++)
		{
			for (int i = 0; i < N; i++)
			{
				double OSum = element_product_Sum(Alpha[t], Beta[t], N);
				Gamma[t][i] = Alpha[t][i] * Beta[t][i] / OSum;
			}
		}

		for (int t = 0; t < T; t++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					double OverSum = Over_Kappa(Alpha, Beta, t, N, Model);
					Kappa[t][i][j] = (Alpha[t][i] * Model.STP.MAT[i][j] * Model.OP.MAT[j][t + 1] * Beta[t + 1][j]) / OverSum;
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
					Sum_Gamma += Gamma[k][i];
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
					Sum_Gamma_Down += Gamma[k][i];
					if (Observation[k] == j)Sum_Gamma_UP += Gamma[k][i];
				}
				Model.OP.MAT[i][j] = Sum_Gamma_UP / Sum_Gamma_Down;
			}
		}

		for (int i = 0; i < N; i++)
		{
			Model.ISP[i] = Gamma[1][i];
		}

		Probability_O_Theta[epoch] = Evaluate(Model.STP, Model.OP, Model.ISP, Observation);
		double Difference = Probability_O_Theta[epoch] - Probability_O_Theta[epoch - 1];
		if (Difference < Threshold)break;

	}

	return Model;
}


