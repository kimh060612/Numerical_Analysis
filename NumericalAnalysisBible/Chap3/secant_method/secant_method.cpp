#include <iostream>
#include <math.h>

using namespace std;

double F(double x);
void SWAP(double &a, double &b);

int main()
{
    int iter = 10, epoch = 0;
    double eps = 0.0001, delta = 0.00000001;
    double a = 2.5, b = 2.9, c, d = 10;
    double fa, fb, fc, fd, fp;
    fa = F(a);
    fb = F(b);

    if (abs(fa) > abs(fb))
    {
        SWAP(a , b);
        SWAP(fa , fb);         
    }

    while (d > eps && epoch < iter)
    {
        if (abs(fa) > abs(fb))
        {
            SWAP(a , b);
            SWAP(fa , fb);  
        }
        d = (b - a) / (fb - fa);
        b = a;
        fb = fa;
        d = d * fa;
        a = a - d;
        fa = F(a);
        epoch ++;
    }

    cout << a << "  " << F(a) << endl;
    return 0;
}

double F(double x)
{
    return x*x*x - 2*x*x + x - 3;
}

void SWAP(double &a, double &b)
{
    double tmp = a;
    a = b;
    b = tmp;
}