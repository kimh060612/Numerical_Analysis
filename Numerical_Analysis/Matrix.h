#include <math.h>
#include <vector>

class Matrix 
{
public:
    int row, col;
    std::vector<std::vector<int>> MAT;

    Matrix(int R, int C);

};

Matrix::Matrix(int R, int C)
{
    this->row = R;
    this->col = C;   
}