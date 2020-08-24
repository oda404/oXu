// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_ttf.h>

#include<oXu/graphics/UI/game.hpp>

#include<oXu/beatmap/songManager.hpp>
#include<oXu/skin/skinManager.hpp>

#include<oXu/core/threading/threads.hpp>

namespace oxu
{
    class GraphicsHandler 
    {
    private:
        SDL_Renderer *renderer = NULL;
        SDL_GLContext context;
        SDL_Window *window = NULL;

        Request request;
        
        SongManager *songManager;
        SkinManager skinManager;

        GameUI gameUI;

        TTF_Font *font = NULL;

        Thread *thisThread;

    public:
        ~GraphicsHandler();

        void init(SDL_Window *window, SongManager *songManager);

    private:
        bool initSDL();

        bool initThread();

        void startThread();

        void renderHitCircles();

        void renderThreadsInfo();

        void renderUI();
    };
}
