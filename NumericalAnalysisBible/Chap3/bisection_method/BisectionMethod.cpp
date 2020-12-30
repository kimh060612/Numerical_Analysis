#include <iostream>
#include <math.h>

using namespace std;

double F(double x);

int main()
{
    int iter = 1000, epoch = 0;
    double eps = 0.0001;
    double a, b, c;
    a = 0.5;
    b = 2.;
    double error = b - a;
    double fa = F(a) , fb = F(b);
    while (abs(error) > eps && epoch < iter)
    {
        error = error/2;
        c = a + error;
        double fc = F(c);
        if (fa*fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
        epoch ++;
    }

    cout << c << " " <<error << endl;

    return 0;
}

double F(double x)
{
    return x*x*x - 2*sin(x);
}