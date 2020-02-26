#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include<functional>

#include "hitObjectManager.h"
#include "../oxuGameComponents/playField.h"
#include"../oxuGameHandlers/mapManager.hpp"
#include"soundHandler.h"
#include"inputHandler.hpp"
#include"../oxuGameComponents/mapSelectButton.hpp"

namespace oxu
{
    class GraphicsHandler
    {
    private:

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

        sf::Texture cursorTexture;
        sf::Texture cursorTrailTexture;
        std::vector<sf::Vector2f> cursorTrailVector;
        std::shared_ptr<sf::Sprite> cursorSprite;

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
            if (mapSound->getAudioPlayingOffset() >= hitObjects->getHitCircleByIndex(hitObjects->getHitCircleIt() + 1)->getSpawnTime() - hitObjects->getApproachCircleByIndex(0)->getApproachSpeedAsMs())
                hitObjects->incrementHitCircleIt();

            for(int i = hitObjects->getHitCircleIt(); i >= hitObjects->getHitCircleCap(); --i)
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
            comboString.setString(std::to_string(inputHandler->getCombo()) + " x");
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

        void setCursor(sf::RenderWindow *window)
        {
        #ifdef __linux__
            window->setMouseCursorVisible(false);
            cursorTexture.loadFromFile("../skins/cursor.png");
            cursorSprite = std::make_shared<sf::Sprite>(cursorTexture);
            cursorSprite->setOrigin(static_cast<sf::Vector2f>(cursorTexture.getSize()) / 2.0f);
            cursorTrailTexture.loadFromFile("../skins/cursortrail.png");
        #endif
        }

    #ifdef __linux__
        void drawCursor(sf::RenderWindow *window, sf::Vector2f mousePos)
        {
            if(cursorTrailVector.size() < 20)
            {
                cursorTrailVector.push_back(mousePos);
                cursorTrailVector.push_back(mousePos);
            }
            else
                cursorTrailVector.erase(cursorTrailVector.begin());
            
            for(auto &pos: cursorTrailVector)
            {
                sf::Sprite trail(cursorTrailTexture);
                trail.setOrigin(static_cast<sf::Vector2f>(cursorTrailTexture.getSize()) / 2.0f);
                trail.setPosition(pos);

                window->draw(trail);
            }

            cursorSprite->setPosition(mousePos);
            window->draw(*cursorSprite);
        }
    #endif

        void drawMainMenu(sf::RenderWindow &window, const float &dt)
        {
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
            for(MapSelectButton &b: *mapSelectButtons)
            {
                b.drawButton(window);
            }
        }
    };
}
