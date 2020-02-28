// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include<vector>
#include<future>

#include"../oxuGameHandlers/graphicsHandler.hpp"
#include"../oxuGameHandlers/soundHandler.hpp"
#include"../oxuGameHandlers/hitObjectManager.hpp"
#include"../oxuGameComponents/playField.hpp"
#include"../oxuGameHandlers/inputHandler.hpp"
#include"../oxuGameHandlers/mapManager.hpp"
#include"../oxuGameComponents/mapSelectButton.hpp"
//#include"WyGMoGnEfRnhqEunHbYR01001011001011010010.hpp"

namespace oxu
{
    class Game
    {
    private:
        sf::Vector2i screenSize = { 1920,1080 };
        std::shared_ptr<sf::RenderWindow> window;
        
        std::vector<MapSelectButton> mapSelectionButtons;
        std::shared_ptr<PlayField> playField;
        std::shared_ptr<GraphicsHandler> graphicsHandler;
        std::shared_ptr<InputHandler> inputHandler;
        SoundHandler soundHandler;
        std::shared_ptr<HitObjectManager> hitObjects;
        std::shared_ptr<MapManager> mapManager;

        std::uint8_t currentScene = 0;

        sf::Clock deltaClock;
	    sf::Time deltaTime;

    public:
        Game();

        void run();

    };
}
