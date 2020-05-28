// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<vector>
#include<math.h>

#include<oXu/components/game/playField.hpp>

#include<oXu/utils/vector2.hpp>

#include<oXu/utils/logger.hpp>

namespace oxu
{
    void calculateLinearPath(const std::vector<Vector2<float>> &controlPoints, std::vector<Vector2<float>> &calculatedPath, const PlayField &playField, const double &expectedLength);
    void calculateCircularPath();
    void calculateBezierPath(const std::vector<Vector2<float>> &controlPoints, std::vector<Vector2<float>> &calculatedPath, const PlayField &playField, const double &precision = 0.005);
}