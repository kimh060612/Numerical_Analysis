#include <iostream>
#include <cmath>
#define PI 3.1415926535
#define EPS 0.9

using namespace std;

double X[30];
double Y[30];
int N = 10;

double Update(double y, int x)
{
    double a = x + EPS * sin (y) - EPS * y * cos(y);
    double b = 1 - EPS * cos(y);
    return a / b;
}

int main()
{
    for (int i = 0; i < 30; i++) X[i] = i * PI / 30;
    for (int i = 0; i < 30; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            Y[i] = Update(Y[i], X[i]);
        }
        cout << X[i] << " : " << Y[i] << endl;
    }
    return 0;
}