#include"hitCircle.hpp"

#include<oXu/skin/config.hpp>
#include<oXu/core/logger.hpp>
#include<oXu/graphics/renderer.hpp>

#define FADE_IN_MULT 10.5f
#define FADE_OUT_MULT 21.f

namespace oxu
{
    HitCircle::HitCircle(
        const Vector2<float> &position_p,
        const std::uint32_t &hitTime_p,
        const std::uint8_t &type_p,
        const Difficulty &difficulty_p
    ) : HitObject(position_p, hitTime_p, type_p, difficulty_p)
    {

    }

    void HitCircle::update(const double &delta, const Difficulty &difficulty)
    {
        if(mx_alpha < 1.f)
        {
            mx_alpha += FADE_IN_MULT * delta;
        }

        if(mx_approachCircle.closeIn(
            delta,
            mx_originPosition, 
            mx_size, 
            difficulty.approachRateMs
        ))
        {
            mx_alpha -= FADE_OUT_MULT * delta;
        }
    }

    void HitCircle::render(const Skin &skin_p)
    {
        graphics::Renderer::copy_texture(
            mx_position, 
            mx_size, 
            skin_p.getTexture(Tex::HIT_CIRCLE),
            mx_alpha
        );
        graphics::Renderer::copy_texture(
            mx_position, 
            mx_size, 
            skin_p.getTexture(Tex::HIT_CIRCLE_OVERLAY),
            mx_alpha
        );
        graphics::Renderer::copy_texture(
            mx_approachCircle.position, 
            mx_approachCircle.size, 
            skin_p.getTexture(Tex::APPROACH_CIRCLE),
            mx_alpha
        );
    }

    void HitCircle::setErrorMargin(const long double &err, const std::uint32_t &approachRateMs)
    {
        mx_approachCircle.lerpT = (err - mx_spawnTime) / approachRateMs;
    }

    bool HitCircle::shouldBeAddedToPool(const std::uint32_t &mapTimeMs)
    {
        return mapTimeMs >= mx_spawnTime;
    }

    bool HitCircle::shouldBeRemovedFromPool()
    {
        if(mx_alpha > 0.f) return false;
        return true;
    }
}
