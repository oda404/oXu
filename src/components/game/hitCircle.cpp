// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"hitCircle.hpp"

oxu::HitCircle::HitCircle(unsigned int infoArr[4], const PlayField &playField, BeatmapInfo &mapInfo):
hitTime(infoArr[2]), combo(infoArr[3]), ARInSeconds(mapInfo.ARInSeconds)
{
    /*
    infoArr[0] == posX
    infoArr[1] == posY
    infoArr[2] == hitTime
    infoArr[3] == combo
    */
    objTruePosition = Vector2<float>(
        playField.getPlayFieldStartPoint().getX() + infoArr[0] * Global::oxuPx,
        playField.getPlayFieldStartPoint().getY() + infoArr[1] * Global::oxuPx
    );

    /* ============================= HIT CIRCLE ================================== */
    // Set the width and height
    HCRect.w = (23.05f - (mapInfo.getDifficultyAttr("CircleSize") - 7.0f) * 4.4825f) * 2.0f * Global::oxuPx;
    HCRect.h = HCRect.w;

    // Offset the true position so it falls on it's center point
    HCRect.x = objTruePosition.getX() - HCRect.w / 2;
    HCRect.y = objTruePosition.getY() - HCRect.h / 2;

    /* ============================ COMBO ================================== */
    /* Check to see if the combo is one digit or bigger to determine it's width */
    if(combo < 10)
    {
        comboRect.h = Textures::getInstance().getComboNumDefaultSurf()->h;
        comboRect.w = Textures::getInstance().getComboNumDefaultSurf()->w;
    }
    else
    {
        comboRect.h = Textures::getInstance().getComboNumDefaultSurf()->h;
        comboRect.w = Textures::getInstance().getComboNumDefaultSurf()->w * 2;
    }

    // Offset the true position so it falls on it's center point
    comboRect.x = objTruePosition.getX() - comboRect.w / 2;
    comboRect.y = objTruePosition.getY() - comboRect.h / 2;

    /* =================== APPROACH CIRCLE ================================= */
    // Set the width and height
    ACRect.w = HCRect.w * (1.5f * Global::oxuPx);
    ACRect.h = ACRect.w;

    /* Figure out the scaled approach circle size based on the hit circle size */
    ACInitialSize = Vector2<float>(ACRect.w, ACRect.h);
    int sizeAfterScaling = Textures::getInstance().getACSurf()->w * HCRect.w / Textures::getInstance().getACSurf()->w;
    ACFinalSize = Vector2<float>(sizeAfterScaling, sizeAfterScaling);

    // Offset the true position so it falls on it's center point
    ACRect.x = objTruePosition.getX() - ACRect.w / 2;
    ACRect.y = objTruePosition.getY() - ACRect.h / 2;
}

const SDL_Rect *oxu::HitCircle::getHCRect()
{
    return &HCRect;
}

const SDL_Rect *oxu::HitCircle::getACRect()
{
    return &ACRect;
}

const SDL_Rect *oxu::HitCircle::getComboRect()
{
    return &comboRect;    
}

const uint32_t &oxu::HitCircle::getHitTime()
{
    return hitTime;
}

oxu::Vector2<float> lerp(const oxu::Vector2<float> &a, const oxu::Vector2<float> &b, const float &t)
{
    return a * (1 - t) + b * t;
}

void oxu::HitCircle::approachCircle(const double &dt)
{
    if(approachT < 1)
    {
        approachT += dt / ARInSeconds;

        Vector2<float> newPos = lerp(ACInitialSize, ACFinalSize, approachT);

        /* Scale the circle down */
        ACRect.w = newPos.getX();
        ACRect.h = newPos.getY();

        /* recenter the approach circle */
        ACRect.x = objTruePosition.getX() - ACRect.w / 2;
        ACRect.y = objTruePosition.getY() - ACRect.h / 2;
    }
    else
    {
        doneApproaching = true;
    }
}

const bool &oxu::HitCircle::isHit() 
{
    return doneApproaching;
}

void oxu::HitCircle::hit()
{
    doneApproaching = true;
}

const int &oxu::HitCircle::getCombo()
{
    return combo;
}
