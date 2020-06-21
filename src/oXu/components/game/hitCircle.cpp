// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"hitCircle.hpp"

oxu::HitCircle::HitCircle(const HitCircleModel &model, const PlayField &playField):
hitTime(model.hitTime), combo(model.combo), ARInSeconds(model.ARInSeconds)
{
    objTruePosition = playField.getPlayFieldStartPoint() + model.position * Scaling::oxuPx;

    /* ============================= HIT CIRCLE ================================== */
    // Set the width and height
    HCRect.w = (23.05f - (model.circleSize - 7.0f) * 4.4825f) * 2.0f * Scaling::oxuPx;
    HCRect.h = HCRect.w;

    // Offset the true position so it falls on it's center point
    HCRect.x = objTruePosition.x - HCRect.w / 2;
    HCRect.y = objTruePosition.y - HCRect.h / 2;

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
    comboRect.x = objTruePosition.x - comboRect.w / 2;
    comboRect.y = objTruePosition.y - comboRect.h / 2;

    /* =================== APPROACH CIRCLE ================================= */
    // Set the width and height
    ACRect.w = HCRect.w * (1.5f * Scaling::oxuPx);
    ACRect.h = ACRect.w;

    ACInitialSize = Vector2<float>(ACRect.w, ACRect.h);
    ACFinalSize = Vector2<float>(HCRect.w, HCRect.h);

    // Offset the true position so it falls on it's center point
    ACRect.x = objTruePosition.x - ACRect.w / 2;
    ACRect.y = objTruePosition.y - ACRect.h / 2;
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

uint32_t oxu::HitCircle::getSpawnTime()
{
    return hitTime - ARInSeconds * 1000;
}

void oxu::HitCircle::approachCircle(const double &dt)
{
    if(approachT <= 1)
    {
        Vector2<float> newPos = Vector2<float>::lerp(ACInitialSize, ACFinalSize, approachT);
        
        ACRect.w = newPos.x;
        ACRect.h = newPos.y;

        /* recenter the approach circle */
        ACRect.x = objTruePosition.x - ACRect.w / 2;
        ACRect.y = objTruePosition.y - ACRect.h / 2;
    }
    else
    {
        doneApproaching = true;
    }

    approachT += dt / ARInSeconds;
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
