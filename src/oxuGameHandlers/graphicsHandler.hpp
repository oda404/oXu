#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
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

        std::vector<std::vector<std::function<void (sf::RenderWindow &window, const float &dt)>>> sceneGraphicsHandlers;

        sf::SoundBuffer buffer;
        sf::Sound sound;

    public:
        GraphicsHandler()
        {
            //
            buffer.loadFromFile("/root/Documents/osuBootleg/src/soft-hitnormal.wav");
            sound.setBuffer(buffer);
            sound.setVolume(50);
            //

            std::vector<std::function<void(sf::RenderWindow &window, const float &dt)>> aux;
            //add main menu graphics handlers @ index 0===========================================================================
            aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawMainMenu(window, dt); });

            sceneGraphicsHandlers.push_back(aux);

            aux.clear();
            //====================================================================================================================

            //add game graphics handlers @ index 1==================================================================================

            aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawHitCircles(window, dt); });

            sceneGraphicsHandlers.push_back(aux);

            aux.clear();
            //======================================================================================================================

        }

        void loadInfo(HitObjectLoader *hitObjectsObj, SoundHandler *soundPtr, PlayField *playFieldPtr)
        {
            hitObjects = hitObjectsObj;
            mapSound = soundPtr;
            playField = playFieldPtr;
        }

        void handleGraphics(sf::RenderWindow &window, const float &dt, const std::uint8_t & sceneID)
        {
            for(auto handler: sceneGraphicsHandlers[sceneID])
            {
                handler(window,dt);
            }
        }

        void drawHitCircles(sf::RenderWindow &window, const float &dt)
        {

			if (mapSound->getAudioPlayingOffset() >= hitObjects->hitCircleVector[hitCircleIt].getSpawnTime() - 450)
			{
				hitCircleIt++;
			}

            for(unsigned int i = hitCircleIt; i > hitCircleCap; i--)
            {
                if(!hitObjects->approachCircleVector[i].getApproachState())
                {   
                    hitObjects->hitCircleVector[i].fadeCircleIn(dt);
                    hitObjects->approachCircleVector[i].fadeCircleIn(dt);                  
                    hitObjects->approachCircleVector[i].approachTheCircle(dt, hitObjects->hitCircleVector[i].getHitCircleScale());
                    window.draw(hitObjects->approachCircleVector[i].getApproachCircle());
                    window.draw(hitObjects->hitCircleVector[i].getHitCircle());    
                }
                else
                {
                    if(hitObjects->hitCircleVector[i].getA())
                        sound.play();

                    if(!hitObjects->hitCircleVector[i].fadeCircleOut(dt))
                    {
                        hitObjects->approachCircleVector[i].fadeCircleOut(dt);
                        window.draw(hitObjects->approachCircleVector[i].getApproachCircle());
                        window.draw(hitObjects->hitCircleVector[i].getHitCircle());
                    }
                    else
                        hitCircleCap++;
                }
            }
        }

        void drawSliders(sf::RenderWindow &window, const float &dt)
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
                else if (hitObjects->sliderVector[i].getSliderType() == 'C')
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

        void drawMainMenu(sf::RenderWindow &window, const float &dt)
        {
            static sf::Texture oLogo;
            static sf::Texture xLogo;
            static sf::Texture uLogo;
#ifdef __linux__
            oLogo.loadFromFile("/root/Documents/osuBootleg/textures/O.png");
            xLogo.loadFromFile("/root/Documents/osuBootleg/textures/X.png");
            uLogo.loadFromFile("/root/Documents/osuBootleg/textures/U.png");
#else
			oLogo.loadFromFile("E:/visualproj/SFMLosuBootleg/textures/O.png");
			xLogo.loadFromFile("E:/visualproj/SFMLosuBootleg/textures/X.png");
			uLogo.loadFromFile("E:/visualproj/SFMLosuBootleg/textures/U.png");
#endif

            sf::Sprite o;
            sf::Sprite x;
            sf::Sprite u;

            o.setTexture(oLogo);
            x.setTexture(xLogo);
            u.setTexture(uLogo);

            o.setPosition(710,340);
            x.setPosition(860,340);
            u.setPosition(1010,340);

            window.draw(o);
            window.draw(x);
            window.draw(u);

            static sf::Font f;
#ifdef __linux__
            f.loadFromFile("/root/Documents/osuBootleg/textures/coolvetica.ttf");
#else
			f.loadFromFile("E:/visualproj/SFMLosuBootleg/textures/coolvetica.ttf");
#endif

            static sf::Text text("Click anywhere to continue!",f);
            text.setFillColor(sf::Color(0,0,0, 122));
            text.setCharacterSize(35);
            text.setPosition(725,750);

            window.draw(text);

        }

        void drawSongSelectMenu()
        {

        }

    };
}
