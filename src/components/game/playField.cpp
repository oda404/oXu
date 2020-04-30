// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"playField.hpp"

oxu::PlayField::PlayField() { }

void oxu::PlayField::init(const Vector2i &screenSize)
{
    oxuPx = screenSize.y / 480.f;
    playFieldStartPoint = { screenSize.x / 2 - 256.0f * oxuPx, screenSize.y / 2 - 192 * oxuPx };
}

oxu::Vector2f &oxu::PlayField::getPlayFieldStartPoint() { return playFieldStartPoint; }

float &oxu::PlayField::getOxuPx() { return oxuPx; }
