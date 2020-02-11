#include "Matrix.h"
#include <memory.h>
#include <math.h>

class Tensor : public Matrix
{
private :
	int Dim;
	int Depth_1;
	int Depth_2;
	int H, W;
public:

	Matrix Tensor_2D;
	Matrix *Tensor_3D;
	Matrix **Tensor_4D;
	
	Tensor();
	Tensor(int W, int H);
	Tensor(int W, int H, int D);
	Tensor(int W, int H, int D1, int D2);
	Tensor(int *A);

	Tensor &operator=(Matrix &op1);
	Tensor &operator=(Tensor &op1);

	~Tensor();

};