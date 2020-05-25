#include"pathCalculator.hpp"

int getFactorialOf(int n)
{
    int result = 1;
    while(n)
    {
        result *= n--;
    }

    return result;
}

int getBinomialCoefficient(const int &n, const int &r)
{
    return getFactorialOf(n) / (getFactorialOf(r) * getFactorialOf(n - r)); 
}

namespace oxu
{
    void calculateBezierPath(const std::vector<Vector2<float>> &controlPoints, std::vector<Vector2<float>> &calculatedPath, const PlayField &playField, const double &precision)
    {
        for(double t = 0; t < 1; t += precision)
        {
            Vector2<float> coord = { 0, 0 };
            unsigned int power = controlPoints.size() - 1;
            unsigned int i = 1;

            coord += controlPoints[0] * pow(1 - t, power--);
            for(unsigned int j = 1; j < controlPoints.size() - 1; ++j)
            {
                coord += controlPoints[j] * (getBinomialCoefficient(controlPoints.size() - 1, i) * pow(1 - t, power--) * pow(t, i++));
            }
            coord += controlPoints[controlPoints.size() - 1] * pow(t, i);
            
            calculatedPath.push_back(coord);
        }
    }
}