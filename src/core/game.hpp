// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

#include"../handlers/graphicsHandler.hpp"
#include"../handlers/inputHandler.hpp"
#include"../handlers/soundHandler.hpp"

#include"../components/cursor.hpp"
#include"../components/textures.hpp"

#include"../beatmap/mapManager.hpp"

#include"../utils/logger.hpp"
#include"../utils/vector2.hpp"

#define GOOD_EXIT     0
#define INIT_FAILURE -1

namespace oxu
{
    class Game
    {
    private:
        Game() = default;

        SDL_Window *window    = NULL;
        std::shared_ptr<std::thread> graphicsThread;

        GraphicsHandler graphicsHandler;
        InputHandler    inputHandler;
        SoundHandler    soundHandler;

        MapManager      beatmapManager;

        MapInfo     &mapInfoI = MapInfo::getInstance();

        /* delta time calculation stuff */
        uint32_t startTick;
        uint32_t lastTick   = 0;
        double   deltaTime  = 0.0;

        unsigned int   maxFPS     = 240;
        static bool    w_isClosed;
        Vector2<int>   screenSize;
        
    public:
        //====== singleton stuff ==============
        static Game &getInstance();
        Game(const Game&) = delete;
        Game(Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(Game&&) = delete;
        //=====================================

        bool init();

        void clean();

        void loop();
    
    private:
        void calculateDeltaTime();

        void limitFPS();

    };
}