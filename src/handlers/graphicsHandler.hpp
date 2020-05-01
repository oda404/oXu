// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>

#include "../components/gameComponents.hpp"
#include"../components/textures.hpp"

namespace oxu
{
    class GraphicsHandler 
    {
    private:
        GameComponents &gcI = GameComponents::getInstance();
        Textures       &texturesI       = Textures::getInstance();

        SDL_Renderer *w_renderer = NULL;

    public:
        GraphicsHandler();
        ~GraphicsHandler();

        bool init(SDL_Window *window);

        void render(const double &dt); // function that takes care of displaying to screen
    };
}