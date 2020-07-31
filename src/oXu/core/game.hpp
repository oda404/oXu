// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

#include<oXu/handlers/graphicsHandler.hpp>
#include<oXu/handlers/inputHandler.hpp>
#include<oXu/handlers/soundHandler.hpp>

#include<oXu/components/cursor.hpp>
#include<oXu/components/textures.hpp>

#include<oXu/utils/logger.hpp>
#include<oXu/utils/vector2.hpp>

#include<oXu/skin/skinManager.hpp>

#include<oXu/core/statusCodes.hpp>
#include<oXu/core/scaling.hpp>

#include<oXu/beatmap/songManager.hpp>

namespace oxu
{
    class Game
    {
    private:
        SDL_Window *window = NULL;
        std::shared_ptr<std::thread> graphicsThread;

        GraphicsHandler graphicsHandler;
        InputHandler inputHandler;
        SoundHandler soundHandler;

        SongManager songManager;
        SkinManager skinManager;
        Cursor cursor;

        /* delta time calculation stuff */
        uint32_t startTick;
        uint32_t lastTick = 0;
        double deltaTime = 0.0;

        uint16_t maxFPS = 1000;
        static bool windowState;
        
    public:
        int init();

        void loop();

        void clean();
    
    private:
        void calculateDeltaTime();

        void limitFPS();
    };
}
