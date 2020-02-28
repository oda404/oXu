#include"playField.hpp"

oxu::PlayField::PlayField(const sf::Vector2u &screenSize):
osuPx(screenSize.y / 480.0f)
{
    playArea.setSize({ osuPx * 512, osuPx * 384 });

    playArea.setFillColor(sf::Color(122, 122, 122, 255));
    playArea.setOrigin(playArea.getSize().x / 2.0f, playArea.getSize().y / 2.0f);
    playArea.move(playArea.getSize() / 2.0f - playArea.getOrigin());
    playArea.setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f);

    playFieldStartPoint = { playArea.getPosition().x - 256.0f * osuPx, playArea.getPosition().y - 192 * osuPx };
}

sf::RectangleShape oxu::PlayField::getPlayField() const { return playArea; }

sf::Vector2f oxu::PlayField::getPlayFieldStartPoint() const { return playFieldStartPoint; }

float oxu::PlayField::getOsuPx() const { return osuPx; }