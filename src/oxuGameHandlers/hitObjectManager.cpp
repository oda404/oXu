#include"hitObjectManager.hpp"

oxu::HitObjectManager::HitObjectManager(PlayField *playFieldPtr):
playField(playFieldPtr)
{
    hitCircleTexture.setSmooth(true);
    approachCircleTexture.setSmooth(true);
    hitCircleOverlayTexture.setSmooth(true);
#ifdef __linux__
    approachCircleTexture.loadFromFile("../skins/approachcircle.png");
    hitCircleTexture.loadFromFile("../skins/hitcircle.png");
    hitCircleOverlayTexture.loadFromFile("../skins/hitcircleoverlay.png");
#else
    approachCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/approachcircle.png");
    hitCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/hitcircle.png");
#endif
}

void oxu::HitObjectManager::createHitObjects(MapManager &beatMap, std::vector<std::string> mapDifficulty)
{
    float AR;

    /* calculate the approach rate in seconds from the map's AR value */
    if(std::stoi(mapDifficulty[3]) <= 5)
        AR = 1800 - std::stoi(mapDifficulty[3]) * 120;
    else if(std::stoi(mapDifficulty[3]) > 5)
        AR = 1200 - (std::stoi(mapDifficulty[3]) - 5) * 150;
    AR /= 1000;

    for (unsigned int i = 0; i < beatMap.getHitObjectPositions().size(); ++i)
    {
        hitCircleVector.push_back(HitCircle(beatMap.getHitObjectPositions()[i], beatMap.gethitObjectSpawnTimes()[i], std::stof(mapDifficulty[1]), *playField, hitCircleTexture, hitCircleOverlayTexture));
        approachCircleVector.push_back(ApproachCircle(AR, hitCircleVector[i].getPos(), hitCircleVector[i].getHitCircleScale() * playField->getOsuPx() * 1.5f, approachCircleTexture));
    }

    for (unsigned int i = 0; i < beatMap.getSlidersPositions().size(); ++i)
    {
        sliderVector.push_back(Slider(
            beatMap.getSlidersPositions()[i],
            beatMap.getSlidersSpawnTimes()[i],
            std::stof(mapDifficulty[1]), //circle size
            beatMap.getSliderPointsCoord()[i],
            beatMap.getSlides()[i],
            beatMap.getSliderLength()[i],
            beatMap.getHitObjectCurveType()[i],
            *playField,
            hitCircleTexture
        ));

        sliderApproachCircles.push_back(ApproachCircle(AR, sliderVector[i].getPos(), sliderVector[i].getHitCircleScale() * playField->getOsuPx() * 1.5f, approachCircleTexture));
    }
}

oxu::HitCircle *oxu::HitObjectManager::getHitCircleByIndex(const uint16_t index) { return &hitCircleVector[index]; }

oxu::ApproachCircle *oxu::HitObjectManager::getApproachCircleByIndex(const uint16_t index) { return &approachCircleVector[index]; }

void oxu::HitObjectManager::incrementHitCircleIt() { ++hitCircleIt; }

void oxu::HitObjectManager::incrementHitCircleCap() { ++hitCircleCap; }

int16_t oxu::HitObjectManager::getHitCircleIt() const { return hitCircleIt; }

int16_t oxu::HitObjectManager::getHitCircleCap() const { return hitCircleCap; }

float oxu::HitObjectManager::getHitCircleSize() { return hitCircleVector[0].getHitCircleScaleInPixels(); }
