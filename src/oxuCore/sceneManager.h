#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<future>

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
        InputHandler inputHandler;
        
        std::uint8_t currentScene;
        std::vector<std::vector<Button>> buttons;

        std::vector<std::future<void>> f;

    public:
        SceneManager(sf::RenderWindow *window, PlayField *playFieldPtr);

        void handleCurrentScene(sf::RenderWindow &window, const float &dt);

        void loadBeatMap();

    };
}