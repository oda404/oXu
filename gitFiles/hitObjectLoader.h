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
		for (unsigned int i = 0; i < beatMap.getHitObjectPositions().size(); i++)
		{
			hitCircleVector.push_back(std::make_shared<HitCircle>(beatMap.getHitObjectPositions()[i], beatMap.gethitObjectSpawnTimes()[i], 4.2f, 0.450f, beatMap.getHitObjectCurveType()[i], playField,hitCircleTexture));
			approachCircleVector.push_back(std::make_shared<ApproachCircle>(0.450f,hitCircleVector[i]->getPos(), hitCircleVector[i]->getHitCircleScale() * 1.5f * playField.getOsuPx(),approachCircleTexture));
		}
	}

private:
	sf::Texture hitCircleTexture;
	sf::Texture approachCircleTexture;
public:
	std::vector<std::shared_ptr<HitCircle>> hitCircleVector;
	std::vector<std::shared_ptr<ApproachCircle>> approachCircleVector;
};
