// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"approachCircle.hpp"

oxu::ApproachCircle::ApproachCircle(const float &approachSpeed, const sf::Vector2f &position, const sf::Vector2f &scale, const sf::Texture &approachCircleTexture):
initialScale(scale), approachSpeed(approachSpeed)
{
    /* set the texture of the approach circle sprite and set it's alpha value to 0
    so it start out transparent */
    approachCircle.setTexture(approachCircleTexture);
    approachCircle.setColor(sf::Color(approachCircle.getColor().r,approachCircle.getColor().g, approachCircle.getColor().b, 0));

    approachCircle.setOrigin((sf::Vector2f)approachCircleTexture.getSize() / 2.0f);
    
    approachCircle.setPosition(position);

    approachCircle.setScale(scale);
}

sf::Sprite *oxu::ApproachCircle::getApproachCircle() { return &approachCircle; }

bool oxu::ApproachCircle::getApproachState() const { return doneApproacing; }

float oxu::ApproachCircle::getApproachSpeedAsMs() const { return approachSpeed * 1000; }

void oxu::ApproachCircle::approachTheCircle(const float &dt, const sf::Vector2f &hitCircleSize)
{
    if (approachCircle.getScale().x > hitCircleSize.x)
    {
        sf::Vector2f AT = (((initialScale - hitCircleSize) / approachSpeed)*dt);
        approachCircle.setScale(approachCircle.getScale() - AT);
    }
    else
        doneApproacing = true;
}

void oxu::ApproachCircle::fadeCircleIn(const float &dt)
{
    if(approachCircle.getColor().a + 1020 *dt < 255)
        approachCircle.setColor(sf::Color(approachCircle.getColor().r,approachCircle.getColor().g, approachCircle.getColor().b, approachCircle.getColor().a + 1020 *dt));
}

void oxu::ApproachCircle::fadeCircleOut(const float &dt)
{
    if(approachCircle.getColor().a - 4080 * dt > 0)
        approachCircle.setColor(sf::Color(approachCircle.getColor().r,approachCircle.getColor().g, approachCircle.getColor().b, approachCircle.getColor().a - 4080 *dt));
}
