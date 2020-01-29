#pragma once
#include"../oxuGameComponents/hitCircle.h"
#include"../oxuGameComponents/approachCircle.h"
#include"../oxuGameComponents/slider.h"

namespace oxu
{
	class HitObjectLoader
	{
	public:
		HitObjectLoader()
		{
			hitCircleTexture.setSmooth(true);
			approachCircleTexture.setSmooth(true);
#ifdef __linux__
			approachCircleTexture.loadFromFile("/root/Documents/osuBootleg/skins/approachcircle.png");
			hitCircleTexture.loadFromFile("/root/Documents/osuBootleg/skins/hitcircle.png");
#else
			approachCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/approachcircle.png");
			hitCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/hitcircle.png");
#endif
		}

		void createHitObjects(BeatMapParser &beatMap, PlayField &playField)
		{
			for (unsigned int i = 0; i < beatMap.getHitObjectPositions().size(); i++)
			{
				hitCircleVector.push_back(HitCircle(beatMap.getHitObjectPositions()[i], beatMap.gethitObjectSpawnTimes()[i], 2.5f, playField, hitCircleTexture));
				approachCircleVector.push_back(ApproachCircle(0.450f, hitCircleVector[i].getPos(), hitCircleVector[i].getHitCircleScale() * 1.5f * playField.getOsuPx(), approachCircleTexture));
			}

			for (unsigned int i = 0; i < beatMap.getSlidersPositions().size(); i++)
			{
				sliderVector.push_back(Slider(
					beatMap.getSlidersPositions()[i],
					beatMap.getSlidersSpawnTimes()[i],
					2.5f,
					beatMap.getSliderPointsCoord()[i],
					beatMap.getSlides()[i],
					beatMap.getSliderLength()[i],
					beatMap.getHitObjectCurveType()[i],
					playField,
					hitCircleTexture
				));

				sliderApproachCircles.push_back(ApproachCircle(0.450f, sliderVector[i].getPos(), sliderVector[i].getHitCircleScale() * 1.5f * playField.getOsuPx(), approachCircleTexture));
			}
		}

	private:
		sf::Texture hitCircleTexture;
		sf::Texture approachCircleTexture;
	public:
		std::vector<HitCircle> hitCircleVector;
		std::vector<ApproachCircle> approachCircleVector;

		std::vector<Slider> sliderVector;
		std::vector<ApproachCircle> sliderApproachCircles;
	};
}
