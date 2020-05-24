#include"objectInfo.hpp"

namespace oxu
{
    void ObjectInfo::clear()
    {
        hitCircles.clear();
        HCTopCap = 0;
        HCBotCap = 0;
    }

    void ObjectInfo::addHitCircle(unsigned int infoArr[4], PlayField &playField, MapInfo &mapInfo)
    {
        hitCircles.emplace_back(infoArr, playField, mapInfo);
    }

    HitCircle &ObjectInfo::getHCAt(const unsigned int &index)
    {
        return hitCircles[index];
    }
}