#include <iostream>
//#include "Function.h"
#include <ctime>

using namespace std;

int main()
{
	/*
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
	

	Matrix A(5,1), B(1,6);
	Matrix C;

	A(0, 0) = 1;
	A(1, 0) = 2;
	A(2, 0) = 3;
	A(3, 0) = 4;
	A(4, 0) = 5;
	A.show();
	cout << endl;
	B(0, 0) = 1;
	B(0, 1) = 2;
	B(0, 2) = 3;
	B(0, 3) = 4;
	B(0, 4) = 5;
	B(0, 5) = 6;
	B.show();
	cout << endl;

	C = A * B;
	C.show();
	*/

	srand((unsigned int)time(NULL));
	double avg_index = 0;

	for (int i = 0; i < 500; i++)
	{
		avg_index += (double)((rand() % 6) + 1.);
	}
	avg_index /= 500.;

	cout << avg_index << endl;

	return 0;
}