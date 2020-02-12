#include "Matrix.h"

class Tensor : public Matrix
{	
public:

	int Dim;
	int Depth_1;
	int Depth_2 = 0;
	int H, W;
	Matrix Tensor_2D;
	Matrix *Tensor_3D;
	Matrix **Tensor_4D;
	int *size;

	Tensor();
	Tensor(int W, int H);
	Tensor(int W, int H, int D);
	Tensor(int W, int H, int D1, int D2); // Maybe Input only
	Tensor(int *A);

	Tensor &operator=(Matrix op1);
	Tensor &operator=(Tensor op1);

	~Tensor();

};