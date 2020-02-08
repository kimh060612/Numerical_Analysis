#include <iostream>
#include "Matrix.h"
#define INF 1001

using namespace std;

struct Theta
{
    Matrix STP;
    Matrix OP;
	vector<double> ISP;
};

vector<int> Create_Observation();
int Evaluate(Matrix STP, Matrix OP);
vector<int> Viterbi(Matrix STP, Matrix OP, Matrix ISP);
Theta Learning_HMM(Matrix OP);

int main()
{

    return 0;
}

int Evaluate(Matrix STP, Matrix OP, vector<double> ISP)
{

    int EVAL_DP[INF][INF] = {0,};
    int sum = 0;

    int T = OP.col, N = OP.row;
    for (int i = 0; i < N;i++)
    {
        EVAL_DP[1][i] = ISP[i]*OP.MAT[i][1];
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
            EVAL_DP[t][i] = sum*OP.MAT[i][t];
        }
    }

    for (int i = 0; i < N; i++)sum += EVAL_DP[T - 1][i];

    return sum;

}

int * Viterbi(Matrix STP, Matrix OP, vector<double> ISP)
{
    int Decoding_DP[INF][INF];
	int Decoding_index[INF][INF];

	int T = OP.col, N = OP.row;

	for (int i = 1; i <= N; i++)
	{
		Decoding_DP[1][i] = (ISP[i]) * (OP.MAT[i][1]);
	}

	for (int t = 2; t <= T; t++)
	{
		for (int i = 1; i <= N; i++)
		{
			int max = -987654321, k;
			for (int j = 1; i <= N; i++)
			{
				int Val = Decoding_DP[t - 1][j] * STP.MAT[j][i];
				if (Val > max)k = j;
			}

			Decoding_DP[t][i] = Decoding_DP[t - 1][k] * STP.MAT[k][i] * OP.MAT[i][t];
			Decoding_index[t][i] = k;
		}
	}

	int Q_hat[INF];

	Q_hat[T] = argmax_1d(Decoding_DP[T], 1, N);

	for (int t = T - 1; t >= 1; t--)
	{
		Q_hat[t] = Decoding_DP[t + 1][Q_hat[t + 1]];
	}

	return Q_hat;

}

Theta Learning_HMM(Matrix OP)
{
    
}