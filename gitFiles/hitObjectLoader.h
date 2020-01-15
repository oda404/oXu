#pragma once
#include"hitCircle.h"
#include"approachCircle.h"
#include"slider.h"

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
			hitCircleVector.push_back(HitCircle(beatMap.getHitObjectPositions()[i], beatMap.gethitObjectSpawnTimes()[i], 4.2f, 0.450f, playField,hitCircleTexture));
			approachCircleVector.push_back(ApproachCircle(0.450f,hitCircleVector[i].getPos(), hitCircleVector[i].getHitCircleScale() * 1.5f * playField.getOsuPx(),approachCircleTexture));
		}

		// another for?
	}

private:
	sf::Texture hitCircleTexture;
	sf::Texture approachCircleTexture;
public:
	std::vector<HitCircle> hitCircleVector;
	std::vector<ApproachCircle> approachCircleVector;
	std::vector<Slider> sliderVector;
};
