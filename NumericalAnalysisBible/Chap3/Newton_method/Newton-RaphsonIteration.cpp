#include <iostream>

using namespace std;

double F(double x);
double F_(double x);

int main()
{
    int iter = 10, epoch = 0;
    double eps = 0.0001, delta = 0.00000001;
    double x = 3.;
    double fx, fp, d;
    fx = F(x);
    fp = F_(x);
    d = fx / fp;
    while (d > eps && epoch < iter)
    {
        x = x - d;
        fx = F(x);
        fp = F_(x);
        d = fx / fp;
        if (fp < delta)
        {
            cout << "Divergence" << endl;
            return 0;
        }
    }

    cout << x << "  " << F(x) << endl;

    return 0;
}

double F(double x)
{
    return x*x*x - 2*x*x + x - 3;
}

double F_(double x)
{
    return 3*x*x - 4*x + 1;
}