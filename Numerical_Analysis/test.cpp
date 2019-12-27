#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix A(3,4);

    cout << A.col  << " " << A.row << endl;

    return 0;

}