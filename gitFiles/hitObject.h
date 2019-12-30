#pragma once
#include"Texture.h"
#include"approachCircle.h"

class HitObject : Textures
{
public:
	HitObject(const sf::Vector2f &position, const float &CS, const float &approachSpeed, const PlayField &playField)
	{
		this->hitCircle.setTexture(hitCircleTexture);

		//Set the origin to center of the circle, and recenter ==============
		this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
		this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
		//===================================================================
		this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x + position.x*playField.getOsuPx(), playField.getPlayFieldStartPoint().y + position.y*playField.getOsuPx());

		//alternative (109-9*CS) * osuPX / hitCircleTexture.getSize().x
		this->hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().y);

		this->approachCircle = std::make_unique<ApproachCircle>(approachSpeed, hitCircle.getPosition(), hitCircle.getScale() * 1.5f*playField.getOsuPx());
	}

	HitObject(const sf::Vector2f &sliderStartPosition, const float &CS, const float &approachSpeed, const PlayField &playField, const char &curveType)
	{
		this->hitCircle.setTexture(hitCircleTexture);

		//Set the origin to center of the circle, and recenter ==============
		this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
		this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
		//===================================================================
		this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x + sliderStartPosition.x*playField.getOsuPx(), playField.getPlayFieldStartPoint().y + sliderStartPosition.y*playField.getOsuPx());

		//alternative (109-9*CS) * osuPX / hitCircleTexture.getSize().x
		this->hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().y);

		this->approachCircle = std::make_unique<ApproachCircle>(approachSpeed, hitCircle.getPosition(), hitCircle.getScale() * 1.5f*playField.getOsuPx());
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

	sf::Vector2f getPos() const
	{
		return this->hitCircle.getPosition();
	}
	//======================================================================

	//Utilities=============================================================
	void approachTheCircle(const float &dt) const
	{
		this->approachCircle->approachTheCircle(dt, getHitCircleScale());
	}

	void setPos(sf::Vector2f &vect, PlayField &pl)
	{
		this->hitCircle.setPosition(pl.getPlayFieldStartPoint() + vect);
	}

	void drawCircle(sf::RenderWindow &window) const
	{
		window.draw(getHitCircle());
		if (!approachCircle->getApproachState())
			window.draw(getApproachCircle());
	}
	void moveOnStraightPath(const float &slideSpeed, const float &dt, PlayField &playField)
	{
		if (this->hitCircle.getPosition().x < playField.getPlayFieldStartPoint().x + 328.0f * playField.getOsuPx() && this->approachCircle->getApproachState())
		{
			sf::Vector2f a = { -19,46 };
			sf::Vector2f AT = ((a / slideSpeed * playField.getOsuPx())*dt);
			this->hitCircle.setPosition(this->hitCircle.getPosition() - AT);
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

	void drawBezierCurve(std::vector<sf::Vector2f> &positions, PlayField &playField,sf::RenderWindow &window)
	{
		sf::RectangleShape rect;
		rect.setSize({ 2,2 });
		for (float t = 0; t < 1; t += 0.001f)
		{
			sf::Vector2f gizm = { 0,0 };
			int power = positions.size() - 1;
			for (int i = 0; i < positions.size(); i++)
			{
				if (i == positions.size() - 1)
				{
					gizm += positions[i] * std::pow(t, i);
				}
				else if (i > 0)
				{
					gizm += std::pow(1 - t, power) * positions[i] * (getPascalTriangleRow(positions)[i - 1] * std::pow(t, i));

				}
				else
					gizm += std::pow(1 - t, power) * positions[i];
				power--;
			}
			power = positions.size() - 1;
			gizm *= playField.getOsuPx();

			rect.setPosition(playField.getPlayFieldStartPoint()+gizm);
			window.draw(rect);
		}
	}

	sf::Vector2f calculateBezierPoint(const float &tParam, const std::vector<sf::Vector2f> &listOfControlPoints, const float &offset = 0.0f)
	{
		sf::Vector2f bezierPoint;
		int power = listOfControlPoints.size() - 1;
		for (int i = 0; i < listOfControlPoints.size(); i++)
		{
			if (i == listOfControlPoints.size() - 1)
				bezierPoint += listOfControlPoints[i] * std::pow(tParam + offset, i);
			else if (i > 0)
				bezierPoint += std::pow(1 - (tParam + offset), power) * listOfControlPoints[i] * (getPascalTriangleRow(listOfControlPoints)[i - 1] * std::pow(tParam + offset, i));
			else
				bezierPoint += std::pow(1 - (tParam + offset), power) * listOfControlPoints[i];
			power--;
		}
		return bezierPoint;
	}

	void moveOnBezierCurve(PlayField &playField, const float &dt, std::vector<sf::Vector2f> &positions,const float &length)
	{

		 static float tParam = 0;
		 static bool shouldCalculateCap = true;
		 static float tParamCap;

		if (shouldCalculateCap)
		{
			float arcLength = 0.0f;
			int power = positions.size() - 1;
			sf::Vector2f a;
			sf::Vector2f b;
			while (arcLength <= length)
			{
				tParam += 0.001f;
				arcLength += std::sqrt(std::pow((calculateBezierPoint(tParam,positions,0.001f) - calculateBezierPoint(tParam, positions)).x,2) + std::pow((calculateBezierPoint(tParam, positions, 0.001f) - calculateBezierPoint(tParam, positions)).y, 2)) ;
				
			}
			tParamCap = tParam;
			tParam = 0.0f;
			shouldCalculateCap = false;
		}
		
		if (tParam <= tParamCap  && this->approachCircle->getApproachState())
		{
			tParam += 0.001f / std::sqrt(std::pow((calculateBezierPoint(tParam, positions, 0.001f) - calculateBezierPoint(tParam, positions)).x, 2) + std::pow((calculateBezierPoint(tParam, positions, 0.001f) - calculateBezierPoint(tParam, positions)).y, 2))/2.25f;

			this->hitCircle.setPosition(playField.getPlayFieldStartPoint() + calculateBezierPoint(tParam, positions) * 2.25f);
		}
	}
	//=====================================================================
	
private:
	sf::Sprite hitCircle;
	std::unique_ptr<ApproachCircle> approachCircle;
};