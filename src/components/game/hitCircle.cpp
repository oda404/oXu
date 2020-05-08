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
    objTruePosition = Vector2<float>(
        playField.getPlayFieldStartPoint().getX() + infoArr[0] * playField.getOxuPx(),
        playField.getPlayFieldStartPoint().getY() + infoArr[1] * playField.getOxuPx()
    );

    // Hit circle width and height
    HCRect.w = (23.05f - (4.2f - 7.0f) * 4.4825f) * 2.0f * playField.getOxuPx();
    HCRect.h = HCRect.w;

    // Offset the true position so it falls on it's center point
    HCRect.x = objTruePosition.getX() - HCRect.w / 2;
    HCRect.y = objTruePosition.getY() - HCRect.h / 2;

    // Approach circle width and height
    ACRect.w = HCRect.w * (2.0f * playField.getOxuPx());
    ACRect.h = ACRect.w;

    /* Figure out the scaled approach circle size based on the hit circle size */
    ACInitialSize = Vector2<float>(ACRect.w, ACRect.h);
    int sizeAfterScaling = Textures::getInstance().gameTexturesSizes[1].getX() * HCRect.w / Textures::getInstance().gameTexturesSizes[0].getX();
    ACFinalSize = Vector2<float>(sizeAfterScaling, sizeAfterScaling);

    // Offset the true position so it falls on it's center point
    ACRect.x = objTruePosition.getX() - ACRect.w / 2;
    ACRect.y = objTruePosition.getY() - ACRect.h / 2;

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

oxu::Vector2<float> lerp(const oxu::Vector2<float> &a, const oxu::Vector2<float> &b, const float &t)
{
    return a * (1 - t) + b * t;
}

bool oxu::HitCircle::approachCircle(const double &dt)
{
    if(approachT <= 1)
    {
        approachT += dt / 0.450f;

        Vector2<float> newPos = lerp(ACInitialSize, ACFinalSize, approachT);

        /* Scale the circle down */
        ACRect.w = newPos.getX();
        ACRect.h = newPos.getY();

        /* recenter the approach circle */
        ACRect.x = objTruePosition.getX() - ACRect.w / 2;
        ACRect.y = objTruePosition.getY() - ACRect.h / 2;

        return true;
    }
    
    return false;
}

const bool &oxu::HitCircle::isFinished() 
{
    return isDone;
}

const float &oxu::HitCircle::getState()
{
    return approachT;
}
