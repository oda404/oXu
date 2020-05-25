#include"slider.hpp"

namespace oxu
{
    /* Extra functions */
    double getDistanceBetween(const Vector2<float> &p0, const Vector2<float> &p1)
    {
        return abs(sqrt(pow(p1.getX() - p0.getX(), 2) + pow(p1.getY() - p0.getY(), 2)));
    }

   /* Public methods */

    Slider::Slider(unsigned int infoArr[4], const std::vector<Vector2<float>> &pControlPoints, const int &pRepeats, const double &pLength, const uint8_t &pType, const PlayField &playField, BeatmapInfo &mapInfo):HitCircle(infoArr, playField, mapInfo)
    {
        controlPoints = pControlPoints;
        expectedLength = pLength;
        type = pType;
        repeats = pRepeats;

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

    void Slider::calculatePath(const PlayField &playField)
    {
        switch(type)
        {
            case SliderType::Linear:
                //calculateLinearPath();
                break;

            case SliderType::Circle:
                //calculateCircularPath();
                break;

            case SliderType::Bezier:
                calculateBezierPath(controlPoints, calculatedPath, playField);
                break;
        } 
    }
}