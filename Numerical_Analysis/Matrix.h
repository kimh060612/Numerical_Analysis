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
    vector<vector<double>> MAT;

    Matrix(int R, int C);
    Matrix(vector<vector<double>> MAT_);

    Matrix operator+(Matrix &op1);
    Matrix operator-(Matrix &op1);
    Matrix operator*(Matrix &op1);
    Matrix operator*(int Constant);

	double EigenValue();
	Matrix EigenVector();
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

Matrix::Matrix(vector<vector<double>> MAT_)
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
		Matrix SUBMAT(n - 1, n - 1);
		if (n == 2) return (Target.MAT[0][0]*Target.MAT[1][1] - Target.MAT[0][1]*Target.MAT[1][0]);
		else
		{
			for (int c = 0; c < n; c++)
			{
				int subi = 0;
				for (int i = 1; i < n; i++)
				{
					int subj = 0;
					for (int j = 0; j < n; j++)
					{
						if (j == c)continue;
						SUBMAT.MAT[subi][subj] = Target.MAT[i][j];
						subj++;
					}
					subi++;
				}
				Det = Det + (pow(-1, c) * Target.MAT[0][c] * Determinant(SUBMAT));
			}
		}
		return Det;
	}
	catch(int e)
	{
		cout << "Cannot get the Determinant. this is not the squre matrix" << endl;
	}
}

Matrix Inverse(Matrix target)
{
	try 
	{
		double DET = Determinant(target);
		if (target.col != target.row || DET == double(0))
		{
			int e = 1;
			throw (e);
		}
		else
		{
			int n = target.col;
			Matrix RES(n, n);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					RES.MAT[j][i] = CoFactor(target, i, j);
				}
			}
			return RES;
		}
	}
	catch(int e)
	{
		cout << "Cannot get the Inverse Matrix." << endl;
	}
}

double CoFactor(Matrix Target, int p, int q)
{
	try
	{
		int n;
		if (Target.col != Target.row) { int e = 1; throw(e); }
		n = Target.col;
		Matrix SUB(n - 1, n - 1);
		for (int i = 0; i < n; i++)
		{
			int suba = 0;
			if (i == p)continue;
			for (int j = 0; j < n; j++)
			{
				int subb = 0;
				if (j == q)continue;
				else
				{
					SUB.MAT[suba][subb] = Target.MAT[i][j];
					subb++;
				}
			}
			suba++;
		}
		return det(p , q)*Determinant(SUB);
	}
	catch (int e)
	{
		cout << "Cannot get the cofactor. this is not the squre matrix" << endl;
	}
}

int argmax_1d(int *A, int s, int e)
{
	int max = -987654321;
	for (int i = s; i <= e; i++)
	{
		if (max < A[i])max = A[i];
	}
	return max;
}

int argmax_2d(int **A, int s, int e)
{

}