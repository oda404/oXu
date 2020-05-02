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

    // Hit circle width and height
    HCRect.w = (23.05f - (4.2f - 7.0f) * 4.4825f) * 2.0f * playField.getOxuPx();
    HCRect.h = HCRect.w;

    // Offset the true position so it falls on it's center point
    HCRect.x = objTruePosition.x - HCRect.w / 2;
    HCRect.y = objTruePosition.y - HCRect.h / 2;

    // Approach circle width and height
    ACRect.w = HCRect.w * (2.0f * playField.getOxuPx());
    ACRect.h = ACRect.w;
    
    // Approach circle initial and final size
    // Needed to approach the circle

    /* Figure out the scaled approach circle size based on the hit circle size */
    ACInitialSize = Vector2f(ACRect.w, ACRect.h);
    int sizeAfterScaling = Textures::getInstance().gameTexturesSizes[1].x * HCRect.w / Textures::getInstance().gameTexturesSizes[0].x;
    ACFinalSize = Vector2f(sizeAfterScaling, sizeAfterScaling);

    // Offset the true position so it falls on it's center point
    ACRect.x = objTruePosition.x - ACRect.w / 2;
    ACRect.y = objTruePosition.y - ACRect.h / 2;

    // Spawn time
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

oxu::Vector2f lerp(const oxu::Vector2f &a, const oxu::Vector2f &b, const float &t)
{
    return a * (1 - t) + b * t;
}

void oxu::HitCircle::approachCircle(const double &dt)
{
    if(approachT <= 1)
    {
        approachT += dt / 0.450f;

        Vector2f newPos = lerp(ACInitialSize, ACFinalSize, approachT);

        /* Scale the circle down */
        ACRect.w = newPos.x;
        ACRect.h = newPos.y;

        /* recenter the approach circle */
        ACRect.x = objTruePosition.x - ACRect.w / 2;
        ACRect.y = objTruePosition.y - ACRect.h / 2;
    }
    else
    {
        isDone = true;
    }
}
