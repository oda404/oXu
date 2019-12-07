#pragma once

class PlayField
{
public:
	PlayField(const sf::Vector2f &size,const int &screenWidth, const int &screenHeight)
	{
		playArea.setSize(size);
		playArea.setFillColor(sf::Color(122, 122, 122, 255));
		playArea.setOrigin(playArea.getSize().x / 2.0f, playArea.getSize().y / 2.0f);
		playArea.move(playArea.getSize() / 2.0f - playArea.getOrigin());
		playArea.setPosition(screenWidth / 2.0f, screenHeight / 2.0f);
	}

	sf::RectangleShape getPlayField() const
	{
		return this->playArea;
	}

protected:
	sf::RectangleShape playArea;
};