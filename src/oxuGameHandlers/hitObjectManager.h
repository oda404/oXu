#pragma once
#include"../oxuGameComponents/hitCircle.h"
#include"../oxuGameComponents/approachCircle.h"
#include"../oxuGameComponents/slider.h"
#include"mapManager.hpp"

namespace oxu
{
	class HitObjectManager
	{
	public:
		HitObjectManager(PlayField *playFieldPtr):
		playField(playFieldPtr)
		{
			hitCircleTexture.setSmooth(true);
			approachCircleTexture.setSmooth(true);
#ifdef __linux__
			approachCircleTexture.loadFromFile("../skins/approachcircle.png");
			hitCircleTexture.loadFromFile("../skins/hitcircle.png");
#else
			approachCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/approachcircle.png");
			hitCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/hitcircle.png");
#endif
		}

		void createHitObjects(MapManager &beatMap, std::vector<std::string> mapDifficulty)
		{
			float AR;

			/* calculate the approach rate in seconds from the map's AR */
			if(std::stoi(mapDifficulty[3]) <= 5)
				AR = 1800 - std::stoi(mapDifficulty[3]) * 120;
			else if(std::stoi(mapDifficulty[3]) > 5)
				AR = 1200 - (std::stoi(mapDifficulty[3]) - 5) * 150;
			AR /= 1000;

			for (unsigned int i = 0; i < beatMap.getHitObjectPositions().size(); i++)
			{
				hitCircleVector.push_back(HitCircle(beatMap.getHitObjectPositions()[i], beatMap.gethitObjectSpawnTimes()[i], std::stof(mapDifficulty[1]), *playField, hitCircleTexture));
				approachCircleVector.push_back(ApproachCircle(AR, hitCircleVector[i].getPos(), hitCircleVector[i].getHitCircleScale() * playField->getOsuPx() * 1.5f, approachCircleTexture));
			}

			for (unsigned int i = 0; i < beatMap.getSlidersPositions().size(); i++)
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

		HitCircle *getHitCircleByIndex(const uint16_t index) { return &hitCircleVector[index]; }

		ApproachCircle *getApproachCircleByIndex(const uint16_t index) { return &approachCircleVector[index]; }

		void incrementHitCircleIt() { ++hitCircleIt; }

		void incrementHitCircleCap() { ++hitCircleCap; }

		uint16_t getHitCircleIt() const { return hitCircleIt; }

		uint16_t getHitCircleCap() const { return hitCircleCap; }

		float getHitCircleSize() { return hitCircleVector[0].getHitCircleScaleInPixels(); }

	private:
		sf::Texture hitCircleTexture;
		sf::Texture approachCircleTexture;

		uint16_t hitCircleIt = 0, hitCircleCap = 0;

		std::vector<HitCircle> hitCircleVector;
		std::vector<ApproachCircle> approachCircleVector;

		std::vector<Slider> sliderVector;
		std::vector<ApproachCircle> sliderApproachCircles;

		PlayField *playField;
	};
}
