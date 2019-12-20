#pragma once
#include"Texture.h"
#include"approachCircle.h"

class HitObject : Textures
{
public:
	HitObject(const sf::Vector2f &position, const float &CS, const float &approachSpeed,const PlayField &playField)
	{
		this->hitCircle.setTexture(hitCircleTexture);

		//Set the origin to center of the circle, and recenter ==============
		this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
		this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
		//===================================================================
		this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x+position.x*playField.getOsuPx(), playField.getPlayFieldStartPoint().y + position.y*playField.getOsuPx());

		//alternative (109-9*CS) * osuPX / hitCircleTexture.getSize().x
		this->hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().y);

		this->approachCircle = std::make_unique<ApproachCircle> (approachSpeed, hitCircle.getPosition(), hitCircle.getScale() * 1.5f*playField.getOsuPx());
	}

	HitObject(const sf::Vector2f &sliderStartPosition, const float &CS, const float &approachSpeed, const PlayField &playField, const char &curveType, const sf::Vector2f &sliderEndPos)
	{
		this->hitCircle.setTexture(hitCircleTexture);

		//Set the origin to center of the circle, and recenter ==============
		this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
		this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
		//===================================================================
		this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x + sliderStartPosition.x*playField.getOsuPx(), playField.getPlayFieldStartPoint().y + sliderStartPosition.y*playField.getOsuPx());

		//alternative (109-9*CS) * osuPX / hitCircleTexture.getSize().x
		this->hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().y);

		this->approachCircle = std::make_unique<ApproachCircle> (approachSpeed, hitCircle.getPosition(), hitCircle.getScale() * 1.5f*playField.getOsuPx());
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

	void drawCircle(sf::RenderWindow &window) const
	{
		window.draw(getHitCircle());
		if(!approachCircle->getApproachState())
			window.draw(getApproachCircle());
	}
	void moveOnStraightPath(const float &slideSpeed ,const float &dt, PlayField &playField)
	{
		if (this->hitCircle.getPosition().x < playField.getPlayFieldStartPoint().x + 328.0f * playField.getOsuPx() && this->approachCircle->getApproachState())
		{
			sf::Vector2f a = { -19,46 };
			sf::Vector2f AT = ((a / slideSpeed* playField.getOsuPx())*dt);
			this->hitCircle.setPosition(this->hitCircle.getPosition() - AT);
		}
	}

	void moveOnBezierCurve(PlayField &playField, const float &dt)
	{
		static sf::Vector2f pos0 = { playField.getPlayFieldStartPoint().x + 70 * playField.getOsuPx(),playField.getPlayFieldStartPoint().y + 26 * playField.getOsuPx() };
		static sf::Vector2f pos1 = { playField.getPlayFieldStartPoint().x + 461 * playField.getOsuPx(),playField.getPlayFieldStartPoint().y + 37 * playField.getOsuPx() };
		static sf::Vector2f pos2 = { playField.getPlayFieldStartPoint().x + 137 * playField.getOsuPx(),playField.getPlayFieldStartPoint().y + 165 * playField.getOsuPx() };
		static sf::Vector2f pos3 = { playField.getPlayFieldStartPoint().x + 429 * playField.getOsuPx(),playField.getPlayFieldStartPoint().y + 147 * playField.getOsuPx() };
		static float arcLength = 0.0f;

		if ( arcLength <= playField.getPlayFieldStartPoint().x + 400.0 * playField.getOsuPx() && this->approachCircle->getApproachState())
		{
			static float tParam = 0;

			sf::Vector2f b = (std::pow(1 - (tParam + 0.001f), 3) * pos0 + 3 * std::pow(1 - (tParam + 0.001f), 2) *  (tParam + 0.001f) * pos1 + 3 * (1 - (tParam + 0.001f)) * std::pow((tParam + 0.001f), 2) * pos2 + std::pow((tParam + 0.001f), 3) * pos3) - (std::pow(1 - tParam, 3) * pos0 + 3 * std::pow(1 - tParam, 2) *  tParam * pos1 + 3 * (1 - tParam) * std::pow(tParam, 2) * pos2 + std::pow(tParam, 3) * pos3);

			tParam += 0.001 / std::sqrt(std::pow(b.x, 2) + std::pow(b.y, 2));

			arcLength += std::sqrt(std::pow(b.x, 2) + std::pow(b.y, 2));
			std::cout << (arcLength /playField.getOsuPx())<< std::endl;

			sf::Vector2f ass = (std::pow(1 - tParam, 3) * pos0 + 3 * std::pow(1 - tParam, 2) *  tParam * pos1 + 3 * (1 - tParam) * std::pow(tParam, 2) * pos2 + std::pow(tParam, 3) * pos3);
			this->hitCircle.setPosition(ass);
		}
	}
	//=====================================================================
	
private:
	sf::Sprite hitCircle;
	std::unique_ptr<ApproachCircle> approachCircle;
};