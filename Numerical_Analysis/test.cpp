#include <iostream>
#include "Matrix.h"

int main()
{
    
    vector<vector<int>> A(4);
    vector<vector<int>> B(4);

    for (int i = 0; i < 4; i++)
    {
        A[i].assign(4,3);
        B[i].assign(4,4);
    }

    Matrix A1(A);
    Matrix B1(B);

    Matrix C(4,4);

    C = A1 * B1;

    C.show();

    cout << "OK" << endl;

    return 0;

}