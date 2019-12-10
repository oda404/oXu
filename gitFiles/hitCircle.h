#pragma once
#include"Texture.h"
#include"approachCircle.h"

class HitCircle : Textures
{
public:
	HitCircle(const sf::Vector2f &position, const float &CS,float const &osuPx, const float &approachSpeed,const PlayField &playField)
	{
		this->hitCircle.setTexture(hitCircleTexture);

		//Set the origin to center of the circle, and recenter ==============
		this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
		this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
		//===================================================================
		this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x+position.x*osuPx, playField.getPlayFieldStartPoint().y + position.y*osuPx);

		//alternative (109-9*CS) * osuPX / hitCircleTexture.getSize().x
		this->hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * osuPx) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * osuPx) / hitCircleTexture.getSize().y);

		this->approachCircle = new ApproachCircle(approachSpeed, hitCircle.getPosition(), hitCircle.getScale() * 1.5f*osuPx);
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

	sf::Sprite getApproachCircle() const
	{
		return this->approachCircle->getApproachCircle();
	}
	//======================================================================

	//Utilities=============================================================
	void approachTheCircle(const float &dt) const
	{
		this->approachCircle->approachTheCircle(dt, getHitCircleScale());
	}

	void clearApproachCircleFromMemory() const
	{
		delete this->approachCircle;
	}

	void drawCircle(sf::RenderWindow &window) const
	{
		window.draw(getHitCircle());
		window.draw(getApproachCircle());
	}
	//=====================================================================
	
private:
	sf::Sprite hitCircle;
	ApproachCircle *approachCircle;
};