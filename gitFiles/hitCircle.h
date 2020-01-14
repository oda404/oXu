#pragma once
#include<math.h>

class HitCircle
{
private:
	sf::Sprite hitCircle;
	long spawnTime;

public:
	HitCircle(const sf::Vector2f &position, const long &spawnTime, const float &CS, const float &approachSpeed, const PlayField &playField, sf::Texture &hitCircleTexture)
	{
		this->hitCircle.setTexture(hitCircleTexture);

		//Set the origin to center of the circle, and recenter ==============
		this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
		this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
		//===================================================================
		this->spawnTime = spawnTime;

		this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x + position.x*playField.getOsuPx(), playField.getPlayFieldStartPoint().y + position.y*playField.getOsuPx());

		//alternative (109-9*CS) * osuPX / hitCircleTexture.getSize().x
		this->hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().y);

	}
	//Getters===============================================================
	sf::Vector2f getHitCircleScale() const
	{
		return this->hitCircle.getScale();
	}

	sf::Sprite getHitCircle() const
	{
		return this->hitCircle;
	}

	sf::Vector2f getPos() const
	{
		return this->hitCircle.getPosition();
	}

	long getSpawnTime() const
	{
		return this->spawnTime;
	}
	//======================================================================
};