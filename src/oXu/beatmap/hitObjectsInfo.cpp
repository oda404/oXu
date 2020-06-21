#include"hitObjectsInfo.hpp"

namespace oxu
{
    void HitObjectsInfo::clear()
    {
        hitCircles.clear();
        HCTopCap = 0;
        HCBotCap = 0;
    }

    void HitObjectsInfo::addHitCircle(const HitCircleModel &model, const PlayField &playField)
    {
        hitCircles.emplace_back(model, playField);
    }

    HitCircle &HitObjectsInfo::getHCAt(const unsigned int &index)
    {
        return hitCircles[index];
    }

    void HitObjectsInfo::checkHitCircleBounds()
    {
        if(hitCircles[HCBotCap].isHit())
        {
            ++HCBotCap;
        }

        if(timer.getEllapsedTimeAsMs() >= hitCircles[HCTopCap].getSpawnTime())
        {
            ++HCTopCap;
        }
    }
}
