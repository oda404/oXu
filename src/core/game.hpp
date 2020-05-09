// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

#include"../handlers/graphicsHandler.hpp"
#include"../handlers/inputHandler.hpp"
#include"../components/cursor.hpp"
#include"../utils/logger.hpp"

namespace oxu
{
    class Game
    {
    private:
        GraphicsHandler              graphicsHandler;
        std::shared_ptr<std::thread> graphicsThread;

        InputHandler                 inputHandler;

        MapInfo     &mapInfoI = MapInfo::getInstance();

        SDL_Window *window    = NULL;

        /* delta time calculation stuff */
        uint32_t startTick;
        uint32_t lastTick   = 0;
        double   deltaTime  = 0.0;

        int      maxFPS     = 240;
        
    public:
        bool w_init();

        void w_clean();

        void g_loop();

    };
}