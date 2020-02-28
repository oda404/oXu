#pragma once
#include<SFML/Graphics.hpp>

#include"../oxuGameComponents/playField.hpp"

namespace oxu
{
	class HitCircle
	{
	private:
		sf::Sprite hitCircle;
		sf::Sprite hitCircleOverlay;
		long spawnTime;
		float TextureSize;

	public:
		HitCircle(const sf::Vector2f &position, const long &spawnTime, const float &CS, const PlayField &playField,const sf::Texture &hitCircleTexture, const sf::Texture &hitCircleOverlayTexture);

		sf::Vector2f getHitCircleScale() const;

		sf::Vector2f getPos() const;

		sf::Sprite *getHitCircle();

		sf::Sprite *getHitCircleOverlay();

		long getSpawnTime() const;

		float getHitCircleScaleInPixels() const;

		void fadeCircleIn(const float &dt);

		bool fadeCircleOut(const float &dt);
	};
}