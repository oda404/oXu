#include"hitObjectsInfo.hpp"

namespace oxu
{
    void HitObjectsInfo::clear()
    {
        hitCircles.clear();
        HCTopCap = 0;
        HCBotCap = 0;
    }

    void HitObjectsInfo::addHitCircle(unsigned int infoArr[4], const PlayField &playField, BeatmapInfo &mapInfo)
    {
        hitCircles.emplace_back(infoArr, playField, mapInfo);
    }

    void HitObjectsInfo::addSlider(
    unsigned int infoArr[4],
    const std::vector<Vector2<float>> &controlPoints, 
    const int &repeats, 
    const double &length, 
    const uint8_t &sliderType, 
    const PlayField &playField, 
    BeatmapInfo &mapInfo
    )
    {
        sliders.emplace_back(infoArr, controlPoints, repeats, length, sliderType, playField, mapInfo);
    }

    HitCircle &HitObjectsInfo::getHCAt(const unsigned int &index)
    {
        return hitCircles[index];
    }
}