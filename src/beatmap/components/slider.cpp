
#include<oxu/beatmap/components/slider.hpp>

namespace oxu
{
    Slider::Slider(
        const ObjectInfo &obj_info_p,
        const SliderInfo &slider_info_p,
        const Difficulty &difficulty_p
    ) : HitCircle(obj_info_p, difficulty_p)
    {
        m_curve_points = slider_info_p.curve_points;
        m_curve_type = slider_info_p.curve_type;
        m_slides = slider_info_p.slides;
        m_length = slider_info_p.length;
    }

    void Slider::update(const double &delta, const Difficulty &difficulty)
    {

    }

    void Slider::render(const Skin &skin)
    {

    }

    void Slider::setErrorMargin(const long double &err, const Difficulty &difficulty_p)
    {
        mxp_approach_circle->m_lerp_t = (err - (mx_hit_time_ms - difficulty_p.approachRateMs)) / difficulty_p.approachRateMs;
    }

    bool Slider::shouldAddToPool(const std::uint32_t &map_time_ms, const std::uint16_t &approach_rate_ms) const
    {
        return map_time_ms >= (mx_hit_time_ms - approach_rate_ms);
    }

    bool Slider::shouldRemoveFromPool() const
    {
        return true;
    }
}
