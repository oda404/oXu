// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"playField.hpp"

oxu::PlayField::PlayField()
{
    playFieldStartPoint = { Scaling::screenSize.x / 2 - 256.0f * Scaling::oxuPx, Scaling::screenSize.y / 2 - 192 * Scaling::oxuPx };
}

const oxu::Vector2<float> &oxu::PlayField::getPlayFieldStartPoint() const { return playFieldStartPoint; }
