#include"hitObject.hpp"

namespace oxu
{
    HitObject::HitObject(const Vector2<float> &position_p, const uint32_t &hitTime_p, uint8_t type_p, const PlayField &playField, const Difficulty &difficulty):
    hitTime(hitTime_p), spawnTime(hitTime_p - difficulty.approachRateMs), type(type_p)
    {
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
    }

    const uint32_t &HitObject::getHitTime()
    {
        return hitTime;
    }

    const uint32_t &HitObject::getSpawnTime()
    {
        return spawnTime;
    }

    const SDL_Rect *HitObject::getHCRect()
    {
        return &HCRect;
    }

    const SDL_Rect *HitObject::getACRect()
    {
        return &ACRect;
    }

    void HitObject::render(SDL_Renderer *targetRenderer)
    {
        
    }

    bool HitObject::shouldBeAddedToPool(const uint32_t &time)
    {
        if(time >= spawnTime)
        {
            return true;
        }

        return false;
    }

    bool HitObject::shouldBeRemovedFromPool(const uint32_t &time)
    {
        if(time >= hitTime)
        {
            return true;
        }
        
        return false;
    }

    void HitObject::approachCircle(const float &delta, const float &AR)
    {
        if(ACT <= 1.f)
        {
            ACT += delta / (AR / 1000.f - errorMargin / 1000.f);

            Vector2<float> newPosition = Vector2<float>::lerp(ACInitialSize, Vector2<float>(HCRect.w, HCRect.h), ACT);

            ACRect.w = newPosition.x;
            ACRect.h = newPosition.y;

            ACRect.x = position.x - ACRect.w / 2;
            ACRect.y = position.y - ACRect.h / 2;
        }
    }
}
