#include"hitCircle.hpp"

#include<oXu/skin/config.hpp>

namespace oxu
{
    HitCircle::HitCircle(
        const Vector2<float> &position_p,
        const std::uint32_t &hitTime_p,
        const std::uint8_t &type_p,
        const Difficulty &difficulty_p
    ) : HitObject(position_p, hitTime_p, type_p)
    {
        /* start padding */
        spawnTime = hitTime;
        hitTime += difficulty_p.approachRateMs;

        rect.w = difficulty_p.circleSizePx;
        rect.h = rect.w;
        rect.x = position.x - rect.w / 2;
        rect.y = position.y - rect.h / 2;

        approachCircle.rect.w = rect.w * 2.75f;
        approachCircle.rect.h = approachCircle.rect.w;
        approachCircle.rect.x = position.x - approachCircle.rect.w / 2;
        approachCircle.rect.y = position.y - approachCircle.rect.h / 2;

        approachCircle.initialSize.setVector(approachCircle.rect.w, approachCircle.rect.h);
    }

    void HitCircle::update(const double &delta, const Difficulty &difficulty)
    {
        approachCircle.closeIn(delta, position, {rect.w, rect.h}, difficulty.approachRateMs);
    }

    void HitCircle::render(SDL_Renderer *targetRenderer, Skin *currentSkin)
    {
        SDL_RenderCopy(
            targetRenderer, 
            currentSkin->getTexture(Tex::HIT_CIRCLE), 
            NULL, 
            &rect
        );
        SDL_RenderCopy(
            targetRenderer, 
            currentSkin->getTexture(Tex::HIT_CIRCLE_OVERLAY), 
            NULL, 
            &rect
        );
        SDL_RenderCopy(
            targetRenderer, 
            currentSkin->getTexture(Tex::APPROACH_CIRCLE), 
            NULL, 
            &approachCircle.rect
        );
    }

    void HitCircle::setErrorMargin(const long double &err, const std::uint32_t &approachRateMs)
    {
        approachCircle.lerpT = (err - spawnTime) / approachRateMs;
    }

    bool HitCircle::shouldBeAddedToPool(const std::uint32_t &mapTimeMs)
    {
        if(mapTimeMs >= spawnTime)
        {
            return true;
        }

        return false;
    }

    bool HitCircle::shouldBeRemovedFromPool(const std::uint32_t &mapTimeMs)
    {
        if(mapTimeMs > hitTime)
        {
            return true;
        }
        
        return false;
    }
}