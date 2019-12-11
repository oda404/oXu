#pragma once
#include"Texture.h"
#include"hitCircle.h"

class Slider
{
public:
	Slider(const sf::Vector2f &sliderStartPosition, const float &CS, const float &approachSpeed,const PlayField &playField,const char &curveType, const sf::Vector2f &sliderEndPos)
	{
		this->sliderStartPoint = new HitCircle(sliderStartPosition,CS,approachSpeed,playField);
	}
	
	void deleteSliderStartPoint()
	{
		this->sliderStartPoint->clearApproachCircleFromMemory();
		delete this->sliderStartPoint;
	}
	
	HitCircle getSliderStartPos()
	{
		return (*this->sliderStartPoint);
	}
	
private:
	HitCircle *sliderStartPoint;
};