// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

#include<thread>
#include<atomic>
#include<cstdint>
#include<mutex>

#include<oXu/components/text.hpp>

#include<oXu/beatmap/songManager.hpp>
#include<oXu/components/textures.hpp>

#include<oXu/utils/logger.hpp>

#include<oXu/core/statusCodes.hpp>

namespace oxu
{
    class GraphicsHandler 
    {
    private:
        Textures &texturesI = Textures::getInstance();

        SDL_Renderer *renderer = NULL;
        SDL_Window *window = NULL;
        SDL_GLContext context;

        uint16_t maxFPS = 240;
        std::atomic<bool> doneInit = false;
        bool *windowState;

        /* delta time calculation stuff */
        uint32_t startTick;
        uint32_t lastTick = 0;
        double delta = 0.0;
        double *inputThreadDelta;

        std::mutex graphicsMutex;

        SongManager *songManager;

        Text text;

        TextBox graphicsThreadFPS;
        TextBox inputThreadFPS;

    public:
        ~GraphicsHandler();

        bool init(SDL_Window *window, std::shared_ptr<std::thread> *graphicsThread, double *inputThreadDelta, bool *windowState, SongManager *songManager);
    
        bool render();

        void calculateDelta();

        void limitFPS();

        void renderHitCircles();

        void renderThreadInfo();
    };
}
