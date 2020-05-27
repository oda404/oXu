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

double getDistanceBetween(const oxu::Vector2<float> &p0, const oxu::Vector2<float> &p1)
{
    return abs(sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2)));
}

namespace oxu
{
    void calculateLinearPath(const std::vector<Vector2<float>> &controlPoints, std::vector<Vector2<float>> &calculatedPath, const PlayField &playField, const double &expectedLength)
    {
        /* If the calculated length is different than the expected length */
        /* the path will always shorten/expand from the last control point */
        /* This not 100% accurate, it's more of an approximation, but it's good enough */

        /* Add the first control point */
        calculatedPath.push_back(controlPoints[0]);

        const double calculatedLength = getDistanceBetween(controlPoints[0], controlPoints[1]);

        /* If the calculated path is the same as the expected length there's nothing to do */
        if(calculatedLength == expectedLength)
        {
            calculatedPath.push_back(controlPoints[1]);
            return;
        }
        
        //TODO: implement a threshold

        /* Get the direction of the vector */
        Vector2<float> dir = (controlPoints[1] - controlPoints[0]).normalized();

        /* Approximate the length */
        calculatedPath.push_back(controlPoints[1] + dir * (float)(expectedLength - calculatedLength));

        /* Add scaling factors to the control points */
        for(Vector2<float> &cp: calculatedPath)
        {
            cp = playField.getPlayFieldStartPoint() + cp * Scaling::oxuPx;
        }
    }

    void calculateBezierPath(const std::vector<Vector2<float>> &controlPoints, std::vector<Vector2<float>> &calculatedPath, const PlayField &playField, const double &precision)
    {
        
    }
}