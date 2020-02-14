#include <iostream>
#include "Function.h"

using namespace std;

int main()
{
	Matrix A(5,5);
	Matrix B(5,5), C(3,3);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			A.MAT[i][j] = (i + 1) * (j + 1);
			B.MAT[i][j] = 1;
		}
	}

	C.MAT[0][0] = 3;
	C.MAT[0][1] = 5;
	C.MAT[0][2] = 3;
	C.MAT[1][0] = 6;
	C.MAT[1][1] = 8;
	C.MAT[1][2] = 1;
	C.MAT[2][0] = 1;
	C.MAT[2][1] = 2;
	C.MAT[2][2] = 4;
	
	C.show();

	cout << Determinant(C) << endl;
	Matrix D;
	D = Inverse(C);
	D.show();

	Matrix E;

	E = D * C;
	E.show();

	for (int i = 0; i < 2; i++)
	{
		cout << i << endl;
	}

	return 0;
}