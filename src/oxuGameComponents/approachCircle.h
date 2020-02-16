#pragma once
#include"playField.h"

namespace oxu
{
	class ApproachCircle
	{
	private:
		sf::Sprite approachCircle;
		sf::Vector2f initialScale;
		sf::Vector2f hitCircleSize;
		float approachSpeed;
		bool doneApproacing = false;

	public:
		ApproachCircle(const float &approachSpeed, const sf::Vector2f &position,sf::Vector2f scale, sf::Texture &approachCircleTexture, const PlayField &playField)
		{
			this->approachCircle.setTexture(approachCircleTexture);
			approachCircle.setColor(sf::Color(approachCircle.getColor().r,approachCircle.getColor().g, approachCircle.getColor().b, 0));

			//Set the origin to center of the circle and recenter===================================================================
			this->approachCircle.setOrigin((sf::Vector2f)approachCircleTexture.getSize() / 2.0f);
			this->approachCircle.move((sf::Vector2f)approachCircleTexture.getSize() / 2.0f - this->approachCircle.getOrigin());
			//======================================================================================================================
			this->approachCircle.setPosition(position);

			hitCircleSize = scale;
			//approach circle scale is 1.5 times the hit circle size times the oxuPx
			scale *= playField.getOsuPx() * 1.5f;
			approachCircle.setScale(scale);
			initialScale = scale;

			this->approachSpeed = approachSpeed;
			this->doneApproacing = false;


		}

		sf::Sprite getApproachCircle() const
		{
			return this->approachCircle;
		}

		bool getApproachState() const
		{
			return this->doneApproacing;
		}

		void approachTheCircle(const float &dt)
		{
			if (approachCircle.getScale().x > hitCircleSize.x)
			{
				sf::Vector2f AT = (((this->initialScale - hitCircleSize) / this->approachSpeed)*dt);
				this->approachCircle.setScale(this->approachCircle.getScale() - AT);
			}
			else
				this->doneApproacing = true;
		}

		void fadeCircleIn(const float &dt)
		{
			if(approachCircle.getColor().a + 1020 *dt < 255)
				approachCircle.setColor(sf::Color(approachCircle.getColor().r,approachCircle.getColor().g, approachCircle.getColor().b, approachCircle.getColor().a + 1020 *dt));
		}

		void fadeCircleOut(const float &dt)
		{
			if(approachCircle.getColor().a - 4080 * dt > 0)
				approachCircle.setColor(sf::Color(approachCircle.getColor().r,approachCircle.getColor().g, approachCircle.getColor().b, approachCircle.getColor().a - 4080 *dt));
		}
	};
}