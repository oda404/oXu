#pragma once
#include"hitCircle.h"
#include"approachCircle.h"

class HitObjectLoader
{
public:
	void createHitObjects(BeatMap &beatMap, PlayField &playField)
	{
		for (unsigned int i = 0; i < beatMap.getHitObjectPositions().size(); i++)
		{
			hitCircleVector.push_back(std::make_shared<HitCircle>(beatMap.getHitObjectPositions()[i], beatMap.gethitObjectSpawnTimes()[i], 4.2f, 0.450f, beatMap.getHitObjectCurveType()[i], playField));
			approachCircleVector.push_back(std::make_shared<ApproachCircle>(0.450f,hitCircleVector[i]->getPos(), hitCircleVector[i]->getHitCircleScale() * 1.5f * playField.getOsuPx()));
		}
	}

	std::vector<std::shared_ptr<HitCircle>> hitCircleVector;
	std::vector<std::shared_ptr<ApproachCircle>> approachCircleVector;
};
