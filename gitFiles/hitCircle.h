#pragma once
#include"approachCircle.h"
#include<math.h>

class HitCircle
{
private:
	sf::Sprite hitCircle;
	std::vector<sf::Vector2f> sliderCurvePointsPositions;
	float sliderLength;
	long spawnTime;
	char curveType;
	bool doneSliding = false;

public:
	HitCircle(
	const sf::Vector2f &position, 
	const long &spawnTime,
	const float &CS, 
	const float &approachSpeed,
	const char &curveType,
	const PlayField &playField,
	const sf::Texture &hitCircleTexture,
	const std::vector<sf::Vector2f> &sliderCurvePointsPositions = {{0,0}},
	const float &sliderLength = 0 // 0 if the hit object is not a slider
	)
	{
		this->hitCircle.setTexture(hitCircleTexture);

		//Set the origin to center of the circle, and recenter ==============
		this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
		this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
		//===================================================================
		this->spawnTime = spawnTime;
		this->curveType = curveType;
		if(curveType == 'N')
			this->doneSliding = true;

		if(sliderLength != 0)
			this->sliderLength = sliderLength;

		if(sliderCurvePointsPositions[0].x != 0)
			this->sliderCurvePointsPositions = sliderCurvePointsPositions;


		this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x + position.x*playField.getOsuPx(), playField.getPlayFieldStartPoint().y + position.y*playField.getOsuPx());

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

	bool isDoneSliding() const
	{
		return this->doneSliding;
	}
	//======================================================================

	//Utilities=============================================================

	void setPos(const sf::Vector2f &vect,const PlayField &pl)
	{
		this->hitCircle.setPosition(pl.getPlayFieldStartPoint() + vect);
	}
	void moveOnStraightPath(const float &slideSpeed, const float &dt,const PlayField &playField)
	{
		if (this->hitCircle.getPosition().x < playField.getPlayFieldStartPoint().x + 106.0f * playField.getOsuPx())
		{
			sf::Vector2f a = { -6,80 };
			sf::Vector2f AT = ((a / slideSpeed * playField.getOsuPx()) * dt);
			this->hitCircle.setPosition(this->hitCircle.getPosition() + AT);                                                                           
		}
	}

	std::vector<int> getPascalTriangleRow(const std::vector<sf::Vector2f> &positions)
	{
		unsigned int n = 1;

		std::vector<int> row;
		row.push_back(1);
		row.push_back(1);

		std::vector<int> newRow;

		while (n < positions.size() - 1)
		{
			if (n + 1 != positions.size() - 1)
				newRow.push_back(1);
			for (unsigned int i = 0; i < row.size() - 1; i++)
			{
				newRow.push_back(row[i] + row[i + 1]);
			}
			if (n + 1 != positions.size() - 1)
				newRow.push_back(1);
			row = newRow;
			n++;
			newRow.clear();
		}

		return row;
	}

	void drawBezierCurve(const std::vector<sf::Vector2f> &positions,const PlayField &playField,sf::RenderWindow &window)
	{
		sf::RectangleShape rect;
		rect.setSize({ 2,2 });
		for (float t = 0; t < 1; t += 0.001f)
		{
			sf::Vector2f gizm = { 0,0 };
			int power = positions.size() - 1;
			for (unsigned int i = 0; i < positions.size(); i++)
			{
				if (i == positions.size() - 1)
				{
					gizm += positions[i] * static_cast<float>(std::pow(t, i));
				}
				else if (i > 0)
				{
					gizm += static_cast<float>(std::pow(1 - t, power)) * positions[i] * (getPascalTriangleRow(positions)[i - 1] * static_cast<float>(std::pow(t, i)));

				}
				else
					gizm += static_cast<float>(std::pow(1 - t, power)) * positions[i];
				power--;
			}
			power = positions.size() - 1;
			gizm *= playField.getOsuPx();

			rect.setPosition(playField.getPlayFieldStartPoint() + gizm);
			window.draw(rect);
		}
	}

	sf::Vector2f calculateBezierPoint(const float &tParam, const std::vector<sf::Vector2f> &listOfControlPoints, const float &offset = 0.0f)
	{
		sf::Vector2f bezierPoint;
		int power = listOfControlPoints.size() - 1;
		for (unsigned int i = 0; i < listOfControlPoints.size(); i++)
		{
			if (i == listOfControlPoints.size() - 1)
				bezierPoint += listOfControlPoints[i] * static_cast<float>(std::pow(tParam - offset, i));
			else if (i > 0)
				bezierPoint += static_cast<float>(std::pow(1 - (tParam - offset), power)) * listOfControlPoints[i] * (getPascalTriangleRow(listOfControlPoints)[i - 1] * static_cast<float>(std::pow(tParam - offset, i)));
			else
				bezierPoint += static_cast<float>(std::pow(1 - (tParam - offset), power)) * listOfControlPoints[i];
			power--;
		}
		return bezierPoint;
	}

	void moveOnBezierCurve(const PlayField &playField, const float &dt,ApproachCircle &approachCircle)
	{
		static bool shouldCalculateCap = true;
		static float tParamCap;
		static std::vector<float> curvePoints;
		float sliderTime = 2.0f;

		if (shouldCalculateCap)
		{
			float arcLength = 0.0f;
			int it = 1;
			bool firstPoint = true;
			float tParam = 0;

			while (arcLength < sliderLength)
			{
				arcLength += std::sqrt(std::pow((calculateBezierPoint(tParam,sliderCurvePointsPositions) - calculateBezierPoint(tParam, sliderCurvePointsPositions,0.0001f)).x,2) + std::pow((calculateBezierPoint(tParam, sliderCurvePointsPositions) - calculateBezierPoint(tParam, sliderCurvePointsPositions,0.0001f)).y, 2)) ;

				if (arcLength >= sliderLength / (sliderLength/ 10) * it || firstPoint)
				{
					curvePoints.push_back(tParam);
					it++;
					firstPoint = false;
				}
				tParam += 0.0001f;
			}
			
			tParamCap = tParam;
			tParam = 0.0f;
			shouldCalculateCap = false;
		}
		//a
		static sf::Clock sliderElapsedTime;
		if (!approachCircle.getApproachState())
			sliderElapsedTime.restart();

		if (sliderElapsedTime.getElapsedTime().asSeconds() <= sliderTime && approachCircle.getApproachState())
		{
			static sf::Clock segmentTime;
			static uint8_t currentSegment = 1;

			if (segmentTime.getElapsedTime().asSeconds() <= sliderTime / (sliderLength / 10))
			{
				sf::Vector2f distanceBetweenPoints = calculateBezierPoint(curvePoints[currentSegment], sliderCurvePointsPositions) - calculateBezierPoint(curvePoints[currentSegment - 1], sliderCurvePointsPositions);
				sf::Vector2f AT = ((distanceBetweenPoints / (sliderTime / (sliderLength / 10)) * playField.getOsuPx()) * dt);
				this->hitCircle.setPosition(this->hitCircle.getPosition() + AT);
			}
			else if(currentSegment + 1 != curvePoints.size())
			{
				currentSegment++;
				segmentTime.restart();
			}
		}
		else if(sliderElapsedTime.getElapsedTime().asSeconds() > sliderTime)
			doneSliding = true;
	}
	//=====================================================================
};