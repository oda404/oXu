#pragma once
#include"hitCircle.h"
#include"approachCircle.h"

class Circle
{
public:
	Circle(const sf::Vector2f &hitCircleNewOrigin, const sf::Vector2f &hitCirclePosition,const float &approachSpeed,const sf::Vector2f &approachCircleNewOrigin,const float &CS,const float &osuPx)
	{
		hitCircle = new HitCircleSprites(hitCircleNewOrigin, hitCirclePosition,CS,osuPx);
		approachCircle = new ApproachCirclesSprites(approachSpeed, approachCircleNewOrigin, hitCirclePosition);
	}

	sf::Sprite getHitCircle() const
	{
		return this->hitCircle->getHitCircle();
	}

	sf::Sprite getApproachCircle() const
	{
		return this->approachCircle->getApproachCircle();
	}

	void clearCirclesFromMemory()
	{
		delete this->hitCircle;
		delete this->approachCircle;
	}

private:
	int hitCircleNewOrigin;
	HitCircleSprites *hitCircle;
	ApproachCirclesSprites *approachCircle;
};
