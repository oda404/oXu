// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"playField.hpp"

oxu::PlayField::PlayField() { }

void oxu::PlayField::init(const Vector2<int> &screenSize)
{
    oxuPx = screenSize.getY() / 480.f;
    playFieldStartPoint = { screenSize.getX() / 2 - 256.0f * oxuPx, screenSize.getY() / 2 - 192 * oxuPx };
}

oxu::Vector2<float> &oxu::PlayField::getPlayFieldStartPoint() { return playFieldStartPoint; }

float &oxu::PlayField::getOxuPx() { return oxuPx; }
