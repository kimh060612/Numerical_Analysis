#include <iostream>
#include <cmath>
#define EPS 0.00001

using namespace std;

pair<double, double> X;
double c[4] = {0.5, 0.25, -0.5, -1.};
int N = 10;

pair<double, double> FX(pair<double, double> x, int c_index)
{
    double c1 = x.first * x.first - x.second + c[c_index];
    double c2 = x.second * x.second - x.first + c[c_index];
    return {c1, c2};
}

pair<double, double> Update(pair<double, double> x, int c_index)
{
    pair<double, double> F = FX(x, c_index);
    double delta_c1 = ( 0.5 / (x.second - x.first) )* (F.second - F.first);
    double delta_c2 = ( 1 / (x.second - x.first) ) * (x.first * F.second - x.second * F.first);
    return {x.first - delta_c1 , x.second - delta_c2};
}

int main()
{
    pair<double, double> x_0 = {1, 0};
    for (int i = 0; i < 4; i++)
    {
        pair<double, double> x_ast = x_0;
        for (int j = 1; j <= N; j++)
        {
            x_ast = Update(x_ast, i);
        }
        cout << "c: " << c[i] << " => [ " << x_ast.first << " , " << x_ast.second << " ] " << endl;
    }
    return 0;
}