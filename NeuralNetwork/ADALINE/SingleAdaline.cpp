#include <iostream>
#include "Adaline.h"

using namespace std;

const double lr = 0.2;
const int epoch = 5000;

int main()
{
    ADALINE Net(3, 1);
    double p1[3], p2[3];
    double t1[1], t2[1];

    p1[0] = 1; p1[1] = -1; p1[2] = -1;
    p1[0] = 1; p1[1] = 1; p1[2] = -1;
    t1[0] = -1;
    t2[0] = 1;

    for (int e = 0; e < epoch; e++)
    {
        Net.backward(t1, p1, lr);
        Net.backward(t2, p2, lr);
        cout << e << endl;
    }

    double *infer1, *infer2;
    infer1 = Net.predict(p1);
    infer2 = Net.predict(p2);

    cout << infer1[0] << "   " << infer2[0] << endl;

    Free1D(infer1);
    Free1D(infer2);
    return 0;
}