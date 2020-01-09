#include <iostream>
#include <math.h>
#include <vector>
#define det(a, b) (a+b)%2 == 0 ? 1 : -1
#define INF 987654321

using namespace std;

class Matrix
{
public:
    int row, col;
    vector<vector<int>> MAT; // type change needed! template type.

    Matrix(int R, int C);
    Matrix(vector<vector<int>> MAT_);

    Matrix operator+(Matrix &op1);
    Matrix operator-(Matrix &op1);
    Matrix operator*(Matrix &op1);
    Matrix operator*(int Constant);

    void Identity();
    void show();
};

Matrix::Matrix(int R, int C)
{
    this->row = R;
    this->col = C;

    this->MAT.resize(R);
    for (int i = 0; i < R; i++)
    {
        this->MAT[i].assign(C, 0);
    }
}

Matrix::Matrix(vector<vector<int>> MAT_)
{
    if (MAT_.size() == 0)
    {
        this->MAT = MAT_;
    }
    else
    {
        this->MAT = MAT_;
        this->row = this->MAT.size();
        this->col = this->MAT[0].size();
    }
    
}

Matrix Matrix::operator+(Matrix &op1)
{
    try
    {
        if (this->row != op1.row || this->col != op1.col)
        {
            int e = 0;
            throw e;
        }

        Matrix RES(this->row, this->col);

        for (int i = 0; i <= this->row; i++)
        {
            for (int j = 0; j <= this->col; j++)
            {
                RES.MAT[i][j] = this->MAT[i][j] + op1.MAT[i][j];
            }
        }

        return RES;
    }
    catch (const int e)
    {
        cout << "Error: The shape of matrix doen't match!" << endl;
    }
}

Matrix Matrix::operator-(Matrix &op1)
{
    try
    {
        if (this->row != op1.row || this->col != op1.col)
        {
            int e = 0;
            throw e;
        }

        Matrix RES(this->row, this->col);

        for (int i = 0; i <= this->row; i++)
        {
            for (int j = 0; j <= this->col; j++)
            {
                RES.MAT[i][j] = this->MAT[i][j] - op1.MAT[i][j];
            }
        }

        return RES;
    }
    catch (const int e)
    {
        cout << "Error: The shape of matrix doen't match!" << endl;
    }
}

Matrix Matrix::operator*(Matrix &op1)
{

    try
    {
        if (this->col != op1.row)
        {
            int e = 0;
            throw e;
        }

        Matrix RES(this->row, op1.col);

        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < op1.col; j++)
            {
                for (int k = 0; k < this->col; k++)
                {
                    RES.MAT[i][j] += this->MAT[i][k] * op1.MAT[k][j];
                }
            }
        }

        return RES;
    }
    catch (const std::exception &e)
    {
        cout << "Error: The shape of matrix doen't match!" << endl;
    }
}

Matrix Matrix::operator*(int Constant)
{

    Matrix RES(this->row, this->col);

    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < this->col; j++)
        {
            RES.MAT[i][j] = Constant * this->MAT[i][j];
        }
    }

    return RES;
}

void Matrix::show()
{
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < this->col; j++)
        {
            cout << this->MAT[i][j] << "  ";
        }
        cout << endl;
    }
}

void Matrix::Identity()
{
    try
    {
        if (this->col != this->row)
        {
            int e = 1;
            throw e;
        }
        else
        {
            int n = this->row;
            for (int i = 0; i < n;i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (i == j)
                    {
                        this->MAT[i][j] = 1;
                    }
                    else
                    {
                        this ->MAT[i][j] = 0;
                    }
                    
                }
            }
        }
        
    }
    catch(int e)
    {
        cout << "Cannot make Identity" << endl;
    }
    
}

double Determinant(Matrix Target) // Same with Inverse_Matrix.
{
	try
	{
		int n;
		double Det = 0;
		if (Target.row != Target.col){ int e = 1; throw(e); }
		n = Target.col;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Det += (det(i, j))*(Cofactor(Target, i, j))*Target.MAT[i][j];
			}
		}
		return Det;
	}
	catch(int e)
	{
		cout << "Cannot get the Determinant" << endl;
	}
}

Matrix Inverse(Matrix target)
{

}

double Cofactor(Matrix target, int p, int q)
{
	try
	{
		int n;
		vector<vector<int>> RES;
		if (target.row != target.col){ int e = 1; throw(e); }
		else
		{

		}
	}
	catch(int e)
	{

	}
}



