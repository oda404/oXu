
#include<oxu/beatmap/components/hitCircle.hpp>
#include<oxu/skin/config.hpp>
#include<oxu/framework/logger.hpp>
#include<oxu/framework/graphics/renderer.hpp>

#define FADE_IN_MULT 10.5f
#define FADE_OUT_MULT 7.5f
#define ZOOM_OUT_MULT 175.f

namespace oxu
{

using namespace framework;

    HitCircle::HitCircle(
        const ObjectInfo &obj_info_p,
        const Difficulty &difficulty_p
    ) : HitObject(obj_info_p, difficulty_p)
    {

    }

    void HitCircle::update(const double &delta, const Difficulty &difficulty)
    {
        if(!m_can_be_hit)
        {
            mx_size += ZOOM_OUT_MULT * delta;
            mx_pos = mx_origin_pos - mx_size / 2;
            mx_alpha -= FADE_OUT_MULT * delta;
        }
        else
        {
            if(mx_alpha < 1.f)
            {
                mx_alpha += FADE_IN_MULT * delta;
            }

            if(!mxp_approach_circle->shrink(
                mx_size * 2.75f,
                mx_size,
                mx_origin_pos,
                delta,
                difficulty.approachRateMs
            ))
            {
                m_can_be_hit = false;
            }
        }
    }

    void HitCircle::render(const Skin &skin_p)
    {
        graphics::Renderer::copy_texture(
            mx_pos, 
            mx_size, 
            skin_p.getTexture(Tex::HIT_CIRCLE),
            mx_alpha
        );
        graphics::Renderer::copy_texture(
            mx_pos, 
            mx_size, 
            skin_p.getTexture(Tex::HIT_CIRCLE_OVERLAY),
            mx_alpha
        );
        
        if(m_can_be_hit)
        {
            graphics::Renderer::copy_texture(
                mxp_approach_circle->getPosition(), 
                mxp_approach_circle->getSize(), 
                skin_p.getTexture(Tex::APPROACH_CIRCLE),
                mx_alpha
            );
        }
    }

    void HitCircle::setErrorMargin(const long double &err, const Difficulty &difficulty_p)
    {
        mxp_approach_circle->m_lerp_t = (err - (mx_hit_time_ms - difficulty_p.approachRateMs)) / difficulty_p.approachRateMs;
    }

    bool HitCircle::shouldAddToPool(const std::uint32_t &map_time_ms, const std::uint16_t &approach_rate_ms) const
    {
        return map_time_ms >= (mx_hit_time_ms - approach_rate_ms);
    }

    bool HitCircle::shouldRemoveFromPool() const
    {
        if(mx_alpha > 0.f || m_can_be_hit) return false;
        return true;
    }
}
