#include"hitObjectsInfo.hpp"

namespace oxu
{
    void HitObjectsInfo::clear()
    {
        hitCircles.clear();
        HCTopCap = 0;
        HCBotCap = 0;
    }

    void HitObjectsInfo::addHitCircle(unsigned int infoArr[4], PlayField &playField, BeatmapInfo &mapInfo)
    {
        hitCircles.emplace_back(infoArr, playField, mapInfo);
    }

    HitCircle &HitObjectsInfo::getHCAt(const unsigned int &index)
    {
        return hitCircles[index];
    }
}