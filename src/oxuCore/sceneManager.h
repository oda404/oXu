#pragma once
#include<SFML/Graphics.hpp>
#include<thread>
#include<vector>
#include<memory>

#include"../oxuGameHandlers/graphicsHandler.hpp"
#include"../oxuGameHandlers/soundHandler.h"
#include"../oxuGameHandlers/beatMapParser.h"
#include"../oxuGameHandlers/hitObjectManager.h"
#include"../oxuGameComponents/playField.h"
#include"../oxuGameHandlers/inputHandler.hpp"
#include"button.h"

namespace oxu
{
    class SceneManager
    {
    private:
        PlayField *playField;

        std::shared_ptr<InputHandler> inputHandler;
        std::shared_ptr<GraphicsHandler> graphicsHandler;
        SoundHandler soundHandler;
        HitObjectManager hitObjects;
        
        std::uint8_t currentScene;
        std::vector<std::vector<Button>> buttons;

    public:
        SceneManager(sf::RenderWindow *window, PlayField *playFieldPtr);

        void handleCurrentScene(sf::RenderWindow &window, const float &dt);

        void loadBeatMap();

    };
}