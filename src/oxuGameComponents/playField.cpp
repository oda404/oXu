// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"playField.hpp"

oxu::PlayField::PlayField(const sf::Vector2u &screenSize):
oxuPx(screenSize.y / 480.0f)
{
    playArea.setOrigin(playArea.getSize().x / 2.0f, playArea.getSize().y / 2.0f);
    playArea.setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f);

    playFieldStartPoint = { playArea.getPosition().x - 256.0f * oxuPx, playArea.getPosition().y - 192 * oxuPx };
}

sf::Vector2f oxu::PlayField::getPlayFieldStartPoint() const { return playFieldStartPoint; }

float oxu::PlayField::getOxuPx() const { return oxuPx; }
