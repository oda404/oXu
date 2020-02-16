#pragma once
#include"../oxuGameComponents/playField.h"
#include<math.h>


namespace oxu
{
	class HitCircle
	{
	private:
		sf::Sprite hitCircle;
		long spawnTime;
		float TextureSize;

	public:
		HitCircle(const sf::Vector2f &position, const long &spawnTime, const float &CS, const PlayField &playField,const sf::Texture &hitCircleTexture)
		{
			this->hitCircle.setTexture(hitCircleTexture);
			hitCircle.setColor(sf::Color(hitCircle.getColor().r,hitCircle.getColor().g, hitCircle.getColor().b, 0));

			//Set the origin to center of the circle, and recenter ==============
			this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
			this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
			//===================================================================
			this->spawnTime = spawnTime;

			this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x + position.x*playField.getOsuPx(), playField.getPlayFieldStartPoint().y + position.y*playField.getOsuPx());

			//alternative (109-9*CS) * osuPX / hitCircleTexture.getSize().x
			this->hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().y);
			TextureSize = hitCircleTexture.getSize().x;
		}

		//Getters===============================================================

		float getHitCircleScaleInPixels()
		{
			return hitCircle.getScale().x * TextureSize;
		}

		sf::Vector2f getHitCircleScale()
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

		void fadeCircleIn(const float &dt)
		{
			if(hitCircle.getColor().a + 1020 *dt < 255)
				hitCircle.setColor(sf::Color(hitCircle.getColor().r,hitCircle.getColor().g, hitCircle.getColor().b, hitCircle.getColor().a + 1020 *dt));
		}

		bool fadeCircleOut(const float &dt)
		{
			if(hitCircle.getColor().a - 2550 * dt > 0)
			{
				hitCircle.setColor(sf::Color(hitCircle.getColor().r,hitCircle.getColor().g, hitCircle.getColor().b, hitCircle.getColor().a - 2550 *dt));
				return false;
			}
			else
				return true;
		}
	};
}