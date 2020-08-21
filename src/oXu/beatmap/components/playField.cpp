// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"playField.hpp"

#include<oXu/core/scaling.hpp>

oxu::PlayField::PlayField()
{
    playFieldStartPoint = { 
        Scaling::screenSize.x / 2.f - 256.f * Scaling::oxuPx, 
        Scaling::screenSize.y / 2.f - 192.f * Scaling::oxuPx 
    };
}
