// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"hitCircle.hpp"

oxu::HitCircle::HitCircle(unsigned int infoArr[3], PlayField &playField)
{
    /*
    infoArr[0] == posX
    infoArr[1] == posY
    infoArr[2] == spawnTime
    */
    objTruePosition = Vector2f(
        playField.getPlayFieldStartPoint().x + infoArr[0] * playField.getOxuPx(),
        playField.getPlayFieldStartPoint().y + infoArr[1] * playField.getOxuPx()
    );

    // Hit circle
    // Offset the true position so it falls on it's center point
    HCRect.w = (((23.05f - (4.2f - 7.0f) * 4.4825f) * 2.0f * playField.getOxuPx()));
    HCRect.h = HCRect.w;

    HCRect.x = objTruePosition.x - HCRect.w / 2;
    HCRect.y = objTruePosition.y - HCRect.h / 2;

    // Approach circle
    ACRect.w = HCRect.w * (2.0f * playField.getOxuPx());
    ACRect.h = ACRect.w;

    ACInitialSize = Vector2f(ACRect.w, ACRect.h);

    ACRect.x = objTruePosition.x - ACRect.w / 2;
    ACRect.y = objTruePosition.y - ACRect.h / 2;

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

void oxu::HitCircle::approachCircle(const double &dt)
{
    /* hardcoded ar value */
    ACRect.w -= ((ACInitialSize.x - HCRect.w) / 0.450f) * dt;
    ACRect.h -= ((ACInitialSize.y - HCRect.h) / 0.450f) * dt;

    /* recenter the approach circle */
    ACRect.x = objTruePosition.x - ACRect.w / 2;
    ACRect.y = objTruePosition.y - ACRect.h / 2;
}
