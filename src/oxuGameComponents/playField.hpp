// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once
#include<SFML/Graphics.hpp>

namespace oxu
{
	class PlayField
	{
	private:
		sf::RectangleShape playArea;
		sf::Vector2f playFieldStartPoint;
		float oxuPx;
		
	public:
		PlayField(const sf::Vector2u &screenSize);

		sf::RectangleShape getPlayField() const;

		sf::Vector2f getPlayFieldStartPoint() const;

		float getOxuPx() const;
	};
}
