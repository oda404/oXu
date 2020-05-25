// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

#include<oXu/handlers/graphicsHandler.hpp>
#include<oXu/handlers/inputHandler.hpp>
#include<oXu/handlers/soundHandler.hpp>

#include<oXu/components/cursor.hpp>
#include<oXu/components/textures.hpp>

#include<oXu/beatmap/beatmapManager.hpp>

#include<oXu/utils/logger.hpp>
#include<oXu/utils/vector2.hpp>

#include<oXu/skin/skinManager.hpp>

#define GOOD_EXIT     0
#define INIT_FAILURE -1

namespace oxu
{
    class Game
    {
    private:
        Game() = default;

        SDL_Window                   *window = NULL;
        std::shared_ptr<std::thread> graphicsThread;

        GraphicsHandler graphicsHandler;
        InputHandler    inputHandler;
        SoundHandler    soundHandler;

        BeatmapManager  beatmapManager;
        SkinManager     skinsManager;

        Cursor          cursor;

        /* delta time calculation stuff */
        uint32_t        startTick;
        uint32_t        lastTick   = 0;
        double          deltaTime  = 0.0;

        unsigned int    maxFPS     = 1000;
        static bool     w_isClosed;
        
    public:
        //====== singleton stuff ==============
        static Game &getInstance();
        Game(const Game&)            = delete;
        Game(Game&&)                 = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(Game&&)      = delete;
        //=====================================

        bool init();

        void loop();

        void clean();
    
    private:
        void calculateDeltaTime();

        void limitFPS();

    };
}
