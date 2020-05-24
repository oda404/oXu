#include"slider.hpp"

namespace oxu
{
    /* Extra functions */
    double getDistanceBetween(const Vector2<float> &p0, const Vector2<float> &p1)
    {
        return abs(sqrt(pow(p1.getX() - p0.getX(), 2) + pow(p1.getY() - p0.getY(), 2)));
    }

   /* Public methods */

    Slider::Slider(unsigned int infoArr[4], const std::vector<Vector2<float>> &pControlPoints, const int &pLength, const uint8_t &pType, PlayField &playField, BeatmapInfo &mapInfo):HitCircle(infoArr, playField, mapInfo)
    {
        controlPoints = pControlPoints;
        expectedLength = pLength;
        type = pType;

        calculatePath(playField);
        calculateLength();
    }

   const std::vector<Vector2<float>> &Slider::getCalculatedPath()
   {
       return calculatedPath;
   }

   const std::vector<Vector2<float>> &Slider::getControlPoints()
   {
       return controlPoints;
   }

   const double &Slider::getExpectedLength()
   {
       return expectedLength;
   }

   const double &Slider::getCalculatedLength()
   {
       return calculatedLength;
   }

   const uint8_t &Slider::getSliderType()
   {
       return type;
   }

   /* Private methods */

    void Slider::calculateLength()
    {
        for(unsigned int i = 1; i < calculatedPath.size(); ++i)
        {
            calculatedLength += getDistanceBetween(calculatedPath[i], calculatedPath[i - 1]);
        }
    }

    void Slider::calculatePath(PlayField &playField, const double &precision)
    {
        Vector2<float> coord;
        for(double t = 0; t < 1; t += precision)
        {
            /* Cubic bezier formula */
            coord = controlPoints[0] *      pow(1 - t, 3) +
                    controlPoints[1] * (3 * pow(1 - t, 2) * t) +
                    controlPoints[2] * (3 * pow(1 - t, 1) * pow(t, 2)) +
                    controlPoints[3] *                      pow(t, 3);

            calculatedPath.push_back(coord);
        }        
    }
}