#include <iostream>
#include <cmath>
#define MAX 101

using namespace std;

int n;
double A[MAX], X[MAX];

double eval(double t)
{
	double temp;
	temp = A[n];
	for (int i = n - 1; i >= 1; i--)
	{
		temp = temp * (t - X[i]) + A[i];
	}
	return temp;
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> X[i] >> A[i];
	}

	for (int j = 2; j <= n; j++)
	{
		for (int i = n; i >= j; i--)
		{
			A[i] = (A[i] - A[i - 1]) / (X[i] - X[i - j + 1]);
		}
	}

	cout << eval(-1) << endl;

	return 0;
}