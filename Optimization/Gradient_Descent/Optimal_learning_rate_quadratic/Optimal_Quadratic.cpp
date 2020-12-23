#include <iostream>
#include <fstream>
#include <cmath>
#define PI 3.1416926535

using namespace std; 

float Fxy(float x, float y);
float dFxydx(float x, float y, float dx);
float dFxydy(float x, float y, float dy);
float Distance(float x0, float y0, float x1, float y1);

int main()
{
    
    float x0 = 0.7, x1 = 0.8;
    float y0 = 0.7, y1 = 0.8;
    float dx = 0.001, dy = 0.001;

    float learning_rate = 0.25 - 0.01, Eps = 0.0001;
    int Epoch = 0;

    while (Distance(x0, y0,x1,y1) > Eps && Epoch < 1000)
    {
        x0 = x1; y0 = y1;
        x1 -= learning_rate*(dFxydx(x0, y0, dx));
        y1 -= learning_rate*(dFxydy(x0, y0, dy));
        Epoch++;
    }

    cout << "Epoch: " << Epoch << " X: " << x1 << "  Y: " << y1 << "  Fxy(x,y): " << Fxy(x1, y1) << endl;

    return 0;
}

float Fxy(float x, float y)
{
    return (x - 10)*(x - 10) + 4*(y - 5)*(y - 5);
}

// Eigen Value of Hessian: 2, 8

float dFxydx(float x, float y, float dx)
{
    return (Fxy(x + dx, y) - Fxy(x, y))/dx;
}

float dFxydy(float x, float y, float dy)
{
    return (Fxy(x, y + dy) - Fxy(x, y))/dy;
}

float Distance(float x0, float y0, float x1, float y1)
{
    return sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
}