#include <math.h>
#include <vector>

using namespace std;

class Matrix 
{
public:
    int row, col;
    vector<vector<int>> MAT;

    Matrix(int R, int C);

    Matrix operator + (Matrix& op1);
    Matrix operator - (Matrix& op1);
    Matrix operator * (Matrix& op1);
    Matrix operator * (int Constant);


};

Matrix::Matrix(int R, int C)
{
    this->row = R;
    this->col = C;
       
    this->MAT.resize(R);
    for (int i = 0; i < R; i++)
    {
        this->MAT[i].assign(C,0);
    }

}

Matrix Matrix::operator+ (Matrix& op1)
{
    if (this->row != op1.row || this->col != op1.col)
    {
        cout << "Error: The shape of matrix doen't match!" << endl;
        return;
    }

    Matrix RES(this->row, this->col);

    for (int i = 0; i <= this->row; i++)
    {
        for(int j = 0; j <= this->col; j++)
        {
            RES.MAT[i][j] = this->MAT[i][j] + op1.MAT[i][j];
        }
    }

    return RES;
}

Matrix Matrix::operator- (Matrix& op1)
{
    if (this->row != op1.row || this->col != op1.col)
    {
        cout << "Error: The shape of matrix doen't match!" << endl;
        return;
    }

    Matrix RES(this->row, this->col);

    for (int i = 0; i < this->row; i++)
    {
        for(int j = 0; j < this->col; j++)
        {
            RES.MAT[i][j] = this->MAT[i][j] - op1.MAT[i][j];
        }
    }
    
    return RES;
}

Matrix Matrix::operator* (Matrix& op1)
{
    if (this->col != op1.row)
    {
        cout << "Error: The shape of matrix doen't match!" << endl;
        return;
    }

    Matrix RES(this->row, op1.col);

    for(int i = 0; i < this->row; i++)
    {
        for(int j = 0; j < op1.col; j++)
        {
            for(int k = 0; k < this->col; k++)
            {
                RES.MAT[i][j] += this->MAT[i][k]*op1.MAT[k][j];
            }
        }
    }

    return RES;
}

Matrix Matrix::operator * (int Constant)
{
    
    Matrix RES(this->row, this->col);

    for (int i = 0; i < this->row; i++)
    {
        for(int j = 0; j < this->col; j++)
        {
            RES.MAT[i][j] = Constant*this->MAT[i][j];
        }
    }
    
    return RES;
}