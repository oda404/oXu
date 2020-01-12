#pragma once
#include"hitObject.h"
#include"approachCircle.h"

class HitObjectLoader
{
public:
	void createHitObjects(BeatMap &beatMap, PlayField &playField)
	{
		for (unsigned int i = 0; i < beatMap.getHitObjectPositions().size(); i++)
		{
			hitCircleVector.push_back(std::make_shared<HitObject>(beatMap.getHitObjectPositions()[i], beatMap.gethitObjectSpawnTimes()[i], 4.2f, 0.450f, playField));
			approachCircleVector.push_back(std::make_shared<ApproachCircle>(0.450f,hitCircleVector[i]->getPos(), hitCircleVector[i]->getHitCircleScale() * 1.5f * playField.getOsuPx()));
		}
	}

	std::vector<std::shared_ptr<HitObject>> hitCircleVector;
	std::vector<std::shared_ptr<ApproachCircle>> approachCircleVector;
};
