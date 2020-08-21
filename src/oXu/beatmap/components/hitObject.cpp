#include"hitObject.hpp"

#include<oXu/core/scaling.hpp>
#include<oXu/beatmap/components/types.hpp>
#include<oXu/utils/logger.hpp>

namespace oxu
{
    static uint8_t getHitObjectType(uint8_t &type)
    {
        if( type  & (1 << 0) )
        {
            return Types::CIRCLE;
        }
        else if( type & (1 << 1) )
        {
            return Types::SLIDER;
        }

        return Types::SPINNER;
    }
    
    HitObject::HitObject(const Vector2<float> &position_p, const uint32_t &hitTime_p, uint8_t type_p, const PlayField &playField, const Difficulty &difficulty):
    realHitTime(hitTime_p), realSpawnTime(hitTime_p - difficulty.approachRateMs)
    {
        localSpawnTime = realHitTime;
        localHitTime = realHitTime + difficulty.approachRateMs;

        position = playField.getPlayFieldStartPoint() + position_p * Scaling::oxuPx;

        HCRect.w = difficulty.circleSizePx;
        HCRect.h = HCRect.w;

        HCRect.x = position.x - HCRect.w / 2;
        HCRect.y = position.y - HCRect.h / 2;

        ACRect.w = HCRect.w * 2.75f;
        ACRect.h = ACRect.w;

        ACInitialSize.setVector(ACRect.w, ACRect.h);

        ACRect.x = position.x - ACRect.w / 2;
        ACRect.y = position.y - ACRect.h / 2;

        type = getHitObjectType(type_p);

        switch(type)
        {
        case Types::SLIDER:
            
            break;

        case Types::SPINNER:

            break;
        }
    }

    const uint32_t &HitObject::getRealHitTime()
    {
        return realHitTime;
    }

    const uint32_t &HitObject::getRealSpawnTime()
    {
        return realSpawnTime;
    }

    const uint32_t &HitObject::getLocalHitTime()
    {
        return localHitTime;
    }

    const uint32_t &HitObject::getLocalSpawnTime()
    {
        return localSpawnTime;
    }

    const SDL_Rect *HitObject::getHCRect()
    {
        return &HCRect;
    }

    const SDL_Rect *HitObject::getACRect()
    {
        return &ACRect;
    }

    bool HitObject::shouldBeAddedToPool(const uint32_t &ellapsedMapTime)
    {
        if(ellapsedMapTime >= localSpawnTime)
        {
            return true;
        }

        return false;
    }

    bool HitObject::shouldBeRemovedFromPool(const uint32_t &ellapsedMapTime)
    {
        if(ellapsedMapTime > localHitTime)
        {
            return true;
        }
        
        return false;
    }
    void HitObject::setErrorMargin(const double &err,  const uint32_t &arMs)
    {
        ACT = (err - localSpawnTime) / arMs;
    }

    void HitObject::approachCircle(const float &delta, const float &AR)
    {
        if(ACT <= 1.f)
        {
            ACT += delta / (AR / 1000.f);

            Vector2<float> newPosition = Vector2<float>::lerp(ACInitialSize, Vector2<float>(HCRect.w, HCRect.h), ACT);

            ACRect.w = newPosition.x;
            ACRect.h = newPosition.y;

            ACRect.x = position.x - ACRect.w / 2;
            ACRect.y = position.y - ACRect.h / 2;
        }
    }
}
