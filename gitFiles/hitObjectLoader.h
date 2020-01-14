#pragma once
#include"hitCircle.h"
#include"approachCircle.h"
#include<memory>

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

	void createHitObjects(BeatMap &beatMap, PlayField &playField)
	{
		int it = 0;

		for (unsigned int i = 0; i < beatMap.getHitObjectPositions().size(); i++)
		{
			if(beatMap.getHitObjectCurveType()[i] != 'N')
			{
				hitCircleVector.push_back(HitCircle(beatMap.getHitObjectPositions()[i], beatMap.gethitObjectSpawnTimes()[i], 4.2f, 0.450f, beatMap.getHitObjectCurveType()[i], playField,hitCircleTexture,beatMap.getHitObjectsCurvePointsPositions()[it],beatMap.getSliderLengths()[it]));
				it++;
			}
			else
			{
				hitCircleVector.push_back(HitCircle(beatMap.getHitObjectPositions()[i], beatMap.gethitObjectSpawnTimes()[i], 4.2f, 0.450f, beatMap.getHitObjectCurveType()[i],playField,hitCircleTexture));
			}
			approachCircleVector.push_back(ApproachCircle(0.450f,hitCircleVector[i].getPos(), hitCircleVector[i].getHitCircleScale() * 1.5f * playField.getOsuPx(),approachCircleTexture));
		}
	}

private:
	sf::Texture hitCircleTexture;
	sf::Texture approachCircleTexture;
public:
	std::vector<HitCircle> hitCircleVector;
	std::vector<ApproachCircle> approachCircleVector;
};
