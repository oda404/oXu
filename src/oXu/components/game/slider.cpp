// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"slider.hpp"

namespace oxu
{
    /* Public methods */

    Slider::Slider(unsigned int infoArr[4], const std::vector<Vector2<float>> &pControlPoints, const int &pRepeats, const double &pLength, const uint8_t &pType, const PlayField &playField, BeatmapInfo &mapInfo):HitCircle(infoArr, playField, mapInfo)
    {
        controlPoints = pControlPoints;
        expectedLength = pLength;
        type = pType;
        repeats = pRepeats;

        calculatePath(playField);
    }

    const std::vector<Vector2<float>> &Slider::getCalculatedPath()
    {
        return calculatedPath;
    }

    const double &Slider::getExpectedLength()
    {
        return expectedLength;
    }

    const uint8_t &Slider::getSliderType()
    {
        return type;
    }

    /* Private methods */

    void Slider::calculatePath(const PlayField &playField)
    {
        switch(type)
        {
            case SliderType::Linear:
                calculateLinearPath(controlPoints, calculatedPath, playField, expectedLength);
                break;
        } 
    }
}