// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"hitCircle.hpp"

oxu::HitCircle::HitCircle(unsigned int infoArr[5], PlayField &playField)
{
    /*
    infoArr[0] == posX
    infoArr[1] == posY
    infoArr[2] == spawnTime
    infoArr[3] == HCHalfTex
    infoArr[4] == ACHalfTex 
    */

    int objTrueX = playField.getPlayFieldStartPoint().x + infoArr[0] * playField.getOxuPx();
    int objTrueY = playField.getPlayFieldStartPoint().y + infoArr[1] * playField.getOxuPx();

    // Hit circle
    // Offset the true position so it falls on it's center point
    HCRect.x = objTrueX - infoArr[3];
    HCRect.y = objTrueY - infoArr[3];

    HCRect.w = infoArr[3] * 2;
    HCRect.h = HCRect.w;

    // Approach circle
    ACRect.x = objTrueX - infoArr[4];
    ACRect.y = objTrueY - infoArr[4];

    ACRect.w = infoArr[4] * 2;
    ACRect.h = ACRect.w;

    spawnTime = infoArr[2];
}

SDL_Rect *oxu::HitCircle::getHCSDLRect()
{
    return &HCRect;
}

SDL_Rect *oxu::HitCircle::getACSDLRect()
{
    return &ACRect;
}

uint32_t &oxu::HitCircle::getSpawnTime()
{
    return spawnTime;
}
