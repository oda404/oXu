// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.


#pragma once

#include<SDL2/SDL_mouse.h>
#include<SDL2/SDL_image.h>

#include"../utils/logger.hpp"

namespace oxu
{
    class Cursor
    {
    private:
        SDL_Cursor *customCursor = NULL;

    public:
        ~Cursor();

        /* Loads whatever png named "cursor.png"
        exists in the skins folder as the cursor */
        void set(const std::string &skinPath);
    };
}