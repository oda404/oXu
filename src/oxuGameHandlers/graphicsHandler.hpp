#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include<functional>

#include "hitObjectManager.h"
#include "../oxuGameComponents/playField.h"
#include "../3rdParty/StandardCursor.hpp"
#include"../oxuGameHandlers/mapManager.hpp"
#include"soundHandler.h"
#include"inputHandler.hpp"
#include"../oxuGameComponents/mapSelectButton.hpp"

namespace oxu
{
    class GraphicsHandler
    {
    private:
        sf::Texture cursorTexture;
        sf::Sprite cursorSprite;

        HitObjectManager *hitObjects;
        SoundHandler *mapSound; 
        PlayField *playField;
        InputHandler *inputHandler;
        MapManager *mapManager;

        std::vector<MapSelectButton> *mapSelectButtons;

        sf::Font font;
        sf::Text comboString;
        sf::RectangleShape xButton;
        sf::RectangleShape zButton;
        

        std::vector<std::vector<std::function<void (sf::RenderWindow &window, const float &dt)>>> sceneGraphicsHandlers;

    public:
        GraphicsHandler(InputHandler *inputHandler, HitObjectManager *hitObjPtr, SoundHandler *soundHandlerPtr, PlayField *playFieldPtr, MapManager *mapManagerPtr, std::vector<MapSelectButton> *buttonsPtr):
        inputHandler(inputHandler), hitObjects(hitObjPtr),  mapSound(soundHandlerPtr), playField(playFieldPtr), mapManager(mapManagerPtr), mapSelectButtons(buttonsPtr)
        {
            //=====================  font and combo text  =================================
#ifdef __linux__
            font.loadFromFile("../textures/coolvetica.ttf");
#else
			font.loadFromFile("E:/visualproj/SFMLosuBootleg/textures/coolvetica.ttf"); 
#endif
            comboString.setFont(font);
            comboString.setFillColor(sf::Color(255,255,255, 255));
            comboString.setCharacterSize(90);
            comboString.setPosition(35,940); 
            //===============================================================================
            xButton.setSize({960,20});
            zButton.setSize({-960,20});
            xButton.setPosition(960,1060);
            xButton.setFillColor(sf::Color::White);
            zButton.setPosition(960,1060);
            zButton.setFillColor(sf::Color::White);


            std::vector<std::function<void(sf::RenderWindow &window, const float &dt)>> aux;
            //add main menu graphics handlers @ index 0===========================================================================
            aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawMainMenu(window, dt); });

            sceneGraphicsHandlers.push_back(aux);

            aux.clear();
            //====================================================================================================================

            // add song select graphics handlers @ index 1========================================================================

            aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawSongSelectMenu(window, dt); });

            sceneGraphicsHandlers.push_back(aux);

            aux.clear();
            //====================================================================================================================

            //add game graphics handlers @ index 2==================================================================================

            aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawHitCircles(window, dt); });
            aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawInputSquares(window, dt); });
            aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawCombo(window, dt); });
            aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawHealthBar(window, dt); });

            sceneGraphicsHandlers.push_back(aux);

            aux.clear();
            //======================================================================================================================

        }

        void handleGraphics(sf::RenderWindow &window, const float &dt, const std::uint8_t &sceneID)
        {
            for(auto handler: sceneGraphicsHandlers[sceneID])
                handler(window,dt);
        }

        void drawHitCircles(sf::RenderWindow &window, const float &dt)
        {
			if (mapSound->getAudioPlayingOffset() >= hitObjects->getHitCircleByIndex(hitObjects->getHitCircleIt())->getSpawnTime() - hitObjects->getApproachCircleByIndex(0)->getApproachSpeedAsMs())
				hitObjects->incrementHitCircleIt();

            for(unsigned int i = hitObjects->getHitCircleIt(); i > hitObjects->getHitCircleCap(); --i)
            {
                if(!hitObjects->getApproachCircleByIndex(i)->getApproachState())
                {
                    hitObjects->getHitCircleByIndex(i)->fadeCircleIn(dt);
                    hitObjects->getApproachCircleByIndex(i)->fadeCircleIn(dt);           
                           
                    hitObjects->getApproachCircleByIndex(i)->approachTheCircle(dt, hitObjects->getHitCircleByIndex(i)->getHitCircleScale());

                    window.draw(hitObjects->getApproachCircleByIndex(i)->getApproachCircle());
                    window.draw(hitObjects->getHitCircleByIndex(i)->getHitCircle());    
                }
                else
                {
                    if(!hitObjects->getHitCircleByIndex(i)->fadeCircleOut(dt))
                    {
                        hitObjects->getApproachCircleByIndex(i)->fadeCircleOut(dt);
                        
                        window.draw(hitObjects->getApproachCircleByIndex(i)->getApproachCircle());
                        window.draw(hitObjects->getHitCircleByIndex(i)->getHitCircle());   
                    }
                    else
                        hitObjects->incrementHitCircleCap();
                }
            }
        }

        void drawInputSquares(sf::RenderWindow &window, const float &dt)
        {
            sf::RectangleShape rec(sf::Vector2f({60,60}));
            rec.setPosition({1860,420});
            rec.setFillColor(sf::Color::White);
            rec.setFillColor(sf::Color(rec.getFillColor().r, rec.getFillColor().g, rec.getFillColor().b, 60));

            sf::RectangleShape rec1(sf::Vector2f({60,60}));
            rec1.setPosition({1860,540});
            rec1.setFillColor(sf::Color::White);
            rec1.setFillColor(sf::Color(rec.getFillColor().r, rec.getFillColor().g, rec.getFillColor().b, 60));

            if(inputHandler->getXKeyState())
                rec.setFillColor(sf::Color(rec.getFillColor().r, rec.getFillColor().g, rec.getFillColor().b, 125));

            if(inputHandler->getZKeyState())
                rec1.setFillColor(sf::Color(rec.getFillColor().r, rec.getFillColor().g, rec.getFillColor().b, 125));
            
            window.draw(rec1);
            window.draw(rec);
        }

        void drawCombo(sf::RenderWindow &window, const float &dt)
        {
            comboString.setString(std::to_string(inputHandler->getCombo()) + " X");
            window.draw(comboString);
        }

        void drawHealthBar(sf::RenderWindow &window, const float &dt)
        {
            if(xButton.getSize().x > 0)
            {
                xButton.setSize({xButton.getSize().x - 400 *dt, xButton.getSize().y});
                zButton.setSize({zButton.getSize().x + 400 *dt, zButton.getSize().y});
            }
            static int hits = inputHandler->getCombo();

            if(inputHandler->getCombo() > hits)
            {
                if(xButton.getSize().x < 960)
                {
                    xButton.setSize({xButton.getSize().x + 50, xButton.getSize().y});
                    zButton.setSize({zButton.getSize().x - 50 , zButton.getSize().y});
                }
            }

            hits = inputHandler->getCombo();

            window.draw(zButton);
            window.draw(xButton);
        }

        /*void drawSliders(sf::RenderWindow &window, const float &dt)
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
        }*/

        void setCursor(sf::RenderWindow *window)
        {
        #ifdef _WIN32
            sf::Image im;
            im.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/cursor.png");
            const sf::Uint8 *ptr = im.getPixelsPtr();
            sf::Cursor curs;
            curs.loadFromPixels(ptr, { 108,108 }, { 54,54 });
            window.setMouseCursor(curs);
        #else
            //window->setMouseCursorVisible(false);
            cursorTexture.loadFromFile("/root/Documents/osuBootleg/skins/cursor.png");
            cursorSprite.setTexture(cursorTexture);
        #endif
        }

    #ifdef __linux__
        void drawCursor(sf::RenderWindow &window)
        {
            //cursorSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
            //window.draw(cursorSprite);
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

            static sf::Text text("Click anywhere to continue!",font);
            text.setString("Click anywhere to continue!");
            text.setFillColor(sf::Color(0,0,0, 122));
            text.setCharacterSize(35);
            text.setPosition(725,750);

            window.draw(text);

            text.setPosition(30,30);
            text.setString("oXu has loaded " + std::to_string(mapManager->getNumberOfMaps()) + " beat maps!");

            window.draw(text);
        }

        void drawSongSelectMenu(sf::RenderWindow &window, const float &dt)
        {
            for(auto b: *mapSelectButtons)
            {
                b.drawButton(window);
            }
        }
    };
}
