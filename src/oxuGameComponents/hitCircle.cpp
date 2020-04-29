// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"hitCircle.hpp"

oxu::HitCircle::HitCircle(unsigned int infoArr[5])
{
    /*
    infoArr[0] == posX
    infoArr[1] == posY
    infoArr[2] == spawnTime
    infoArr[3] == HCHalfTex
    infoArr[4] == ACHalfTex 
    */

    circleRect.x = infoArr[0] - infoArr[3];
    circleRect.y = infoArr[1] - infoArr[3];

    circleRect.w = infoArr[3] * 2;
    circleRect.h = circleRect.w;

    spawnTime = infoArr[2];
}

SDL_Rect *oxu::HitCircle::getSDLRect()
{
    return &circleRect;
}
