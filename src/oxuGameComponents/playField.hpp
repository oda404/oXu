#pragma once
#include<SFML/Graphics.hpp>

namespace oxu
{
	class PlayField
	{
	private:
		sf::RectangleShape playArea;
		sf::Vector2f playFieldStartPoint;
		float osuPx;
		
	public:
		PlayField(const sf::Vector2u &screenSize);

		sf::RectangleShape getPlayField() const;

		sf::Vector2f getPlayFieldStartPoint() const;

		float getOsuPx() const;
	};
}
