// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"hitCircle.hpp"

oxu::HitCircle::HitCircle(const sf::Vector2f &position, const long &spawnTime, const float &CS, const PlayField &playField,const sf::Texture &hitCircleTexture, const sf::Texture &hitCircleOverlayTexture):
spawnTime(spawnTime), TextureSize(hitCircleTexture.getSize().x)
{
    hitCircle.setTexture(hitCircleTexture);
    hitCircle.setColor(sf::Color(hitCircle.getColor().r,hitCircle.getColor().g, hitCircle.getColor().b, 0));

    hitCircleOverlay.setTexture(hitCircleOverlayTexture);
    hitCircleOverlay.setColor(sf::Color(hitCircleOverlay.getColor().r, hitCircleOverlay.getColor().g, hitCircleOverlay.getColor().b, 0));

    hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
    hitCircleOverlay.setOrigin(hitCircle.getOrigin());

    hitCircle.setPosition(playField.getPlayFieldStartPoint().x + position.x*playField.getOxuPx(), playField.getPlayFieldStartPoint().y + position.y*playField.getOxuPx());
    hitCircleOverlay.setPosition(hitCircle.getPosition());

    hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOxuPx()) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOxuPx()) / hitCircleTexture.getSize().y);
    hitCircleOverlay.setScale(hitCircle.getScale());
}

sf::Vector2f oxu::HitCircle::getHitCircleScale() const { return hitCircle.getScale(); }

sf::Vector2f oxu::HitCircle::getPos() const { return hitCircle.getPosition(); }

sf::Sprite *oxu::HitCircle::getHitCircle() { return &hitCircle; }

sf::Sprite *oxu::HitCircle::getHitCircleOverlay() { return &hitCircleOverlay; }

long oxu::HitCircle::getSpawnTime() const { return spawnTime; }

float oxu::HitCircle::getHitCircleScaleInPixels() const { return hitCircle.getScale().x * TextureSize; }

void oxu::HitCircle::fadeCircleIn(const float &dt)
{
    if(hitCircle.getColor().a + 1020 *dt < 255)
    {
        hitCircle.setColor(sf::Color(hitCircle.getColor().r,hitCircle.getColor().g, hitCircle.getColor().b, hitCircle.getColor().a + 1020 *dt));
        hitCircleOverlay.setColor(sf::Color(hitCircleOverlay.getColor().r, hitCircleOverlay.getColor().g, hitCircleOverlay.getColor().b, hitCircleOverlay.getColor().a + 1020 * dt));
    }
}

bool oxu::HitCircle::fadeCircleOut(const float &dt)
{
    if(hitCircle.getColor().a - 2550 * dt > 0)
    {
        hitCircle.setColor(sf::Color(hitCircle.getColor().r,hitCircle.getColor().g, hitCircle.getColor().b, hitCircle.getColor().a - 2550 *dt));
        hitCircleOverlay.setColor(sf::Color(hitCircleOverlay.getColor().r, hitCircleOverlay.getColor().g, hitCircleOverlay.getColor().b, hitCircleOverlay.getColor().a - 2550 * dt));
        return false;
    }
    else
        return true;
}
