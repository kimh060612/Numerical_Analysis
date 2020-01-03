#include <iostream>
#include "Matrix.h"
#define INF 1001

using namespace std;

int Decoding_DP[INF][INF];
int Evaluate(Matrix STP, Matrix OP);

int main()
{

    return 0;
}

int Evaluate(Matrix STP, Matrix OP, vector<int> ISP)
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