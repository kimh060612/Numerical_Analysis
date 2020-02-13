#include <iostream>
#include "Function.h"

using namespace std;



int main()
{
	Matrix A(5,5);
	Matrix B(5,5), C;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			A.MAT[i][j] = (i + 1) * (j + 1);
			B.MAT[i][j] = 1;
		}
	}

	C = A + A; // 메모리 에러.
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << C.MAT[i][j] << "  ";
		}
		cout << endl;
	}

	return 0;
}