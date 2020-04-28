
#pragma once

#include<SDL2/SDL_mouse.h>
#include<SDL2/SDL_image.h>

#include "../oxuUtils/vector2.hpp"

namespace oxu
{
    class Cursor
    {
    private:
        SDL_Cursor *customCursor = NULL;

    public:
        Cursor();
        ~Cursor();

        /* declared void because if the initialization fails
        it's not a core component and doesn't stop the game (no return value needed) */
        void init();
    };
}