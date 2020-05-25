#pragma once

#include<vector>
#include<math.h>

#include"../components/game/playField.hpp"

#include"vector2.hpp"

namespace oxu
{
    void calculateLinearPath();
    void calculateCircularPath();
    void calculateBezierPath(const std::vector<Vector2<float>> &controlPoints, std::vector<Vector2<float>> &calculatedPath, const PlayField &playField, const double &precision = 0.005);
}