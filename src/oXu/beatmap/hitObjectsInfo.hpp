#pragma once

#include<vector>
#include<cstdint>

#include<oXu/components/game/hitCircle.hpp>
#include<oXu/components/game/models/hitCircldeModel.hpp>

#include<oXu/utils/timer.hpp>

namespace oxu
{
    struct HitObjectsInfo
    {
    private:
        std::vector< HitCircle > hitCircles;

    public:
        Timer   timer;
        int16_t HCTopCap = 0;
        int16_t HCBotCap = 0;

        void clear();

        void addHitCircle(const HitCircleModel &model, const PlayField &playField);

        void addSlider(unsigned int infoArr[4], const std::vector<Vector2<float>> &controlPoints, const int &repeats, const double &length, const uint8_t &sliderType, const PlayField &playField, BeatmapInfo &mapInfo);

        HitCircle &getHCAt(const unsigned int &index);

        void      checkHitCircleBounds();
    };
}