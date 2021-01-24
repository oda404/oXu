#include"hitCircle.hpp"

#include<oXu/skin/config.hpp>
#include<oXu/core/logger.hpp>
#include<oXu/graphics/renderer.hpp>

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
        mx_approachCircle.closeIn(delta, mx_originPosition, mx_size, difficulty.approachRateMs);
    }

    void HitCircle::render(const Skin &skin_p)
    {
        Renderer::drawTexture(mx_position, mx_size, skin_p.getTexture(Tex::HIT_CIRCLE));
        Renderer::drawTexture(mx_position, mx_size, skin_p.getTexture(Tex::HIT_CIRCLE_OVERLAY));
        Renderer::drawTexture(mx_approachCircle.position, mx_approachCircle.size, skin_p.getTexture(Tex::APPROACH_CIRCLE));
    }

    void HitCircle::setErrorMargin(const long double &err, const std::uint32_t &approachRateMs)
    {
        mx_approachCircle.lerpT = (err - mx_spawnTime) / approachRateMs;
    }

    bool HitCircle::shouldBeAddedToPool(const std::uint32_t &mapTimeMs)
    {
      return mapTimeMs >= mx_spawnTime ? true : false;
    }

    bool HitCircle::shouldBeRemovedFromPool(const std::uint32_t &mapTimeMs)
    {
      return mapTimeMs > mx_hitTime ? true : false;
    }
}
