#pragma once

#include<cstdint>
#include<string>
#include<memory>
#include<oxu/beatmap/sections/difficulty.hpp>
#include<oxu/skin/skin.hpp>
#include<oxu/framework/utils/vector2.hpp>

namespace oxu
{
    struct HitSample
    {
        std::uint8_t  normal_set;
        std::uint8_t  additional_set;
        std::uint16_t index;
        std::uint8_t  volume;
        std::string   filename;
    };

    struct ObjectInfo
    {
        framework::Vector2<float> position;
        /* when the object should be hit in ms */
        std::uint32_t time;
        std::uint8_t type;
        std::uint8_t hit_sound;
        HitSample hit_sample;
    };

    class ApproachCircle
    {
    private:
        framework::Vector2<float> m_pos;
        framework::Vector2<float> m_size;
    public:
        float m_lerp_t = 0.f;

    public:
        ApproachCircle(const framework::Vector2<float> &pos, const framework::Vector2<float> &size);

        /* returns false if it is done shrinking */
        bool shrink(
            const framework::Vector2<float> &init_size,
            const framework::Vector2<float> &target_size,
            const framework::Vector2<float> &origin_pos,
            const double &delta, 
            const float &approach_rate_ms
        );
        const framework::Vector2<float> &getPosition() const;
        const framework::Vector2<float> &getSize() const;
    };

    /* Base class for all the other hitObjects */
    class HitObject
    {
    protected:
        std::unique_ptr<ApproachCircle> mxp_approach_circle;
        framework::Vector2<float> mx_pos;
        framework::Vector2<float> mx_size;
        const framework::Vector2<float> mx_origin_pos;
        const std::uint32_t mx_hit_time_ms;
        float mx_alpha = 0.f;
        /* false during fade out or if the object has been hit already */
        bool m_can_be_hit = true;

    public:
        HitObject(
            const ObjectInfo &obj_info_p,
            const Difficulty &difficulty_p
        );
        virtual ~HitObject() = 0;

        virtual void update(const double &delta, const Difficulty &difficulty) = 0;
        virtual void render(const Skin &skin) = 0;
        virtual void setErrorMargin(const long double &err, const Difficulty &difficulty) = 0;
        virtual bool shouldAddToPool(const std::uint32_t &map_time_ms, const std::uint16_t &approach_rate_ms) const = 0;
        virtual bool shouldRemoveFromPool() const = 0;
        double getApproachCircleDonePercentage();
        const framework::Vector2<float> &getPosition() const;
        const std::uint32_t &getHitTime() const;
    };
}
