#pragma once

class PlayField
{
public:
	PlayField(const sf::Vector2f &screenSize,float &osuPx)
	{
		osuPx = screenSize.y / 480;
		this->playArea.setSize({ osuPx * 512, osuPx * 384 });

		playArea.setFillColor(sf::Color(122, 122, 122, 255));
		playArea.setOrigin(playArea.getSize().x / 2.0f, playArea.getSize().y / 2.0f);
		playArea.move(playArea.getSize() / 2.0f - playArea.getOrigin());
		playArea.setPosition(screenSize.x/2,screenSize.y/2);
	}

	sf::RectangleShape getPlayField() const
	{
		return this->playArea;
	}

protected:
	sf::RectangleShape playArea;
};