
#include<oxu/beatmap/components/hitObject.hpp>

namespace oxu
{
    ApproachCircle::ApproachCircle(const Vector2<float> &pos, const Vector2<float> &size):
    m_pos(pos), m_size(size)
    {
        
    }

    bool ApproachCircle::shrink(
        const Vector2<float> &init_size,
        const Vector2<float> &target_size,
        const Vector2<float> &origin_pos,
        const double &delta, 
        const float &approach_rate_ms
    )
    {
        if(m_lerp_t <= 1)
        {
            m_size = Vector2<float>::lerp(init_size, target_size, m_lerp_t);
            m_pos = origin_pos - m_size / 2;
            m_lerp_t += delta / (approach_rate_ms / 1000.f);
            return true;
        }

        return false;
    }
    
    const Vector2<float> &ApproachCircle::getPosition() const
    {
        return m_pos;
    }

    const Vector2<float> &ApproachCircle::getSize() const
    {
        return m_size;
    }

    HitObject::HitObject(
        const ObjectInfo &obj_info_p,
        const Difficulty &difficulty_p
    ): 
    mx_origin_pos(obj_info_p.position), 
    mx_hit_time_ms(obj_info_p.time)
    {
        mx_size.x = difficulty_p.circleSizePx;
        mx_size.y = mx_size.x;

        mx_pos = mx_origin_pos - mx_size / 2;

        mxp_approach_circle = std::make_unique<ApproachCircle>(
            mx_size * 2.75f,
            mx_origin_pos - mx_size * 2.75f / 2
        );
    }

    double HitObject::getApproachCircleDonePercentage()
    {
        return mxp_approach_circle->m_lerp_t * 100.f;
    }

    const Vector2<float> &HitObject::getPosition() const
    {
        return mx_pos;
    }

    const std::uint32_t &HitObject::getHitTime() const
    {
        return mx_hit_time_ms;
    }
}
