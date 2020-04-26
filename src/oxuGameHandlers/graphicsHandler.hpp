// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"../oxuUtils/log.hpp"

namespace oxu
{
    class GraphicsHandler 
    {
    private:
        Log logUtil;

        SDL_Renderer *w_renderer = NULL; // the window renderer

        SDL_Texture *cursorTex = NULL; // texture for the cursor
    public:
        GraphicsHandler();
        ~GraphicsHandler();

        bool init(SDL_Window *window);

        void render(); // function that takes care of displaying to screen
    };
}