#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

#include"../oxuGameHandlers/graphicsHandler.hpp"
#include"../oxuGameHandlers/soundHandler.h"
#include"../oxuGameHandlers/beatMapParser.h"
#include"../oxuGameHandlers/hitObjectLoader.h"
#include"../oxuGameComponents/playField.h"
#include"../oxuGameHandlers/inputHandler.hpp"
#include"button.h"

namespace oxu
{
    class SceneManager
    {
    private:
        PlayField *playField;

        GraphicsHandler graphicsHandler;
        SoundHandler soundHandler;
        HitObjectLoader hitObjects;
        
        std::uint8_t currentScene;
        std::vector<std::vector<Button>> buttons;

    public:
        SceneManager(PlayField *playFieldPtr):
        playField(playFieldPtr) , currentScene(0)
        {
            std::vector<Button> aux;
            aux.emplace_back(sf::Vector2f({0,0}),sf::Vector2f({1920,1080}), 1);

            buttons.push_back(aux);
            aux.clear();
        }

        void handleCurrentScene(sf::RenderWindow &window, const float &dt)
        {
            static bool go = true;
            soundHandler.handleSound(currentScene);
            graphicsHandler.handleGraphics(window, dt, currentScene);
            //InputHandler::Get().handleInput(&buttons[currentScene], );

            for(auto button: buttons[0])
            {
                button.handleButton(currentScene);
                if(currentScene == 1 && go)
                {
                    loadBeatMap();
                    go = false;
                }
            }
        }

        void loadBeatMap()
        {
            BeatMapParser parser;
            hitObjects.createHitObjects(parser, *playField);
            graphicsHandler.loadInfo(&hitObjects, &soundHandler, playField);
        }

    };
}