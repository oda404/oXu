#pragma once
#include"Texture.h"

class ApproachCirclesSprites : Textures
{
private:
	sf::Sprite approachCircle;
	sf::Vector2f initalScale;
	float approachSpeed;
	
public:
	ApproachCirclesSprites(const float &approachSpeed,const sf::Vector2f &newOrigin,const sf::Vector2f &position,const sf::Vector2f &scale)
	{
		this->approachCircle.setTexture(approachCircleTexture);
		this->approachCircle.setScale(scale);
		this->initalScale = this->approachCircle.getScale();
		
		//Set the origin to center of the circle, move the circle there======
		this->approachCircle.setOrigin(newOrigin);
		this->approachCircle.move(newOrigin - this->approachCircle.getOrigin());
		//===================================================================
		
		this->approachCircle.setPosition(position);
		this->approachSpeed = approachSpeed;
	}
	
	sf::Sprite getApproachCircle() const
	{
		return this->approachCircle;
	}
	
	void approachTheCircle(const float &dt)
	{
		sf::Vector2f a ={1.0f,1.0f};
		sf::Vector2f AT = (((this->initalScale - a) / this->approachSpeed)*dt);
		this->approachCircle.setScale(this->approachCircle.getScale() - AT);
	}

};