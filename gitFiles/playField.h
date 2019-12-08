#pragma once

class PlayField
{
public:
	PlayField(const sf::Vector2i &screenSize,float &osuPx)
	{
		osuPx = screenSize.y / 480.0f;
		this->playArea.setSize({ osuPx * 512, osuPx * 384 });

		playArea.setFillColor(sf::Color(122, 122, 122, 255));
		playArea.setOrigin(playArea.getSize().x / 2.0f, playArea.getSize().y / 2.0f);
		playArea.move(playArea.getSize() / 2.0f - playArea.getOrigin());
		playArea.setPosition(screenSize.x/2.0f,screenSize.y/2.0f);
	}

	sf::RectangleShape getPlayField() const
	{
		return this->playArea;
	}

protected:
	sf::RectangleShape playArea;
};