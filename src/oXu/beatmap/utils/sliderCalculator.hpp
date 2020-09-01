#pragma once

#include<vector>
#include<oXu/utils/vector2.hpp>

namespace oxu
{
    void calculate_linear_path(std::vector<Vector2<float>> &control_points, double expected_length);
}