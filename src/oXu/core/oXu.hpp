// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

#include<mutex>

#include<oXu/handlers/graphics.hpp>
#include<oXu/handlers/input.hpp>
#include<oXu/handlers/sound.hpp>

#include<oXu/utils/logger.hpp>

#include<oXu/core/threading/threads.hpp>
#include<oXu/core/status.hpp>
#include<oXu/core/scaling.hpp>

#include<oXu/beatmap/songManager.hpp>
#include<oXu/skin/skinManager.hpp>

#include<oXu/core/dirs.hpp>

namespace oxu
{
    class oXu
    {
    private:
        SDL_Window *window = NULL;
        bool windowState = false;

        GraphicsHandler graphicsHandler;
        InputHandler inputHandler;
        SoundHandler soundHandler;

        SongManager songManager;
        Beatmap *currentBeatmap;

        Thread *thisThread;

        bool initSDL();

        void start();
        
    public:
        ~oXu();

        bool init();
    };
}
