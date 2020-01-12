#pragma once
#include"Texture.h"

class ApproachCircle : Textures
{
private:
	sf::Sprite approachCircle;
	sf::Vector2f initalScale;
	float approachSpeed;
	bool doneApproacing = false;
	
public:
	ApproachCircle(const float &approachSpeed, const sf::Vector2f &position, const sf::Vector2f &scale)
	{
		this->approachCircle.setTexture(approachCircleTexture);

		//Set the origin to center of the circle and recenter===================================================================
		this->approachCircle.setOrigin((sf::Vector2f)approachCircleTexture.getSize() / 2.0f);
		this->approachCircle.move((sf::Vector2f)approachCircleTexture.getSize() / 2.0f - this->approachCircle.getOrigin());
		//======================================================================================================================
		this->approachCircle.setPosition(position);

		this->approachCircle.setScale(scale);
		this->initalScale = this->approachCircle.getScale();
		
		this->approachSpeed = approachSpeed;
	}
	
	sf::Sprite getApproachCircle() const
	{
		return this->approachCircle;
	}

	bool getApproachState() const
	{
		return this->doneApproacing;
	}
	
	void approachTheCircle(const float &dt, const sf::Vector2f &hitCircleSize)
	{
		if (approachCircle.getScale().x > hitCircleSize.x)
		{
			sf::Vector2f AT = (((this->initalScale - hitCircleSize) / this->approachSpeed)*dt);
			this->approachCircle.setScale(this->approachCircle.getScale() - AT);
		}
		else
			this->doneApproacing = true;
	}
};