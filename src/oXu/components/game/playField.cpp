// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"playField.hpp"

oxu::PlayField::PlayField()
{
    playFieldStartPoint = { Global::screenSize.getX() / 2 - 256.0f * Global::oxuPx, Global::screenSize.getY() / 2 - 192 * Global::oxuPx };
}

const oxu::Vector2<float> &oxu::PlayField::getPlayFieldStartPoint() const { return playFieldStartPoint; }
