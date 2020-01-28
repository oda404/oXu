#pragma once
#include <SFML/Graphics.hpp>

#include "oxuGameHandlers/hitObjectLoader.h"
#include "oxuGameComponents/playField.h"
#include "3rdParty/StandardCursor.hpp"

namespace oxu
{
    class GraphicsHandler
    {
    private:
        sf::Texture cursorTexture;
        sf::Sprite cursorSprite;
        uint16_t hitCircleIt = 0;
        unsigned int hitCircleCap = 0;

    public:
        void drawHitCircles(HitObjectLoader &hitObjects, const sf::Int32 &mapElapsedTime, const float &dt, sf::RenderWindow &window)
        {
            if(mapElapsedTime >= hitObjects.hitCircleVector[hitCircleIt].getSpawnTime())
                hitCircleIt++;

            for(unsigned int i = hitCircleCap; i < hitCircleIt; i++)
            {
                if(!hitObjects.approachCircleVector[i].getApproachState())
                {
                    window.draw(hitObjects.approachCircleVector[i].getApproachCircle());
                    window.draw(hitObjects.hitCircleVector[i].getHitCircle());
                    hitObjects.approachCircleVector[i].approachTheCircle(dt, hitObjects.hitCircleVector[i].getHitCircleScale());
                }
                else
                    hitCircleCap++;
            }
        }

        void drawSliders(HitObjectLoader &hitObjects, const sf::Int32 &mapElapsedTime, const float &dt, PlayField &playField, sf::RenderWindow &window)
        {
            for (unsigned int i = 0; i < hitObjects.sliderVector.size(); i++)
            {
                if (hitObjects.sliderVector[i].getSliderType() == 'L')
                {
                    if (mapElapsedTime >= hitObjects.sliderVector[i].getSpawnTime() && !hitObjects.sliderApproachCircles[i].getApproachState())
                    {
                        window.draw(hitObjects.sliderVector[i].getHitCircle());
                        window.draw(hitObjects.sliderApproachCircles[i].getApproachCircle());
                        hitObjects.sliderApproachCircles[i].approachTheCircle(dt, hitObjects.sliderVector[i].getHitCircleScale());
                    }
                    else if (hitObjects.sliderApproachCircles[i].getApproachState())
                    {
                        window.draw(hitObjects.sliderVector[i].getHitCircle());
                        hitObjects.sliderVector[i].moveOnStraightSlider(dt, 0.300f, playField, hitObjects.sliderApproachCircles[i]);
                    }
                }
                else if (hitObjects.sliderVector[i].getSliderType() == 'B')
                {
                    if (mapElapsedTime >= hitObjects.sliderVector[i].getSpawnTime() && !hitObjects.sliderApproachCircles[i].getApproachState())
                    {
                        window.draw(hitObjects.sliderVector[i].getHitCircle());
                        window.draw(hitObjects.sliderApproachCircles[i].getApproachCircle());
                        hitObjects.sliderApproachCircles[i].approachTheCircle(dt, hitObjects.sliderVector[i].getHitCircleScale());
                    }
                    else if (hitObjects.sliderApproachCircles[i].getApproachState())
                    {
                        window.draw(hitObjects.sliderVector[i].getHitCircle());
                        hitObjects.sliderVector[i].moveOnBezierSlider(0.1f, playField,dt ,hitObjects.sliderApproachCircles[i],window);
                    }
                }
            }          
        }

        void setCursor(sf::RenderWindow &window)
        {
        #ifdef _WIN32
            sf::Image im;
            im.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/cursor.png");
            const sf::Uint8 *ptr = im.getPixelsPtr();
            sf::Cursor curs;
            curs.loadFromPixels(ptr, { 108,108 }, { 54,54 });
            window.setMouseCursor(curs);
        #else
            window.setMouseCursorVisible(false);
            cursorTexture.loadFromFile("/root/Documents/osuBootleg/skins/cursor.png");
            cursorSprite.setTexture(cursorTexture);
        #endif
        }

    #ifdef __linux__
        void drawCursor(sf::RenderWindow &window)
        {
            cursorSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
            window.draw(cursorSprite);
        }
    #endif
    };
}
