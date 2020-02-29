// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

#include"mapManager.hpp"
#include"../oxuGameComponents/playField.hpp"
#include"../oxuGameComponents/hitCircle.hpp"
#include"../oxuGameComponents/approachCircle.hpp"

namespace oxu
{
	class HitObjectManager
	{
	private:
		sf::Texture hitCircleTexture;
		sf::Texture approachCircleTexture;
		sf::Texture hitCircleOverlayTexture;

		int16_t hitCircleIt = -1, hitCircleCap = 0;

		std::vector<HitCircle> hitCircleVector;
		std::vector<ApproachCircle> approachCircleVector;

		//std::vector<Slider> sliderVector;
		//std::vector<ApproachCircle> sliderApproachCircles;

		PlayField *playField;
		
	public:
		HitObjectManager(PlayField *playFieldPtr);

		void createHitObjects(MapManager &beatMap, std::vector<std::string> mapDifficulty);

		HitCircle *getHitCircleByIndex(const uint16_t index);

		ApproachCircle *getApproachCircleByIndex(const uint16_t index);

		int getHitCircleVectorSize() const;

		void incrementHitCircleIt();

		void incrementHitCircleCap();

		int16_t getHitCircleIt() const;

		int16_t getHitCircleCap() const;

		float getHitCircleSize();
	};
}
