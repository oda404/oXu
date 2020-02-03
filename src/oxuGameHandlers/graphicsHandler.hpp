#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include<functional>

#include "hitObjectLoader.h"
#include "../oxuGameComponents/playField.h"
#include "../3rdParty/StandardCursor.hpp"
#include"soundHandler.h"

namespace oxu
{
    class GraphicsHandler
    {
    private:
        sf::Texture cursorTexture;
        sf::Sprite cursorSprite;
        uint16_t hitCircleIt = 0;
        unsigned int hitCircleCap = 0;

        HitObjectLoader *hitObjects;
        SoundHandler *mapSound;
        PlayField *playField;

        std::vector<std::function<void (sf::RenderWindow &window, const float &dt)>> Handlers;


    public:
        GraphicsHandler(HitObjectLoader *hitObjPtr, SoundHandler *soundPtr, PlayField *playFieldPtr):
        playField(playFieldPtr), mapSound(soundPtr), hitObjects(hitObjPtr)
        {
            Handlers.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawHitCircles(window, dt); });
        }

        void handleGraphics(sf::RenderWindow &window, const float &dt, const std::uint8_t & sceneID)
        {
            Handlers[sceneID](window,dt);
        }

        void drawHitCircles(sf::RenderWindow &window, const float &dt)
        {
			if (mapSound->getAudioPlayingOffset() >= hitObjects->hitCircleVector[hitCircleIt].getSpawnTime())
			{
				hitCircleIt++;
			}

            for(unsigned int i = hitCircleCap; i < hitCircleIt; i++)
            {
                if(!hitObjects->approachCircleVector[i].getApproachState())
                {
                    window.draw(hitObjects->approachCircleVector[i].getApproachCircle());
                    window.draw(hitObjects->hitCircleVector[i].getHitCircle());
                    hitObjects->approachCircleVector[i].approachTheCircle(dt, hitObjects->hitCircleVector[i].getHitCircleScale());
                }
                else
                    hitCircleCap++;
            }
        }

        void drawSliders(const float &dt,sf::RenderWindow &window)
        {
            for (unsigned int i = 0; i < hitObjects->sliderVector.size(); i++)
            {
                if (hitObjects->sliderVector[i].getSliderType() == 'L')
                {
                    if (mapSound->getAudioPlayingOffset() >= hitObjects->sliderVector[i].getSpawnTime() && !hitObjects->sliderApproachCircles[i].getApproachState())
                    {
                        window.draw(hitObjects->sliderVector[i].getHitCircle());
                        window.draw(hitObjects->sliderApproachCircles[i].getApproachCircle());
                        hitObjects->sliderApproachCircles[i].approachTheCircle(dt, hitObjects->sliderVector[i].getHitCircleScale());
                    }
                    else if (hitObjects->sliderApproachCircles[i].getApproachState())
                    {
                        window.draw(hitObjects->sliderVector[i].getHitCircle());
                        hitObjects->sliderVector[i].moveOnStraightSlider(dt, 0.300f, *playField, hitObjects->sliderApproachCircles[i]);
                    }
                }
                else if (hitObjects->sliderVector[i].getSliderType() == 'B')
                {
                    if (mapSound->getAudioPlayingOffset() >= hitObjects->sliderVector[i].getSpawnTime() && !hitObjects->sliderApproachCircles[i].getApproachState())
                    {
                        window.draw(hitObjects->sliderVector[i].getHitCircle());
                        window.draw(hitObjects->sliderApproachCircles[i].getApproachCircle());
                        hitObjects->sliderApproachCircles[i].approachTheCircle(dt, hitObjects->sliderVector[i].getHitCircleScale());
                    }
                    else if (hitObjects->sliderApproachCircles[i].getApproachState())
                    {
                        window.draw(hitObjects->sliderVector[i].getHitCircle());
                        hitObjects->sliderVector[i].moveOnBezierSlider(0.1f, *playField,dt ,hitObjects->sliderApproachCircles[i],window);
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
