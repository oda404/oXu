// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once
#include<SFML/Graphics.hpp>

namespace oxu
{
	class ApproachCircle
	{
	private:
		sf::Sprite approachCircle;
		sf::Vector2f initialScale;
		float approachSpeed;
		bool doneApproacing = false;

	public:
		ApproachCircle(const float &approachSpeed, const sf::Vector2f &position, const sf::Vector2f &scale, const sf::Texture &approachCircleTexture);

		sf::Sprite *getApproachCircle();

		bool getApproachState() const;

		float getApproachSpeedAsMs() const;

		void approachTheCircle(const float &dt, const sf::Vector2f &hitCircleSize);

		void fadeCircleIn(const float &dt);

		void fadeCircleOut(const float &dt);
	};
}
